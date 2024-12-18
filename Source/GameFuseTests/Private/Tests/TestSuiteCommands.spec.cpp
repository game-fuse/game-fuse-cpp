#include "Library/GameFuseLog.h"
#if WITH_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "Commands/TestSuiteCommands.h"

BEGIN_DEFINE_SPEC(FTestSuiteCommandsSpec, "GameFuseTests.TestSuiteCommands", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UTestAPIHandler* APIHandler;
	TSharedPtr<FGFGameData> GameData;
	TSharedPtr<FGFUserData> UserData;
	TSharedPtr<FGFStoreItem> StoreItem;
	bool bCleanupSuccess;
END_DEFINE_SPEC(FTestSuiteCommandsSpec)

void FTestSuiteCommandsSpec::Define()
{
	APIHandler = NewObject<UTestAPIHandler>();
	TestTrue(TEXT("API Handler should be valid"), APIHandler != nullptr);
	GameData = MakeShared<FGFGameData>();
	UserData = MakeShared<FGFUserData>();
	StoreItem = MakeShared<FGFStoreItem>();

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
			TestTrue("Create game request succeeded", Response.bSuccess);
			if (!Response.bSuccess) {
				AddError(FString::Printf(TEXT("Create Game Request failed. Response: %s"), *Response.ResponseStr));
				return;
			}

			bool parseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, GameData.Get());
			TestTrue("got game data from response", parseSuccess);
		});

		ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(APIHandler, GameData, OnGameCreated, this, RequestId));

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