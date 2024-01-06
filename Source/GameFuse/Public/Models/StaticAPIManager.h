// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "HTTPResponseManager.h"
#include "StaticAPIManager.generated.h"



/**
 * 
 */
UCLASS()
class GAMEFUSE_API UStaticAPIManager : public UHTTPResponseManager
{
	GENERATED_BODY()

public:
	
	//> Setup Game Request
	
	static void SetUpGame(const FString& InGameId, const FString& InToken, bool bSeedStore);
	
	//> Action Requests
	
	static void SendPasswordResetEmail(const FString& Email, const int GameID, const FString Token);
	
	static void FetchLeaderboardEntries(const int Limit, bool bOnePerUser, const FString& LeaderboardName, const int GameId, const FString& UserAuthenticationToken);
	
	static void FetchGameVariables(const int GameID, const FString Token);
	
	static void FetchStoreItems(const int GameID, const FString Token);
	
};
