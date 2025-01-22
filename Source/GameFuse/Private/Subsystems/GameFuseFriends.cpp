#include "Subsystems/GameFuseFriends.h"
#include "Library/GameFuseLog.h"
#include "Subsystems/GameFuseUser.h"
#include "Library/GameFuseUtilities.h"

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
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	SendFriendRequest(Username, InternalCallback);
}

void UGameFuseFriends::BP_AcceptFriendRequest(int32 FriendshipId, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	AcceptFriendRequest(FriendshipId, InternalCallback);
}

void UGameFuseFriends::BP_DeclineFriendRequest(int32 FriendshipId, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	DeclineFriendRequest(FriendshipId, InternalCallback);
}

void UGameFuseFriends::BP_CancelFriendRequest(int32 FriendshipId, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	CancelFriendRequest(FriendshipId, InternalCallback);
}

void UGameFuseFriends::BP_UnfriendPlayer(int32 UserId, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	UnfriendPlayer(UserId, InternalCallback);
}

void UGameFuseFriends::BP_GetFriendshipData(FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	GetFriendshipData(InternalCallback);
}

void UGameFuseFriends::BP_GetFriendsList(FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	GetFriendsList(InternalCallback);
}

void UGameFuseFriends::BP_GetOutgoingFriendRequests(FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	GetOutgoingFriendRequests(InternalCallback);
}

void UGameFuseFriends::BP_GetIncomingFriendRequests(FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	GetIncomingFriendRequests(InternalCallback);
}

#pragma endregion

#pragma region C++ Functions

FGuid UGameFuseFriends::SendFriendRequest(const FString& Username, FGFApiCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to send friend request"));
		return FGuid();
	}

	Callback.AddUObject(this, &UGameFuseFriends::HandleFriendRequestResponse);
	return RequestHandler->SendFriendRequest(Username, GameFuseUser->GetUserData(), Callback);
}

FGuid UGameFuseFriends::AcceptFriendRequest(int32 FriendshipId, FGFApiCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to accept friend request"));
		return FGuid();
	}

	Callback.AddUObject(this, &UGameFuseFriends::HandleFriendActionResponse);
	return RequestHandler->RespondToFriendRequest(FriendshipId, TEXT("accepted"), GameFuseUser->GetUserData(), Callback);
}

FGuid UGameFuseFriends::DeclineFriendRequest(int32 FriendshipId, FGFApiCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to decline friend request"));
		return FGuid();
	}

	Callback.AddUObject(this, &UGameFuseFriends::HandleFriendActionResponse);
	return RequestHandler->RespondToFriendRequest(FriendshipId, TEXT("declined"), GameFuseUser->GetUserData(), Callback);
}

FGuid UGameFuseFriends::CancelFriendRequest(int32 FriendshipId, FGFApiCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to cancel friend request"));
		return FGuid();
	}

	Callback.AddUObject(this, &UGameFuseFriends::HandleFriendActionResponse);
	return RequestHandler->CancelFriendRequest(FriendshipId, GameFuseUser->GetUserData(), Callback);
}

FGuid UGameFuseFriends::UnfriendPlayer(int32 UserId, FGFApiCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to unfriend player"));
		return FGuid();
	}

	Callback.AddUObject(this, &UGameFuseFriends::HandleFriendActionResponse);
	return RequestHandler->UnfriendPlayer(UserId, GameFuseUser->GetUserData(), Callback);
}

FGuid UGameFuseFriends::GetFriendshipData(FGFApiCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to get friendship data"));
		return FGuid();
	}

	Callback.AddUObject(this, &UGameFuseFriends::HandleFriendshipDataResponse);
	return RequestHandler->GetFriendshipData(GameFuseUser->GetUserData(), Callback);
}

FGuid UGameFuseFriends::GetFriendsList(FGFApiCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to get friends list"));
		return FGuid();
	}

	Callback.AddUObject(this, &UGameFuseFriends::HandleFriendsListResponse);
	return RequestHandler->GetFriendsList(GameFuseUser->GetUserData(), Callback);
}

FGuid UGameFuseFriends::GetOutgoingFriendRequests(FGFApiCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to get outgoing friend requests"));
		return FGuid();
	}

	Callback.AddUObject(this, &UGameFuseFriends::HandleOutgoingRequestsResponse);
	return RequestHandler->GetOutgoingFriendRequests(GameFuseUser->GetUserData(), Callback);
}

FGuid UGameFuseFriends::GetIncomingFriendRequests(FGFApiCallback Callback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to get incoming friend requests"));
		return FGuid();
	}

	Callback.AddUObject(this, &UGameFuseFriends::HandleIncomingRequestsResponse);
	return RequestHandler->GetIncomingFriendRequests(GameFuseUser->GetUserData(), Callback);
}

#pragma endregion

#pragma region Response Handlers

