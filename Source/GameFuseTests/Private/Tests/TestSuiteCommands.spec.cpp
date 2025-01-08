#include "Tests/AutomationCommon.h"
#if WITH_AUTOMATION_TESTS
#include "GameFuseTests.h"
#include "Library/GameFuseLog.h"
#include "Misc/AutomationTest.h"
#include "Commands/TestSuiteCommands.h"


BEGIN_DEFINE_SPEC(FTestSuiteCommandsSpec, "GameFuseTests.TestSuiteCommands", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UTestAPIHandler* APIHandler;
	TSharedPtr<FGFGameData> GameData;
	TSharedPtr<FGFUserData> UserData;
	TSharedPtr<FGFStoreItem> StoreItem;
	bool bCleanupSuccess;
	UGameFuseManager* GameFuseManager;
	UGameInstance* GameInstance;
END_DEFINE_SPEC(FTestSuiteCommandsSpec)

void FTestSuiteCommandsSpec::Define()
{
	APIHandler = NewObject<UTestAPIHandler>();
	TestTrue(TEXT("API Handler should be valid"), APIHandler != nullptr);
	GameData = MakeShared<FGFGameData>();
	UserData = MakeShared<FGFUserData>();
	StoreItem = MakeShared<FGFStoreItem>();

	// Get GameInstance and GameFuseManager
	GameInstance = NewObject<UGameInstance>();
	GameInstance->Init();
	GameFuseManager = GameInstance->GetSubsystem<UGameFuseManager>();
	TestTrue(TEXT("GameFuseManager should be valid"), GameFuseManager != nullptr);

	It("Creates a Game", [this]() {
		// Create game with callback
		FGFApiCallback OnGameCreated;
		OnGameCreated.AddLambda([this](const FGFAPIResponse& Response) {
			TestTrue("Create game request succeeded", Response.bSuccess);
			if (!Response.bSuccess) {
				AddError(FString::Printf(TEXT("Create Game Request failed. Response: %s"), *Response.ResponseStr));
				return;
			}

			bool parseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, GameData.Get());
			UE_LOG(LogGameFuse, Log, TEXT("Parsing CreateGame response. Success: %d, GameData: ID=%d, Token=%s"),
			       parseSuccess, GameData->Id, *GameData->Token);

			TestTrue("got game data from response", parseSuccess);
			TestTrue("Game ID should be valid", GameData->Id != 0);
			AddErrorIfFalse(GameData->Id != 0, TEXT("Game was not initialized"));
			AddErrorIfFalse(GameData->Token.Len() > 0, TEXT("Game Authentication Token was not initialized"));
		});

		ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(APIHandler, GameData, OnGameCreated, this, FGuid()));

		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
			TestTrue("GameData should be updated locally", GameData->Id != 0 && GameData->Token.Len() > 0);
			return true;
			}));

		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
			TestTrue("FCreateGame filled GameData", GameData->Id != 0);
			return true;
			}));
	});

	It("Creates a User", [this]() {
		// Create game first
		FGFApiCallback OnGameCreated;
		OnGameCreated.AddLambda([this](const FGFAPIResponse& Response) {
			TestTrue("Create game request succeeded", Response.bSuccess);
			if (!Response.bSuccess) {
				AddError(FString::Printf(TEXT("Create Game Request failed. Response: %s"), *Response.ResponseStr));
				return;
			}

			bool parseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, GameData.Get());
			TestTrue("got game data from response", parseSuccess);
		});

		ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(APIHandler, GameData, OnGameCreated, this, FGuid()));

		// Create user with callback
		FGFApiCallback OnUserCreated;
		OnUserCreated.AddLambda([this](const FGFAPIResponse& Response) {
			TestTrue("Create user request succeeded", Response.bSuccess);
			if (!Response.bSuccess) {
				AddError(FString::Printf(TEXT("Create User Request failed. Response: %s"), *Response.ResponseStr));
				return;
			}

			// Parse the response
			FGFUserData TempData;
			bool bParseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, &TempData);
			TestTrue("Parse user data response", bParseSuccess);

			if (bParseSuccess) {
				// Update UserData with parsed values
				UserData->Id = TempData.Id;
				UserData->Credits = TempData.Credits;

				TestTrue("User ID should be valid", UserData->Id != 0);
				UE_LOG(LogGameFuse, Log, TEXT("UserData updated - ID: %d, Username: %s"), UserData->Id, *UserData->Username);
			}
		});

		ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(APIHandler, GameData, UserData, OnUserCreated, this));
	});

	It("creates a store item", [this]() {

		ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(APIHandler, GameData, FGFApiCallback(), this, FGuid()));

		ADD_LATENT_AUTOMATION_COMMAND(FCreateStoreItem(APIHandler, GameData, StoreItem, this, FGuid()));

		ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(APIHandler, GameData, bCleanupSuccess, this, FGuid()));
	});

	It("waits for FGF response correctly", [this]() {
		// Create a game and capture its request ID
		FGuid RequestId;
		FGFApiCallback OnGameCreated;
		OnGameCreated.AddLambda([this](const FGFAPIResponse& Response) {
			AddErrorIfFalse(Response.bSuccess, TEXT("Create Game Request failed"));
			TestTrue("Setup game request succeeded", Response.bSuccess);
			if (!Response.bSuccess) {
				AddError(FString::Printf(TEXT("Setup Game Request failed. Response: %s"), *Response.ResponseStr));
			}
		});

		ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(APIHandler, GameData, OnGameCreated, this, RequestId));

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

			// Set up the game using GameFuseManager but track request with APIHandler
			SetUpRequestId = GameFuseManager->SetUpGame(GameData->Id, GameData->Token, SetUpCallback);
			return true;
			}));

		// Wait for setup response using APIHandler
		ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(APIHandler, SetUpRequestId));

		// Clean up
		ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(APIHandler, GameData, bCleanupSuccess, this, FGuid()));
	});

	It("confirms SetupTestGame is working", [this]() {

		UE_LOG(LogGameFuse, Log, TEXT("Before SetupTestGame: GameData ID=%d, Token=%s"), GameData->Id, *GameData->Token);

		FGuid SetupGameRequestId;

		ADD_LATENT_AUTOMATION_COMMAND(FSetupGame(APIHandler, GameData, GameFuseManager, this, SetupGameRequestId));

		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]
		{
			ADD_LATENT_AUTOMATION_COMMAND(FEditorAutomationLogCommand("Waiting for set up..."));
			return GameFuseManager->IsSetUp();
		}));

		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {

			const FGFGameData& InternalGameData = GameFuseManager->GetGameData();
			UE_LOG(LogGameFuse, Log, TEXT("After SetupTestGame: GameData ID=%d, Token=%s"), InternalGameData.Id, *InternalGameData.Token);
			TestTrue("GameData should be updated in manager", InternalGameData.Id != 0 && InternalGameData.Token.Len() > 0);
			return true;
			}));


	});
}
#endif