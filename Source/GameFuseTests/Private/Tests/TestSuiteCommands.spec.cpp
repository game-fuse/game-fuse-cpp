#if WITH_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "Commands/TestSuiteCommands.h"

BEGIN_DEFINE_SPEC(FGameFuseTestSpec, "GameFuseTests.TestSuiteCommands", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UTestAPIHandler* APIHandler;
	TSharedPtr<FGFGameData> GameData;
	FGFUserData UserData;
	FGFStoreItem StoreItem;
	bool bCleanupSuccess;
END_DEFINE_SPEC(FGameFuseTestSpec)

void FGameFuseTestSpec::Define()
{
	APIHandler = NewObject<UTestAPIHandler>();
	TestTrue(TEXT("API Handler should be valid"), APIHandler != nullptr);
	GameData = MakeShared<FGFGameData>();

	It("creates a game and cleans it up", [this]() {
		ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(APIHandler, GameData, this, FGuid()));

		ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(APIHandler, GameData, UserData, this, FGuid()));

		// Endpoint does not exist currently
		// ADD_LATENT_AUTOMATION_COMMAND(FCreateStoreItem(APIHandler, *GameData, StoreItem, this, FGuid()));
		AddWarning("CreateStoreItem endpoint isn't working yet");

		ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(APIHandler, *GameData, bCleanupSuccess, this, FGuid()));

	});


}
#endif