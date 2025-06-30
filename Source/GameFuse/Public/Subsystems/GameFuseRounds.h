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
	/**
	 * Creates a new game round (Blueprint version)
	 * @param GameRound The game round data to create
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Create Game Round", Category = "GameFuse|Rounds")
	void BP_CreateGameRound(const FGFGameRound& GameRound, const FBP_GFApiCallback& Callback);

	/**
	 * Fetches a specific game round by ID (Blueprint version)
	 * @param RoundId The ID of the round to fetch
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Game Round", Category = "GameFuse|Rounds")
	void BP_FetchGameRound(const int32 RoundId, const FBP_GFApiCallback& Callback);

	/**
	 * Updates an existing game round (Blueprint version)
	 * @param RoundId The ID of the round to update
	 * @param GameRound Updated game round data
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Update Game Round", Category = "GameFuse|Rounds")
	void BP_UpdateGameRound(const int32 RoundId, const FGFGameRound& GameRound, const FBP_GFApiCallback& Callback);

	/**
	 * Fetches game rounds for the current user (Blueprint version)
	 * @param GameType Optional game type filter
	 * @param Page Page number for pagination
	 * @param PerPage Number of rounds per page
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch My Game Rounds", Category = "GameFuse|Rounds")
	void BP_FetchMyGameRounds(const FString& GameType, int32 Page, int32 PerPage, const FBP_GFApiCallback& Callback);

	/**
	 * Fetches game rounds for a specific user (Blueprint version)
	 * @param UserId The user ID to fetch rounds for
	 * @param GameType Optional game type filter
	 * @param Page Page number for pagination
	 * @param PerPage Number of rounds per page
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch User Game Rounds", Category = "GameFuse|Rounds")
	void BP_FetchUserGameRounds(int32 UserId, const FString& GameType, int32 Page, int32 PerPage, const FBP_GFApiCallback& Callback);

	/**
	 * Deletes a game round (Blueprint version)
	 * @param RoundId The ID of the round to delete
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Delete Game Round", Category = "GameFuse|Rounds")
	void BP_DeleteGameRound(const int32 RoundId, const FBP_GFApiCallback& Callback);

	// C++ callable functions with typed callbacks
	/**
	 * Creates a new game round
	 * @param GameRound The game round data to create
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid CreateGameRound(const FGFGameRound& GameRound, FGFGameRoundCallback TypedCallback);
	
	/**
	 * Creates a new game round with specific user data
	 * @param GameRound The game round data to create
	 * @param UserData User data for authentication
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid CreateGameRound(const FGFGameRound& GameRound, const FGFUserData& UserData, FGFGameRoundCallback TypedCallback);
	
	/**
	 * Fetches a specific game round by ID
	 * @param RoundId The ID of the round to fetch
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid FetchGameRound(const int32 RoundId, FGFGameRoundCallback TypedCallback);
	
	/**
	 * Updates an existing game round
	 * @param RoundId The ID of the round to update
	 * @param GameRound Updated game round data
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid UpdateGameRound(const int32 RoundId, const FGFGameRound& GameRound, FGFGameRoundCallback TypedCallback);
	
	/**
	 * Fetches game rounds for the current user
	 * @param TypedCallback Callback executed when the request completes
	 * @param GameType Optional game type filter
	 * @param Page Page number for pagination
	 * @param PerPage Number of rounds per page
	 * @return Request ID for tracking
	 */
	FGuid FetchMyGameRounds(FGFGameRoundListCallback TypedCallback, const FString& GameType = "", int32 Page = 0, int32 PerPage = 0);
	
	/**
	 * Fetches game rounds for a specific user
	 * @param UserId The user ID to fetch rounds for
	 * @param TypedCallback Callback executed when the request completes
	 * @param GameType Optional game type filter
	 * @param Page Page number for pagination
	 * @param PerPage Number of rounds per page
	 * @return Request ID for tracking
	 */
	FGuid FetchUserGameRounds(int32 UserId, FGFGameRoundListCallback TypedCallback, const FString& GameType = "", int32 Page = 0, int32 PerPage = 0);
	
	/**
	 * Deletes a game round
	 * @param RoundId The ID of the round to delete
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid DeleteGameRound(const int32 RoundId, FGFGameRoundActionCallback TypedCallback);

	// Getters for cached data
	/**
	 * Gets the cached list of user game rounds
	 * @return The last fetched user game rounds
	 */
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	const TArray<FGFGameRound>& GetUserRounds() const
	{
		return UserGameRounds;
	}

	/**
	 * Gets the request handler for direct API access
	 * @return Pointer to the rounds API handler
	 */
	TObjectPtr<URoundsAPIHandler> GetRequestHandler() const
	{
		return RequestHandler;
	}

	/**
	 * Clears all cached rounds data
	 */
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
	/**
	 * Handles responses for single game round operations
	 * @param Response The API response to process
	 */
	void HandleGameRoundResponse(FGFAPIResponse Response);
	
	/**
	 * Handles responses for fetching current user's game rounds
	 * @param Response The API response to process
	 */
	void HandleMyGameRoundListResponse(FGFAPIResponse Response);
	
	/**
	 * Handles responses for fetching specific user's game rounds
	 * @param Response The API response to process
	 */
	void HandleUserGameRoundListResponse(FGFAPIResponse Response);
	
	/**
	 * Handles responses for delete operations
	 * @param Response The API response to process
	 */
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