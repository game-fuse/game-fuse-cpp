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
#include "GameFuseLeaderboardEntry.h"
#include "GameFuseStoreItem.h"
#include "UObject/NoExportTypes.h"
#include "HttpModule.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "Containers/UnrealString.h"
#include "Kismet/KismetStringLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/WeakObjectPtr.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "GameFuseUser.generated.h"


DECLARE_DYNAMIC_DELEGATE_TwoParams(FUserCallback, bool, bSuccess, const FString&, Response);

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
        
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        FString GetAttributeValue(const FString Key) const;

    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
        TArray<UGameFuseStoreItem*>& GetPurchasedStoreItems();
        
    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
        TArray<UGameFuseLeaderboardEntry*>& GetLeaderboards();
    
    //> Sign
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
    void SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FUserCallback CompletionCallback);
		
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
    void SignIn(const FString& Email, const FString& Password, FUserCallback CompletionCallback);

    UFUNCTION(BlueprintPure, Category = "GameFuse|User")
    bool IsSignedIn() const;

    //> Action Requests
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void AddCredits(const int AddCredits, FUserCallback CompletionCallback);

    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void SetCredits(const int SetCredits, FUserCallback CompletionCallback);

    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void AddScore(const int AddScore, FUserCallback CompletionCallback);
        
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void SetScore(const int SetScore, FUserCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void SetAttribute(const FString& SetKey,const FString& SetValue, FUserCallback CompletionCallback);
        
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void RemoveAttribute(const FString& SetKey, FUserCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void PurchaseStoreItemWithId(const int StoreItemId, FUserCallback CompletionCallback);

    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void PurchaseStoreItem(const UGameFuseStoreItem* StoreItem, FUserCallback CompletionCallback);
        
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void RemoveStoreItemWithId(const int StoreItemId, FUserCallback CompletionCallback);

    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void RemoveStoreItem(const UGameFuseStoreItem* StoreItem, FUserCallback CompletionCallback);
        
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void AddLeaderboardEntry(const FString& LeaderboardName,const int OurScore, FUserCallback CompletionCallback);

    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void AddLeaderboardEntryWithAttributes(const FString& LeaderboardName, const int OurScore, TMap<FString, FString> ExtraAttributes, FUserCallback
                                 CompletionCallback);

    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void ClearLeaderboardEntry(const FString& LeaderboardName, FUserCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, FUserCallback CompletionCallback);
    
    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void FetchAttributes(bool bChainedFromLogin, FUserCallback CompletionCallback);

    UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
        void FetchPurchaseStoreItems(bool bChainedFromLogin, FUserCallback CompletionCallback);

    FString GetAuthenticationToken() const;

private:

    bool SignedIn = false;
    int32 NumberOfLogins = 0;
    FString LastLogin;
    FString AuthenticationToken;
    FString Username;
    int32 Score = 0;
    int32 Credits = 0;
    int32 Id = 0;
    TMap<FString, FString> Attributes;
    TArray<UGameFuseStoreItem*> PurchasedStoreItems;
    TArray<UGameFuseLeaderboardEntry*> LeaderboardEntries;
    TSharedRef<IHttpRequest> RequestManager = FHttpModule::Get().CreateRequest();

    //> Setters
    void SetSignInInternal(const TSharedPtr<FJsonObject>& JsonObject);
    void SetCreditsInternal(const TSharedPtr<FJsonObject>& JsonObject);
    void SetScoresInternal(const TSharedPtr<FJsonObject>& JsonObject);
    void SetAttributesInternal(const TSharedPtr<FJsonObject>& JsonObject);
    void SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject);
    void SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject);

    //> Request Manager
    void OnHttpResponseReceivedManager(FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful, FUserCallback CompletionCallback);
    
};
