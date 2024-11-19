/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */


#pragma once

#include "CoreMinimal.h"
#include "APIRequestHandler.h"
#include "Objects/GameFuseAsyncAction.h"

#include "CoreAPIHandler.generated.h"



/**
 * 
 */
UCLASS()
class GAMEFUSE_API UCoreAPIHandler : public UAPIRequestHandler
{
	GENERATED_BODY()

public:

	//> Setup Game Request

	void SetUpGame(const FString& InGameId, const FString& InToken, const FApiCallback& Callback);

	//> Action Requests

	void SendPasswordResetEmail(const FString& Email, int GameID, const FString& Token, const FApiCallback& Callback);

	void FetchLeaderboardEntries(int Limit, bool bOnePerUser, const FString& LeaderboardName, int GameId, const FString& UserAuthenticationToken, const FApiCallback& Callback);

	void FetchGameVariables(int GameID, const FString& Token, const FApiCallback& Callback);

	void FetchStoreItems(int GameID, const FString& Token, const FApiCallback& Callback);

	// UFUNCTION()
	// void OnHTTPResponseManager(bool bSuccess, FString ResponseContent, FString RequestId);


};