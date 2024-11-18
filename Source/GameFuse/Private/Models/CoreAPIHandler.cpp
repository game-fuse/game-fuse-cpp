/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "Models/CoreAPIHandler.h"

#include "GameFuseManager.h"
#include "Models/APIResponseManager.h"
#include "Models/GameFuseUtilities.h"
#include "Objects/GameFuseAsyncAction.h"


void UCoreAPIHandler::SetUpGame(const FString& InGameId, const FString& InToken, FOnApiResponseReceived Callback)
{
	FString ApiEndpoint = FString::Printf(TEXT("/games/verify?client_from_library=cpp&game_id=%s&game_token=%s"), *InGameId, *InToken);

	UE_LOG(LogGameFuse, Log, TEXT("Sending Static Request - Setting Up Game : %s"), *ApiEndpoint);

	// Callback.BindDynamic(this, &ThisClass::OnHTTPResponseManager);

	SendRequest(ApiEndpoint, TEXT("GET"), Callback);

	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("GET");
	//
	// RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHTTPResponseManager);
	// RequestManager->ProcessRequest();
}


void UCoreAPIHandler::FetchLeaderboardEntries(const int Limit, bool bOnePerUser, const FString& LeaderboardName, const int GameId, const FString& UserAuthenticationToken, FOnApiResponseReceived Callback)
{
	const FString OnePerUserStr = (bOnePerUser) ? TEXT("true") : TEXT("false");
	const FString ApiEndpoint = FString::Printf(
	TEXT("%s/games/%d/leaderboard_entries?authentication_token=%s&leaderboard_name=%s&limit=%d&one_per_user=%s")
	, *BaseUrl, GameId, *UserAuthenticationToken, *LeaderboardName, Limit, *OnePerUserStr);

	UE_LOG(LogGameFuse, Log, TEXT("Fetching Leaderboard : %s : %d"), *LeaderboardName, Limit);
	SendRequest(ApiEndpoint, TEXT("GET"), Callback);
	// Callback.BindDynamic(this, &ThisClass::OnHTTPResponseManager);


	// RequestManager->SetURL(ApiEndpoint);
	// RequestManageru->SetVerb("GET");
	//
	// RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHTTPResponseManager);
	// RequestManager->ProcessRequest();
}

void UCoreAPIHandler::SendPasswordResetEmail(const FString& Email, const int GameID, const FString Token, FOnApiResponseReceived Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/games/%d/forget_password?game_token=%s&game_id=%d&email=%s")
	                                            , *BaseUrl, GameID, *Token, GameID, *Email);

	UE_LOG(LogGameFuse, Log, TEXT("Sending Static Request - Password Reset Email - %s "), *ApiEndpoint);

	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("GET");
	//
	// RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHTTPResponseManager);
	// RequestManager->ProcessRequest();
}

void UCoreAPIHandler::FetchGameVariables(const int GameID, const FString Token, FOnApiResponseReceived Callback)
{
	const FString ApiEndpoint = FString::Printf(
	TEXT("%s/games/fetch_game_variables.json?game_id=%d&game_token=%s"), *BaseUrl, GameID, *Token);

	UE_LOG(LogGameFuse, Log, TEXT("Sending Static Request - Fetching Game Variables: %s"), *ApiEndpoint);

	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("GET");
	//
	// RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHTTPResponseManager);
	// RequestManager->ProcessRequest();
}

void UCoreAPIHandler::FetchStoreItems(const int GameID, const FString Token, FOnApiResponseReceived Callback)
{
	FString ApiEndpoint = FString::Printf(TEXT("%s/games/store_items?game_id=%d&game_token=%s")
	                                      , *BaseUrl, GameID, *Token);

	UE_LOG(LogGameFuse, Log, TEXT("Sending Static Request - Fetching Store Items"));

	// RequestManager->SetURL(ApiEndpoint);
	// RequestManager->SetVerb("GET");
	//
	// RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHTTPResponseManager);
	// RequestManager->ProcessRequest();
}

//
// void UCoreAPIHandler::OnHTTPResponseManager(bool bSuccess, FString ResponseContent, FString RequestId)
// {
//
//
// 	UE_LOG(LogGameFuse, Log, TEXT("Core API Response Received: %i"), bSuccess);
// }