/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "Models/CoreAPIHandler.h"


#include "Models/APIResponseManager.h"



void UCoreAPIHandler::SetUpGame(const FString& InGameId, const FString& InToken, const FApiCallback& Callback)
{
	FString ApiEndpoint = FString::Printf(TEXT("/games/verify?client_from_library=cpp&game_id=%s&game_token=%s"), *InGameId, *InToken);

	UE_LOG(LogGameFuse, Verbose, TEXT("Sending Static Request - Setting Up Game : %s"), *ApiEndpoint);

	SendRequest(ApiEndpoint, TEXT("GET"), Callback);
}


void UCoreAPIHandler::FetchLeaderboardEntries(const int Limit, bool bOnePerUser, const FString& LeaderboardName, const int GameId, const FString& UserAuthenticationToken, const FApiCallback& Callback)
{
	const FString OnePerUserStr = (bOnePerUser) ? TEXT("true") : TEXT("false");
	const FString ApiEndpoint = FString::Printf(
	TEXT("%s/games/%d/leaderboard_entries?authentication_token=%s&leaderboard_name=%s&limit=%d&one_per_user=%s")
	, *BaseUrl, GameId, *UserAuthenticationToken, *LeaderboardName, Limit, *OnePerUserStr);

	UE_LOG(LogGameFuse, Verbose, TEXT("Fetching Leaderboard : %s : %d"), *LeaderboardName, Limit);
	SendRequest(ApiEndpoint, TEXT("GET"), Callback);

}

void UCoreAPIHandler::SendPasswordResetEmail(const FString& Email, const int GameID, const FString& Token, const FApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("%s/games/%d/forget_password?game_token=%s&game_id=%d&email=%s")
	                                            , *BaseUrl, GameID, *Token, GameID, *Email);

	UE_LOG(LogGameFuse, Verbose, TEXT("Sending Static Request - Password Reset Email - %s "), *ApiEndpoint);
	SendRequest(ApiEndpoint, TEXT("GET"), Callback);

}

void UCoreAPIHandler::FetchGameVariables(const int GameID, const FString& Token, const FApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(
	TEXT("%s/games/fetch_game_variables.json?game_id=%d&game_token=%s"), *BaseUrl, GameID, *Token);

	UE_LOG(LogGameFuse, Verbose, TEXT("Sending Static Request - Fetching Game Variables: %s"), *ApiEndpoint);
	SendRequest(ApiEndpoint, TEXT("GET"), Callback);

}

void UCoreAPIHandler::FetchStoreItems(const int GameID, const FString& Token, const FApiCallback& Callback)
{
	FString ApiEndpoint = FString::Printf(TEXT("%s/games/store_items?game_id=%d&game_token=%s")
	                                      , *BaseUrl, GameID, *Token);

	UE_LOG(LogGameFuse, Verbose, TEXT("Sending Static Request - Fetching Store Items"));
	SendRequest(ApiEndpoint, TEXT("GET"), Callback);

}