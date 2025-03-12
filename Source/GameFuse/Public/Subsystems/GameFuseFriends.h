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
	UFUNCTION(BlueprintCallable, DisplayName = "Send Friend Request", Category = "GameFuse|Friends")
	void BP_SendFriendRequest(const FString& Username, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Accept Friend Request", Category = "GameFuse|Friends")
	void BP_AcceptFriendRequest(int32 FriendshipId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Decline Friend Request", Category = "GameFuse|Friends")
	void BP_DeclineFriendRequest(int32 FriendshipId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Cancel Friend Request", Category = "GameFuse|Friends")
	void BP_CancelFriendRequest(int32 FriendshipId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Unfriend Player", Category = "GameFuse|Friends")
	void BP_UnfriendPlayer(int32 UserId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Friendship Data", Category = "GameFuse|Friends")
	void BP_FetchFriendshipData(const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Friends List", Category = "GameFuse|Friends")
	void BP_FetchFriendsList(const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Outgoing Friend Requests", Category = "GameFuse|Friends")
	void BP_FetchOutgoingFriendRequests(const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Incoming Friend Requests", Category = "GameFuse|Friends")
	void BP_FetchIncomingFriendRequests(const FBP_GFApiCallback& Callback);

	// C++ callable functions with typed callbacks
	FGuid SendFriendRequest(const FString& Username, FGFFriendRequestCallback TypedCallback);
	FGuid AcceptFriendRequest(const int32 FriendshipId, FGFFriendActionCallback TypedCallback);
	FGuid DeclineFriendRequest(const int32 FriendshipId, FGFFriendActionCallback TypedCallback);
	FGuid CancelFriendRequest(const int32 FriendshipId, FGFFriendActionCallback TypedCallback);
	FGuid UnfriendPlayer(const int32 UserId, FGFFriendActionCallback TypedCallback);
	FGuid FetchFriendshipData(FGFFriendsCallback TypedCallback);
	FGuid FetchFriendsList(FGFFriendsCallback TypedCallback);
	FGuid FetchOutgoingFriendRequests(FGFFriendRequestsCallback TypedCallback);
	FGuid FetchIncomingFriendRequests(FGFFriendRequestsCallback TypedCallback);

	// Getters for cached data
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	const TArray<FGFUserData>& GetFriendsList() const
	{
		return FriendsList;
	}

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	const TArray<FGFFriendRequest>& GetOutgoingRequests() const
	{
		return OutgoingRequests;
	}

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	const TArray<FGFFriendRequest>& GetIncomingRequests() const
	{
		return IncomingRequests;
	}

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
	void HandleFriendshipDataResponse(FGFAPIResponse Response);
	void HandleFriendsListResponse(FGFAPIResponse Response);
	void HandleOutgoingRequestsResponse(FGFAPIResponse Response);
	void HandleIncomingRequestsResponse(FGFAPIResponse Response);
	void HandleFriendRequestResponse(FGFAPIResponse Response);
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