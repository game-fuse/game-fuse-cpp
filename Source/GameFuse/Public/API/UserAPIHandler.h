// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "API/APIRequestHandler.h"
#include "UserAPIHandler.generated.h"

/**
 *
 */
UCLASS()
class GAMEFUSE_API UUserAPIHandler : public UAPIRequestHandler
{
	GENERATED_BODY()

public:

	FGuid SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, const int InGameId, const FString& InToken, const FGFApiCallback& Callback);
	FGuid SignIn(const FString& Email, const FString& Password, const int InGameId, const FString& InToken, const FGFApiCallback& Callback);

	//> User Requests

	FGuid AddCredits(const int AddCredits, const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid SetCredits(const int SetCredits, const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid AddScore(const int AddScore, const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid SetScore(const int SetScore, const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid SetAttribute(const FString& SetKey, const FString& SetValue, const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid SyncLocalAttributes(const TMap<FString, FString>& DirtyAttributes, const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid RemoveAttribute(const FString& SetKey, const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid PurchaseStoreItem(const int StoreItemId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid RemoveStoreItem(const int StoreItemId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid AddLeaderboardEntry(const FString& LeaderboardName, const int OurScore, const TMap<FString, FString>& ExtraAttributes, const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid ClearLeaderboardEntry(const FString& LeaderboardName, const FGFUserData& UserData, const FGFApiCallback& Callback);

	//> Action Requests

	FGuid FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid FetchAttributes(const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid FetchPurchaseStoreItems(const FGFUserData& UserData, const FGFApiCallback& Callback);


	//> Helper Functions
	// TFunction<void(FHttpRequestPtr, const FHttpResponsePtr&, bool)> HandleResponseReceived(const FGFApiCallback& Callback);
};