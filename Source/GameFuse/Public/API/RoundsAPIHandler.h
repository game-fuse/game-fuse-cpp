#pragma once

#include "CoreMinimal.h"
#include "API/APIRequestHandler.h"
#include "Library/GameFuseStructLibrary.h"
#include "RoundsAPIHandler.generated.h"

/**
 * API Handler for GameFuse Rounds functionality
 */
UCLASS()
class GAMEFUSE_API URoundsAPIHandler : public UAPIRequestHandler
{
	GENERATED_BODY()

public:

	// Create a new game round
	FGuid CreateGameRound(const FGFUserData& UserData, const FGFGameRound& GameRound, const FGFApiCallback& Callback);

	// Fetch a specific game round
	FGuid FetchGameRound(const int32 RoundId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Update a game round
	FGuid UpdateGameRound(const int32 RoundId, const FGFUserData& UserData,
	                      const FGFGameRound& GameRound, const FGFApiCallback& Callback);

	// Fetch user's game rounds
	FGuid FetchUserGameRounds(const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Delete a game round
	FGuid DeleteGameRound(const int32 RoundId, const FGFUserData& UserData, const FGFApiCallback& Callback);


};