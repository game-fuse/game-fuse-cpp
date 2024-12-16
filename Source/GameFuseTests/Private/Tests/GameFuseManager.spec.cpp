#if WITH_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "Subsystems/GameFuseManager.h"
#include "Commands/TestSuiteCommands.h"

BEGIN_DEFINE_SPEC(GameFuseManagerSpec, "GameFuseTests.GameFuseManager",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UGameFuseManager *GameFuseManager;
	UGameInstance *GameInstance;
	UTestAPIHandler *TestAPIHandler;
	TSharedPtr<FGFGameData> GameData;
	// Declare Variables Here (basically a header)

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
		// Create the game first
		ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(TestAPIHandler, GameData, this, FGuid()));

		// Delay function to wait for create game command completion
		ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
			// Define the callback
			FGFApiCallback Callback = FGFApiCallback();
			Callback.AddLambda([this](const FGFAPIResponse& Response) {
				TestTrue("setup game should be successful", Response.bSuccess);

				});

			// Call the SetUpGame function
			GameFuseManager->SetUpGame(GameData->Id, GameData->Token, Callback);

			// Return true to indicate the command has completed
			return GameFuseManager->IsSetUp();
			}));
		ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
			TestTrue("GameFuseManager should be set up", GameFuseManager->SetupCheck());
			TestTrue("has correct GameData", GameFuseManager->GetGameData() == *GameData);
			return true;
			}));
	});

}

#endif