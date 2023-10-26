// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFuseUser.h"

#include "GameFuseManager.h"
#include "GameFuseSaveData.h"
#include "GameFuseUtilities.h"


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
        
        UE_LOG(LogTemp, Error, TEXT("GameFuse ====> Game Loaded"));
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

FString UGameFuseUser::GetAttributeValue(const FString Key) const
{
    return Attributes.FindRef(Key);
}

TArray<UGameFuseStoreItem*>& UGameFuseUser::GetPurchasedStoreItems()
{
    return PurchasedStoreItems;
}

TArray<UGameFuseLeaderboardEntry*>& UGameFuseUser::GetLeaderboards()
{
    return LeaderboardEntries;
}

FString UGameFuseUser::GetAuthenticationToken() const
{
    return AuthenticationToken;
}

// < End Region
// > Region Game Fuse User SignUp and SignIn

void UGameFuseUser::SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& OurUsername, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users?email=%s&password=%s&password_confirmation=%s&username=%s&game_id=%d&game_token=%s")
    , *UGameFuseManager::GetBaseURL(), *Email, *Password, *PasswordConfirmation, *OurUsername, UGameFuseManager::GetGameId(), *UGameFuseManager::GetGameToken());

    UE_LOG(LogTemp, Error, TEXT("GameFuse Sign In: %s : %s"), *Email, *OurUsername);

    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("POST");
    
    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::SignIn(const FString& Email, const FString& Password, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/sessions?email=%s&password=%s&game_id=%d&game_token=%s")
    , *UGameFuseManager::GetBaseURL(), *Email, *Password, UGameFuseManager::GetGameId(), *UGameFuseManager::GetGameToken());

    UE_LOG(LogTemp, Error, TEXT("GameFuse Sign In: %s"), *Email);

    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("POST");
    
    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

// < End Region
// > Region Game Fuse User Sending Requests

void UGameFuseUser::AddCredits(const int AddCredits, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/add_credits?authentication_token=%s&credits=%d")
        , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, AddCredits);

    UE_LOG(LogTemp, Error, TEXT("GameFuse Add Credits: %d"), AddCredits);

    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("POST");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::SetCredits(const int SetCredits, FUserCallback CompletionCallback) 
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/set_credits?authentication_token=%s&credits=%d")
        , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, SetCredits);

    UE_LOG(LogTemp, Error, TEXT("GameFuse Set Credits: %d"), SetCredits);

    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("POST");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::AddScore(const int AddScore, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/add_score?authentication_token=%s&score=%d")
        , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, AddScore);

    UE_LOG(LogTemp, Error, TEXT("GameFuse Add Score: %d"), AddScore);

    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("POST");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::SetScore(const int SetScore, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/set_score?authentication_token=%s&score=%d")
        , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, SetScore);

    UE_LOG(LogTemp, Error, TEXT("GameFuse Set Score: %d"), SetScore);

    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("POST");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::SetAttribute(const FString& SetKey, const FString& SetValue, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/add_game_user_attribute?authentication_token=%s&key=%s&value=%s")
        , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, *SetKey, *SetValue);

    UE_LOG(LogTemp, Error, TEXT("GameFuse Set Attribute: %s : %s"), *SetKey, *SetValue);
    
    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("POST");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::RemoveAttribute(const FString& SetKey, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/remove_game_user_attributes?authentication_token=%s&key=%s")
        , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, *SetKey);

    UE_LOG(LogTemp, Error, TEXT("GameFuse Remove Attribute: %s"), *SetKey);
    
    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("GET");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::PurchaseStoreItem(const UGameFuseStoreItem* StoreItem, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/purchase_game_user_store_item?authentication_token=%s&store_item_id=%d")
        , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, StoreItem->Id);

    UE_LOG(LogTemp, Error, TEXT("GameFuse Purchase Store Item : %s"), *StoreItem->Name);
    
    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("POST");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::PurchaseStoreItemWithId(const int StoreItemId, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/purchase_game_user_store_item?authentication_token=%s&store_item_id=%d")
        , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, StoreItemId);

    UE_LOG(LogTemp, Error, TEXT("GameFuse Purchase Store Item: %d"), StoreItemId);
    
    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("POST");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::RemoveStoreItem(const UGameFuseStoreItem* StoreItem, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/purchase_game_user_store_item?authentication_token=%s&store_item_id=%d")
        , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, StoreItem->Id);
 
    UE_LOG(LogTemp, Error, TEXT("GameFuse Remove Store Item: %d"), *StoreItem->Name);
    
    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("GET");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::RemoveStoreItemWithId(const int StoreItemId, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/purchase_game_user_store_item?authentication_token=%s&store_item_id=%d")
        , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, StoreItemId);

    UE_LOG(LogTemp, Error, TEXT("GameFuse Remove Store Item: %d"), StoreItemId);
    
    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("GET");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::AddLeaderboardEntryWithAttributes(const FString& LeaderboardName, const int OurScore,
                                        TMap<FString, FString> ExtraAttributes, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(
        TEXT("%s/users/%d/add_leaderboard_entry?authentication_token=%s&score=%d&leaderboard_name=%s&extra_attributes=%s")
    , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, OurScore, *LeaderboardName, *GameFuseUtilities::ConvertMapToJsonStr(ExtraAttributes));

    UE_LOG(LogTemp, Error, TEXT("GameFuse User Adding Leaderboard Entry: %s : %d"), *LeaderboardName, OurScore);
    
    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("POST");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::AddLeaderboardEntry(const FString& LeaderboardName, const int OurScore,
    FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/add_leaderboard_entry?authentication_token=%s&score=%d&leaderboard_name=%s")
    , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, OurScore, *LeaderboardName);

    UE_LOG(LogTemp, Error, TEXT("GameFuse User Adding Leaderboard Entry: %s : %d"), *LeaderboardName, OurScore);
    
    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("POST");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, FUserCallback CompletionCallback)
{
    const FString OnePerUserStr = (bOnePerUser) ? TEXT("true") : TEXT("false");
    const FString ApiEndpoint = FString::Printf(
        TEXT("%s/users/%d/leaderboard_entries?authentication_token=%s&limit=%d&one_per_user=%s")
        , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, Limit, *OnePerUserStr);

    UE_LOG(LogTemp, Error, TEXT("GameFuse Fetch My Leaderboard Entries: %d : %s"), Limit, *OnePerUserStr);
    
    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("GET");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::ClearLeaderboardEntry(const FString& LeaderboardName, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/clear_my_leaderboard_entries?authentication_token=%s&leaderboard_name=%s")
    , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken, *LeaderboardName);

    UE_LOG(LogTemp, Error, TEXT("GameFuse User Clearing Leaderboard Entry: %s"), *LeaderboardName);
    
    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("POST");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}


