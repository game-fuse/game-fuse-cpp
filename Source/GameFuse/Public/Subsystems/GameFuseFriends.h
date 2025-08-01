#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Library/GameFuseStructLibrary.h"
#include "API/FriendsAPIHandler.h"

#include "GameFuseFriends.generated.h"

// Single-cast delegates for user callbacks
DECLARE_DELEGATE_OneParam(FGFFriendRequestCallback, const FGFFriendRequest&);
DECLARE_DELEGATE_OneParam(FGFFriendRequestsCallback, const TArray<FGFFriendRequest>&);
DECLARE_DELEGATE_OneParam(FGFFriendsCallback, const TArray<FGFUserData>&);
DECLARE_DELEGATE_OneParam(FGFFriendActionCallback, bool);

// Blueprint callback is now using the standard FBP_GFApiCallback

UCLASS()
class GAMEFUSE_API UGameFuseFriends : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	//> Blueprint Callable Functions
	/**
	 * Sends a friend request to a user by username (Blueprint version)
	 * @param Username The username to send the request to
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Send Friend Request", Category = "GameFuse|Friends")
	void BP_SendFriendRequest(const FString& Username, const FBP_GFApiCallback& Callback);

	/**
	 * Accepts a friend request (Blueprint version)
	 * @param FriendshipId The ID of the friendship request to accept
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Accept Friend Request", Category = "GameFuse|Friends")
	void BP_AcceptFriendRequest(int32 FriendshipId, const FBP_GFApiCallback& Callback);

	/**
	 * Declines a friend request (Blueprint version)
	 * @param FriendshipId The ID of the friendship request to decline
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Decline Friend Request", Category = "GameFuse|Friends")
	void BP_DeclineFriendRequest(int32 FriendshipId, const FBP_GFApiCallback& Callback);

	/**
	 * Cancels a sent friend request (Blueprint version)
	 * @param FriendshipId The ID of the friendship request to cancel
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Cancel Friend Request", Category = "GameFuse|Friends")
	void BP_CancelFriendRequest(int32 FriendshipId, const FBP_GFApiCallback& Callback);

	/**
	 * Removes a user from friends list (Blueprint version)
	 * @param UserId The ID of the user to unfriend
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Unfriend Player", Category = "GameFuse|Friends")
	void BP_UnfriendPlayer(int32 UserId, const FBP_GFApiCallback& Callback);

	/**
	 * Retrieves the list of friends, outgoing, and incoming friendship requests for the current user (Blueprint version)
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Friendship Data", Category = "GameFuse|Friends")
	void BP_FetchFriendshipData(const FBP_GFApiCallback& Callback);

	/**
	 * Fetches a list of all your friends (Blueprint version)
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch My Friends List", Category = "GameFuse|Friends")
	void BP_FetchMyFriendsList(const FBP_GFApiCallback& Callback);

	/**
	 * Fetches a list of all friends for a specific user (Blueprint version)
	 * @param UserId The ID of the user to fetch friends for
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch User Friends List", Category = "GameFuse|Friends")
	void BP_FetchUserFriendsList(int32 UserId, const FBP_GFApiCallback& Callback);

	/**
	 * Fetches outgoing friend requests for the current user (Blueprint version)
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Outgoing Friend Requests", Category = "GameFuse|Friends")
	void BP_FetchOutgoingFriendRequests(const FBP_GFApiCallback& Callback);

	/**
	 * Fetches incoming friend requests for the current user (Blueprint version)
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Incoming Friend Requests", Category = "GameFuse|Friends")
	void BP_FetchIncomingFriendRequests(const FBP_GFApiCallback& Callback);

	// C++ callable functions with typed callbacks
	/**
	 * Sends a friend request to a user by username
	 * @param Username The username to send the request to
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid SendFriendRequest(const FString& Username, FGFFriendRequestCallback TypedCallback);
	
	/**
	 * Accepts a friend request
	 * @param FriendshipId The ID of the friendship request to accept
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid AcceptFriendRequest(const int32 FriendshipId, FGFFriendActionCallback TypedCallback);
	
	/**
	 * Declines a friend request
	 * @param FriendshipId The ID of the friendship request to decline
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid DeclineFriendRequest(const int32 FriendshipId, FGFFriendActionCallback TypedCallback);
	
	/**
	 * Cancels a sent friend request
	 * @param FriendshipId The ID of the friendship request to cancel
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid CancelFriendRequest(const int32 FriendshipId, FGFFriendActionCallback TypedCallback);
	
	/**
	 * Removes a user from friends list
	 * @param UserId The ID of the user to unfriend
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid UnfriendPlayer(const int32 UserId, FGFFriendActionCallback TypedCallback);

	/** Retrieve the list of friends, outgoing, and incoming friendship requests for the current user. */
	FGuid FetchFriendshipData(FGFFriendsCallback TypedCallback);
	
	/** Fetch a list of all your friends */
	FGuid FetchMyFriendsList(FGFFriendsCallback TypedCallback);
	
	/** Fetch a list of all friends for a specific user */
	FGuid FetchUserFriendsList(int32 UserId, FGFFriendsCallback TypedCallback);
	
	/**
	 * Fetches outgoing friend requests for the current user
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid FetchOutgoingFriendRequests(FGFFriendRequestsCallback TypedCallback);
	
	/**
	 * Fetches incoming friend requests for the current user
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid FetchIncomingFriendRequests(FGFFriendRequestsCallback TypedCallback);

	/**
	 * Gets the cached list of friends
	 * @return The last fetched friends list
	 */
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	const TArray<FGFUserData>& GetFriendsList() const
	{
		return FriendsList;
	}

	/**
	 * Gets the cached list of outgoing friend requests
	 * @return Last fetched list of outgoing friend requests
	 */
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	const TArray<FGFFriendRequest>& GetOutgoingRequests() const
	{
		return OutgoingRequests;
	}

	/**
	 * Gets the cached list of incoming friend requests
	 * @return Last fetched list of incoming friend requests
	 */
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	const TArray<FGFFriendRequest>& GetIncomingRequests() const
	{
		return IncomingRequests;
	}

	/**
	 * Gets the request handler for direct API access
	 * @return Pointer to the friends API handler
	 */
	TObjectPtr<UFriendsAPIHandler> GetRequestHandler() const
	{
		return RequestHandler;
	}

