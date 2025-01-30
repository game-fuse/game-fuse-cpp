#include "API/GroupsAPIHandler.h"
#include "Library/GameFuseLog.h"
#include "Library/GameFuseUtilities.h"

FGuid UGroupsAPIHandler::CreateGroup(const FGFGroup& Group, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	if (!GameFuseUtilities::ConvertGroupToJson(Group, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to serialize group to JSON"));
		return FGuid();
	}

	return SendRequest("/groups", "POST", Callback, JsonObject);
}

FGuid UGroupsAPIHandler::GetAllGroups(const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	return SendRequest("/groups", "GET", Callback);
}

FGuid UGroupsAPIHandler::RequestToJoinGroup(int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetNumberField("group_id", GroupId);
	JsonObject->SetNumberField("user_id", UserData.Id);

	return SendRequest("/group_connections", "POST", Callback, JsonObject);
}

FGuid UGroupsAPIHandler::GetGroup(const int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/groups/%d"), GroupId);
	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid UGroupsAPIHandler::DeleteGroup(const int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/groups/%d"), GroupId);
	return SendRequest(ApiEndpoint, "DELETE", Callback);
}

FGuid UGroupsAPIHandler::GetUserGroups(const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	return SendRequest("/groups", "GET", Callback);
}

FGuid UGroupsAPIHandler::SearchGroups(const FString& Query, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/groups?query=%s"), *Query);
	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid UGroupsAPIHandler::JoinGroup(const int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/group_connections"));
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetNumberField("group_id", GroupId);

	return SendRequest(ApiEndpoint, "POST", Callback, JsonObject);
}

FGuid UGroupsAPIHandler::LeaveGroup(const int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/group_connections/%d"), GroupId);
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField("status", "declined");

	return SendRequest(ApiEndpoint, "PUT", Callback, JsonObject);
}

FGuid UGroupsAPIHandler::AddAdmin(const int32 GroupId, const int32 UserId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetNumberField("user_id", UserId);

	const FString ApiEndpoint = FString::Printf(TEXT("/groups/%d/admins"), GroupId);
	return SendRequest(ApiEndpoint, "POST", Callback, JsonObject);
}

FGuid UGroupsAPIHandler::RemoveAdmin(const int32 GroupId, const int32 UserId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/groups/%d/admins/%d"), GroupId, UserId);
	return SendRequest(ApiEndpoint, "DELETE", Callback);
}

FGuid UGroupsAPIHandler::AddAttribute(const int32 GroupId, const FString& Key, const FString& Value, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField("key", Key);
	JsonObject->SetStringField("value", Value);

	const FString ApiEndpoint = FString::Printf(TEXT("/groups/%d/add_attribute"), GroupId);
	return SendRequest(ApiEndpoint, "POST", Callback, JsonObject);
}

FGuid UGroupsAPIHandler::UpdateAttribute(const int32 GroupId, const int32 AttributeId, const FString& Value, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField("value", Value);

	const FString ApiEndpoint = FString::Printf(TEXT("/groups/%d/modify_attribute"), GroupId);
	return SendRequest(ApiEndpoint, "PATCH", Callback, JsonObject);
}

FGuid UGroupsAPIHandler::DeleteAttribute(const int32 GroupId, const int32 AttributeId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/groups/%d/attributes/%d"), GroupId, AttributeId);
	return SendRequest(ApiEndpoint, "DELETE", Callback);
}