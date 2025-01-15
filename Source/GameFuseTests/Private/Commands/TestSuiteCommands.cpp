#include "Commands/TestSuiteCommands.h"
#include "Library/GameFuseLog.h"
#include "Library/GameFuseUtilities.h"

bool FCreateGame::Update()
{
	if (RequestId.IsValid()) {
		const bool bRequestActive = APIHandler->IsRequestActive(RequestId);
		return !bRequestActive;
	}

	UE_LOG(LogGameFuse, Log, TEXT("Creating Game"));

	FGFApiCallback Callback;
	Callback.AddLambda([this](const FGFAPIResponse& Response) {
		Test->TestTrue("Create game request succeeded", Response.bSuccess);
		if (!Response.bSuccess) {
			Test->AddError(FString::Printf(TEXT("Create Game Request failed. Response: %s"), *Response.ResponseStr));
			return;
		}

		bool parseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, GameData.Get());
		UE_LOG(LogGameFuse, Log, TEXT("Parsing CreateGame response. Success: %d, GameData: ID=%d, Token=%s"),
			   parseSuccess, GameData->Id, *GameData->Token);

		Test->TestTrue("got game data from response", parseSuccess);
		Test->TestTrue("Game ID should be valid", GameData->Id != 0);
		Test->AddErrorIfFalse(GameData->Id != 0, TEXT("Game was not initialized"));
		Test->AddErrorIfFalse(GameData->Token.Len() > 0, TEXT("Game Authentication Token was not initialized"));
	});

	RequestId = APIHandler->CreateGame(Callback);
	return false;
}

bool FCreateUser::Update()
{
	if (RequestId.IsValid()) {
		return !APIHandler->IsRequestActive(RequestId);
	}

	UE_LOG(LogGameFuse, Log, TEXT("Creating User"));

	// Generate random username using GUID
	FString RandomGuid = FGuid::NewGuid().ToString();
	FString Username = FString::Printf(TEXT("user_%s"), *RandomGuid.Left(8));
	FString Email = FString::Printf(TEXT("%s@gamefuse.com"), *Username);

	// Store the username for later use
	UserData->Username = Username;
	UE_LOG(LogGameFuse, Log, TEXT("Creating user with Username: %s, Email: %s"), *Username, *Email);

	FGFApiCallback Callback;
	Callback.AddLambda([this](const FGFAPIResponse& Response) {
		Test->TestTrue("Create user request succeeded", Response.bSuccess);
		if (!Response.bSuccess) {
			Test->AddError(FString::Printf(TEXT("Create User Request failed. Response: %s"), *Response.ResponseStr));
			return;
		}

		bool parseSuccess = GameFuseUtilities::ConvertJsonToUserData(*UserData, Response.ResponseStr);
		Test->TestTrue("Parse user data response", parseSuccess);

		if (parseSuccess) {
			Test->TestTrue("User ID should be valid", UserData->Id != 0);
			UE_LOG(LogGameFuse, Log, TEXT("UserData updated - ID: %d, Username: %s"), UserData->Id, *UserData->Username);
		} else {
			Test->AddError(TEXT("Failed to parse user data response"));
		}
	});

	if (GameData->Id != 0) {
		RequestId = APIHandler->CreateUser(GameData->Id, Username, Email, Callback);
	} else {
		Test->AddError(TEXT("GameData ID is 0 in FCreateUser::Update"));
	}

	return false;
}

bool FCreateStoreItem::Update()
{
	if (RequestId.IsValid()) {
		return !APIHandler->IsRequestActive(RequestId);
	}

	UE_LOG(LogGameFuse, Log, TEXT("Creating Store Item"));

	FGFApiCallback Callback;
	Callback.AddLambda([this](const FGFAPIResponse& Response) {
		Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Create Store Item Request failed. Response: %s"), *Response.ResponseStr));
		if (Response.bSuccess) {
			bool parseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, StoreItem.Get());
			Test->TestTrue("Store Item parsed successfully", parseSuccess);
		}
	});

	// Generate random store item name and description
	FString RandomGuid = FGuid::NewGuid().ToString();
	FString StoreItemName = FString::Printf(TEXT("Item_%s"), *RandomGuid.Left(8));
	FString StoreItemDescription = FString::Printf(TEXT("This is a description for item %s"), *StoreItemName);

	// Create a store item object with the provided data
	FGFStoreItem Item;
	Item.Name = StoreItemName;
	Item.Description = StoreItemDescription;
	Item.Cost = 10;

	RequestId = APIHandler->CreateStoreItem(GameData->Id, Item, Callback);
	return false;
}

