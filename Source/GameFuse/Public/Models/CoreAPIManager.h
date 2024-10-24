/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */


#pragma once

#include "CoreMinimal.h"
#include "APIResponseManager.h"
#include "CoreAPIManager.generated.h"



/**
 * 
 */
UCLASS()
class GAMEFUSE_API UCoreAPIManager : public UHTTPResponseManager
{
	GENERATED_BODY()

public:
	
	//> Setup Game Request
	
	static void SetUpGame(const FString& InGameId, const FString& InToken);
	
	//> Action Requests
	
	static void SendPasswordResetEmail(const FString& Email, const int GameID, const FString Token);
	
	static void FetchLeaderboardEntries(const int Limit, bool bOnePerUser, const FString& LeaderboardName, const int GameId, const FString& UserAuthenticationToken);
	
	static void FetchGameVariables(const int GameID, const FString Token);
	
	static void FetchStoreItems(const int GameID, const FString Token);
	
};
