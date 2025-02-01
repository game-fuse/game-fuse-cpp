// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "API/APIRequestHandler.h"
#include "UserAPIHandler.generated.h"

/**
 * API Handler for GameFuse User functionality
 */
UCLASS()
class GAMEFUSE_API UUserAPIHandler : public UAPIRequestHandler
{
	GENERATED_BODY()

public:

	FGuid SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, const int InGameId, const FString& InToken, const FGFApiCallback& Callback);
	FGuid SignIn(const FString& Email, const FString& Password, const int InGameId, const FString& InToken, const FGFApiCallback& Callback);

	//> User Requests
	FGuid AddCredits(const int32 Credits, const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid SetCredits(const int32 Credits, const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid AddScore(const int32 Score, const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid SetScore(const int32 Score, const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid SetAttribute(const FString& Key, const FString& Value, const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid SetAttributes(const TMap<FString, FString>& Attributes, const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid RemoveAttribute(const FString& Key, const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid PurchaseStoreItem(const int32 StoreItemId, const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid RemoveStoreItem(const int32 StoreItemId, const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid AddLeaderboardEntry(const FString& LeaderboardName, const int32 Score, const TMap<FString, FString>& Metadata, const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid AddLeaderboardEntry(const FGFLeaderboardEntry& LeaderboardEntry, const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid ClearLeaderboardEntry(const FString& LeaderboardName, const FGFUserData& UserData, const FGFApiCallback& Callback);

	//> Action Requests
	FGuid FetchMyLeaderboardEntries(const int32 Limit, bool bOnePerUser, const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid FetchAttributes(const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid FetchPurchaseStoreItems(const FGFUserData& UserData, const FGFApiCallback& Callback);

	//> Helper Functions
	// TFunction<void(FHttpRequestPtr, const FHttpResponsePtr&, bool)> HandleResponseReceived(const FGFApiCallback& Callback);
};