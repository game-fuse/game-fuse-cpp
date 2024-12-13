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

	void SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, const int InGameId, const FString& InToken, const FGFApiCallback& Callback);
	void SignIn(const FString& Email, const FString& Password, const int InGameId, const FString& InToken, const FGFApiCallback& Callback);

	//> User Requests

	void AddCredits(const int AddCredits, const FGFUserData& UserData, const FGFApiCallback& Callback);

	void SetCredits(const int SetCredits, const FGFUserData& UserData, const FGFApiCallback& Callback);

	void AddScore(const int AddScore, const FGFUserData& UserData, const FGFApiCallback& Callback);

	void SetScore(const int SetScore, const FGFUserData& UserData, const FGFApiCallback& Callback);

	void SetAttribute(const FString& SetKey, const FString& SetValue, const FGFUserData& UserData, const FGFApiCallback& Callback);

	void SyncLocalAttributes(const TMap<FString, FString>& DirtyAttributes, const FGFUserData& UserData, const FGFApiCallback& Callback);

	void RemoveAttribute(const FString& SetKey, const FGFUserData& UserData, const FGFApiCallback& Callback);

	void PurchaseStoreItem(const int StoreItemId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	void RemoveStoreItem(const int StoreItemId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	void AddLeaderboardEntry(const FString& LeaderboardName, const int OurScore, TMap<FString, FString>* ExtraAttributes, const FGFUserData& UserData, const FGFApiCallback& Callback);

	void ClearLeaderboardEntry(const FString& LeaderboardName, const FGFUserData& UserData, const FGFApiCallback& Callback);

	//> Action Requests

	void FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, const FGFUserData& UserData, const FGFApiCallback& Callback);

	void FetchAttributes(const FGFUserData& UserData, const FGFApiCallback& Callback);

	void FetchPurchaseStoreItems(const FGFUserData& UserData, const FGFApiCallback& Callback);


	//> Helper Functions
	// TFunction<void(FHttpRequestPtr, const FHttpResponsePtr&, bool)> HandleResponseReceived(const FGFApiCallback& Callback);




};