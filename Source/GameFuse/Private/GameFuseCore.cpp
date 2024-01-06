/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */
#include "GameFuseUser.h"

#include "GameFuseCore.h"

int32 UGameFuseCore::GameId        = 0;
FString UGameFuseCore::Token       = "";
FString UGameFuseCore::Name        = "";
FString UGameFuseCore::Description = "";

TArray<UGameFuseStoreItem*>        UGameFuseCore::StoreItems;
TArray<UGameFuseLeaderboardItem*> UGameFuseCore::LeaderboardEntries; 
TMap<FString, FString>             UGameFuseCore::GameVariables; 


// > Region Instance Getters

int32 UGameFuseCore::GetGameId()
{
    return GameId;
}

FString UGameFuseCore::GetGameName()
{
    return Name;
}

FString UGameFuseCore::GetGameDescription()
{
    return Description;
}

FString UGameFuseCore::GetGameToken()
{
    return Token;
}

const TMap<FString, FString>& UGameFuseCore::GetGameVariables()
{
    return GameVariables;
}

const TArray<UGameFuseStoreItem*>& UGameFuseCore::GetGameStoreItems()
{
    return StoreItems;
}

const TArray<UGameFuseLeaderboardItem*>& UGameFuseCore::GetLeaderboard()
{
    return LeaderboardEntries;
}

// < End Region
// > Region Game Fuse Asynchronous Functions

UGameFuseCore* UGameFuseCore::SetUpGame(const FString& InGameId, const FString& InToken, bool bSeedStore)
{
    UGameFuseCore* AsyncTask = NewObject<UGameFuseCore>();
    AsyncTask->AddToRoot();

    UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseCore::InternalResponseManager);

    UStaticAPIManager::SetUpGame(InGameId, InToken, bSeedStore);

    return AsyncTask;
}


UGameFuseCore* UGameFuseCore::SendPasswordResetEmail(const FString& Email)
{
    UGameFuseCore* AsyncTask = NewObject<UGameFuseCore>();
    AsyncTask->AddToRoot();
    
    if(GameId == 0)
    {
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  Please set up your game with SetUpGame() before sending password resets"));
        AsyncTask->CompleteTask(false, "Please set up your game with SetUpGame() before sending password resets");
        return AsyncTask;
    }
    
    UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseCore::InternalResponseManager);

    UStaticAPIManager::SendPasswordResetEmail(Email, GameId, Token);

    return AsyncTask;

}

UGameFuseCore* UGameFuseCore::FetchGameVariables()
{
    UGameFuseCore* AsyncTask = NewObject<UGameFuseCore>();
    AsyncTask->AddToRoot();

    UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseCore::InternalResponseManager);

    UStaticAPIManager::FetchGameVariables(GameId, Token);

    return AsyncTask;
}

UGameFuseCore* UGameFuseCore::FetchLeaderboardEntries(UGameFuseUser* GameFuseUser, const int Limit, bool bOnePerUser, const FString& LeaderboardName)
{
    UGameFuseCore* AsyncTask = NewObject<UGameFuseCore>();
    AsyncTask->AddToRoot();

    UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseCore::InternalResponseManager);

    // UStaticAPIManager::FetchLeaderboardEntries(Limit,  bOnePerUser, LeaderboardName, GameId, GameFuseUser->GetAuthenticationToken());

    return AsyncTask;
}

UGameFuseCore* UGameFuseCore::FetchStoreItems()
{
    UGameFuseCore* AsyncTask = NewObject<UGameFuseCore>();
    AsyncTask->AddToRoot();

    UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseCore::InternalResponseManager);

    UStaticAPIManager::FetchStoreItems(GameId, Token);

    return AsyncTask;
}

// < End Region


void UGameFuseCore::CompleteTask(bool bSuccess, const FString& Result)
{
    if (bSuccess)
    {
        OnSuccess.Broadcast(Result);
    }
    else
    {
        OnError.Broadcast(Result);
    }
    RemoveFromRoot(); // Allow garbage collection
}


// > Region Internal Setters

void UGameFuseCore::InternalResponseManager(bool bWasSuccessful, const FString& ResponseStr)
{
    this->CompleteTask(bWasSuccessful , ResponseStr);
    
    if(!bWasSuccessful)
    {
        return;
    }
    
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseStr);
    TSharedPtr<FJsonObject> JsonObject;
    
    if (!FJsonSerializer::Deserialize(Reader, JsonObject))
    {
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  Failed To Parse JSON Response"));
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
}

void UGameFuseCore::SetSetUpGameInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
    GameId = JsonObject->GetIntegerField(TEXT("id"));
    JsonObject->TryGetStringField(TEXT("name"), Name);
    JsonObject->TryGetStringField(TEXT("token"), Token);
    JsonObject->TryGetStringField(TEXT("description"), Description);

    UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  SetUp Game Completed : %d : %s"), GameId, *Token);
}

void UGameFuseCore::SetVariablesInternal(const FString& JsonStr)
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

void UGameFuseCore::SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject)
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
                UGameFuseLeaderboardItem* NewItem = NewObject<UGameFuseLeaderboardItem>();
            
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

void UGameFuseCore::SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject)
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