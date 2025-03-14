#include "Subsystems/GameFuseFriends.h"
#include "Library/GameFuseLog.h"
#include "Subsystems/GameFuseUser.h"
#include "Library/GameFuseUtilities.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

void UGameFuseFriends::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RequestHandler = NewObject<UFriendsAPIHandler>();
}

void UGameFuseFriends::Deinitialize()
{
	Super::Deinitialize();
}

void UGameFuseFriends::StoreBlueprintCallback(const FGuid& RequestId, const FBP_GFApiCallback& Callback)
{
	if (Callback.IsBound()) {
		BlueprintCallbacks.Add(RequestId, Callback);
	}
}

void UGameFuseFriends::ExecuteBlueprintCallback(const FGFAPIResponse& Response)
{
	if (BlueprintCallbacks.Contains(Response.RequestId)) {
		BlueprintCallbacks[Response.RequestId].ExecuteIfBound(Response);
		BlueprintCallbacks.Remove(Response.RequestId);
	}
}

FGuid UGameFuseFriends::SendFriendRequest(const FString& Username, FGFFriendRequestCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to send friend request"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleFriendRequestResponse(Response);
	});

	FGuid RequestId = RequestHandler->SendFriendRequest(Username, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		FriendRequestCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseFriends::AcceptFriendRequest(const int32 FriendshipId, FGFFriendActionCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to accept friend request"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleFriendActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->RespondToFriendRequest(FriendshipId, EGFInviteRequestStatus::Accepted, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		FriendActionCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseFriends::DeclineFriendRequest(const int32 FriendshipId, FGFFriendActionCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to decline friend request"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleFriendActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->RespondToFriendRequest(FriendshipId, EGFInviteRequestStatus::Declined, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		FriendActionCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseFriends::CancelFriendRequest(const int32 FriendshipId, FGFFriendActionCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to cancel friend request"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleFriendActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->CancelFriendRequest(FriendshipId, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		FriendActionCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseFriends::UnfriendPlayer(const int32 UserId, FGFFriendActionCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to unfriend player"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleFriendActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->UnfriendPlayer(UserId, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		FriendActionCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseFriends::FetchFriendshipData(FGFFriendsCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to fetch friendship data"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleFriendshipDataResponse(Response);
	});

	FGuid RequestId = RequestHandler->GetFriendshipData(GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		FriendsCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseFriends::FetchFriendsList(FGFFriendsCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to fetch friends list"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleFriendsListResponse(Response);
	});

	FGuid RequestId = RequestHandler->GetFriendsList(GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		FriendsCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseFriends::FetchOutgoingFriendRequests(FGFFriendRequestsCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to fetch outgoing friend requests"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleOutgoingRequestsResponse(Response);
	});

	FGuid RequestId = RequestHandler->GetOutgoingFriendRequests(GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		FriendRequestsCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseFriends::FetchIncomingFriendRequests(FGFFriendRequestsCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to fetch incoming friend requests"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleIncomingRequestsResponse(Response);
	});
	FGuid RequestId = RequestHandler->GetIncomingFriendRequests(GameFuseUser->GetUserData(), InternalCallback);

	if (TypedCallback.IsBound()) {
		FriendRequestsCallbacks.Add(RequestId, TypedCallback);
	}

	return RequestId;
}

void UGameFuseFriends::HandleFriendshipDataResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle friendship data response: %s"), *Response.ResponseStr);
		if (FriendsCallbacks.Contains(Response.RequestId)) {
			FriendsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFUserData>());
			FriendsCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	// Parse friends list
	if (!GameFuseUtilities::ConvertJsonToFriendsList(FriendsList, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse friends list from friendship data"));
		if (FriendsCallbacks.Contains(Response.RequestId)) {
			FriendsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFUserData>());
			FriendsCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	// Parse outgoing requests
	if (!GameFuseUtilities::ConvertJsonToFriendRequests(OutgoingRequests, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse outgoing requests from friendship data"));
	}

	// Parse incoming requests
	if (!GameFuseUtilities::ConvertJsonToFriendRequests(IncomingRequests, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse incoming requests from friendship data"));
	}

	if (FriendsCallbacks.Contains(Response.RequestId)) {
		FriendsCallbacks[Response.RequestId].ExecuteIfBound(FriendsList);
		FriendsCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseFriends::HandleFriendsListResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle friends list response: %s"), *Response.ResponseStr);
		if (FriendsCallbacks.Contains(Response.RequestId)) {
			FriendsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFUserData>());
			FriendsCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	if (!GameFuseUtilities::ConvertJsonToFriendsList(FriendsList, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse friends list"));
		if (FriendsCallbacks.Contains(Response.RequestId)) {
			FriendsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFUserData>());
			FriendsCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	if (FriendsCallbacks.Contains(Response.RequestId)) {
		FriendsCallbacks[Response.RequestId].ExecuteIfBound(FriendsList);
		FriendsCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseFriends::HandleOutgoingRequestsResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle outgoing requests response: %s"), *Response.ResponseStr);
		if (FriendRequestsCallbacks.Contains(Response.RequestId)) {
			FriendRequestsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFFriendRequest>());
			FriendRequestsCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	if (!GameFuseUtilities::ConvertJsonToFriendRequests(OutgoingRequests, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse outgoing requests"));
		if (FriendRequestsCallbacks.Contains(Response.RequestId)) {
			FriendRequestsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFFriendRequest>());
			FriendRequestsCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	if (FriendRequestsCallbacks.Contains(Response.RequestId)) {
		FriendRequestsCallbacks[Response.RequestId].ExecuteIfBound(OutgoingRequests);
		FriendRequestsCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseFriends::HandleIncomingRequestsResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle incoming requests response: %s"), *Response.ResponseStr);
		if (FriendRequestsCallbacks.Contains(Response.RequestId)) {
			FriendRequestsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFFriendRequest>());
			FriendRequestsCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	if (!GameFuseUtilities::ConvertJsonToFriendRequests(IncomingRequests, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse incoming requests"));
		if (FriendRequestsCallbacks.Contains(Response.RequestId)) {
			FriendRequestsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFFriendRequest>());
			FriendRequestsCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	if (FriendRequestsCallbacks.Contains(Response.RequestId)) {
		FriendRequestsCallbacks[Response.RequestId].ExecuteIfBound(IncomingRequests);
		FriendRequestsCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseFriends::HandleFriendRequestResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle friend request response: %s"), *Response.ResponseStr);
		if (FriendRequestCallbacks.Contains(Response.RequestId)) {
			FriendRequestCallbacks[Response.RequestId].ExecuteIfBound(FGFFriendRequest());
			FriendRequestCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	FGFFriendRequest FriendRequest;
	if (!GameFuseUtilities::ConvertJsonToFriendRequest(FriendRequest, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse friend request"));
		if (FriendRequestCallbacks.Contains(Response.RequestId)) {
			FriendRequestCallbacks[Response.RequestId].ExecuteIfBound(FGFFriendRequest());
			FriendRequestCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	// Update cached data
	OutgoingRequests.Add(FriendRequest);

	if (FriendRequestCallbacks.Contains(Response.RequestId)) {
		FriendRequestCallbacks[Response.RequestId].ExecuteIfBound(FriendRequest);
		FriendRequestCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseFriends::HandleFriendActionResponse(FGFAPIResponse Response)
{
	if (FriendActionCallbacks.Contains(Response.RequestId)) {
		FriendActionCallbacks[Response.RequestId].ExecuteIfBound(Response.bSuccess);
		FriendActionCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseFriends::BP_SendFriendRequest(const FString& Username, const FBP_GFApiCallback& Callback)
{
	FGFFriendRequestCallback TypedCallback;
	FGuid RequestId = SendFriendRequest(Username, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseFriends::BP_AcceptFriendRequest(int32 FriendshipId, const FBP_GFApiCallback& Callback)
{
	FGFFriendActionCallback TypedCallback;
	FGuid RequestId = AcceptFriendRequest(FriendshipId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseFriends::BP_DeclineFriendRequest(int32 FriendshipId, const FBP_GFApiCallback& Callback)
{
	FGFFriendActionCallback TypedCallback;
	FGuid RequestId = DeclineFriendRequest(FriendshipId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseFriends::BP_CancelFriendRequest(int32 FriendshipId, const FBP_GFApiCallback& Callback)
{
	FGFFriendActionCallback TypedCallback;
	FGuid RequestId = CancelFriendRequest(FriendshipId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseFriends::BP_UnfriendPlayer(int32 UserId, const FBP_GFApiCallback& Callback)
{
	FGFFriendActionCallback TypedCallback;
	FGuid RequestId = UnfriendPlayer(UserId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseFriends::BP_FetchFriendshipData(const FBP_GFApiCallback& Callback)
{
	FGFFriendsCallback TypedCallback;
	FGuid RequestId = FetchFriendshipData(TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseFriends::BP_FetchFriendsList(const FBP_GFApiCallback& Callback)
{
	FGFFriendsCallback TypedCallback;
	FGuid RequestId = FetchFriendsList(TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseFriends::BP_FetchOutgoingFriendRequests(const FBP_GFApiCallback& Callback)
{
	FGFFriendRequestsCallback TypedCallback;
	FGuid RequestId = FetchOutgoingFriendRequests(TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseFriends::BP_FetchIncomingFriendRequests(const FBP_GFApiCallback& Callback)
{
	FGFFriendRequestsCallback TypedCallback;
	FGuid RequestId = FetchIncomingFriendRequests(TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}