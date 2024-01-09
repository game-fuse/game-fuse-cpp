/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */


#include "Models/UserAPIManager.h"

#include "Models/Utilities.h"
#include "Unix/UnixPlatformHttp.h"



void UUserAPIManager::SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, const int InGameId, const FString& InToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/users?email=%s&password=%s&password_confirmation=%s&username=%s&game_id=%d&game_token=%s")
	, *BaseURL, *Email, *Password, *PasswordConfirmation, *Username, InGameId, *InToken);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Sending Static Request - Signing Up"));

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("POST");
    
	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});
	
	RequestManager->ProcessRequest();
}

void UUserAPIManager::SignIn(const FString& Email, const FString& Password, const int InGameId, const FString& InToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/sessions?email=%s&password=%s&game_id=%d&game_token=%s")
   , *BaseURL, *Email, *Password, InGameId, *InToken);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Sending Static Request - Signing In"));
	
	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("POST");
    
	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::AddCredits(const int AddCredits, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/add_credits?authentication_token=%s&credits=%d")
		, *BaseURL, Id, *AuthenticationToken, AddCredits);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Adding Credits: %d"), AddCredits);

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("POST");

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::SetCredits(const int SetCredits, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/set_credits?authentication_token=%s&credits=%d")
		, *BaseURL, Id, *AuthenticationToken, SetCredits);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Setting Credits: %d"), SetCredits);

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("POST");

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::AddScore(const int AddScore, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/add_score?authentication_token=%s&score=%d")
		, *BaseURL, Id, *AuthenticationToken, AddScore);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Adding Scores: %d"), AddScore);

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("POST");

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::SetScore(const int SetScore, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/set_score?authentication_token=%s&score=%d")
		, *BaseURL, Id, *AuthenticationToken, SetScore);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Setting Scores: %d"), SetScore);

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("POST");

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::SetAttribute(const FString& SetKey, const FString& SetValue, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/add_game_user_attribute?authentication_token=%s&key=%s&value=%s")
		, *BaseURL, Id, *AuthenticationToken, *SetKey, *SetValue);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Setting Attribute: %s : %s"), *SetKey, *SetValue);
    
	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("POST");

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::SyncLocalAttributes(const TMap<FString, FString>& DirtyAttributes, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString Json_Dirty_Attributes = GameFuseUtilities::MakeStrRequestBody(AuthenticationToken, "attributes", DirtyAttributes);

	const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/add_game_user_attribute")
	, *BaseURL, Id);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Syncing All Local Dirty Attributes: %s, %s"), *Json_Dirty_Attributes, *AuthenticationToken);
    
	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("POST");
	RequestManager->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	RequestManager->SetContentAsString(Json_Dirty_Attributes);
	RequestManager->SetHeader(TEXT("authentication_token"), *AuthenticationToken);

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::RemoveAttribute(const FString& SetKey, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/remove_game_user_attributes?authentication_token=%s&key=%s")
		, *BaseURL, Id, *AuthenticationToken, *SetKey);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Removing Attribute: %s"), *SetKey);
    
	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::PurchaseStoreItem(const int StoreItemId, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/purchase_game_user_store_item?authentication_token=%s&store_item_id=%d")
			, *BaseURL, Id, *AuthenticationToken, StoreItemId);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Purchasing Store Item: %d"), StoreItemId);
    
	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("POST");

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::RemoveStoreItem(const int StoreItemId, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/purchase_game_user_store_item?authentication_token=%s&store_item_id=%d")
		, *BaseURL, Id, *AuthenticationToken, StoreItemId);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Removing Store Item: %d"), StoreItemId);
    
	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::AddLeaderboardEntry(const FString& LeaderboardName, const int OurScore, TMap<FString, FString>* ExtraAttributes, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ExtraAttributes_Encoded = FPlatformHttp::UrlEncode(GameFuseUtilities::ConvertMapToJsonStr(*ExtraAttributes));
    
	const FString ApiEndpoint = FString::Printf(
		TEXT("%s/users/%d/add_leaderboard_entry?authentication_token=%s&score=%d&leaderboard_name=%s&extra_attributes=%s")
	, *BaseURL, Id, *AuthenticationToken, OurScore, *LeaderboardName, *ExtraAttributes_Encoded);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  User Adding Leaderboard : %s : %d"), *LeaderboardName, OurScore);

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("POST");

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::ClearLeaderboardEntry(const FString& LeaderboardName, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/clear_my_leaderboard_entries?authentication_token=%s&leaderboard_name=%s")
	, *BaseURL, Id, *AuthenticationToken, *LeaderboardName);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  User Clearing Leaderboard : %s"), *LeaderboardName);
    
	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("POST");

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString OnePerUserStr = (bOnePerUser) ? TEXT("true") : TEXT("false");
	const FString ApiEndpoint = FString::Printf(
		TEXT("%s/users/%d/leaderboard_entries?authentication_token=%s&limit=%d&one_per_user=%s")
		, *BaseURL, Id, *AuthenticationToken, Limit, *OnePerUserStr);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Fetching My Leaderboard : %d : %s"), Limit, *OnePerUserStr);
    
	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::FetchAttributes(bool bChainedFromLogin, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/game_user_attributes?authentication_token=%s")
		, *BaseURL, Id, *AuthenticationToken);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  User Fetching Attributes"));

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}

void UUserAPIManager::FetchPurchaseStoreItems(bool bChainedFromLogin, const int Id, const FString& AuthenticationToken, const FGameFuseAPIResponseCallback& APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/users/%d/game_user_store_items?authentication_token=%s")
		, *BaseURL, Id, *AuthenticationToken);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  User Fetching Purchased Store Items"));

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindLambda([APICompletionCallback](FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
	{
		UHTTPResponseManager::OnHttpResponseReceivedManager(Request, Response, bWasSuccessful);
		const FString ResponseStr = Response->GetContentAsString();
		const int32 ResponseCode = Response->GetResponseCode();
		const bool bSuccess = (ResponseCode == 200);
		APICompletionCallback.Execute(bSuccess, ResponseStr);
	});

	RequestManager->ProcessRequest();
}
