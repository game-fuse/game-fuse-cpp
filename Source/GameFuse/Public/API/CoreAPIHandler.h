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

	FGuid SetUpGame(const int InGameId, const FString& InToken, const FGFApiCallback& Callback);

	//> Action Requests

	FGuid SendPasswordResetEmail(const FString& Email, int GameID, const FString& Token, const FGFApiCallback& Callback);

	FGuid FetchLeaderboardEntries(int Limit, bool bOnePerUser, const FString& LeaderboardName, int GameId, const FString& UserAuthenticationToken, const FGFApiCallback& Callback);

	FGuid FetchGameVariables(int GameID, const FString& Token, const FGFApiCallback& Callback);

	FGuid FetchStoreItems(int GameID, const FString& Token, const FGFApiCallback& Callback);

	// UFUNCTION()
	// void OnHTTPResponseManager(bool bSuccess, FString ResponseContent, FString RequestId);


};