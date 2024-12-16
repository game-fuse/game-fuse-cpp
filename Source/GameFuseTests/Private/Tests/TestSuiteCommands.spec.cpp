#if WITH_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "Commands/TestSuiteCommands.h"

BEGIN_DEFINE_SPEC(FGameFuseTestSpec, "GameFuseTests.TestSuiteCommands", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UTestAPIHandler* APIHandler;
	TSharedPtr<FGFGameData> GameData;
	TSharedPtr<FGFUserData> UserData;
	TSharedPtr<FGFStoreItem> StoreItem;
	bool bCleanupSuccess;
END_DEFINE_SPEC(FGameFuseTestSpec)

void FGameFuseTestSpec::Define()
{
	APIHandler = NewObject<UTestAPIHandler>();
	TestTrue(TEXT("API Handler should be valid"), APIHandler != nullptr);
	GameData = MakeShared<FGFGameData>();
	UserData = MakeShared<FGFUserData>();

	It("creates a game and cleans it up", [this]() {

		ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(APIHandler, GameData, this, FGuid()));
		// Endpoint does not exist currently
		// ADD_LATENT_AUTOMATION_COMMAND(FCreateStoreItem(APIHandler, GameData, StoreItem, this, FGuid()));
		AddWarning("CreateStoreItem endpoint isn't working yet");

		ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(APIHandler, GameData, bCleanupSuccess, this, FGuid()));

	});

	It("creates a user and cleans it up", [this]() {
		ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(APIHandler, GameData, this, FGuid()));

		ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(APIHandler, GameData, UserData, this, FGuid()));

		ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(APIHandler, GameData, bCleanupSuccess, this, FGuid()));
	});

	It("waits for FGF response correctly", [this]() {
		// Create a game and capture its request ID
		FGuid RequestId;
		ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(APIHandler, GameData, this, RequestId));
		
		// Wait for the response using our new command
		ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(APIHandler, RequestId));
		
		// Verify the game was created successfully
		TestTrue(TEXT("Game ID should be valid after waiting for response"), GameData->Id != 0);
		TestTrue(TEXT("Game Token should be valid after waiting for response"), GameData->Token.Len() > 0);
		
		// Clean up
		ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(APIHandler, GameData, bCleanupSuccess, this, FGuid()));
	});

}
#endif