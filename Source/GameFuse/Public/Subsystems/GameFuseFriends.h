#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Library/GameFuseStructLibrary.h"
#include "API/FriendsAPIHandler.h"

#include "GameFuseFriends.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnFriendshipDataResponseNative, const TArray<FGFUserData>&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFriendRequestsResponseNative, const TArray<FGFFriendRequest>&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFriendRequestResponseNative, const FGFFriendRequest&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFriendActionResponseNative, bool);

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
	void BP_GetFriendshipData(FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	void BP_GetFriendsList(FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	void BP_GetOutgoingFriendRequests(FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Friends")
	void BP_GetIncomingFriendRequests(FBP_GFApiCallback Callback);

	// C++ callable functions
	FGuid SendFriendRequest(const FString& Username, FGFApiCallback Callback);
	FGuid AcceptFriendRequest(int32 FriendshipId, FGFApiCallback Callback);
	FGuid DeclineFriendRequest(int32 FriendshipId, FGFApiCallback Callback);
	FGuid CancelFriendRequest(int32 FriendshipId, FGFApiCallback Callback);
	FGuid UnfriendPlayer(int32 UserId, FGFApiCallback Callback);
	FGuid GetFriendshipData(FGFApiCallback Callback);
	FGuid GetFriendsList(FGFApiCallback Callback);
	FGuid GetOutgoingFriendRequests(FGFApiCallback Callback);
	FGuid GetIncomingFriendRequests(FGFApiCallback Callback);

	// Native delegates for response handling
	FOnFriendshipDataResponseNative OnFriendsListResponse;
	FOnFriendRequestsResponseNative OnOutgoingRequestsResponse;
	FOnFriendRequestsResponseNative OnIncomingRequestsResponse;
	FOnFriendRequestResponseNative OnFriendRequestResponse;
	FOnFriendActionResponseNative OnFriendActionResponse;

	TObjectPtr<UAPIRequestHandler> GetRequestHandler()
	{
		return RequestHandler;
	}

	// Getters for cached data
	UFUNCTION(BlueprintPure, Category = "GameFuse|Friends")
	const TArray<FGFUserData>& GetFriends() const
	{
		return Friends;
	}

	UFUNCTION(BlueprintPure, Category = "GameFuse|Friends")
	const TArray<FGFFriendRequest>& GetOutgoingRequests() const
	{
		return OutgoingRequests;
	}

	UFUNCTION(BlueprintPure, Category = "GameFuse|Friends")
	const TArray<FGFFriendRequest>& GetIncomingRequests() const
	{
		return IncomingRequests;
	}


private:

	TObjectPtr<UFriendsAPIHandler> RequestHandler;
	static void WrapBlueprintCallback(const FBP_GFApiCallback& Callback, FGFApiCallback& InternalCallback);

	// Cached friendship data
	TArray<FGFUserData> Friends;
	TArray<FGFFriendRequest> OutgoingRequests;
	TArray<FGFFriendRequest> IncomingRequests;

	// Internal response handlers
	void HandleFriendshipDataResponse(FGFAPIResponse Response);
	void HandleFriendsListResponse(FGFAPIResponse Response);
	void HandleOutgoingRequestsResponse(FGFAPIResponse Response);
	void HandleIncomingRequestsResponse(FGFAPIResponse Response);
	void HandleFriendRequestResponse(FGFAPIResponse Response);
	void HandleFriendActionResponse(FGFAPIResponse Response);
};