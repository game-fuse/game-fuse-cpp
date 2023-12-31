// Fill out your copyright notice in the Description page of Project Settings.


#include "Models/StaticAPIManager.h"


void UStaticAPIManager::SetUpGame(const FString& InGameId, const FString& InToken, bool bSeedStore, const FGameFuseAPIResponseCallback* APICompletionCallback)
{
	FString ApiEndpoint = FString::Printf(TEXT("%s/games/verify?client_from_library=cpp&game_id=%s&game_token=%s")
		, *BaseURL, *InGameId, *InToken);
	if (bSeedStore) ApiEndpoint.Append("&seed_store=true");
    
	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Sending Static Request - Setting Up Game : %s"), *ApiEndpoint);

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHttpResponseReceivedManagerStatic, APICompletionCallback);
	RequestManager->ProcessRequest();
}

void UStaticAPIManager::FetchLeaderboardEntries(const int Limit, bool bOnePerUser, const FString& LeaderboardName,
	const int GameId, const FString& UserAuthenticationToken, const FGameFuseAPIResponseCallback* APICompletionCallback)
{
	const FString OnePerUserStr = (bOnePerUser) ? TEXT("true") : TEXT("false");
	const FString ApiEndpoint = FString::Printf(
		TEXT("%s/games/%d/leaderboard_entries?authentication_token=%s&leaderboard_name=%s&limit=%d&one_per_user=%s")
		, *BaseURL, GameId, *UserAuthenticationToken, *LeaderboardName, Limit, *OnePerUserStr);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Fetching Leaderboard : %s"), *ApiEndpoint);
	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Fetching Leaderboard : %s : %d"), *LeaderboardName, Limit);

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHttpResponseReceivedManagerStatic, APICompletionCallback);
	RequestManager->ProcessRequest();
}

void UStaticAPIManager::SendPasswordResetEmail(const FString& Email, const int GameID, const FString Token, const FGameFuseAPIResponseCallback* APICompletionCallback)
{
	FString ApiEndpoint = FString::Printf(TEXT("%s/games/%d/forget_password?game_token=%s&game_id=%d&email=%s")
	   , *BaseURL, GameID, *Token, GameID,*Email);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Sending Static Request - Password Reset Email"));

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("POST");

	RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHttpResponseReceivedManagerStatic, APICompletionCallback);
	RequestManager->ProcessRequest();
}

void UStaticAPIManager::FetchGameVariables(const int GameID, const FString Token, const FGameFuseAPIResponseCallback* APICompletionCallback)
{
	const FString ApiEndpoint = FString::Printf(
	   TEXT("%s/games/fetch_game_variables.json?game_id=%d&game_token=%s"), *BaseURL, GameID, *Token);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Sending Static Request - Fetching Game Variables: %s"), *ApiEndpoint);

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHttpResponseReceivedManagerStatic, APICompletionCallback);
	RequestManager->ProcessRequest();
}

void UStaticAPIManager::FetchStoreItems(const int GameID, const FString Token, const FGameFuseAPIResponseCallback* APICompletionCallback)
{
	FString ApiEndpoint = FString::Printf(TEXT("%s/games/store_items?game_id=%d&game_token=%s")
		, *BaseURL, GameID, *Token);

	UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  Sending Static Request - Fetching Store Items"));

	RequestManager->SetURL(ApiEndpoint);
	RequestManager->SetVerb("GET");

	RequestManager->OnProcessRequestComplete().BindStatic(&UHTTPResponseManager::OnHttpResponseReceivedManagerStatic, APICompletionCallback);
	RequestManager->ProcessRequest();
}
