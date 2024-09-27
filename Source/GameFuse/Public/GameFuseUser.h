/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#pragma once

#include "CoreMinimal.h"

#include "Subsystems/GameInstanceSubsystem.h"
#include "Objects/GameFuseLeaderboardItem.h"
#include "Objects/GameFuseStoreItem.h"

#include "Models/UserAPIManager.h"

#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"

#include "GameFuseUser.generated.h"


//TODO: update class methods.md docs to reflect this list
UCLASS()
class GAMEFUSE_API UGameFuseUser : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

    //> Subsystem Initialization and Deinitialization
    
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;

    //> Getters
    
    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
        int32 GetNumberOfLogins() const;

    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
        FString GetLastLogin() const;

    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
        FString GetUsername() const;
    
    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
        int32 GetScore() const;

    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
        int32 GetCredits() const;

    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
        TMap<FString, FString>& GetAttributes();

    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
        TArray<FString> GetAttributesKeys() const;
    
    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
        TMap<FString, FString>& GetDirtyAttributes();
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        FString GetAttributeValue(const FString Key) const;

    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
        TArray<UGameFuseStoreItem*>& GetPurchasedStoreItems();
        
    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
        TArray<UGameFuseLeaderboardItem*>& GetLeaderboards();

    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
        bool IsSignedIn() const;

    FString GetAuthenticationToken() const;
    
    //> Sign
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void SignIn(const FString& Email, const FString& Password, FGameFuseAPIResponseCallback CompletionCallback);
    
    //> Action Requests
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void AddCredits(const int AddCredits, FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void SetCredits(const int SetCredits, FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void AddScore(const int AddScore, FGameFuseAPIResponseCallback CompletionCallback);
        
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void SetScore(const int SetScore, FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void SetAttribute(const FString& SetKey,const FString& SetValue, FGameFuseAPIResponseCallback CompletionCallback);
     
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void SetAttributeLocal(const FString& SetKey,const FString& SetValue, FGameFuseAPIResponseCallback CompletionCallback);
               
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void RemoveAttribute(const FString& SetKey, FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void PurchaseStoreItemWithId(const int StoreItemId, FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void PurchaseStoreItem(const UGameFuseStoreItem* StoreItem, FGameFuseAPIResponseCallback CompletionCallback);
        
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void RemoveStoreItemWithId(const int StoreItemId, FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void RemoveStoreItem(const UGameFuseStoreItem* StoreItem, FGameFuseAPIResponseCallback CompletionCallback);
        
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void AddLeaderboardEntry(const FString& LeaderboardName,const int OurScore, FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void AddLeaderboardEntryWithAttributes(const FString& LeaderboardName, const int OurScore, TMap<FString, FString> ExtraAttributes, FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void ClearLeaderboardEntry(const FString& LeaderboardName, FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void FetchAttributes(bool bChainedFromLogin, FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void SyncLocalAttributes(FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void FetchPurchaseStoreItems(bool bChainedFromLogin, FGameFuseAPIResponseCallback CompletionCallback);
    
    UFUNCTION()
        void InternalResponseManager(bool bSuccess, const FString& ResponseStr);

private:

    int32 NumberOfLogins = 0;
    FString LastLogin;
    FString AuthenticationToken;
    FString Username;
    int32 Id = 0;
    bool SignedIn = false;
    int32 Score = 0;
    int32 Credits = 0;
    
    TMap<FString, FString> Attributes;
    TMap<FString, FString> DirtyAttributes;
    TArray<UGameFuseStoreItem*> PurchasedStoreItems;
    TArray<UGameFuseLeaderboardItem*> LeaderboardEntries;
    TSharedRef<IHttpRequest> RequestManager = FHttpModule::Get().CreateRequest();
    
    FGameFuseAPIResponseCallback* CompletionCallbackInternal;

    //> Setters
    
    void SetLoginInternal(const TSharedPtr<FJsonObject>& JsonObject);
    void SetCreditsInternal(const TSharedPtr<FJsonObject>& JsonObject);
    void SetScoresInternal(const TSharedPtr<FJsonObject>& JsonObject);
    void SetAttributesInternal(const TSharedPtr<FJsonObject>& JsonObject);
    void SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject);
    void SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject);
    

};
