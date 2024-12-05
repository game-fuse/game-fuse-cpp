#include "API/TestAPIHandler.h"
#include "Commands/TestSuiteCommands.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"

BEGIN_DEFINE_SPEC(FGameFuseSpec, "GameFuseTests.TestSuite",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

	UTestAPIHandler* APIHandler;
	FGFGameData GameData;
	bool bCleanupSuccess;

END_DEFINE_SPEC(FGameFuseSpec)

void FGameFuseSpec::Define()
{
	BeforeEach([this]() {
		APIHandler = NewObject<UTestAPIHandler>();
		TestTrue("API Handler should be valid", APIHandler != nullptr);
		bCleanupSuccess = false;
	});

	Describe("Game Creation", [this]() {
		LatentIt("Should create and cleanup game", EAsyncExecution::TaskGraph, [this](const FDoneDelegate& Done) {
			// Create game and validate
			ADD_LATENT_AUTOMATION_COMMAND(FCreateGameLatentCommand(APIHandler, GameData));
			TestTrue("Game ID should be valid", GameData.Id != 0);
			// // Create user and validate
			// FGFUserData UserData;
			// ADD_LATENT_AUTOMATION_COMMAND(FCreateUserLatentCommand(APIHandler, GameData, UserData));
			// TestTrue(TEXT("User ID should be valid"), UserData.Id != 0);

			// // Create store item and validate
			// FGFStoreItem StoreItem;
			// ADD_LATENT_AUTOMATION_COMMAND(FCreateStoreItemLatentCommand(APIHandler, GameData, StoreItem));
			// TestTrue(TEXT("Store Item ID should be valid"), StoreItem.Id != 0);

			// Cleanup and validate
			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGameLatentCommand(APIHandler, GameData, bCleanupSuccess));
			TestTrue("Game cleanup should succeed", GameData.Id == 0);

			Done.Execute();
		});
	});
}