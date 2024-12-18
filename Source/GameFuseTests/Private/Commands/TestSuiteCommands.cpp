#include "Commands/TestSuiteCommands.h"

#include "Library/GameFuseLog.h"

bool FCreateGame::Update()
{
    if (RequestId.IsValid()) {
        const bool bRequestActive = APIHandler->IsRequestActive(RequestId);
        UE_LOG(LogGameFuse, Log, TEXT("Request %s is active: %i"), *RequestId.ToString(), bRequestActive);
        return !bRequestActive;
    }

    UE_LOG(LogGameFuse, Log, TEXT("Creating Game"));

    FGFApiCallback Callback;
    Callback.AddLambda([this](const FGFAPIResponse& Response) {
        Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Create Game Request failed. Response: %s"), *Response.ResponseStr));

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
    static bool bRequestSent = false;
    static bool bWaitingForData = false;

    if (!APIHandler || !GameData || !UserData.IsValid()) {
        Test->AddError(TEXT("APIHandler, GameData, or UserData is null in FCreateUser::Update"));
        return true; // End the command
    }

    if (!bRequestSent)
    {
        // Generate random username using GUID
        FString RandomGuid = FGuid::NewGuid().ToString();
        FString Username = FString::Printf(TEXT("user_%s"), *RandomGuid.Left(8));
        FString Email = FString::Printf(TEXT("%s@gamefuse.com"), *Username);

        // Store the username for later use
        UserData->Username = Username;

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
            
            bWaitingForData = true;
        });

        if (GameData->Id != 0) {
            RequestId = APIHandler->CreateUser(GameData->Id, Username, Email, Callback);
            bRequestSent = true;
            return false;
        } else {
            Test->AddError(TEXT("GameData ID is 0 in FCreateUser::Update"));
            return true; // End the command
        }
    }

    if (RequestId.IsValid() && !bWaitingForData) {
        return !APIHandler->IsRequestActive(RequestId);
    }

    if (bWaitingForData)
    {
        if (!UserData.IsValid() || UserData->Id == 0 || UserData->Username.IsEmpty()) {
            UE_LOG(LogGameFuse, Warning, TEXT("Waiting for UserData to be populated... ID: %d, Username: %s"), 
                UserData.IsValid() ? UserData->Id : -1, 
                UserData.IsValid() ? *UserData->Username : TEXT("Invalid"));
            return false;
        }

        // Reset static variables for next run
        bRequestSent = false;
        bWaitingForData = false;
        return true;
    }

    return false;
}

bool FCreateStoreItem::Update()
{

    if (RequestId.IsValid()) {
        return !APIHandler->IsRequestActive(RequestId);
    }

    FGFStoreItem NewItem;
    NewItem.Name = TEXT("TestItem");
    NewItem.Description = TEXT("Test Item Description");
    NewItem.Cost = 100;

    FGFApiCallback Callback;
    Callback.AddLambda([this](const FGFAPIResponse& Response) {
        Test->AddInfo(FString::Printf(TEXT("FCreateStoreItem::Update - Callback invoked, Success: %d"), Response.bSuccess));
        Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Create Store ItemRequest failed. Response: %s"), *Response.ResponseStr));

        FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, StoreItem.Get());

        Test->TestTrue("Store Item ID should be valid", StoreItem->Id != 0);
        Test->AddErrorIfFalse(StoreItem->Id != 0, TEXT("Store Item was not initialized"));
    });

    RequestId = APIHandler->CreateStoreItem(GameData->Id, NewItem, Callback);
    return false;
}



bool FCleanupGame::Update()
{
    if (RequestId.IsValid()) {
        return !APIHandler->IsRequestActive(RequestId);
    }

    FGFApiCallback Callback;
    Callback.AddLambda([this](const FGFAPIResponse& Response) {
        Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Clean up request failed. Response: %s"), *Response.ResponseStr));

        bCleanupSuccess = Response.bSuccess;
    });

    RequestId = APIHandler->CleanupGame(GameData->Id, Callback);
    return false;
}

bool FWaitForFGFResponse::Update()
{
    if (!RequestId.IsValid()) {
        return true;
    }

    const bool bRequestActive = APIHandler->IsRequestActive(RequestId);
    if (!bRequestActive) {
        // Add a small delay to allow for response processing
        FPlatformProcess::Sleep(0.1f);
    }
    
    UE_LOG(LogGameFuse, Log, TEXT("Waiting for request %s to complete. Is Active: %s"), 
        *RequestId.ToString(), 
        bRequestActive ? TEXT("True") : TEXT("False"));

    return !bRequestActive;
}

bool FSetupGame::Update()
{
    static bool bCreateGameSent = false;
    static bool bCreateGameComplete = false;
    static bool bSetupGameSent = false;
    static bool bSetupGameComplete = false;

    if (!bCreateGameSent)
    {
        // First create the game
        FGFApiCallback CreateGameCallback;
        CreateGameCallback.AddLambda([this](const FGFAPIResponse& Response) {
            Test->TestTrue("Create game should be successful", Response.bSuccess);
            if (!Response.bSuccess)
            {
                Test->AddError(FString::Printf(TEXT("Failed to create game: %s"), *Response.ResponseStr));
                bCreateGameComplete = true;
                return;
            }
            
            // Parse game data from response
            TSharedPtr<FJsonObject> JsonObject;
            if (!FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Response.ResponseStr), JsonObject))
            {
                Test->AddError(TEXT("Failed to parse game data response"));
                bCreateGameComplete = true;
                return;
            }
            
            FGFGameData NewGameData;
            if (!FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &NewGameData))
            {
                Test->AddError(TEXT("Failed to convert game data from JSON"));
                bCreateGameComplete = true;
                return;
            }
            
            // Update game data
            *GameData = NewGameData;
            bCreateGameComplete = true;
        });
        
        // Send create game request
        RequestId = APIHandler->CreateGame(CreateGameCallback);
        bCreateGameSent = true;
        return false;
    }

    if (!bCreateGameComplete)
    {
        return false;
    }

    if (!bSetupGameSent && bCreateGameComplete)
    {
        if (!GameFuseManager)
        {
            Test->AddError(TEXT("GameFuseManager not found"));
            bSetupGameComplete = true;
            return true;
        }

        FGFApiCallback SetUpGameCallback;
        SetUpGameCallback.AddLambda([this](const FGFAPIResponse& Response) {
            Test->TestTrue("Setup game should be successful", Response.bSuccess);
            if (!Response.bSuccess)
            {
                Test->AddError(TEXT("Failed to setup game"));
            }
            bSetupGameComplete = true;
        });

        GameFuseManager->SetUpGame(GameData->Id, GameData->Token, SetUpGameCallback);
        bSetupGameSent = true;
        return false;
    }

    if (!bSetupGameComplete)
    {
        return false;
    }

    // Reset static variables for next run
    bCreateGameSent = false;
    bCreateGameComplete = false;
    bSetupGameSent = false;
    bSetupGameComplete = false;

    return true;
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