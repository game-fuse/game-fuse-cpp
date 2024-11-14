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

	void SetUpGame(
	/*UGameFuseAsyncAction* AsyncAction, */
	const FString& InGameId, const FString& InToken, FOnApiResponseReceived Callback);

	//> Action Requests

	void SendPasswordResetEmail(const FString& Email, const int GameID, const FString Token);

	void FetchLeaderboardEntries(const int Limit, bool bOnePerUser, const FString& LeaderboardName, const int GameId, const FString& UserAuthenticationToken);

	void FetchGameVariables(const int GameID, const FString Token);

	void FetchStoreItems(const int GameID, const FString Token);

	UFUNCTION()
	void OnHttpResponseReceivedManager(bool bSuccess, FString ResponseContent, FString RequestId);


};