#include "Library/GameFuseLog.h"
#include "Library/GameFuseUtilities.h"
#if WITH_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "Subsystems/GameFuseManager.h"
#include "Commands/TestSuiteCommands.h"

BEGIN_DEFINE_SPEC(GameFuseManagerSpec, "GameFuseTests.GameFuseManager",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UGameFuseManager* GameFuseManager;
	UGameInstance* GameInstance;
	UTestAPIHandler* TestAPIHandler;
	TSharedPtr<FGFGameData> GameData;
END_DEFINE_SPEC(GameFuseManagerSpec);

void GameFuseManagerSpec::Define()
{

	GameInstance = NewObject<UGameInstance>();
	GameInstance->Init();
	GameFuseManager = GameInstance->GetSubsystem<UGameFuseManager>();
	GameData = MakeShared<FGFGameData>();
	TestAPIHandler = NewObject<UTestAPIHandler>();

	It("Has valid classes", [this]() {
		TestTrueExpr(GameFuseManager != nullptr);
		TestTrueExpr(TestAPIHandler != nullptr);
	});

	It("Sets up GameFuse", [this]() {
		// Create game with callback
		FGuid CreateGameRequestId;
		ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(TestAPIHandler, GameData, this, CreateGameRequestId));

		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
			TestTrue("Game ID should be valid", GameData->Id != 0);
			AddErrorIfFalse(GameData->Id != 0, TEXT("Game was not initialized"));
			AddErrorIfFalse(GameData->Token.Len() > 0, TEXT("Game Authentication Token was not initialized"));
			return true;
		}));

		FGuid SetupRequestId;
		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, &SetupRequestId]() -> bool {
			FGFApiCallback SetUpCallback;
			SetUpCallback.AddLambda(
				[this](const FGFAPIResponse& Response) {
				UE_LOG(LogGameFuse, Log, TEXT("Setup Game Responded: %s"), *Response.ResponseStr);
				TestTrue("setup game should be successful", Response.bSuccess);
				TestTrue("GameFuseManager should be set up", GameFuseManager->IsSetUp());
				TestTrue("has correct GameData", GameFuseManager->GetGameData() == *GameData);
				});

			// Set up the game and capture its request ID
			SetupRequestId = GameFuseManager->SetUpGame(GameData->Id, GameData->Token, SetUpCallback);
			return true;
			}));

		// Wait for setup to complete
		ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseManager->GetRequestHandler(), SetupRequestId));
	});
}

#endif