bool FCleanupGame::Update()
{

	if (GameData->Id == 0) {
		Test->AddWarning("Tried to clean up game with ID 0");
		return true;
	}
	if (RequestId.IsValid()) {
		return !APIHandler->IsRequestActive(RequestId);
	}

	UE_LOG(LogGameFuse, Log, TEXT("Cleaning up Game"));

	FGFApiCallback Callback;
	Callback.AddLambda([this](const FGFAPIResponse& Response) {
		bCleanupSuccess = Response.bSuccess;
		GameData = MakeShared<FGFGameData>();
		Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Cleanup Game Request failed. Response: %s"), *Response.ResponseStr));
	});

	RequestId = APIHandler->CleanupGame(GameData->Id, Callback);

	if (RequestId.IsValid() && APIHandler->IsRequestActive(RequestId)) {
		return false;
	}

	// Ensure cleanup success is checked after request completion
	if (!RequestId.IsValid() && !APIHandler->IsRequestActive(RequestId)) {
		Test->TestTrue("Cleanup should be successful", bCleanupSuccess);
		return true;
	}

	// Wait for cleanup to complete
	while (APIHandler->IsRequestActive(RequestId)) {
		return false;
	}

	// Verify cleanup success after completion
	Test->TestTrue("Cleanup should be successful", bCleanupSuccess);
	Test->TestTrue("GameData should be cleared", *GameData == FGFGameData());
	return true;
}

bool FWaitForFGFResponse::Update()
{
	if (!APIHandler) {
		return true;
	}
	if (!RequestId.IsValid()) {
		UE_LOG(LogGameFuse, Warning, TEXT("Tried to wait for invalid request id: %s"), *RequestId.ToString());
		return true; // No request ID, nothing to wait for()
	}
	UE_LOG(LogGameFuse, Log, TEXT("Waiting for request %s to complete"), *RequestId.ToString());

	return !APIHandler->IsRequestActive(RequestId);
}

bool FSetupGame::Update()
{
	static bool bCreateRequestSent = false;
	static bool bSetupRequestSent = false;

	if (!APIHandler || !GameData || !GameFuseManager) {
		Test->AddError(TEXT("APIHandler, GameData, or GameFuseManager is null in FSetupGame::Update"));
		return true;
	}

	if (!bCreateRequestSent) {
		UE_LOG(LogGameFuse, Log, TEXT("Setting up GameFuse"));

		FGFApiCallback Callback;
		Callback.AddLambda([this](const FGFAPIResponse& Response) {
			Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Setup Game Request failed. Response: %s"), *Response.ResponseStr));

			if (Response.bSuccess) {
				bool parseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, GameData.Get());
				Test->TestTrue("got game data from response", parseSuccess);
				Test->TestTrue("Game ID should be valid", GameData->Id != 0);
			}
		});

		RequestId = APIHandler->CreateGame(Callback);
		bCreateRequestSent = true;
		return false;
	}

	if (RequestId.IsValid() && APIHandler->IsRequestActive(RequestId)) {
		return false;
	}

	// Once the request is complete, set up GameFuseManager
	if (bCreateRequestSent && !bSetupRequestSent && !GameFuseManager->IsSetUp()) {
		GameFuseManager->GetRequestHandler() = APIHandler;
		GameFuseManager->SetUpGame(GameData->Id, GameData->Token, FGFApiCallback());
		bSetupRequestSent = true;
		return false;
	}

	// Wait for GameFuseManager to be set up()
	if (bSetupRequestSent && !GameFuseManager->IsSetUp()) {
		return false;
	}

	// Reset for next run
	bCreateRequestSent = false;
	bSetupRequestSent = false;
	return true;
}

