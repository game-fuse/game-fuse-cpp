#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Library/GameFuseStructLibrary.h"
#include "API/RoundsAPIHandler.h"

#include "GameFuseRounds.generated.h"

// Single-cast delegates for user callbacks
DECLARE_DELEGATE_OneParam(FGFGameRoundCallback, const FGFGameRound&);
DECLARE_DELEGATE_OneParam(FGFGameRoundListCallback, const TArray<FGFGameRound>&);
DECLARE_DELEGATE_OneParam(FGFGameRoundActionCallback, bool);

UCLASS()
class GAMEFUSE_API UGameFuseRounds : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	//> Blueprint Callable Functions
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_CreateGameRound(const FGFGameRound& GameRound, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_FetchGameRound(const int32 RoundId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_UpdateGameRound(const int32 RoundId, const FGFGameRound& GameRound, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_FetchUserGameRounds(const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_DeleteGameRound(const int32 RoundId, const FBP_GFApiCallback& Callback);

	// C++ callable functions with typed callbacks
	FGuid CreateGameRound(const FGFGameRound& GameRound, FGFGameRoundCallback TypedCallback);
	FGuid CreateGameRound(const FGFGameRound& GameRound, const FGFUserData& UserData, FGFGameRoundCallback TypedCallback);
	FGuid FetchGameRound(const int32 RoundId, FGFGameRoundCallback TypedCallback);
	FGuid UpdateGameRound(const int32 RoundId, const FGFGameRound& GameRound, FGFGameRoundCallback TypedCallback);
	FGuid FetchUserGameRounds(FGFGameRoundListCallback TypedCallback);
	FGuid DeleteGameRound(const int32 RoundId, FGFGameRoundActionCallback TypedCallback);

	// Getters for cached data
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	const TArray<FGFGameRound>& GetUserRounds() const
	{
		return UserGameRounds;
	}

	TObjectPtr<URoundsAPIHandler> GetRequestHandler() const
	{
		return RequestHandler;
	}

	// Clear cached rounds data
	void ClearRoundsData()
	{
		UserGameRounds.Empty();
	}

private:

	UPROPERTY()
	TObjectPtr<URoundsAPIHandler> RequestHandler;

	// Cached rounds data
	TArray<FGFGameRound> UserGameRounds;

	// Internal response handlers
	void HandleGameRoundResponse(FGFAPIResponse Response);
	void HandleGameRoundListResponse(FGFAPIResponse Response);
	void HandleDeleteResponse(FGFAPIResponse Response);

	// User callbacks storage
	TMap<FGuid, FGFGameRoundCallback> GameRoundCallbacks;
	TMap<FGuid, FGFGameRoundListCallback> GameRoundListCallbacks;
	TMap<FGuid, FGFGameRoundActionCallback> GameRoundActionCallbacks;
	
	/** Map to store blueprint callbacks by request ID */
	TMap<FGuid, FBP_GFApiCallback> BlueprintCallbacks;

	/**
	 * @brief Stores the blueprint callback in the BlueprintCallbacks map
	 * @param RequestId The request ID to associate with the callback
	 * @param Callback The blueprint callback to store
	 */
	void StoreBlueprintCallback(const FGuid& RequestId, const FBP_GFApiCallback& Callback);

	/**
	 * @brief Executes the blueprint callback associated with the given request ID
	 * @param Response The API response to pass to the callback
	 */
	void ExecuteBlueprintCallback(const FGFAPIResponse& Response);
};