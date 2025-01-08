#include "Commands/TestSuiteCommands.h"
#include "Library/GameFuseLog.h"

bool FCreateGame::Update()
{
    if (RequestId.IsValid()) {
        const bool bRequestActive = APIHandler->IsRequestActive(RequestId);
        return !bRequestActive;
    }

    UE_LOG(LogGameFuse, Log, TEXT("Creating Game"));

    FGFApiCallback Callback;
    Callback.AddLambda([this](const FGFAPIResponse& Response) {
        OnGameCreated.Broadcast(Response);
    });

    RequestId = APIHandler->CreateGame(Callback);
    return false;
}

bool FCreateUser::Update()
{
    static bool bRequestSent = false;
    static FGuid CurrentRequestId;

    if (!APIHandler || !GameData || !UserData.IsValid()) {
        Test->AddError(TEXT("APIHandler, GameData, or UserData is null in FCreateUser::Update"));
        return true;
    }

    if (!bRequestSent)
    {
        // Generate random username using GUID
        FString RandomGuid = FGuid::NewGuid().ToString();
        FString Username = FString::Printf(TEXT("user_%s"), *RandomGuid.Left(8));
        FString Email = FString::Printf(TEXT("%s@gamefuse.com"), *Username);

        // Store the username for later use
        UserData->Username = Username;
        UE_LOG(LogGameFuse, Log, TEXT("Creating user with Username: %s, Email: %s"), *Username, *Email);

        FGFApiCallback Callback;
        Callback.AddLambda([this](const FGFAPIResponse& Response) {
            OnUserCreated.Broadcast(Response);
        });

        if (GameData->Id != 0) {
            CurrentRequestId = APIHandler->CreateUser(GameData->Id, Username, Email, Callback);
            bRequestSent = true;
            return false;
        } else {
            Test->AddError(TEXT("GameData ID is 0 in FCreateUser::Update"));
            return true;
        }
    }

    if (CurrentRequestId.IsValid())
    {
        return !APIHandler->IsRequestActive(CurrentRequestId);
    }

    bRequestSent = false; // Reset for next run
    return true;
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
        Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Cleanup Game Request failed. Response: %s"), *Response.ResponseStr));
    });

    RequestId = APIHandler->CleanupGame(GameData->Id, Callback);
    return false;
}

bool FWaitForFGFResponse::Update()
{
    if (!APIHandler) {
        return true;
    }

    return !APIHandler->IsRequestActive(RequestId);
}

bool FSetupGame::Update()
{
    static bool bRequestSent = false;
    static FGuid CurrentRequestId;

    if (!APIHandler || !GameData || !GameFuseManager) {
        Test->AddError(TEXT("APIHandler, GameData, or GameFuseManager is null in FSetupGame::Update"));
        return true;
    }

    if (!bRequestSent)
    {
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

        CurrentRequestId = APIHandler->CreateGame(Callback);
        bRequestSent = true;
        return false;
    }

    if (CurrentRequestId.IsValid() && APIHandler->IsRequestActive(CurrentRequestId))
    {
        return false;
    }

    // Once the request is complete, set up GameFuseManager
    if (!GameFuseManager->IsSetUp())
    {
        GameFuseManager->GetRequestHandler() = APIHandler;
        GameFuseManager->SetUpGame(GameData->Id, GameData->Token, FGFApiCallback());

    }

    bRequestSent = false; // Reset for next run
    return GameFuseManager->IsSetUp();
}

bool FSetupUser::Update()
{
    static bool bCreateUserSent = false;
    static bool bSignInSent = false;
    static bool bWaitingForUserData = false;
    static bool bWaitingForSignIn = false;
    static FGuid RequestId;

    if (!APIHandler || !GameData || !UserData.IsValid() || !GameFuseUser) {
        Test->AddError(TEXT("APIHandler, GameData, UserData, or GameFuseUser is null in FSetupUser::Update"));
        return true;
    }

    // Step 1: Create User
    if (!bCreateUserSent)
    {
        // Generate random username using GUID
        FString RandomGuid = FGuid::NewGuid().ToString();
        FString Username = FString::Printf(TEXT("user_%s"), *RandomGuid.Left(8));
        FString Email = FString::Printf(TEXT("%s@gamefuse.com"), *Username);

        // Store the username for later use
        UserData->Username = Username;
        UE_LOG(LogGameFuse, Log, TEXT("Creating user with Username: %s, Email: %s"), *Username, *Email);

        FGFApiCallback Callback;
        Callback.AddLambda([this](const FGFAPIResponse& Response) {
            if (!Response.bSuccess) {
                Test->AddError(FString::Printf(TEXT("Create User Request failed. Response: %s"), *Response.ResponseStr));
                return;
            }

            // Create a temporary struct to parse into
            FGFUserData TempData;
            bool bParseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, &TempData);
            Test->TestTrue("Parse user data response", bParseSuccess);

            if (bParseSuccess) {
                // Update the existing UserData with the parsed values
                UserData->Id = TempData.Id;
                UserData->Credits = TempData.Credits;
                // Keep the username we set earlier
                
                Test->TestTrue("User ID should be valid", UserData->Id != 0);
                UE_LOG(LogGameFuse, Log, TEXT("UserData updated - ID: %d, Username: %s"), UserData->Id, *UserData->Username);
            } else {
                Test->AddError(TEXT("Failed to parse user data response"));
            }
            
            bWaitingForUserData = true;
        });

        if (GameData->Id != 0) {
            RequestId = APIHandler->CreateUser(GameData->Id, Username, Email, Callback);
            bCreateUserSent = true;
            return false;
        } else {
            Test->AddError(TEXT("GameData ID is 0 in FSetupUser::Update"));
            return true;
        }
    }

    // Wait for user creation to complete
    if (bCreateUserSent && !bWaitingForUserData) {
        return !APIHandler->IsRequestActive(RequestId);
    }

    // Step 2: Sign In User
    if (bWaitingForUserData && !bSignInSent && UserData->Id != 0)
    {
        UE_LOG(LogGameFuse, Log, TEXT("Signing in user with Username: %s"), *UserData->Username);

        FGFApiCallback SignInCallback;
        SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
            Test->TestTrue("Sign in should be successful", Response.bSuccess);
            if (!Response.bSuccess) {
                Test->AddError(FString::Printf(TEXT("Sign in failed: %s"), *Response.ResponseStr));
                return;
            }
            bWaitingForSignIn = true;
        });

        RequestId = GameFuseUser->SignIn(UserData->Username, TEXT("password"), SignInCallback);
        bSignInSent = true;
        return false;
    }

    // Wait for sign in to complete
    if (bSignInSent && !bWaitingForSignIn) {
        return !GameFuseUser->GetRequestHandler()->IsRequestActive(RequestId);
    }

    // Verify final state
    if (bWaitingForSignIn)
    {
        Test->TestTrue("User should be signed in", GameFuseUser->IsSignedIn());
        const FGFUserData& CurrentUserData = GameFuseUser->GetUserData();
        Test->TestEqual("User IDs should match", CurrentUserData.Id, UserData->Id);
        Test->TestEqual("Usernames should match", CurrentUserData.Username, UserData->Username);
        return true;
    }

    return false;
}