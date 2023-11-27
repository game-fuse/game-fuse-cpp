/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "GameFuseManager.h"

inline static TSharedRef<IHttpRequest> RequestManager = FHttpModule::Get().CreateRequest();;
const FString BaseURL = "https://gamefuse.co/api/v1";

int32 UGameFuseManager::GameId        = 0;
FString UGameFuseManager::Token       = "";
FString UGameFuseManager::Name        = "";
FString UGameFuseManager::Description = "";

TArray<UGameFuseStoreItem*>        UGameFuseManager::StoreItems;
TArray<UGameFuseLeaderboardEntry*> UGameFuseManager::LeaderboardEntries; 
TMap<FString, FString>             UGameFuseManager::GameVariables; 


// > Region Instance Getters

int32 UGameFuseManager::GetGameId()
{
    return GameId;
}

FString UGameFuseManager::GetGameName()
{
    return Name;
}

FString UGameFuseManager::GetGameDescription()
{
    return Description;
}

FString UGameFuseManager::GetGameToken()
{
    return Token;
}

FString UGameFuseManager::GetBaseURL()
{
    return BaseURL;
}

const TMap<FString, FString>& UGameFuseManager::GetGameVariables()
{
    return GameVariables;
}

const TArray<UGameFuseStoreItem*>& UGameFuseManager::GetGameStoreItems()
{
    return StoreItems;
}

const TArray<UGameFuseLeaderboardEntry*>& UGameFuseManager::GetLeaderboard()
{
    return LeaderboardEntries;
}

// < End Region
// > Region Game Fuse Requests

