#if WITH_AUTOMATION_TESTS

#include "Subsystems/GameFuseRounds.h"
#include "Commands/TestSuiteCommands.h"
#include "Library/GameFuseLog.h"
#include "Library/GameFuseStructLibrary.h"
#include "Misc/AutomationTest.h"
#include "Subsystems/GameFuseManager.h"
#include "Subsystems/GameFuseUser.h"

BEGIN_DEFINE_SPEC(GameFuseRoundsSpec, "GameFuseTests.GameFuseRounds",
				  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
UGameFuseManager* GameFuseManager;
UGameFuseRounds* GameFuseRounds;
UGameFuseUser* GameFuseUser;
UGameInstance* GameInstance;
UTestAPIHandler* TestAPIHandler;
TSharedPtr<FGFGameData> GameData;
TSharedPtr<FGFUserData> UserData;

bool bCleanupSuccess;
END_DEFINE_SPEC(GameFuseRoundsSpec);

void GameFuseRoundsSpec::Define()
{
	UE_LOG(LogGameFuse, Log, TEXT("GameFuseRoundsSpec::DEFINE was called"));

	// Setup
	GameInstance = NewObject<UGameInstance>();
	GameInstance->Init();

	// Get subsystems and test api handler
	GameFuseManager = GameInstance->GetSubsystem<UGameFuseManager>();
	GameFuseRounds = GameInstance->GetSubsystem<UGameFuseRounds>();
	GameFuseUser = GameInstance->GetSubsystem<UGameFuseUser>();
	TestAPIHandler = NewObject<UTestAPIHandler>();

	// Init testing data
	GameData = MakeShared<FGFGameData>();
	UserData = MakeShared<FGFUserData>();

	Describe("GameFuseRounds Basic Operations", [this]() {
		BeforeEach([this]() {
			// Create and setup game
			FGuid SetupGameRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FSetupGame(TestAPIHandler, GameData, GameFuseManager, this, SetupGameRequestId));
			// Removed unnecessary wait for response after FSetupGame
			// ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(TestAPIHandler, SetupGameRequestId));

			// Wait for GameFuseManager to be fully set up
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				if (!GameFuseManager->IsSetUp()) {
					UE_LOG(LogGameFuse, Warning, TEXT("Waiting for GameFuseManager setup..."));
					return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("GameFuseManager setup complete"));
				return true;
			}));

			// Create and sign in user

			ADD_LATENT_AUTOMATION_COMMAND(FSetupUser(TestAPIHandler, GameData, UserData, GameFuseUser, this));

			// Wait for user to be fully signed in
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
					UE_LOG(LogGameFuse, Warning, TEXT("Waiting for user signin..."));
					return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("User signed in successfully"));
				return true;
			}));
		});

		It("creates a game round", [this]() {
			// Create round data
			TSharedPtr<FGFGameRound> RoundData = MakeShared<FGFGameRound>();
			RoundData->Score = 100;
			RoundData->StartTime = FDateTime::Now();
			RoundData->EndTime = RoundData->StartTime + FTimespan::FromMinutes(1);
			RoundData->GameType = "SinglePlayer";

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData]() -> bool {
				GameFuseRounds->OnGameRoundResponse.AddLambda([this](const FGFGameRound& _RoundData) {
					TestTrue("has good id", _RoundData.Id != 0);
					TestTrue("has good score", _RoundData.Score == 100);
					TestTrue("has good game type", _RoundData.GameType == "SinglePlayer");
					TestTrue("has valid start time", _RoundData.StartTime != FDateTime());
					TestTrue("has valid end time", _RoundData.EndTime != FDateTime());
					TestTrue("keeps end time difference", _RoundData.EndTime - _RoundData.StartTime == FTimespan::FromMinutes(1));

					GameFuseRounds->OnGameRoundResponse.Clear();
				});
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*RoundData, FGFApiCallback())));
				return true;
			}));

			// ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData]() -> bool {
			//
			//
			//
			// 	}));

			// ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
		});

		It("creates a game round with metadata", [this]() {
			// Create round data

			TSharedPtr<FGFGameRound> RoundData = MakeShared<FGFGameRound>();
			RoundData->Score = 100;
			RoundData->StartTime = FDateTime::Now();
			RoundData->EndTime = RoundData->StartTime + FTimespan::FromMinutes(1);
			RoundData->GameType = "SinglePlayer";

			RoundData->Metadata.Add("key1", "value1");
			RoundData->Metadata.Add("key2", "value2");

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData]() -> bool {
				GameFuseRounds->OnGameRoundResponse.AddLambda([this](const FGFGameRound& _RoundData) {
					AddErrorIfFalse(!_RoundData.Metadata.IsEmpty(), "metadata should be present");
					TestTrue("metadata has the right number of keys", _RoundData.Metadata.Num() == 2);

					TestTrue("metadata has the right key", _RoundData.Metadata.Contains("key1"));
					TestTrue("metadata has the right value", _RoundData.Metadata["key1"] == "value1");

					GameFuseRounds->OnGameRoundResponse.Clear();
				});
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*RoundData, FGFApiCallback())));
				return true;
			}));

			// ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
		});

		It("creates a multiplayer game round", [this]() {
			// Create round data

			TSharedPtr<FGFGameRound> OriginalRoundData = MakeShared<FGFGameRound>();
			OriginalRoundData->Score = 100;
			OriginalRoundData->StartTime = FDateTime::Now();
			OriginalRoundData->EndTime = OriginalRoundData->StartTime + FTimespan::FromMinutes(1);
			OriginalRoundData->GameType = "Multiplayer";
			OriginalRoundData->bMultiplayer = true;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->SetCredits(888, FGFApiCallback())));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->SetScore(888, FGFApiCallback())));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, OriginalRoundData]() -> bool {
				GameFuseRounds->OnGameRoundResponse.AddLambda([this, OriginalRoundData](const FGFGameRound& _RoundData) {
					TestTrue("has good id", _RoundData.Id != 0);
					TestTrue("has good score", _RoundData.Score == 100);
					TestTrue("has good multiplayer game round id", _RoundData.MultiplayerGameRoundId != 0);

					TestTrue("has round rankings", !_RoundData.Rankings.IsEmpty());

					if (!_RoundData.Rankings.IsEmpty()) {
						const FGFGameRoundRanking& Ranking = _RoundData.Rankings[0];
						// test place == -1
						TestTrue("has null ranking place", Ranking.Place == -1);
						TestTrue("has good ranking score", Ranking.Score == 100);

						// test user obj
						TestTrue("has good ranking user id", Ranking.User.Id == UserData->Id);
						TestTrue("has User's score value", Ranking.User.Score == 888);
						TestTrue("has good credits", Ranking.User.Credits == 888);
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*OriginalRoundData, FGFApiCallback())));
				return true;
			}));
		});
		// ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
	});
}

#endif