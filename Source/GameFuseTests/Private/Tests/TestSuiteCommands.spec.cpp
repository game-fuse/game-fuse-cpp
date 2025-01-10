#include "Tests/AutomationCommon.h"
#if WITH_AUTOMATION_TESTS
#include "GameFuseTests.h"
#include "Library/GameFuseLog.h"
#include "Misc/AutomationTest.h"
#include "Commands/TestSuiteCommands.h"


BEGIN_DEFINE_SPEC(FTestSuiteCommandsSpec, "GameFuseTests.TestSuiteCommands", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UTestAPIHandler* TestAPIHandler;
	TSharedPtr<FGFGameData> GameData;
	TSharedPtr<FGFUserData> UserData;
	TSharedPtr<FGFStoreItem> StoreItem;
	bool bCleanupSuccess;
	UGameFuseManager* GameFuseManager;
	UGameInstance* GameInstance;
	UGameFuseUser* GameFuseUser;
END_DEFINE_SPEC(FTestSuiteCommandsSpec)

void FTestSuiteCommandsSpec::Define()
{
	TestAPIHandler = NewObject<UTestAPIHandler>();
	TestTrue(TEXT("API Handler should be valid"), TestAPIHandler != nullptr);
	GameData = MakeShared<FGFGameData>();
	UserData = MakeShared<FGFUserData>();
	StoreItem = MakeShared<FGFStoreItem>();

	// Get GameInstance and GameFuseManager
	GameInstance = NewObject<UGameInstance>();
	GameInstance->Init();
	GameFuseManager = GameInstance->GetSubsystem<UGameFuseManager>();
	GameFuseUser = GameInstance->GetSubsystem<UGameFuseUser>();

	Describe("Latent Command Tests", [this]() {
		TestTrue(TEXT("GameFuseManager should be valid"), GameFuseManager != nullptr);

		BeforeEach([this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FWaitLatentCommand(1.0f));
		});

		It("Creates a Game", [this]() {
			// Create game with callback

			ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(TestAPIHandler, GameData, this, FGuid()));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				TestTrue("GameData should be updated locally", GameData->Id != 0 && GameData->Token.Len() > 0);
				return true;
				}));

			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() {
				GameFuseManager->ClearGameData();
				return true;
				}));


		});
		It("Creates a User", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(TestAPIHandler, GameData, this, FGuid()));

			ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, UserData, this, FGuid()));
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				TestTrue("UserData should be updated locally", UserData->Id != 0);
				TestFalse("User Authentication Token is updated", UserData->AuthenticationToken.IsEmpty());
				return true;
				}));

			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() {
				GameFuseManager->ClearGameData();
				return true;
				}));
		});

		It("creates a store item", [this]() {

			ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(TestAPIHandler, GameData, this, FGuid()));

			ADD_LATENT_AUTOMATION_COMMAND(FCreateStoreItem(TestAPIHandler, GameData, StoreItem, this, FGuid()))

			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() {
				GameFuseManager->ClearGameData();
				return true;
				}));
		});

		It("waits for FGF response correctly", [this]() {
			// Create a game and capture its request IDGameData = MakeShared<FGFGameData>();
			ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(TestAPIHandler, GameData, this, FGuid()));
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				TestTrue("GameData should be updated locally", GameData->Id != 0 && GameData->Token.Len() > 0);
				return true;
				}));
			// Setup game with callback in a FunctionLatentCommand
			FGuid SetUpRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, &SetUpRequestId]() -> bool {
				TestTrue("FCreateGame filled GameData", GameData->Id != 0);
				FGFApiCallback SetUpCallback;
				SetUpCallback.AddLambda([this](const FGFAPIResponse& Response) {
					TestTrue("Setup game should be successful", Response.bSuccess);
					if (!Response.bSuccess) {
					AddError(FString::Printf(TEXT("Setup Game Request failed. Response: %s"), *Response.ResponseStr));
					}
					});

				// Set up the game using GameFuseManager
				SetUpRequestId = GameFuseManager->SetUpGame(GameData->Id, GameData->Token, SetUpCallback);


				return true;
				}));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, &SetUpRequestId]() -> bool {
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseManager->GetRequestHandler(), SetUpRequestId));
				return true;
				}));

			// Wait for setup response using APIHandler

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]{
				TestTrue("GameFuseManager should be set up", GameFuseManager->IsSetUp());
				return true;

				}));

			// Clean up
			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() {
				GameFuseManager->ClearGameData();
				return true;
				}));
		});

		It("confirms SetupTestGame is working", [this]() {
			GameData = MakeShared<FGFGameData>();
			UserData = MakeShared<FGFUserData>();

			UE_LOG(LogGameFuse, Log, TEXT("Before SetupTestGame: GameData ID=%d, Token=%s"), GameData->Id, *GameData->Token);

			FGuid SetupGameRequestId;

			ADD_LATENT_AUTOMATION_COMMAND(FSetupGame(TestAPIHandler, GameData, GameFuseManager, this, SetupGameRequestId));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]
				{
				TestTrue("GameFuseManager should be set up", GameFuseManager->IsSetUp());
				TestTrue("GameData should be updated locally", GameData->Id != 0 && GameData->Token.Len() > 0);
				TestTrue("GameFuseManager::GameData should be updated", GameFuseManager->GetGameId() != 0 && GameFuseManager->GetGameToken().Len() > 0);
				return true;
				}));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {

				const FGFGameData& InternalGameData = GameFuseManager->GetGameData();
				UE_LOG(LogGameFuse, Log, TEXT("After SetupTestGame: GameData ID=%d, Token=%s"), InternalGameData.Id, *InternalGameData.Token);
				TestTrue("GameData should be updated in manager", InternalGameData.Id != 0 && InternalGameData.Token.Len() > 0);
				return true;
				}));

			// Clean up
			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() {
				GameFuseManager->ClearGameData();
				return true;
				}));

		});

		It("confirms SetupTestUser is working", [this]() {
			GameData = MakeShared<FGFGameData>();
			UserData = MakeShared<FGFUserData>();

			ADD_LATENT_AUTOMATION_COMMAND(FSetupGame(TestAPIHandler, GameData, GameFuseManager, this, FGuid()));

			ADD_LATENT_AUTOMATION_COMMAND(FSetupUser(TestAPIHandler, GameData, UserData, GameFuseUser, this));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				TestTrue("UserData should be updated locally", UserData->Id != 0);
				TestTrue("UserData has authentication token", !UserData->AuthenticationToken.IsEmpty());
				TestTrue("User should be signed in", GameFuseUser->IsSignedIn());
				return true;
				}));

			// Clean up
			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() {
				GameFuseManager->ClearGameData();
				return true;
				}));
		});
	});
}
#endif