bool FSetupUser::Update()
{
	static bool bCreateUserSent = false;
	static bool bSignInSent = false;
	static FGuid RequestId;

	if (!GameFuseUser) {
		Test->AddError(TEXT("GameFuseUser is null in FSetupUser::Update"));
		return true;
	}

	if (!APIHandler || !GameData || !UserData.IsValid()) {
		Test->AddError(TEXT("APIHandler, GameData, or UserData is null in FSetupUser::Update"));
		return true;
	}

	// Ensure GameData is valid before proceeding
	if (GameData->Id == 0 || GameData->Token.IsEmpty()) {
		Test->AddError(TEXT("Invalid GameData: ID or Token is not set properly"));
		return true;
	}

	// Step 1: Create User
	if (!bCreateUserSent) {
		FString RandomGuid = FGuid::NewGuid().ToString();
		FString Username = FString::Printf(TEXT("user_%s"), *RandomGuid.Left(8));
		FString Email = FString::Printf(TEXT("%s@gamefuse.com"), *Username);

		UserData->Username = Username;
		UE_LOG(LogGameFuse, Log, TEXT("Creating user with Username: %s, Email: %s"), *Username, *Email);

		FGFApiCallback Callback;
		Callback.AddLambda([this](const FGFAPIResponse& Response) {
			if (!Response.bSuccess) {
				Test->AddError(FString::Printf(TEXT("Create User Request failed. Response: %s"), *Response.ResponseStr));
				return;
			}

			bool parseSuccess = GameFuseUtilities::ConvertJsonToUserData(*UserData, Response.ResponseStr);
			Test->TestTrue("Parse user data response", parseSuccess);

			if (!parseSuccess || UserData->Id == 0) {
				Test->AddError(TEXT("Failed to parse user data response or invalid User ID"));
				return;
			}

			UE_LOG(LogGameFuse, Log, TEXT("UserData updated - ID: %d, Username: %s"), UserData->Id, *UserData->Username);

			// Proceed to sign in
			bSignInSent = false;
		});


		RequestId = APIHandler->CreateUser(GameData->Id, Username, Email, Callback);
		bCreateUserSent = true;
		return false;
	}

	// Wait for user creation to complete
	if (bCreateUserSent && APIHandler->IsRequestActive(RequestId)) {
		UE_LOG(LogGameFuse, Log, TEXT("Waiting for user creation to complete..."));
		return false;
	}

	// Step 2: Sign In User
	if (!bSignInSent && UserData->Id != 0) {
		UE_LOG(LogGameFuse, Log, TEXT("Signing in user with Username: %s"), *UserData->Username);

		FGFApiCallback SignInCallback;
		SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
			Test->TestTrue("Sign in should be successful", Response.bSuccess);
			if (!Response.bSuccess) {
				Test->AddError(FString::Printf(TEXT("Sign in failed: %s"), *Response.ResponseStr));
				return;
			}
			bool parseSuccess = GameFuseUtilities::ConvertJsonToUserData(*UserData, Response.ResponseStr);
			Test->AddErrorIfFalse(parseSuccess, TEXT("Failed to parse user data response"));

			// Reset RequestId after handling the response
			RequestId.Invalidate();
		});

		RequestId = GameFuseUser->SignIn(*GameData, UserData->Username + TEXT("@gamefuse.com"), TEXT("password"), SignInCallback);
		bSignInSent = true;
		return false;
	}

	// Wait for sign in to complete
	if (bSignInSent && GameFuseUser->GetRequestHandler()->IsRequestActive(RequestId)) {
		return false;
	}

	// Verify final state
	if (bSignInSent && GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Log, TEXT("+++ User signed in successfully +++"));
		Test->TestTrue("User should be signed in", GameFuseUser->IsSignedIn());
		const FGFUserData& CurrentUserData = GameFuseUser->GetUserData();
		Test->TestEqual("User IDs should match", CurrentUserData.Id, UserData->Id);
		Test->TestEqual("Usernames should match", CurrentUserData.Username, UserData->Username);

		// reset static vars
		bCreateUserSent = false;
		bSignInSent = false;
		return true;
	}

	return true; // Exit if any errors occurred
}