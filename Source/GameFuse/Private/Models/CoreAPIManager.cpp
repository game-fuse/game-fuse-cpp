/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "Models/CoreAPIManager.h"


void UCoreAPIManager::SetUpGame(const FString& InGameId, const FString& InToken)
{
	FString ApiEndpoint = FString::Printf(TEXT("%s/games/verify?client_from_library=cpp&game_id=%s&game_token=%s")
	                                      , *BaseURL, *InGameId, *InToken);

	UE_LOG(LogGameFuse, Log, TEXT("Sending Static Request - Setting Up Game : %s"), *ApiEndpoint);

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHttpResponseReceivedManager);
	RequestManager->ProcessRequest();
}


void UCoreAPIManager::FetchLeaderboardEntries(const int Limit, bool bOnePerUser, const FString& LeaderboardName, const int GameId, const FString& UserAuthenticationToken)
{
	const FString OnePerUserStr = (bOnePerUser) ? TEXT("true") : TEXT("false");
	const FString ApiEndpoint = FString::Printf(
	TEXT("%s/games/%d/leaderboard_entries?authentication_token=%s&leaderboard_name=%s&limit=%d&one_per_user=%s")
	, *BaseURL, GameId, *UserAuthenticationToken, *LeaderboardName, Limit, *OnePerUserStr);

	UE_LOG(LogGameFuse, Log, TEXT("Fetching Leaderboard : %s : %d"), *LeaderboardName, Limit);

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHttpResponseReceivedManager);
	RequestManager->ProcessRequest();
}

void UCoreAPIManager::SendPasswordResetEmail(const FString& Email, const int GameID, const FString Token)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/games/%d/forget_password?game_token=%s&game_id=%d&email=%s")
	                                            , *BaseURL, GameID, *Token, GameID, *Email);

	UE_LOG(LogGameFuse, Log, TEXT("Sending Static Request - Password Reset Email - %s "), *ApiEndpoint);

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHttpResponseReceivedManager);
	RequestManager->ProcessRequest();
}

void UCoreAPIManager::FetchGameVariables(const int GameID, const FString Token)
{
	const FString ApiEndpoint = FString::Printf(
	TEXT("%s/games/fetch_game_variables.json?game_id=%d&game_token=%s"), *BaseURL, GameID, *Token);

	UE_LOG(LogGameFuse, Log, TEXT("Sending Static Request - Fetching Game Variables: %s"), *ApiEndpoint);

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHttpResponseReceivedManager);
	RequestManager->ProcessRequest();
}

void UCoreAPIManager::FetchStoreItems(const int GameID, const FString Token)
{
	FString ApiEndpoint = FString::Printf(TEXT("%s/games/store_items?game_id=%d&game_token=%s")
	                                      , *BaseURL, GameID, *Token);

	UE_LOG(LogGameFuse, Log, TEXT("Sending Static Request - Fetching Store Items"));

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHttpResponseReceivedManager);
	RequestManager->ProcessRequest();
}