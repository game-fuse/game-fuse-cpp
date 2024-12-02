// Fill out your copyright notice in the Description page of Project Settings.


#include "API/UserAPIHandler.h"
#include "Library/GameFuseLog.h"
#include "Library/GameFuseUtilities.h"

void UUserAPIHandler::SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, const int InGameId, const FString& InToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/users?email=%s&password=%s&password_confirmation=%s&username=%s&game_id=%d&game_token=%s")
	                                            , *Email, *Password, *PasswordConfirmation, *Username, InGameId, *InToken);

	UE_LOG(LogGameFuse, Verbose, TEXT("Sending Static Request - Signing Up"));
	SendRequest(ApiEndpoint, "POST", Callback);
	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("POST");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::SignIn(const FString& Email, const FString& Password, const int InGameId, const FString& InToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/sessions?email=%s&password=%s&game_id=%d&game_token=%s")
	                                            , *Email, *Password, InGameId, *InToken);

	UE_LOG(LogGameFuse, Verbose, TEXT("Sending Static Request - Signing In"));

	SendRequest(ApiEndpoint, "POST", Callback);
	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("POST");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::AddCredits(const int AddCredits, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_credits?authentication_token=%s&credits=%d")
	                                            , Id, *AuthenticationToken, AddCredits);

	UE_LOG(LogGameFuse, Verbose, TEXT("Adding Credits: %d"), AddCredits);
	SendRequest(ApiEndpoint, "POST", Callback);
	//
	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("POST");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::SetCredits(const int SetCredits, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/set_credits?authentication_token=%s&credits=%d")
	                                            , Id, *AuthenticationToken, SetCredits);

	UE_LOG(LogGameFuse, Verbose, TEXT("Setting Credits: %d"), SetCredits);
	SendRequest(ApiEndpoint, "POST", Callback);

	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("POST");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::AddScore(const int AddScore, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_score?authentication_token=%s&score=%d")
	                                            , Id, *AuthenticationToken, AddScore);

	UE_LOG(LogGameFuse, Verbose, TEXT("Adding Scores: %d"), AddScore);
	SendRequest(ApiEndpoint, "POST", Callback);

	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("POST");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::SetScore(const int SetScore, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/set_score?authentication_token=%s&score=%d")
	                                            , Id, *AuthenticationToken, SetScore);

	UE_LOG(LogGameFuse, Verbose, TEXT("Setting Scores: %d"), SetScore);
	SendRequest(ApiEndpoint, "POST", Callback);
	//
	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("POST");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::SetAttribute(const FString& SetKey, const FString& SetValue, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_game_user_attribute?authentication_token=%s&key=%s&value=%s")
	                                            , Id, *AuthenticationToken, *SetKey, *SetValue);

	UE_LOG(LogGameFuse, Verbose, TEXT("Setting Attribute: %s : %s"), *SetKey, *SetValue);
	SendRequest(ApiEndpoint, "POST", Callback);

	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("POST");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::SyncLocalAttributes(const TMap<FString, FString>& DirtyAttributes, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	const FString Json_Dirty_Attributes = GameFuseUtilities::MakeStrRequestBody(AuthenticationToken, "attributes", DirtyAttributes);

	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/add_game_user_attribute")
	                                            , Id);

	UE_LOG(LogGameFuse, Verbose, TEXT("Syncing All Local Dirty Attributes: %s, %s"), *Json_Dirty_Attributes, *AuthenticationToken);

	SendRequest(ApiEndpoint, "POST", Callback);

	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("POST");
	// RequestManager->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	// RequestManager->SetContentAsString(Json_Dirty_Attributes);
	// RequestManager->SetHeader(TEXT("authentication_token"), *AuthenticationToken);
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::RemoveAttribute(const FString& SetKey, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/remove_game_user_attributes?authentication_token=%s&key=%s")
	                                            , Id, *AuthenticationToken, *SetKey);

	UE_LOG(LogGameFuse, Verbose, TEXT("Removing Attribute: %s"), *SetKey);

	SendRequest(ApiEndpoint, "GET", Callback);
	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("GET");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::PurchaseStoreItem(const int StoreItemId, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/purchase_game_user_store_item?authentication_token=%s&store_item_id=%d")
	                                            , Id, *AuthenticationToken, StoreItemId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Purchasing Store Item: %d"), StoreItemId);

	SendRequest(ApiEndpoint, "POST", Callback);
	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("POST");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::RemoveStoreItem(const int StoreItemId, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/remove_game_user_store_item?authentication_token=%s&store_item_id=%d")
	                                            , Id, *AuthenticationToken, StoreItemId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Removing Store Item: %d"), StoreItemId);

	SendRequest(ApiEndpoint, "GET", Callback);
	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("GET");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::AddLeaderboardEntry(const FString& LeaderboardName, const int OurScore, TMap<FString, FString>* ExtraAttributes, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	FString ExtraAttributesStr = "";


	if (ExtraAttributes != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("TODO:: FIX EXTRA ATTRIBUTE ENCODING"))
		//TODO:: find cross platform way to encode Attribs
		const FString ExtraAttributes_Encoded = ""; //FPlatformHttp::UrlEncode(GameFuseUtilities::ConvertMapToJsonStr(*ExtraAttributes));
		ExtraAttributesStr = FString::Printf(TEXT("&extra_attributes=%s"), *ExtraAttributes_Encoded);
	}

	const FString ApiEndpoint = FString::Printf(
	TEXT("/users/%d/add_leaderboard_entry?authentication_token=%s&score=%d&leaderboard_name=%s%s")
	, Id, *AuthenticationToken, OurScore, *LeaderboardName, *ExtraAttributesStr);

	UE_LOG(LogGameFuse, Verbose, TEXT("User Adding Leaderboard : %s : %d"), *LeaderboardName, OurScore);

	SendRequest(ApiEndpoint, "POST", Callback);
	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("POST");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::ClearLeaderboardEntry(const FString& LeaderboardName, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/clear_my_leaderboard_entries?authentication_token=%s&leaderboard_name=%s")
	                                            , Id, *AuthenticationToken, *LeaderboardName);

	UE_LOG(LogGameFuse, Verbose, TEXT("User Clearing Leaderboard : %s"), *LeaderboardName);

	SendRequest(ApiEndpoint, "POST", Callback);
	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("POST");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	const FString OnePerUserStr = (bOnePerUser) ? TEXT("true") : TEXT("false");
	const FString ApiEndpoint = FString::Printf(
	TEXT("/users/%d/leaderboard_entries?authentication_token=%s&limit=%d&one_per_user=%s")
	, Id, *AuthenticationToken, Limit, *OnePerUserStr);

	UE_LOG(LogGameFuse, Verbose, TEXT("Fetching My Leaderboard : %d : %s"), Limit, *OnePerUserStr);

	SendRequest(ApiEndpoint, "GET", Callback);
	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("GET");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}


void UUserAPIHandler::FetchAttributes(bool bChainedFromLogin, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/game_user_attributes?authentication_token=%s")
	                                            , Id, *AuthenticationToken);

	UE_LOG(LogGameFuse, Verbose, TEXT("User Fetching Attributes"));

	SendRequest(ApiEndpoint, "GET", Callback);
	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("GET");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}

void UUserAPIHandler::FetchPurchaseStoreItems(bool bChainedFromLogin, const int Id, const FString& AuthenticationToken, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/users/%d/game_user_store_items?authentication_token=%s")
	                                            , Id, *AuthenticationToken);

	UE_LOG(LogGameFuse, Verbose, TEXT("User Fetching Purchased Store Items"));

	SendRequest(ApiEndpoint, "GET", Callback);
	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("GET");
	//
	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponseReceived(Callback));
	//
	// RequestManager->ProcessRequest();
}