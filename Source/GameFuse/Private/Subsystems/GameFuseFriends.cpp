#include "Subsystems/GameFuseFriends.h"
#include "Library/GameFuseLog.h"
#include "Subsystems/GameFuseUser.h"
#include "Library/GameFuseUtilities.h"
#include "JsonObjectConverter.h"
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
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get friendship data: %s"), *Response.ResponseStr);
		if (FriendsCallbacks.Contains(Response.RequestId)) {
			FriendsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFUserData>());
			FriendsCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	// Parse friends list
	if (!GameFuseUtilities::ConvertJsonToFriendsList(FriendsList, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse friends list from friendship data"));
		if (FriendsCallbacks.Contains(Response.RequestId)) {
			FriendsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFUserData>());
			FriendsCallbacks.Remove(Response.RequestId);
		}
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
}

void UGameFuseFriends::HandleFriendsListResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get friends list: %s"), *Response.ResponseStr);
		if (FriendsCallbacks.Contains(Response.RequestId)) {
			FriendsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFUserData>());
			FriendsCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (!GameFuseUtilities::ConvertJsonToFriendsList(FriendsList, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse friends list"));
		if (FriendsCallbacks.Contains(Response.RequestId)) {
			FriendsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFUserData>());
			FriendsCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (FriendsCallbacks.Contains(Response.RequestId)) {
		FriendsCallbacks[Response.RequestId].ExecuteIfBound(FriendsList);
		FriendsCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseFriends::HandleOutgoingRequestsResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get outgoing requests: %s"), *Response.ResponseStr);
		if (FriendRequestsCallbacks.Contains(Response.RequestId)) {
			FriendRequestsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFFriendRequest>());
			FriendRequestsCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (!GameFuseUtilities::ConvertJsonToFriendRequests(OutgoingRequests, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse outgoing requests"));
		if (FriendRequestsCallbacks.Contains(Response.RequestId)) {
			FriendRequestsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFFriendRequest>());
			FriendRequestsCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (FriendRequestsCallbacks.Contains(Response.RequestId)) {
		FriendRequestsCallbacks[Response.RequestId].ExecuteIfBound(OutgoingRequests);
		FriendRequestsCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseFriends::HandleIncomingRequestsResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get incoming requests: %s"), *Response.ResponseStr);
		if (FriendRequestsCallbacks.Contains(Response.RequestId)) {
			FriendRequestsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFFriendRequest>());
			FriendRequestsCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (!GameFuseUtilities::ConvertJsonToFriendRequests(IncomingRequests, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse incoming requests"));
		if (FriendRequestsCallbacks.Contains(Response.RequestId)) {
			FriendRequestsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFFriendRequest>());
			FriendRequestsCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (FriendRequestsCallbacks.Contains(Response.RequestId)) {
		FriendRequestsCallbacks[Response.RequestId].ExecuteIfBound(IncomingRequests);
		FriendRequestsCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseFriends::HandleFriendRequestResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle friend request: %s"), *Response.ResponseStr);
		if (FriendRequestCallbacks.Contains(Response.RequestId)) {
			FriendRequestCallbacks[Response.RequestId].ExecuteIfBound(FGFFriendRequest());
			FriendRequestCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.ResponseStr);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse friend request response"));
		if (FriendRequestCallbacks.Contains(Response.RequestId)) {
			FriendRequestCallbacks[Response.RequestId].ExecuteIfBound(FGFFriendRequest());
			FriendRequestCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	FGFFriendRequest Request;
	if (!GameFuseUtilities::ConvertJsonToFriendRequest(Request, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse friend request"));
		if (FriendRequestCallbacks.Contains(Response.RequestId)) {
			FriendRequestCallbacks[Response.RequestId].ExecuteIfBound(FGFFriendRequest());
			FriendRequestCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (FriendRequestCallbacks.Contains(Response.RequestId)) {
		FriendRequestCallbacks[Response.RequestId].ExecuteIfBound(Request);
		FriendRequestCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseFriends::HandleFriendActionResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle friend action: %s"), *Response.ResponseStr);
		if (FriendActionCallbacks.Contains(Response.RequestId)) {
			FriendActionCallbacks[Response.RequestId].ExecuteIfBound(false);
			FriendActionCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (FriendActionCallbacks.Contains(Response.RequestId)) {
		FriendActionCallbacks[Response.RequestId].ExecuteIfBound(true);
		FriendActionCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseFriends::BP_SendFriendRequest(const FString& Username, FBP_GFFriendCallback Callback)
{
	FGFFriendRequestCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const FGFFriendRequest&) {
		Callback.ExecuteIfBound(true);
	});
	SendFriendRequest(Username, TypedCallback);
}

void UGameFuseFriends::BP_AcceptFriendRequest(int32 FriendshipId, FBP_GFFriendCallback Callback)
{
	FGFFriendActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		Callback.ExecuteIfBound(bSuccess);
	});
	AcceptFriendRequest(FriendshipId, TypedCallback);
}

void UGameFuseFriends::BP_DeclineFriendRequest(int32 FriendshipId, FBP_GFFriendCallback Callback)
{
	FGFFriendActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		Callback.ExecuteIfBound(bSuccess);
	});
	DeclineFriendRequest(FriendshipId, TypedCallback);
}

void UGameFuseFriends::BP_CancelFriendRequest(int32 FriendshipId, FBP_GFFriendCallback Callback)
{
	FGFFriendActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		Callback.ExecuteIfBound(bSuccess);
	});
	CancelFriendRequest(FriendshipId, TypedCallback);
}

void UGameFuseFriends::BP_UnfriendPlayer(int32 UserId, FBP_GFFriendCallback Callback)
{
	FGFFriendActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		Callback.ExecuteIfBound(bSuccess);
	});
	UnfriendPlayer(UserId, TypedCallback);
}

void UGameFuseFriends::BP_FetchFriendshipData(FBP_GFFriendCallback Callback)
{
	FGFFriendsCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFUserData>&) {
		Callback.ExecuteIfBound(true);
	});
	FetchFriendshipData(TypedCallback);
}

void UGameFuseFriends::BP_FetchFriendsList(FBP_GFFriendCallback Callback)
{
	FGFFriendsCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFUserData>&) {
		Callback.ExecuteIfBound(true);
	});
	FetchFriendsList(TypedCallback);
}

void UGameFuseFriends::BP_FetchOutgoingFriendRequests(FBP_GFFriendCallback Callback)
{
	FGFFriendRequestsCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFFriendRequest>&) {
		Callback.ExecuteIfBound(true);
	});
	FetchOutgoingFriendRequests(TypedCallback);
}

void UGameFuseFriends::BP_FetchIncomingFriendRequests(FBP_GFFriendCallback Callback)
{
	FGFFriendRequestsCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFFriendRequest>&) {
		Callback.ExecuteIfBound(true);
	});
	FetchIncomingFriendRequests(TypedCallback);
}