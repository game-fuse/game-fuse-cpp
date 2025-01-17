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

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_credits?authentication_token=%s&credits=%d"), UserData.Id, *UserData.AuthenticationToken, AddCredits);

	UE_LOG(LogGameFuse, Verbose, TEXT("Adding Credits: %d"), AddCredits);
	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UUserAPIHandler::SetCredits(const int SetCredits, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/set_credits?authentication_token=%s&credits=%d"), UserData.Id, *UserData.AuthenticationToken, SetCredits);

	UE_LOG(LogGameFuse, Verbose, TEXT("Setting Credits: %d"), SetCredits);
	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UUserAPIHandler::AddScore(const int AddScore, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_score?authentication_token=%s&score=%d"), UserData.Id, *UserData.AuthenticationToken, AddScore);

	UE_LOG(LogGameFuse, Verbose, TEXT("Adding Scores: %d"), AddScore);
	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UUserAPIHandler::SetScore(const int SetScore, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/set_score?authentication_token=%s&score=%d"), UserData.Id, *UserData.AuthenticationToken, SetScore);

	UE_LOG(LogGameFuse, Verbose, TEXT("Setting Scores: %d"), SetScore);
	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UUserAPIHandler::SetAttribute(const FString& SetKey, const FString& SetValue, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_game_user_attribute?authentication_token=%s&key=%s&value=%s"), UserData.Id, *UserData.AuthenticationToken, *SetKey, *SetValue);

	UE_LOG(LogGameFuse, Verbose, TEXT("Setting Attribute: %s : %s"), *SetKey, *SetValue);
	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UUserAPIHandler::SyncLocalAttributes(const TMap<FString, FString>& DirtyAttributes, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	const FString Json_Dirty_Attributes = GameFuseUtilities::MakeStrRequestBody(UserData.AuthenticationToken, "attributes", DirtyAttributes);

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_game_user_attribute"), UserData.Id);

	UE_LOG(LogGameFuse, Verbose, TEXT("Syncing All Local Dirty Attributes: %s, %s"), *Json_Dirty_Attributes, *UserData.AuthenticationToken);

	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UUserAPIHandler::RemoveAttribute(const FString& SetKey, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/remove_game_user_attributes?authentication_token=%s&key=%s"), UserData.Id, *UserData.AuthenticationToken, *SetKey);

	UE_LOG(LogGameFuse, Verbose, TEXT("Removing Attribute: %s"), *SetKey);

	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid UUserAPIHandler::PurchaseStoreItem(const int StoreItemId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/purchase_game_user_store_item?authentication_token=%s&store_item_id=%d"), UserData.Id, *UserData.AuthenticationToken, StoreItemId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Purchasing Store Item: %d"), StoreItemId);

	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UUserAPIHandler::RemoveStoreItem(const int StoreItemId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/remove_game_user_store_item?authentication_token=%s&store_item_id=%d"), UserData.Id, *UserData.AuthenticationToken, StoreItemId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Removing Store Item: %d"), StoreItemId);

	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid UUserAPIHandler::AddLeaderboardEntry(const FString& LeaderboardName, const int OurScore, const TMap<FString, FString>& ExtraAttributes, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	// json body
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);
	if (ExtraAttributes.Num() > 0) {
		JsonObject->SetObjectField(TEXT("extra_attributes"), GameFuseUtilities::ConvertMapToJsonObject(ExtraAttributes));
	}

	// !! convert JsonObject to string, this is inconsistent with GameRounds::MetaData, essentially the same thing
	const FString& EncodedAttribStr = FGenericPlatformHttp::UrlEncode(GameFuseUtilities::ConvertMapToJsonStr(ExtraAttributes));
	const FString ApiEndpoint = FString::Printf(
	TEXT("/users/%d/add_leaderboard_entry?authentication_token=%s&score=%d&leaderboard_name=%s&extra_attributes=%s"), UserData.Id, *UserData.AuthenticationToken, OurScore, *LeaderboardName, *EncodedAttribStr);

	UE_LOG(LogGameFuse, Verbose, TEXT("User Adding Leaderboard : %s : %d"), *LeaderboardName, OurScore);
	// !! replace with json object when endpoint accepts json body data
	return SendRequest(ApiEndpoint, "POST", Callback); //, JsonObject);
}

FGuid UUserAPIHandler::ClearLeaderboardEntry(const FString& LeaderboardName, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/clear_my_leaderboard_entries?authentication_token=%s&leaderboard_name=%s"), UserData.Id, *UserData.AuthenticationToken, *LeaderboardName);

	UE_LOG(LogGameFuse, Verbose, TEXT("User Clearing Leaderboard : %s"), *LeaderboardName);

	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UUserAPIHandler::FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	const FString OnePerUserStr = (bOnePerUser) ? TEXT("true") : TEXT("false");
	const FString ApiEndpoint = FString::Printf(
	TEXT("/users/%d/leaderboard_entries?authentication_token=%s&limit=%d&one_per_user=%s"), UserData.Id, *UserData.AuthenticationToken, Limit, *OnePerUserStr);

	UE_LOG(LogGameFuse, Verbose, TEXT("Fetching My Leaderboard : %d : %s"), Limit, *OnePerUserStr);

	return SendRequest(ApiEndpoint, "GET", Callback);
}


FGuid UUserAPIHandler::FetchAttributes(const FGFUserData& UserData, const FGFApiCallback& Callback)
{

	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/game_user_attributes?authentication_token=%s"), UserData.Id, *UserData.AuthenticationToken);

	UE_LOG(LogGameFuse, Verbose, TEXT("User Fetching Attributes"));

	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid UUserAPIHandler::FetchPurchaseStoreItems(const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/game_user_store_items?authentication_token=%s"), UserData.Id, *UserData.AuthenticationToken);

	UE_LOG(LogGameFuse, Verbose, TEXT("User Fetching Purchased Store Items"));

	return SendRequest(ApiEndpoint, "GET", Callback);
}