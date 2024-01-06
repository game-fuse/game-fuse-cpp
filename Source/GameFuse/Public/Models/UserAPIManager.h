// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTPResponseManager.h"
#include "UserAPIManager.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFUSE_API UUserAPIManager : public UHTTPResponseManager
{
	GENERATED_BODY()

public:
	
	static void SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, const int InGameId, const FString& InToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
	static void SignIn(const FString& Email, const FString& Password, const int InGameId, const FString& InToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
    
	//> User Requests
 
	static void AddCredits(const int AddCredits, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
 
    static void SetCredits(const int SetCredits, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
 
    static void AddScore(const int AddScore, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
        
    static void SetScore(const int SetScore, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
    
	static void SetAttribute(const FString& SetKey, const FString& SetValue, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
	
	static void SyncLocalAttributes(const TMap<FString, FString>& DirtyAttributes, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
 
	static void RemoveAttribute(const FString& SetKey, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
	
	static void PurchaseStoreItem(const int StoreItemId, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
	
	static void RemoveStoreItem(const int StoreItemId, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
        
	static void AddLeaderboardEntry(const FString& LeaderboardName, const int OurScore, TMap<FString, FString>* ExtraAttributes, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
	
	static void ClearLeaderboardEntry(const FString& LeaderboardName, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
 
	//> Action Requests
 
	static void FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
	
	static void FetchAttributes(bool bChainedFromLogin, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
	
	static void FetchPurchaseStoreItems(bool bChainedFromLogin, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
	
};
