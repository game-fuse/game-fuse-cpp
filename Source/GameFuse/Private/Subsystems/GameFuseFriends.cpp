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

void UGameFuseFriends::WrapBlueprintCallback(const FBP_GFApiCallback& Callback, FGFApiCallback& InternalCallback)
{
	InternalCallback.AddLambda([Callback](const FGFAPIResponse& ResponseData) {
		Callback.ExecuteIfBound(ResponseData);
	});
}

#pragma region Blueprint Wrapper Functions

void UGameFuseFriends::BP_SendFriendRequest(const FString& Username, FBP_GFApiCallback Callback)
{
	FGFFriendRequestCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const FGFFriendRequest& Request) {
		FGFAPIResponse Response;
		Response.bSuccess = true;
		Callback.ExecuteIfBound(Response);
	});
	SendFriendRequest(Username, TypedCallback);
}

void UGameFuseFriends::BP_AcceptFriendRequest(int32 FriendshipId, FBP_GFApiCallback Callback)
{
	FGFFriendActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		FGFAPIResponse Response;
		Response.bSuccess = bSuccess;
		Callback.ExecuteIfBound(Response);
	});
	AcceptFriendRequest(FriendshipId, TypedCallback);
}

void UGameFuseFriends::BP_DeclineFriendRequest(int32 FriendshipId, FBP_GFApiCallback Callback)
{
	FGFFriendActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		FGFAPIResponse Response;
		Response.bSuccess = bSuccess;
		Callback.ExecuteIfBound(Response);
	});
	DeclineFriendRequest(FriendshipId, TypedCallback);
}

void UGameFuseFriends::BP_CancelFriendRequest(int32 FriendshipId, FBP_GFApiCallback Callback)
{
	FGFFriendActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		FGFAPIResponse Response;
		Response.bSuccess = bSuccess;
		Callback.ExecuteIfBound(Response);
	});
	CancelFriendRequest(FriendshipId, TypedCallback);
}

void UGameFuseFriends::BP_UnfriendPlayer(int32 UserId, FBP_GFApiCallback Callback)
{
	FGFFriendActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		FGFAPIResponse Response;
		Response.bSuccess = bSuccess;
		Callback.ExecuteIfBound(Response);
	});
	UnfriendPlayer(UserId, TypedCallback);
}

void UGameFuseFriends::BP_FetchFriendshipData(FBP_GFApiCallback Callback)
{
	FGFFriendsCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFUserData>& Friends) {
		FGFAPIResponse Response;
		Response.bSuccess = true;
		Callback.ExecuteIfBound(Response);
	});
	FetchFriendshipData(TypedCallback);
}

void UGameFuseFriends::BP_FetchFriendsList(FBP_GFApiCallback Callback)
{
	FGFFriendsCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFUserData>& Friends) {
		FGFAPIResponse Response;
		Response.bSuccess = true;
		Callback.ExecuteIfBound(Response);
	});
	FetchFriendsList(TypedCallback);
}

void UGameFuseFriends::BP_FetchOutgoingFriendRequests(FBP_GFApiCallback Callback)
{
	FGFFriendRequestsCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFFriendRequest>& Requests) {
		FGFAPIResponse Response;
		Response.bSuccess = true;
		Callback.ExecuteIfBound(Response);
	});
	FetchOutgoingFriendRequests(TypedCallback);
}

void UGameFuseFriends::BP_FetchIncomingFriendRequests(FBP_GFApiCallback Callback)
{
	FGFFriendRequestsCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFFriendRequest>& Requests) {
		FGFAPIResponse Response;
		Response.bSuccess = true;
		Callback.ExecuteIfBound(Response);
	});
	FetchIncomingFriendRequests(TypedCallback);
}

#pragma endregion

#pragma region C++ Functions

FGuid UGameFuseFriends::SendFriendRequest(const FString& Username, FGFFriendRequestCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to send friend request"));
		return FGuid();
	}

	FGuid RequestId = FGuid::NewGuid();
	if (Callback.IsBound()) {
		FriendRequestCallbacks.Add(RequestId, Callback);
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this, RequestId](const FGFAPIResponse& Response) {
		HandleFriendRequestResponse(Response);
	});

	return RequestHandler->SendFriendRequest(Username, GameFuseUser->GetUserData(), InternalCallback);
}

FGuid UGameFuseFriends::AcceptFriendRequest(int32 FriendshipId, FGFFriendActionCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to accept friend request"));
		return FGuid();
	}

	FGuid RequestId = FGuid::NewGuid();
	if (Callback.IsBound()) {
		FriendActionCallbacks.Add(RequestId, Callback);
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this, RequestId](const FGFAPIResponse& Response) {
		HandleFriendActionResponse(Response);
	});

	return RequestHandler->RespondToFriendRequest(FriendshipId, EGFFriendRequestStatus::Accepted, GameFuseUser->GetUserData(), InternalCallback);
}

FGuid UGameFuseFriends::DeclineFriendRequest(int32 FriendshipId, FGFFriendActionCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to decline friend request"));
		return FGuid();
	}

	FGuid RequestId = FGuid::NewGuid();
	if (Callback.IsBound()) {
		FriendActionCallbacks.Add(RequestId, Callback);
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this, RequestId](const FGFAPIResponse& Response) {
		HandleFriendActionResponse(Response);
	});

	return RequestHandler->RespondToFriendRequest(FriendshipId, EGFFriendRequestStatus::Declined, GameFuseUser->GetUserData(), InternalCallback);
}