void UGameFuseManager::SetUpGame(const FString& InGameId, const FString& InToken, const bool bSeedStore, FManagerCallback CompletionCallback)
{
    FString ApiEndpoint = FString::Printf(TEXT("%s/games/verify.json?game_id=%s&game_token=%s")
        , *BaseURL, *InGameId, *InToken);
    if (bSeedStore) ApiEndpoint.Append("&seed_store=true");
    
    UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Setting Up Game: %d : %s"), GameId, *Token);
    UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Setting Up Game Sending Request: %s"), *ApiEndpoint);

    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("GET");

    RequestManager->OnProcessRequestComplete().BindStatic(&UGameFuseManager::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseManager::SendPasswordResetEmail(const FString& Email, FManagerCallback CompletionCallback)
{
    if(GameId == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  Please set up your game with SetUpGame() before sending password resets"));
        return;
    }
    
    FString ApiEndpoint = FString::Printf(TEXT("%s/games/%d/forget_password?game_token=%s&game_id=%d&email=%s")
        , *BaseURL, GameId, *Token, GameId,*Email);

    UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Sending Password Reset Email : GameId: %s , GameToken: %s, Email : %s"), GameId, *Token, *Email);

    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("POST");

    RequestManager->OnProcessRequestComplete().BindStatic(&UGameFuseManager::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseManager::FetchGameVariables(FManagerCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(
        TEXT("%s/games/fetch_game_variables.json?game_id=%d&game_token=%s"), *BaseURL, GameId, *Token);

    UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Fetching Game Variables : %d : %s"), GameId, *Token);
    UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Fetching Game Variables Sending Request: %s"), *ApiEndpoint);

    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("GET");

    RequestManager->OnProcessRequestComplete().BindStatic(&UGameFuseManager::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseManager::FetchLeaderboardEntries(UGameFuseUser* GameFuseUser, const int Limit, bool bOnePerUser, const FString& LeaderboardName,
    FManagerCallback CompletionCallback)
{
    const FString OnePerUserStr = (bOnePerUser) ? TEXT("true") : TEXT("false");
    const FString ApiEndpoint = FString::Printf(
        TEXT("%s/games/%d/leaderboard_entries?authentication_token=%s&leaderboard_name=%s&limit=%d&one_per_user=%s")
        , *BaseURL, GameId, *GameFuseUser->GetAuthenticationToken(), *LeaderboardName, Limit, *OnePerUserStr);

    UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Fetching Leaderboard : %s"), *ApiEndpoint);
    UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Fetching Leaderboard : %s : %d"), *LeaderboardName, Limit);

    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("GET");

    RequestManager->OnProcessRequestComplete().BindStatic(&UGameFuseManager::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseManager::FetchStoreItems(FManagerCallback CompletionCallback)
{
    FString ApiEndpoint = FString::Printf(TEXT("%s/games/store_items?game_id=%d&game_token=%s")
        , *BaseURL, GameId, *Token);

    UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Fetching Store Items"));

    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("GET");

    RequestManager->OnProcessRequestComplete().BindStatic(&UGameFuseManager::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

// < End Region
// > Region HTTP Request Received Manager

void UGameFuseManager::OnHttpResponseReceivedManager(FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful, FManagerCallback CompletionCallback)
{
    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Request Failed"));
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(bWasSuccessful, "Game Fuse HTTP Request Failed");
        return;
    }

    const FString ResponseStr = Response->GetContentAsString();

    if (const int32 ResponseCode = Response->GetResponseCode(); ResponseCode == 200)
    {
        const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseStr);
        TSharedPtr<FJsonObject> JsonObject;
        
        if (!FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  Failed To Parse JSON Response From API"));
            if (CompletionCallback.IsBound()) CompletionCallback.Execute(bWasSuccessful, "Game Fuse Failed To Parse JSON Response From API");
            return;
        }

        if(JsonObject->HasField("id") && JsonObject->HasField("game_variables")) // the request is for SetUpGame and Variables
        {
            SetSetUpGameInternal(JsonObject);
            SetVariablesInternal(ResponseStr);
        }
        else if (JsonObject->HasField("leaderboard_entries"))                    // the request is for : Leaderboards
        {
            SetLeaderboardsInternal(JsonObject);
        }else if (JsonObject->HasField("store_items"))                           // the request is for : Store Items
        {
            SetStoreItemsInternal(JsonObject);
        }else if (JsonObject->HasField("mailer_response"))                       // the request is for : forgot email
        {
            UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Forgot Password Email Sent!"));
        }else                                                                    // the request is for : nothings !
        {
            UE_LOG(LogTemp, Warning, TEXT("LogGameFuse :  Unknown Json"));
        }
        
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(bWasSuccessful, ResponseStr);
    }
    else
    {
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(bWasSuccessful, ResponseStr);
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Request Returned Status Code %d"), ResponseCode);
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Response : %s"), *ResponseStr);
    }
}

// < End Region
// > Region Internal Setters

void UGameFuseManager::SetSetUpGameInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
    GameId = JsonObject->GetIntegerField(TEXT("id"));
    JsonObject->TryGetStringField(TEXT("name"), Name);
    JsonObject->TryGetStringField(TEXT("token"), Token);
    JsonObject->TryGetStringField(TEXT("description"), Description);

    UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  SetUp Game Completed : %d : %s"), GameId, *Token);
}

void UGameFuseManager::SetVariablesInternal(const FString& JsonStr)
{
    GameVariables.Empty();

    const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);

    if (TSharedPtr<FJsonObject> JsonObject; FJsonSerializer::Deserialize(JsonReader, JsonObject))
    {
        if (const TArray<TSharedPtr<FJsonValue>>* GameVariablesArray = nullptr; JsonObject->TryGetArrayField("game_variables", GameVariablesArray))
        {
            for (const TSharedPtr<FJsonValue>& JsonValue : *GameVariablesArray)
            {
                const TSharedPtr<FJsonObject> VariableObject = JsonValue->AsObject();

                FString Key = "";
                FString Value = "";

                if (VariableObject->TryGetStringField("key", Key) && VariableObject->TryGetStringField("value", Value))
                {
                    GameVariables.Add(Key, Value);
                }
            }
            UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Fetched Variables amount of : %d"), GameVariables.Num());
        }
    }
    else
    {
        // Handle JSON parsing error
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  Fetching Game Variables Failed to parse JSON"));
    }
}

void UGameFuseManager::SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
    LeaderboardEntries.Empty();
    
    if (const TArray<TSharedPtr<FJsonValue>>* AttributeArray; JsonObject->TryGetArrayField(TEXT("leaderboard_entries"), AttributeArray))
    {
        FString Score = "";
        FString GameUserId = "";
        
        for (const TSharedPtr<FJsonValue>& AttributeValue : *AttributeArray)
        {
            if (AttributeValue->Type == EJson::Object)
            {
                const TSharedPtr<FJsonObject> AttributeObject = AttributeValue->AsObject();
                UGameFuseLeaderboardEntry* NewItem = NewObject<UGameFuseLeaderboardEntry>();
            
                // Extract key and value from the JSON object
                AttributeObject->TryGetStringField(TEXT("username"), NewItem->Username);
                AttributeObject->TryGetStringField(TEXT("score"), Score);
                AttributeObject->TryGetStringField(TEXT("leaderboard_name"), NewItem->LeaderboardName);
                AttributeObject->TryGetStringField(TEXT("game_user_id"), GameUserId);
                AttributeObject->TryGetStringField(TEXT("extra_attributes"), NewItem->ExtraAttributes);
                NewItem->Score = UKismetStringLibrary::Conv_StringToInt(Score);
                NewItem->GameUserId = UKismetStringLibrary::Conv_StringToInt(GameUserId);
                
                // Add to the attribute map
                LeaderboardEntries.Add(NewItem);
            }else
            {
                UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  Fetching Leaderboard Failed to parse JSON Items"));
                return;
            }
        }
        UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Fetched Leaderboards amount of : %d"), LeaderboardEntries.Num());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  Fetching Leaderboard Failed to parse JSON"));
    }
}

void UGameFuseManager::SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
    StoreItems.Empty();
    
    if (const TArray<TSharedPtr<FJsonValue>>* AttributeArray; JsonObject->TryGetArrayField(TEXT("store_items"), AttributeArray))
    {
        FString Cost = "";
        FString Id = "";
        
        for (const TSharedPtr<FJsonValue>& AttributeValue : *AttributeArray)
        {
            if (AttributeValue->Type == EJson::Object)
            {
                const TSharedPtr<FJsonObject> AttributeObject = AttributeValue->AsObject();
                UGameFuseStoreItem* NewItem = NewObject<UGameFuseStoreItem>();
            
                // Extract key and value from the JSON object
                AttributeObject->TryGetStringField(TEXT("name"), NewItem->Name);
                AttributeObject->TryGetStringField(TEXT("category"), NewItem->Category);
                AttributeObject->TryGetStringField(TEXT("description"), NewItem->Description);
                AttributeObject->TryGetStringField(TEXT("cost"), Cost);
                AttributeObject->TryGetStringField(TEXT("id"), Id);
                AttributeObject->TryGetStringField(TEXT("icon_url"), NewItem->IconUrl);
                NewItem->Cost = UKismetStringLibrary::Conv_StringToInt(Cost);
                NewItem->Id = UKismetStringLibrary::Conv_StringToInt(Id);
                
                // Add to the attribute map
                StoreItems.Add(NewItem);
            }else
            {
                UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  Fetching Store Items Failed to parse JSON Items"));
                return;
            }
        }
        UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Fetched Store Items amount of : %d"), LeaderboardEntries.Num());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  Fetching Store Items Failed to parse JSON"));
    }
}

// < End Region