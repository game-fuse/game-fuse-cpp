/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */


#include "GameFuseUser.h"

#include "GameFuseCore.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "Objects/GameFuseSignData.h"
#include "Models/Utilities.h"
#include "Unix/UnixPlatformHttp.h"


// > Region Game Fuse User Initialization and Deinitialization

void UGameFuseUser::Initialize(FSubsystemCollectionBase& Collection)
{
    Super::Initialize(Collection);

    if (const UGameFuseSaveData* LoadedSaveGame = Cast<UGameFuseSaveData>(UGameplayStatics::LoadGameFromSlot("GameFuseSaveSlot", 0)))
    {
        FString LastLoginUser = LoadedSaveGame->LastLogin;
        FString AuthenticationTokenUser = LoadedSaveGame->AuthenticationToken;
        FString UsernameUser = LoadedSaveGame->Username;

        this->SignedIn = true;
        this->NumberOfLogins = (LoadedSaveGame->NumberOfLogins);
        this->LastLogin = (LastLoginUser);
        this->AuthenticationToken = (AuthenticationTokenUser);
        this->Username = (UsernameUser);
        this->Score = (LoadedSaveGame->Score);
        this->Credits = (LoadedSaveGame->Credits);
        this->Id = (LoadedSaveGame->Id);
        
        UE_LOG(LogGameFuse, Display, TEXT("Game Fuse Subsystem Loaded"));
    }
    
}

void UGameFuseUser::Deinitialize()
{
    Super::Deinitialize();
}


// < End Region
// > Region Game Fuse User Getters

bool UGameFuseUser::IsSignedIn() const
{
    return SignedIn;
}

int32 UGameFuseUser::GetNumberOfLogins() const
{
    return NumberOfLogins;
}

FString UGameFuseUser::GetLastLogin() const
{
    return LastLogin;
}

FString UGameFuseUser::GetUsername() const
{
    return Username;
}

int32 UGameFuseUser::GetScore() const
{
    return Score;
}

int32 UGameFuseUser::GetCredits() const
{
    return Credits;
}

TMap<FString, FString>& UGameFuseUser::GetAttributes()
{
    return Attributes;
}

TArray<FString> UGameFuseUser::GetAttributesKeys() const
{
    TArray<FString> KeysArray;
    KeysArray.Reserve(Attributes.Num()); // Optional: Reserving memory for efficiency
    Attributes.GenerateKeyArray(KeysArray);
    return KeysArray;
}

TMap<FString, FString>& UGameFuseUser::GetDirtyAttributes()
{
    return DirtyAttributes;
}

FString UGameFuseUser::GetAttributeValue(const FString Key) const
{
    return Attributes.FindRef(Key);
}

TArray<UGameFuseStoreItem*>& UGameFuseUser::GetPurchasedStoreItems()
{
    return PurchasedStoreItems;
}

TArray<UGameFuseLeaderboardItem*>& UGameFuseUser::GetLeaderboards()
{
    return LeaderboardEntries;
}

FString UGameFuseUser::GetAuthenticationToken() const
{
    return AuthenticationToken;
}

// < End Region
// > Region Game Fuse User SignUp and SignIn

void UGameFuseUser::SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& OurUsername, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);

    UUserAPIManager::SignUp(Email, Password, PasswordConfirmation, OurUsername, UGameFuseCore::GetGameId(), UGameFuseCore::GetGameToken(), CompletionCallback);
}

void UGameFuseUser::SignIn(const FString& Email, const FString& Password, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::SignIn(Email, Password, UGameFuseCore::GetGameId(), UGameFuseCore::GetGameToken(), CompletionCallback);
}

// < End Region
// > Region Game Fuse User Sending Requests