FGuid UGameFuseFriends::CancelFriendRequest(int32 FriendshipId, FGFFriendActionCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to cancel friend request"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	FGuid RequestId = FGuid::NewGuid();
	if (Callback.IsBound()) {
		FriendActionCallbacks.Add(RequestId, Callback);
	}

	InternalCallback.AddLambda([this, RequestId](const FGFAPIResponse& Response) {
		if (!Response.bSuccess) {
			UE_LOG(LogGameFuse, Error, TEXT("Failed to cancel friend request: %s"), *Response.ResponseStr);
			if (FriendActionCallbacks.Contains(RequestId)) {
				FriendActionCallbacks[RequestId].ExecuteIfBound(false);
				FriendActionCallbacks.Remove(RequestId);
			}
			return;
		}

		if (FriendActionCallbacks.Contains(RequestId)) {
			FriendActionCallbacks[RequestId].ExecuteIfBound(true);
			FriendActionCallbacks.Remove(RequestId);
		}
	});

	return RequestHandler->CancelFriendRequest(FriendshipId, GameFuseUser->GetUserData(), InternalCallback);
}

FGuid UGameFuseFriends::UnfriendPlayer(int32 UserId, FGFFriendActionCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to unfriend player"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	FGuid RequestId = FGuid::NewGuid();
	if (Callback.IsBound()) {
		FriendActionCallbacks.Add(RequestId, Callback);
	}

	InternalCallback.AddLambda([this, RequestId](const FGFAPIResponse& Response) {
		if (!Response.bSuccess) {
			UE_LOG(LogGameFuse, Error, TEXT("Failed to unfriend player: %s"), *Response.ResponseStr);
			if (FriendActionCallbacks.Contains(RequestId)) {
				FriendActionCallbacks[RequestId].ExecuteIfBound(false);
				FriendActionCallbacks.Remove(RequestId);
			}
			return;
		}

		if (FriendActionCallbacks.Contains(RequestId)) {
			FriendActionCallbacks[RequestId].ExecuteIfBound(true);
			FriendActionCallbacks.Remove(RequestId);
		}
	});

	return RequestHandler->UnfriendPlayer(UserId, GameFuseUser->GetUserData(), InternalCallback);
}

FGuid UGameFuseFriends::FetchFriendshipData(FGFFriendsCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to get friendship data"));
		return FGuid();
	}

	FGuid RequestId = FGuid::NewGuid();
	if (Callback.IsBound()) {
		FriendsCallbacks.Add(RequestId, Callback);
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this, RequestId](const FGFAPIResponse& Response) {
		HandleFriendshipDataResponse(Response);
	});

	return RequestHandler->GetFriendshipData(GameFuseUser->GetUserData(), InternalCallback);
}

FGuid UGameFuseFriends::FetchFriendsList(FGFFriendsCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to get friends list"));
		return FGuid();
	}

	FGuid RequestId = FGuid::NewGuid();
	if (Callback.IsBound()) {
		FriendsCallbacks.Add(RequestId, Callback);
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this, RequestId](const FGFAPIResponse& Response) {
		HandleFriendsListResponse(Response);
	});

	return RequestHandler->GetFriendsList(GameFuseUser->GetUserData(), InternalCallback);
}

FGuid UGameFuseFriends::FetchOutgoingFriendRequests(FGFFriendRequestsCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to get outgoing friend requests"));
		return FGuid();
	}

	FGuid RequestId = FGuid::NewGuid();
	if (Callback.IsBound()) {
		FriendRequestsCallbacks.Add(RequestId, Callback);
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this, RequestId](const FGFAPIResponse& Response) {
		HandleOutgoingRequestsResponse(Response);
	});

	return RequestHandler->GetOutgoingFriendRequests(GameFuseUser->GetUserData(), InternalCallback);
}

FGuid UGameFuseFriends::FetchIncomingFriendRequests(FGFFriendRequestsCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to get incoming friend requests"));
		return FGuid();
	}

	FGuid RequestId = FGuid::NewGuid();
	if (Callback.IsBound()) {
		FriendRequestsCallbacks.Add(RequestId, Callback);
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this, RequestId](const FGFAPIResponse& Response) {
		HandleIncomingRequestsResponse(Response);
	});

	return RequestHandler->GetIncomingFriendRequests(GameFuseUser->GetUserData(), InternalCallback);
}

#pragma endregion

#pragma region Response Handlers

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
	if (!GameFuseUtilities::ConvertJsonToFriendsList(FriendsList, Response.ResponseStr))
	{
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse friends list from friendship data"));
		if (FriendsCallbacks.Contains(Response.RequestId)) {
			FriendsCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFUserData>());
			FriendsCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	// Parse outgoing requests
	if (!GameFuseUtilities::ConvertJsonToFriendRequests(OutgoingRequests, Response.ResponseStr))
	{
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse outgoing requests from friendship data"));
	}

	// Parse incoming requests
	if (!GameFuseUtilities::ConvertJsonToFriendRequests(IncomingRequests, Response.ResponseStr))
	{
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

	if (!GameFuseUtilities::ConvertJsonToFriendsList(FriendsList, Response.ResponseStr))
	{
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

	if (!GameFuseUtilities::ConvertJsonToFriendRequests(OutgoingRequests, Response.ResponseStr))
	{
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

	if (!GameFuseUtilities::ConvertJsonToFriendRequests(IncomingRequests, Response.ResponseStr))
	{
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
	if (!GameFuseUtilities::ConvertJsonToFriendRequest(Request, JsonObject))
	{
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

#pragma endregion

#pragma endregion
#pragma endregion
#pragma endregion