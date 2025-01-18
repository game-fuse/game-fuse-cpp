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

FGuid UUserAPIHandler::AddCredits(const int AddCredits, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_credits?credits=%d"), UserData.Id, AddCredits);

	UE_LOG(LogGameFuse, Verbose, TEXT("Adding Credits: %d"), AddCredits);
	return SendRequest(ApiEndpoint, "POST", Callback);
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

FGuid UUserAPIHandler::AddScore(const int AddScore, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_score&score=%d"), UserData.Id, AddScore);

	UE_LOG(LogGameFuse, Verbose, TEXT("Adding Scores: %d"), AddScore);
	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UUserAPIHandler::SetScore(const int SetScore, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}


	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/set_score&score=%d"), UserData.Id, SetScore);

	UE_LOG(LogGameFuse, Verbose, TEXT("Setting Scores: %d"), SetScore);
	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UUserAPIHandler::SetAttribute(const FString& SetKey, const FString& SetValue, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_game_user_attribute"), UserData.Id); //&key=%s&value=%s"), UserData.Id, *SetKey, *SetValue);

	// add attributes object to body
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetStringField("key", SetKey);
	JsonObject->SetStringField("value", SetValue);


	UE_LOG(LogGameFuse, Verbose, TEXT("Setting Attribute: %s : %s"), *SetKey, *SetValue);
	return SendRequest(ApiEndpoint, "POST", Callback, JsonObject);
}

FGuid UUserAPIHandler::SyncLocalAttributes(const TMap<FString, FString>& DirtyAttributes, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);
	// add dirty attrs to json object
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	JsonObject->SetObjectField(TEXT("attributes"), GameFuseUtilities::ConvertMapToJsonObject(DirtyAttributes));


	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/game_user_attributes"), UserData.Id);

	UE_LOG(LogGameFuse, Verbose, TEXT("Syncing All Local Dirty Attributes"));

	return SendRequest(ApiEndpoint, "GET", Callback, JsonObject);
}

FGuid UUserAPIHandler::RemoveAttribute(const FString& SetKey, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/remove_game_user_attributes?key=%s"), UserData.Id, *SetKey);

	UE_LOG(LogGameFuse, Verbose, TEXT("Removing Attribute: %s"), *SetKey);

	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid UUserAPIHandler::PurchaseStoreItem(const int StoreItemId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/purchase_game_user_store_item?store_item_id=%d"), UserData.Id, StoreItemId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Purchasing Store Item: %d"), StoreItemId);

	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UUserAPIHandler::RemoveStoreItem(const int StoreItemId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/remove_game_user_store_item?store_item_id=%d"), UserData.Id, StoreItemId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Removing Store Item: %d"), StoreItemId);

	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid UUserAPIHandler::AddLeaderboardEntry(const FString& LeaderboardName, const int OurScore, const TMap<FString, FString>& ExtraAttributes, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	// json body
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	if (ExtraAttributes.Num() > 0) {
		JsonObject->SetObjectField(TEXT("extra_attributes"), GameFuseUtilities::ConvertMapToJsonObject(ExtraAttributes));
	}

	// !! convert JsonObject to string, this is inconsistent with GameRounds::MetaData, essentially the same thing
	const FString& EncodedAttribStr = FGenericPlatformHttp::UrlEncode(GameFuseUtilities::ConvertMapToJsonStr(ExtraAttributes));
	const FString ApiEndpoint = FString::Printf(
	TEXT("/users/%d/add_leaderboard_entry?score=%d&leaderboard_name=%s&extra_attributes=%s"), UserData.Id, OurScore, *LeaderboardName, *EncodedAttribStr);

	UE_LOG(LogGameFuse, Verbose, TEXT("User Adding Leaderboard : %s : %d"), *LeaderboardName, OurScore);
	// !! replace with json object when endpoint accepts json body data
	return SendRequest(ApiEndpoint, "POST", Callback); //, JsonObject);
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

FGuid UUserAPIHandler::FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);
	const FString OnePerUserStr = (bOnePerUser) ? TEXT("true") : TEXT("false");
	const FString ApiEndpoint = FString::Printf(
	TEXT("/users/%d/leaderboard_entries?limit=%d&one_per_user=%s"), UserData.Id, Limit, *OnePerUserStr);

	UE_LOG(LogGameFuse, Verbose, TEXT("Fetching My Leaderboard : %d : %s"), Limit, *OnePerUserStr);

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

FGuid UUserAPIHandler::FetchPurchaseStoreItems(const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/game_user_store_items"), UserData.Id);

	UE_LOG(LogGameFuse, Verbose, TEXT("User Fetching Purchased Store Items"));

	return SendRequest(ApiEndpoint, "GET", Callback);
}