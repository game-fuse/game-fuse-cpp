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
			OriginalRoundData->Place = 10;

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
						TestTrue("has good ranking place", Ranking.Place == 10);
						TestTrue("has good ranking score", Ranking.Score == 100);

						// test user obj
						TestTrue("has good ranking user id", Ranking.User.Id == UserData->Id);
						TestTrue("has User's score value", Ranking.User.Score == 888);
						TestTrue("has good credits", Ranking.User.Credits == 888);
					}
					GameFuseRounds->OnGameRoundResponse.Clear();
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*OriginalRoundData, FGFApiCallback())));
				return true;
			}));
		});

		It("adds multiple players to 1 GameRound", [this]() {
			// Create round data
			TSharedPtr<FGFUserData> OtherUser = MakeShared<FGFUserData>();
			ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, OtherUser, this, FGuid()));

			TSharedPtr<FGFGameRound> OriginalRoundData = MakeShared<FGFGameRound>();
			OriginalRoundData->GameUserId = UserData->Id;
			OriginalRoundData->Score = 100;
			OriginalRoundData->StartTime = FDateTime::Now();
			OriginalRoundData->EndTime = OriginalRoundData->StartTime + FTimespan::FromMinutes(1);
			OriginalRoundData->GameType = "Multiplayer";
			OriginalRoundData->bMultiplayer = true;
			OriginalRoundData->Place = 1;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, OriginalRoundData, OtherUser]() -> bool {
				GameFuseRounds->OnGameRoundResponse.AddLambda([this, OriginalRoundData](const FGFGameRound& _RoundData) {
					AddInfo("OnGameRoundResponse 1");
					TestTrue("has good id", _RoundData.Id != 0);
					TestTrue("has good score", _RoundData.Score == 100);
					TestTrue("has good multiplayer game round id", _RoundData.MultiplayerGameRoundId != 0);

					OriginalRoundData->MultiplayerGameRoundId = _RoundData.MultiplayerGameRoundId;
					TestTrue("updates original round data with multiplayer game round id", OriginalRoundData->MultiplayerGameRoundId == _RoundData.MultiplayerGameRoundId);
					TestTrue("has round rankings", !_RoundData.Rankings.IsEmpty());
					GameFuseRounds->OnGameRoundResponse.Clear();
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*OriginalRoundData, FGFApiCallback())));


				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, OriginalRoundData, OtherUser]() -> bool {
					TSharedPtr<FGFGameRound> SecondPlayerRoundData = MakeShared<FGFGameRound>();
					TestTrue("has updated original multiplayer game round id", OriginalRoundData->MultiplayerGameRoundId != 0);
					TestTrue("Other User has good id", OtherUser->Id != 0);

					SecondPlayerRoundData->MultiplayerGameRoundId = OriginalRoundData->MultiplayerGameRoundId; // required for multiplayer rounds
					SecondPlayerRoundData->GameUserId = OtherUser->Id;
					SecondPlayerRoundData->Score = 50; // lower score
					SecondPlayerRoundData->StartTime = FDateTime::Now();
					SecondPlayerRoundData->EndTime = SecondPlayerRoundData->StartTime + FTimespan::FromMinutes(1);
					SecondPlayerRoundData->GameType = "Multiplayer";
					SecondPlayerRoundData->Place = 10;

					GameFuseRounds->OnGameRoundResponse.AddLambda([this, SecondPlayerRoundData](const FGFGameRound& _RoundData) {
						AddInfo("OnGameRoundResponse 2");

						TestTrue("still has good multiplayer game round id", _RoundData.MultiplayerGameRoundId == SecondPlayerRoundData->MultiplayerGameRoundId);
						TestTrue("has good id", _RoundData.Id != 0);
						TestTrue("has lower score", _RoundData.Score == 50);
						TestTrue("has arbitrary place", _RoundData.Place == 10);

						int NumRankings = _RoundData.Rankings.Num();
						TestTrue("has 2 rankings", NumRankings == 2);
						GameFuseRounds->OnGameRoundResponse.Clear();
					});
					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*SecondPlayerRoundData, *OtherUser, FGFApiCallback())));
					return true;
				}));
				return true;
			}));
		});
		// ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));

		It("updates game rounds", [this]() {
			// Create round data
			TSharedPtr<FGFGameRound> RoundData = MakeShared<FGFGameRound>();
			RoundData->Score = 100;
			RoundData->Place = 2;
			RoundData->StartTime = FDateTime::Now();
			RoundData->EndTime = RoundData->StartTime + FTimespan::FromMinutes(1);
			RoundData->GameType = "SinglePlayer";

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData]() -> bool {
				GameFuseRounds->OnGameRoundResponse.AddLambda([this, RoundData](const FGFGameRound& _RoundData) {
					AddInfo("UpdateGameRound 1");

					TestTrue("has good id", _RoundData.Id != 0);
					TestTrue("has good score", _RoundData.Score == 100);
					TestTrue("has good game type", _RoundData.GameType == "SinglePlayer");
					TestTrue("has valid start time", _RoundData.StartTime != FDateTime());
					TestTrue("has valid end time", _RoundData.EndTime != FDateTime());
					TestTrue("keeps end time difference", _RoundData.EndTime - _RoundData.StartTime == FTimespan::FromMinutes(1));

					// RoundData->MultiplayerGameRoundId = _RoundData.MultiplayerGameRoundId;
					RoundData->Id = _RoundData.Id;

					GameFuseRounds->OnGameRoundResponse.Clear();
				});
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*RoundData, FGFApiCallback())));


				// update round data
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData]() -> bool {
					RoundData->Score = 200;
					RoundData->Place = 1;
					RoundData->GameType = "SinglePlayerUpdated";
					RoundData->EndTime = RoundData->StartTime + FTimespan::FromMinutes(2);

					TestTrue("has updated round id", RoundData->Id != 0);

					GameFuseRounds->OnGameRoundResponse.AddLambda([this, RoundData](const FGFGameRound& _RoundData) {
						AddInfo("UpdateGameRound 2");

						TestTrue("has good id", _RoundData.Id != 0);
						TestTrue("has updated score", _RoundData.Score == 200);
						TestTrue("has updated place", _RoundData.Place == 1);
						TestTrue("has good game type", _RoundData.GameType == "SinglePlayerUpdated");
						TestTrue("has updated end time", _RoundData.EndTime - _RoundData.StartTime == FTimespan::FromMinutes(2));

						GameFuseRounds->OnGameRoundResponse.Clear();
					});
					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->UpdateGameRound(RoundData->Id, *RoundData, FGFApiCallback())));
					return true;
				}));

				return true;
			}));
		});
	});
}

#endif