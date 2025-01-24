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

UCLASS()
class GAMEFUSE_API UGameFuseFriends : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	//> Blueprint Callable Functions
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	void BP_SendFriendRequest(const FString& Username, FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	void BP_AcceptFriendRequest(int32 FriendshipId, FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	void BP_DeclineFriendRequest(int32 FriendshipId, FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	void BP_CancelFriendRequest(int32 FriendshipId, FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	void BP_UnfriendPlayer(int32 UserId, FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	void BP_FetchFriendshipData(FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	void BP_FetchFriendsList(FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	void BP_FetchOutgoingFriendRequests(FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	void BP_FetchIncomingFriendRequests(FBP_GFApiCallback Callback);

	// C++ callable functions with typed callbacks
	FGuid SendFriendRequest(const FString& Username, FGFFriendRequestCallback Callback);
	FGuid AcceptFriendRequest(int32 FriendshipId, FGFFriendActionCallback Callback);
	FGuid DeclineFriendRequest(int32 FriendshipId, FGFFriendActionCallback Callback);
	FGuid CancelFriendRequest(int32 FriendshipId, FGFFriendActionCallback Callback);
	FGuid UnfriendPlayer(int32 UserId, FGFFriendActionCallback Callback);
	FGuid FetchFriendshipData(FGFFriendsCallback Callback);
	FGuid FetchFriendsList(FGFFriendsCallback Callback);
	FGuid FetchOutgoingFriendRequests(FGFFriendRequestsCallback Callback);
	FGuid FetchIncomingFriendRequests(FGFFriendRequestsCallback Callback);

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
	static void WrapBlueprintCallback(const FBP_GFApiCallback& Callback, FGFApiCallback& InternalCallback);

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
};