void UGameFuseUser::FetchAttributes(bool bChainedFromLogin, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/game_user_attributes?authentication_token=%s")
        , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken);

    UE_LOG(LogTemp, Error, TEXT("GameFuse User Downloading Attributes"));

    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("GET");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}

void UGameFuseUser::FetchPurchaseStoreItems(bool bChainedFromLogin, FUserCallback CompletionCallback)
{
    const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/game_user_store_items?authentication_token=%s")
        , *UGameFuseManager::GetBaseURL(), Id, *AuthenticationToken);

    UE_LOG(LogTemp, Error, TEXT("GameFuse User Downloading Purchase Store Items"));

    RequestManager->SetURL(ApiEndpoint);
    RequestManager->SetVerb("GET");

    RequestManager->OnProcessRequestComplete().BindUObject(this, &UGameFuseUser::OnHttpResponseReceivedManager, CompletionCallback);
    RequestManager->ProcessRequest();
}


// < End Region
// > Region Game Fuse User Request Manager

void UGameFuseUser::OnHttpResponseReceivedManager(FHttpRequestPtr Request, const FHttpResponsePtr Response,
                                                  bool bWasSuccessful, FUserCallback CompletionCallback)
{
    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("Game Fuse HTTP Request failed."));
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(false, "Game Fuse HTTP Request failed.");
        return;
    }

    if (const int32 ResponseCode = Response->GetResponseCode(); ResponseCode == 200)
    {
        const FString ResponseStr = Response->GetContentAsString();
        const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseStr);
        TSharedPtr<FJsonObject> JsonObject;
        
        if (!FJsonSerializer::Deserialize(Reader, JsonObject))
        {
            UE_LOG(LogTemp, Error, TEXT("Game Fuse Failed to parse JSON response from API."));
            if (CompletionCallback.IsBound()) CompletionCallback.Execute(false, "Game Fuse Failed to parse JSON response from API.");
            return;
        }
        
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
            UE_LOG(LogTemp, Error, TEXT("Game Fuse Unknown Json"));
        }
        
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(true, ResponseStr);
    }
    else
    {
        const FString Message = FString::Printf(TEXT("Game Fuse HTTP Request returned status code %d"), ResponseCode);
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(false, Message);
        UE_LOG(LogTemp, Warning, TEXT("Game Fuse HTTP Request returned status code %d"), ResponseCode);
    }
}

// < End Region
// > Region Game Fuse User Setters

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
        UE_LOG(LogTemp, Error, TEXT("Game Fuse Saved Login Data Into SlotName:GameFuseSaveSlot UserIndex:0"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Game Fuse User Failed To Save SignIn Information !"));
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
        UE_LOG(LogTemp, Error, TEXT("Game Fuse Updated The Credits Into SlotName:GameFuseSaveSlot UserIndex:0"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Game Fuse User Failed To Update Credits !"));
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
        UE_LOG(LogTemp, Error, TEXT("Game Fuse Updated The Scores Into SlotName:GameFuseSaveSlot UserIndex:0"));
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Game Fuse User Failed To Update Scores !"));
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
                UE_LOG(LogTemp, Error, TEXT("Game Fuse User SetAttributes : %s : %s"), *Key, *Value);
            }else
            {
                UE_LOG(LogTemp, Error, TEXT("Game Fuse User Failed to parse JSON"));
                return;
            }
        }
        UE_LOG(LogTemp, Error, TEXT("Game Fuse User Attributes Updated"), Attributes.Num());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Game Fuse User Failed to parse JSON"));
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
                UE_LOG(LogTemp, Error, TEXT("Game Fuse User StoreItems %s, %s"), *NewItem->Name, *NewItem->Category);
            }else
            {
                UE_LOG(LogTemp, Error, TEXT("Game Fuse User Failed to parse JSON"));
                return;
            }
        }
        UE_LOG(LogTemp, Error, TEXT("Game Fuse User Store Items Updated"), Attributes.Num());
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("Game Fuse User Failed to parse JSON"));
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
                UGameFuseLeaderboardEntry* NewItem = NewObject<UGameFuseLeaderboardEntry>();
            
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
                UE_LOG(LogTemp, Error, TEXT("GameFuse has failed to parse JSON Store Items"));
                return;
            }
        }
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("GameFuse Downloading Store Items Failed"));
    }
}

