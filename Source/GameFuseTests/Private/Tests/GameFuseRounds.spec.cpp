#if WITH_AUTOMATION_TESTS

#include "Library/GameFuseLog.h"
#include "Misc/AutomationTest.h"
#include "Subsystems/GameFuseManager.h"
#include "Subsystems/GameFuseRounds.h"
#include "Subsystems/GameFuseUser.h"
#include "Library/GameFuseStructLibrary.h"
#include "Commands/TestSuiteCommands.h"

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
	bCleanupSuccess = false;

	Describe("GameFuseRounds Basic Operations", [this]() {
		BeforeEach([this]() {
			// Create and setup game
			FGuid SetupGameRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FSetupGame(TestAPIHandler, GameData, GameFuseManager, this, SetupGameRequestId));
			// Removed unnecessary wait for response after FSetupGame
			// ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(TestAPIHandler, SetupGameRequestId));

			// Wait for GameFuseManager to be fully set up
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
				if (!GameFuseManager->IsSetUp()) {
				UE_LOG(LogGameFuse, Warning, TEXT("Waiting for GameFuseManager setup..."));
				return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("GameFuseManager setup complete"));
				return true;
				}));

			// // Create and sign in user
			// TSharedPtr<FGFUserData> TestUserData = MakeShared<FGFUserData>();
			ADD_LATENT_AUTOMATION_COMMAND(FSetupUser(TestAPIHandler, GameData, UserData, GameFuseUser, this));

			// Wait for user to be fully signed in
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
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

			TSharedPtr<FGuid> CreateRoundRequestId = MakeShared<FGuid>();
			FGFApiCallback OnCreatedRound;
			OnCreatedRound.AddLambda([this](const FGFAPIResponse& Response) {
				UE_LOG(LogGameFuse, Error, TEXT("Round created response: %s"), *Response.ResponseStr);
				TestTrue("Create round request succeeded", Response.bSuccess);
			});

			// Create the round after user setup is complete
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, RoundData, CreateRoundRequestId, OnCreatedRound]() -> bool {
				UE_LOG(LogGameFuse, Log, TEXT("Creating game round"));
				*CreateRoundRequestId = GameFuseRounds->CreateGameRound(*RoundData, OnCreatedRound);
				return true;
				}));

			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(TestAPIHandler, *CreateRoundRequestId));
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, RoundData]() -> bool {
				TestTrue("Round has good id", RoundData->Id != 0);
				TestTrue("Round has good score", RoundData->Score == 100);

				return true;
				}));
		});
	});
}

#endif