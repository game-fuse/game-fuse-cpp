/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */


#pragma once

#include "CoreMinimal.h"
#include "APIRequestManager.h"
#include "UserAPIManager.generated.h"

/**
 * 
 */
UCLASS()
class GAMEFUSE_API UUserAPIManager : public UAPIRequestManager
{
	GENERATED_BODY()

public:
	
	static void SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, int InGameId, const FString& InToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
	static void SignIn(const FString& Email, const FString& Password, int InGameId, const FString& InToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
    
	//> User Requests
 
	static void AddCredits(int AddCredits, int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
 
    static void SetCredits(int SetCredits, int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
 
    static void AddScore(int AddScore, int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
        
    static void SetScore(int SetScore, int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);
    
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
	
	static void FetchPurchaseStoreItems(bool bChainedFromLogin, int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback);

	//> Helper Functions
	static TFunction<void(FHttpRequestPtr, const FHttpResponsePtr&, bool)> HandleResponseReceived(UAPIRequestManager* RequestManager, const FGameFuseAPIResponseCallback& APICompletionCallback);
	
};