private:

	UPROPERTY()
	TObjectPtr<UFriendsAPIHandler> RequestHandler;

	// Cached friendship data
	TArray<FGFUserData> FriendsList;
	TArray<FGFFriendRequest> OutgoingRequests;
	TArray<FGFFriendRequest> IncomingRequests;

	// Internal response handlers
	/**
	 * Handles responses for friendship data operations
	 * @param Response The API response to process
	 */
	void HandleFriendshipDataResponse(FGFAPIResponse Response);
	
	/**
	 * Handles responses for friends list operations
	 * @param Response The API response to process
	 */
	void HandleFriendsListResponse(FGFAPIResponse Response);
	
	/**
	 * Handles responses for specific user friends list operations
	 * @param Response The API response to process
	 */
	void HandleUserFriendsListResponse(FGFAPIResponse Response);
	
	/**
	 * Handles responses for outgoing friend requests
	 * @param Response The API response to process
	 */
	void HandleOutgoingRequestsResponse(FGFAPIResponse Response);
	
	/**
	 * Handles responses for incoming friend requests
	 * @param Response The API response to process
	 */
	void HandleIncomingRequestsResponse(FGFAPIResponse Response);
	
	/**
	 * Handles responses for friend request operations
	 * @param Response The API response to process
	 */
	void HandleFriendRequestResponse(FGFAPIResponse Response);
	
	/**
	 * Handles responses for friend action operations
	 * @param Response The API response to process
	 */
	void HandleFriendActionResponse(FGFAPIResponse Response);

	// User callbacks storage
	TMap<FGuid, FGFFriendRequestCallback> FriendRequestCallbacks;
	TMap<FGuid, FGFFriendRequestsCallback> FriendRequestsCallbacks;
	TMap<FGuid, FGFFriendsCallback> FriendsCallbacks;
	TMap<FGuid, FGFFriendActionCallback> FriendActionCallbacks;

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