void UGameFuseFriends::HandleFriendshipDataResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get friendship data: %s"), *Response.ResponseStr);
		return;
	}

	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.ResponseStr);
	TSharedPtr<FJsonObject> JsonObject;
	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse friendship data response"));
		return;
	}

	// Parse friends
	Friends.Empty();
	if (const TArray<TSharedPtr<FJsonValue>>* FriendsArray; JsonObject->TryGetArrayField(TEXT("friends"), FriendsArray)) {
		for (const TSharedPtr<FJsonValue>& Value : *FriendsArray) {
			if (const TSharedPtr<FJsonObject> UserObject = Value->AsObject()) {
				FGFUserData UserData;
				if (GameFuseUtilities::ConvertJsonToUserData(UserData, UserObject)) {
					Friends.Add(UserData);
				}
			}
		}
	}

	// Parse outgoing requests
	OutgoingRequests.Empty();
	if (const TArray<TSharedPtr<FJsonValue>>* OutgoingArray; JsonObject->TryGetArrayField(TEXT("outgoing_friend_requests"), OutgoingArray)) {
		for (const TSharedPtr<FJsonValue>& Value : *OutgoingArray) {
			if (const TSharedPtr<FJsonObject> RequestObject = Value->AsObject()) {
				FGFFriendRequest Request;
				if (GameFuseUtilities::ConvertJsonToFriendRequest(Request, RequestObject)) {
					OutgoingRequests.Add(Request);
				}
			}
		}
	}

	// Parse incoming requests
	IncomingRequests.Empty();
	if (const TArray<TSharedPtr<FJsonValue>>* IncomingArray; JsonObject->TryGetArrayField(TEXT("incoming_friend_requests"), IncomingArray)) {
		for (const TSharedPtr<FJsonValue>& Value : *IncomingArray) {
			if (const TSharedPtr<FJsonObject> RequestObject = Value->AsObject()) {
				FGFFriendRequest Request;
				if (GameFuseUtilities::ConvertJsonToFriendRequest(Request, RequestObject)) {
					IncomingRequests.Add(Request);
				}
			}
		}
	}

	OnFriendsListResponse.Broadcast(Friends);
	OnOutgoingRequestsResponse.Broadcast(OutgoingRequests);
	OnIncomingRequestsResponse.Broadcast(IncomingRequests);
}

void UGameFuseFriends::HandleFriendsListResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get friends list: %s"), *Response.ResponseStr);
		return;
	}

	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.ResponseStr);
	TSharedPtr<FJsonObject> JsonObject;
	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse friends list response"));
		return;
	}

	Friends.Empty();
	if (const TArray<TSharedPtr<FJsonValue>>* FriendsArray; JsonObject->TryGetArrayField(TEXT("friends"), FriendsArray)) {
		for (const TSharedPtr<FJsonValue>& Value : *FriendsArray) {
			if (const TSharedPtr<FJsonObject> UserObject = Value->AsObject()) {
				FGFUserData UserData;
				if (GameFuseUtilities::ConvertJsonToUserData(UserData, UserObject)) {
					Friends.Add(UserData);
				}
			}
		}
	}

	OnFriendsListResponse.Broadcast(Friends);
}

void UGameFuseFriends::HandleOutgoingRequestsResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get outgoing requests: %s"), *Response.ResponseStr);
		return;
	}

	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.ResponseStr);
	TSharedPtr<FJsonObject> JsonObject;
	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse outgoing requests response"));
		return;
	}

	OutgoingRequests.Empty();
	if (const TArray<TSharedPtr<FJsonValue>>* RequestsArray; JsonObject->TryGetArrayField(TEXT("outgoing_friend_requests"), RequestsArray)) {
		for (const TSharedPtr<FJsonValue>& Value : *RequestsArray) {
			if (const TSharedPtr<FJsonObject> RequestObject = Value->AsObject()) {
				FGFFriendRequest Request;
				if (GameFuseUtilities::ConvertJsonToFriendRequest(Request, RequestObject)) {
					OutgoingRequests.Add(Request);
				}
			}
		}
	}

	OnOutgoingRequestsResponse.Broadcast(OutgoingRequests);
}

void UGameFuseFriends::HandleIncomingRequestsResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get incoming requests: %s"), *Response.ResponseStr);
		return;
	}

	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.ResponseStr);
	TSharedPtr<FJsonObject> JsonObject;
	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse incoming requests response"));
		return;
	}

	IncomingRequests.Empty();
	if (const TArray<TSharedPtr<FJsonValue>>* RequestsArray; JsonObject->TryGetArrayField(TEXT("incoming_friend_requests"), RequestsArray)) {
		for (const TSharedPtr<FJsonValue>& Value : *RequestsArray) {
			if (const TSharedPtr<FJsonObject> RequestObject = Value->AsObject()) {
				FGFFriendRequest Request;
				if (GameFuseUtilities::ConvertJsonToFriendRequest(Request, RequestObject)) {
					IncomingRequests.Add(Request);
				}
			}
		}
	}

	OnIncomingRequestsResponse.Broadcast(IncomingRequests);
}

void UGameFuseFriends::HandleFriendRequestResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle friend request: %s"), *Response.ResponseStr);
		return;
	}

	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.ResponseStr);
	TSharedPtr<FJsonObject> JsonObject;
	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse friend request response"));
		return;
	}

	FGFFriendRequest Request;
	if (GameFuseUtilities::ConvertJsonToFriendRequest(Request, JsonObject)) {
		OnFriendRequestResponse.Broadcast(Request);
	}
}

void UGameFuseFriends::HandleFriendActionResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle friend action: %s"), *Response.ResponseStr);
		OnFriendActionResponse.Broadcast(false);
		return;
	}

	OnFriendActionResponse.Broadcast(true);
}

#pragma endregion