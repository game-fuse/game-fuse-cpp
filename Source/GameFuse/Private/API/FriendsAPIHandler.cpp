#include "API/FriendsAPIHandler.h"
#include "Library/GameFuseLog.h"

FGuid UFriendsAPIHandler::SendFriendRequest(const FString& Username, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(TEXT("username"), Username);

	return SendRequest("/friendships", "POST", Callback, JsonObject);
}

FGuid UFriendsAPIHandler::RespondToFriendRequest(const int32 FriendshipId, const EGFFriendRequestStatus Status, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);

	FString StatusStr;
	switch (Status) {
		case EGFFriendRequestStatus::Accepted:
			StatusStr = TEXT("accepted");
			break;
		case EGFFriendRequestStatus::Declined:
			StatusStr = TEXT("declined");
			break;
		default:
			UE_LOG(LogGameFuse, Error, TEXT("Invalid friend request status"));
			return FGuid();
	}

	const FString ApiEndpoint = FString::Printf(TEXT("/friendships/%d"), FriendshipId);
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(TEXT("status"), StatusStr);

	return SendRequest(ApiEndpoint, "PUT", Callback, JsonObject);
}

FGuid UFriendsAPIHandler::CancelFriendRequest(const int32 FriendshipId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/friendships/%d"), FriendshipId);
	return SendRequest(ApiEndpoint, "DELETE", Callback);
}

FGuid UFriendsAPIHandler::UnfriendPlayer(const int32 UserId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/unfriend?user_id=%d"), UserId);
	return SendRequest(ApiEndpoint, "DELETE", Callback);
}

FGuid UFriendsAPIHandler::GetFriendshipData(const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);
	return SendRequest("/friendships", "GET", Callback);
}

FGuid UFriendsAPIHandler::GetFriendsList(const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);
	return SendRequest("/friends", "GET", Callback);
}

FGuid UFriendsAPIHandler::GetOutgoingFriendRequests(const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);
	return SendRequest("/outgoing_friend_requests", "GET", Callback);
}

FGuid UFriendsAPIHandler::GetIncomingFriendRequests(const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);
	return SendRequest("/incoming_friend_requests", "GET", Callback);
}