void UGameFuseUser::AddCredits(const int AddCredits, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::AddCredits(AddCredits, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::SetCredits(const int SetCredits, FGameFuseAPIResponseCallback CompletionCallback) 
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::SetCredits(SetCredits, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::AddScore(const int AddScore, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::AddScore(AddScore, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::SetScore(const int SetScore, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::SetScore(SetScore, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::SetAttribute(const FString& SetKey, const FString& SetValue, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::SetAttribute(SetKey, SetValue, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::SetAttributeLocal(const FString& SetKey, const FString& SetValue, FGameFuseAPIResponseCallback CompletionCallback)
{
    DirtyAttributes.Add(SetKey, SetValue);

    FString Set_Dirty_Attribute_Message = FString::Printf(TEXT("Setting Dirty Attribute (local-and-temporary) : %s : %s"), *SetKey, *SetValue);;

    UE_LOG(LogGameFuse, Display, TEXT("%s"), *Set_Dirty_Attribute_Message);
    
    UHTTPResponseManager::CompletionCallback.Execute(true, Set_Dirty_Attribute_Message);
}

void UGameFuseUser::SyncLocalAttributes(FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::SyncLocalAttributes(DirtyAttributes, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::RemoveAttribute(const FString& SetKey, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::RemoveAttribute(SetKey, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::PurchaseStoreItem(const UGameFuseStoreItem* StoreItem, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::PurchaseStoreItem(StoreItem->Id, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::PurchaseStoreItemWithId(const int StoreItemId, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::PurchaseStoreItem(StoreItemId, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::RemoveStoreItem(const UGameFuseStoreItem* StoreItem, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::RemoveStoreItem(StoreItem->Id, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::RemoveStoreItemWithId(const int StoreItemId, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::RemoveStoreItem(StoreItemId, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::AddLeaderboardEntryWithAttributes(const FString& LeaderboardName, const int OurScore, TMap<FString, FString> ExtraAttributes, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::AddLeaderboardEntry(LeaderboardName, OurScore, &ExtraAttributes, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::AddLeaderboardEntry(const FString& LeaderboardName, const int OurScore, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::AddLeaderboardEntry(LeaderboardName, OurScore, nullptr, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::FetchMyLeaderboardEntries(Limit, bOnePerUser, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::ClearLeaderboardEntry(const FString& LeaderboardName, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::ClearLeaderboardEntry(LeaderboardName, Id, AuthenticationToken, CompletionCallback);
}


void UGameFuseUser::FetchAttributes(bool bChainedFromLogin, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::FetchAttributes(bChainedFromLogin, Id, AuthenticationToken, CompletionCallback);
}

void UGameFuseUser::FetchPurchaseStoreItems(const bool bChainedFromLogin, FGameFuseAPIResponseCallback CompletionCallback)
{
    UHTTPResponseManager::CompletionCallback.BindDynamic(this, &UGameFuseUser::InternalResponseManager);
    
    UUserAPIManager::FetchPurchaseStoreItems(bChainedFromLogin, Id, AuthenticationToken, CompletionCallback);
}


// < End Region
// > Region Game Fuse User Setters

void UGameFuseUser::InternalResponseManager(bool bSuccess, const FString& ResponseStr)
{
    if(!bSuccess)
    {
        return;
    }
    
    const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseStr);
    TSharedPtr<FJsonObject> JsonObject;
        
    if (!FJsonSerializer::Deserialize(Reader, JsonObject))
    {
        UE_LOG(LogGameFuse, Error, TEXT("Failed To Parse JSON Response From API"));
        return;
    }
    //surely theres a cleaner way to write this
    if(JsonObject->HasField("id") && JsonObject->HasField("username")) // the request is for : SignUp or SignIn
    {
        SetSignInInternal(JsonObject);
    }
    else if (JsonObject->HasField("game_user_attributes"))             // the request is for : Attributes
    {
        SetAttributesInternal(JsonObject);
    }else if (JsonObject->HasField("game_user_store_items"))           // the request is for : User Store Items
    {
        SetCreditsInternal(JsonObject);
        SetStoreItemsInternal(JsonObject);
    }else if (JsonObject->HasField("leaderboard_entries"))                    // the request is for : Leaderboards
    {
        SetLeaderboardsInternal(JsonObject);
    }else if (JsonObject->HasField("credits"))                         // the request is for : Update the Credits
    {
        SetCreditsInternal(JsonObject);
    }else if (JsonObject->HasField("score"))                           // the request is for : Update the Scores
    {
        SetScoresInternal(JsonObject);
    }else                                                              // the request is for : nothings !
    {
        UE_LOG(LogGameFuse, Warning, TEXT("Unknown Json"));
    }
}

void UGameFuseUser::SetSignInInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
    this->SignedIn = true;
    this->NumberOfLogins = UKismetStringLibrary::Conv_StringToInt(JsonObject->GetStringField("number_of_logins"));
    JsonObject->TryGetStringField(TEXT("last_login"), this->LastLogin);
    JsonObject->TryGetStringField(TEXT("authentication_token"), this->AuthenticationToken);
    JsonObject->TryGetStringField(TEXT("username"), this->Username);
    this->Score = UKismetStringLibrary::Conv_StringToInt(JsonObject->GetStringField("score"));
    this->Credits = UKismetStringLibrary::Conv_StringToInt(JsonObject->GetStringField("credits"));
    this->Id = UKismetStringLibrary::Conv_StringToInt(JsonObject->GetStringField("id"));

    if (UGameFuseSaveData* SaveGameInstance = Cast<UGameFuseSaveData>(UGameplayStatics::CreateSaveGameObject(UGameFuseSaveData::StaticClass())))
    {
        SaveGameInstance->NumberOfLogins = this->NumberOfLogins;
        SaveGameInstance->LastLogin = this->LastLogin;
        SaveGameInstance->AuthenticationToken = this->AuthenticationToken;
        SaveGameInstance->Username = this->Username;
        SaveGameInstance->Score = this->Score;
        SaveGameInstance->Credits = this->Credits;
        SaveGameInstance->Id = this->Id;
    
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, "GameFuseSaveSlot", 0);
        UE_LOG(LogGameFuse, Display, TEXT("Saved Login Data Into SlotName:GameFuseSaveSlot UserIndex:0"));
    }
    else
    {
        UE_LOG(LogGameFuse, Error, TEXT("User Failed To Save SignIn Information !"));
    }
}

void UGameFuseUser::SetCreditsInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
    const int32 NewCredits = UKismetStringLibrary::Conv_StringToInt(JsonObject->GetStringField("credits"));

    if (UGameFuseSaveData* SaveGameInstance = Cast<UGameFuseSaveData>(UGameplayStatics::LoadGameFromSlot("GameFuseSaveSlot", 0)))
    {
        this->Credits = NewCredits;
        SaveGameInstance->Credits = NewCredits;
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, "GameFuseSaveSlot", 0);
        UE_LOG(LogGameFuse, Display, TEXT("Updated The Credits Into SlotName:GameFuseSaveSlot UserIndex:0"));
    }
    else
    {
        UE_LOG(LogGameFuse, Error, TEXT("User Failed To Update Credits !"));
    }
}

void UGameFuseUser::SetScoresInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
    const int32 NewScores = UKismetStringLibrary::Conv_StringToInt(JsonObject->GetStringField("score"));

    if (UGameFuseSaveData* SaveGameInstance = Cast<UGameFuseSaveData>(UGameplayStatics::LoadGameFromSlot("GameFuseSaveSlot", 0)))
    {
        this->Score = NewScores;
        SaveGameInstance->Score = NewScores;
        UGameplayStatics::SaveGameToSlot(SaveGameInstance, "GameFuseSaveSlot", 0);
        UE_LOG(LogGameFuse, Display, TEXT("Updated The Scores Into SlotName:GameFuseSaveSlot UserIndex:0"));
    }
    else
    {
        UE_LOG(LogGameFuse, Error, TEXT("User Failed To Update Scores !"));
    }
}


void UGameFuseUser::SetAttributesInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
    Attributes.Empty();
    
    if (const TArray<TSharedPtr<FJsonValue>>* AttributeArray; JsonObject->TryGetArrayField(TEXT("game_user_attributes"), AttributeArray))
    {
        for (const TSharedPtr<FJsonValue>& AttributeValue : *AttributeArray)
        {
            if (AttributeValue->Type == EJson::Object)
            {
                const TSharedPtr<FJsonObject> AttributeObject = AttributeValue->AsObject();
                FString Key = "";
                FString Value = "";

                // Extract key and value from the JSON object
                AttributeObject->TryGetStringField(TEXT("key"), Key);
                AttributeObject->TryGetStringField(TEXT("value"), Value);

                // Add to the attribute map
                Attributes.Add(Key, Value);
                UE_LOG(LogGameFuse, Display, TEXT("User SetAttributes : %s : %s"), *Key, *Value);
            }else
            {
                UE_LOG(LogGameFuse, Error, TEXT("User Failed to parse JSON"));
                return;
            }
        }
        UE_LOG(LogGameFuse, Display, TEXT("User Attributes Updated"), Attributes.Num());
    }
    else
    {
        UE_LOG(LogGameFuse, Error, TEXT("User Failed To Parse JSON"));
    }
}

void UGameFuseUser::SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
    PurchasedStoreItems.Empty();
    
    if (const TArray<TSharedPtr<FJsonValue>>* AttributeArray; JsonObject->TryGetArrayField(TEXT("game_user_store_items"), AttributeArray))
    {
        for (const TSharedPtr<FJsonValue>& AttributeValue : *AttributeArray)
        {
            if (AttributeValue->Type == EJson::Object)
            {
                const TSharedPtr<FJsonObject> AttributeObject = AttributeValue->AsObject();
                UGameFuseStoreItem* NewItem = NewObject<UGameFuseStoreItem>();
   
                FString Cost = "";
                FString ItemId = "";
                    
                // Extract key and value from the JSON object
                AttributeObject->TryGetStringField(TEXT("name"), NewItem->Name);
                AttributeObject->TryGetStringField(TEXT("category"), NewItem->Category);
                AttributeObject->TryGetStringField(TEXT("description"), NewItem->Description);
                AttributeObject->TryGetStringField(TEXT("cost"), Cost);
                AttributeObject->TryGetStringField(TEXT("id"), ItemId);
                AttributeObject->TryGetStringField(TEXT("icon_url"), NewItem->IconUrl);
                NewItem->Cost = UKismetStringLibrary::Conv_StringToInt(Cost);
                NewItem->Id = UKismetStringLibrary::Conv_StringToInt(ItemId);
                        
                // Add to the attribute map
                PurchasedStoreItems.Add(NewItem);
                UE_LOG(LogGameFuse, Display, TEXT("User Store Item : %s, %s"), *NewItem->Name, *NewItem->Category);
            }else
            {
                UE_LOG(LogGameFuse, Error, TEXT("User Failed To Parse JSON"));
                return;
            }
        }
        UE_LOG(LogGameFuse, Display, TEXT("User Store Items Updated"), Attributes.Num());
    }
    else
    {
        UE_LOG(LogGameFuse, Error, TEXT("User Failed To Parse JSON"));
    }
}

void UGameFuseUser::SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
    LeaderboardEntries.Empty();
    
    if (const TArray<TSharedPtr<FJsonValue>>* AttributeArray; JsonObject->TryGetArrayField(TEXT("leaderboard_entries"), AttributeArray))
    {
        FString GainedScore = "";
        FString GameUserId = "";
        
        for (const TSharedPtr<FJsonValue>& AttributeValue : *AttributeArray)
        {
            if (AttributeValue->Type == EJson::Object)
            {
                const TSharedPtr<FJsonObject> AttributeObject = AttributeValue->AsObject();
                UGameFuseLeaderboardItem* NewItem = NewObject<UGameFuseLeaderboardItem>();
            
                // Extract key and value from the JSON object
                AttributeObject->TryGetStringField(TEXT("username"), NewItem->Username);
                AttributeObject->TryGetStringField(TEXT("score"), GainedScore);
                AttributeObject->TryGetStringField(TEXT("leaderboard_name"), NewItem->LeaderboardName);
                AttributeObject->TryGetStringField(TEXT("game_user_id"), GameUserId);
                AttributeObject->TryGetStringField(TEXT("extra_attributes"), NewItem->ExtraAttributes);
                NewItem->Score = UKismetStringLibrary::Conv_StringToInt(GainedScore);
                NewItem->GameUserId = UKismetStringLibrary::Conv_StringToInt(GameUserId);
                
                // Add to the attribute map
                LeaderboardEntries.Add(NewItem);
            }else
            {
                UE_LOG(LogGameFuse, Error, TEXT("Fetching My Leaderboard Failed to parse JSON Items"));
                return;
            }
        }
    }
    else
    {
        UE_LOG(LogGameFuse, Error, TEXT("Fetching My Leaderboard Failed to parse JSON"));
    }
}