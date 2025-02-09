// Fill out your copyright notice in the Description page of Project Settings.
#include "API/UserAPIHandler.h"

#include "GenericPlatform/GenericPlatformHttp.h"
#include "Library/GameFuseLog.h"
#include "Library/GameFuseUtilities.h"

FGuid UUserAPIHandler::SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, const int InGameId, const FString& InToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/users?game_id=%d&game_token=%s"), InGameId, *InToken);

	const TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField("email", Email);
	Body->SetStringField("username", Username);
	Body->SetStringField("password", Password);
	Body->SetStringField("password_confirmation", PasswordConfirmation);

	UE_LOG(LogGameFuse, Verbose, TEXT("Sending Static Request - Signing Up"));
	return SendRequest(ApiEndpoint, "POST", Callback, Body);
}

FGuid UUserAPIHandler::SignIn(const FString& Email, const FString& Password, const int InGameId, const FString& InToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/sessions?game_id=%d&game_token=%s"), InGameId, *InToken);

	const TSharedPtr<FJsonObject> Body = MakeShared<FJsonObject>();
	Body->SetStringField("email", Email);
	Body->SetStringField("password", Password);

	UE_LOG(LogGameFuse, Verbose, TEXT("Sending Static Request - Signing In"));

	return SendRequest(ApiEndpoint, "POST", Callback, Body);
}

FGuid UUserAPIHandler::AddCredits(const int32 Credits, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_credits"), UserData.Id);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetNumberField("credits", Credits);

	UE_LOG(LogGameFuse, Verbose, TEXT("Adding Credits: %d"), Credits);
	return SendRequest(ApiEndpoint, "POST", Callback, JsonObject);
}

FGuid UUserAPIHandler::SetCredits(const int SetCredits, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}


	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/set_credits"), UserData.Id);
	// add attributes object to body
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetNumberField("credits", SetCredits);

	UE_LOG(LogGameFuse, Verbose, TEXT("Setting Credits: %d"), SetCredits);
	return SendRequest(ApiEndpoint, "POST", Callback, JsonObject);
}

FGuid UUserAPIHandler::AddScore(const int32 Score, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_score"), UserData.Id);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetNumberField("score", Score);

	UE_LOG(LogGameFuse, Verbose, TEXT("Adding Score: %d"), Score);
	return SendRequest(ApiEndpoint, "POST", Callback, JsonObject);
}

FGuid UUserAPIHandler::SetScore(const int32 Score, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/set_score"), UserData.Id);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetNumberField("score", Score);

	UE_LOG(LogGameFuse, Verbose, TEXT("Setting Score: %d"), Score);
	return SendRequest(ApiEndpoint, "POST", Callback, JsonObject);
}

FGuid UUserAPIHandler::SetAttribute(const FString& SetKey, const FString& SetValue, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_game_user_attribute"), UserData.Id);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField("key", SetKey);
	JsonObject->SetStringField("value", SetValue);

	UE_LOG(LogGameFuse, Verbose, TEXT("Setting Attribute: %s : %s"), *SetKey, *SetValue);
	return SendRequest(ApiEndpoint, "POST", Callback, JsonObject);
}

FGuid UUserAPIHandler::SetAttributes(const TMap<FString, FString>& Attributes, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_game_user_attribute"), UserData.Id);

	// Create JSON object for batch attributes
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	TArray<TSharedPtr<FJsonValue>> AttributesArray;

	// Convert attributes map to array of key-value objects
	for (const auto& Pair : Attributes) {
		TSharedPtr<FJsonObject> AttributeObject = MakeShareable(new FJsonObject);
		AttributeObject->SetStringField("key", Pair.Key);
		AttributeObject->SetStringField("value", Pair.Value);
		AttributesArray.Add(MakeShareable(new FJsonValueObject(AttributeObject)));
	}

	JsonObject->SetArrayField("attributes", AttributesArray);

	UE_LOG(LogGameFuse, Verbose, TEXT("Setting %d attributes in batch"), Attributes.Num());
	return SendRequest(ApiEndpoint, "POST", Callback, JsonObject);
}

FGuid UUserAPIHandler::RemoveAttribute(const FString& Key, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/remove_game_user_attributes?game_user_attribute_key=%s"), UserData.Id, *Key);

	UE_LOG(LogGameFuse, Verbose, TEXT("Removing Attribute: %s"), *Key);
	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid UUserAPIHandler::PurchaseStoreItem(const int32 StoreItemId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/purchase_game_user_store_item"), UserData.Id);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetNumberField("store_item_id", StoreItemId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Purchasing Store Item: %d"), StoreItemId);
	return SendRequest(ApiEndpoint, "POST", Callback, JsonObject);
}

FGuid UUserAPIHandler::RemoveStoreItem(const int32 StoreItemId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/remove_game_user_store_item?store_item_id=%d"), UserData.Id, StoreItemId);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetNumberField("store_item_id", StoreItemId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Removing Store Item: %d"), StoreItemId);
	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid UUserAPIHandler::AddLeaderboardEntry(const FString& LeaderboardName, const int Score, const TMap<FString, FString>& Metadata, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	FGFLeaderboardEntry LeaderboardEntry;
	LeaderboardEntry.LeaderboardName = LeaderboardName;
	LeaderboardEntry.Score = Score;
	LeaderboardEntry.Metadata = Metadata;

	return AddLeaderboardEntry(LeaderboardEntry, UserData, Callback);
}

FGuid UUserAPIHandler::AddLeaderboardEntry(const FGFLeaderboardEntry& LeaderboardEntry, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);

	// Create JSON body with all parameters
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	if (GameFuseUtilities::ConvertLeaderboardItemToJson(LeaderboardEntry, JsonObject)) {
		const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_leaderboard_entry"), UserData.Id);

		UE_LOG(LogGameFuse, Verbose, TEXT("User Adding Leaderboard : %s : %d"), *LeaderboardEntry.LeaderboardName, LeaderboardEntry.Score);
		return SendRequest(ApiEndpoint, "POST", Callback, JsonObject);
	}
	return FGuid();
}

FGuid UUserAPIHandler::ClearLeaderboardEntry(const FString& LeaderboardName, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/clear_my_leaderboard_entries?leaderboard_name=%s"), UserData.Id, *LeaderboardName);

	UE_LOG(LogGameFuse, Verbose, TEXT("User Clearing Leaderboard : %s"), *LeaderboardName);
	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UUserAPIHandler::FetchMyLeaderboardEntries(const int32 Limit, bool bOnePerUser, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/leaderboard_entries?limit=%d&one_per_user=%s"),
												UserData.Id, Limit, bOnePerUser ? TEXT("true") : TEXT("false"));

	UE_LOG(LogGameFuse, Verbose, TEXT("Fetching My Leaderboard : %d : %s"), Limit, bOnePerUser ? TEXT("true") : TEXT("false"));
	return SendRequest(ApiEndpoint, "GET", Callback);
}


FGuid UUserAPIHandler::FetchAttributes(const FGFUserData& UserData, const FGFApiCallback& Callback)
{

	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/game_user_attributes"), UserData.Id);

	UE_LOG(LogGameFuse, Verbose, TEXT("User Fetching Attributes"));

	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid UUserAPIHandler::FetchPurchasedStoreItems(const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/game_user_store_items"), UserData.Id);

	UE_LOG(LogGameFuse, Verbose, TEXT("User Fetching Purchased Store Items"));

	return SendRequest(ApiEndpoint, "GET", Callback);
}