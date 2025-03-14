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

FGuid UGroupsAPIHandler::FetchAllGroups(const FGFUserData& UserData, const FGFApiCallback& Callback)
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

FGuid UGroupsAPIHandler::FetchGroup(int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback)
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

FGuid UGroupsAPIHandler::FetchUserGroups(const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	const FString Endpoint = TEXT("/user/groups");
	return SendRequest(Endpoint, TEXT("GET"), Callback);
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

FGuid UGroupsAPIHandler::AddAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, bool bOnlyCreatorCanEdit, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonValue>> AttributesArray;

	// Create the attribute object
	TSharedPtr<FJsonObject> AttributeObject = MakeShared<FJsonObject>();
	AttributeObject->SetStringField(TEXT("key"), Attribute.Key);
	AttributeObject->SetStringField(TEXT("value"), Attribute.Value);
	AttributeObject->SetBoolField(TEXT("only_can_edit_by_creator"), bOnlyCreatorCanEdit);

	// Add it to the array
	AttributesArray.Add(MakeShared<FJsonValueObject>(AttributeObject));

	// Set the attributes array in the main object
	JsonObject->SetArrayField(TEXT("attributes"), AttributesArray);

	const FString ApiEndpoint = FString::Printf(TEXT("/groups/%d/add_attribute"), GroupId);
	return SendRequest(ApiEndpoint, TEXT("POST"), Callback, JsonObject);
}

FGuid UGroupsAPIHandler::UpdateGroupAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, const FGFUserData& UserData, FGFApiCallback Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	if (GroupId <= 0) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid group ID"));
		return FGuid();
	}

	if (Attribute.Id <= 0) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid attribute ID"));
		return FGuid();
	}

	// Create request body
	TSharedPtr<FJsonObject> JsonBody = MakeShared<FJsonObject>();
	JsonBody->SetStringField(TEXT("value"), Attribute.Value);
	JsonBody->SetStringField(TEXT("key"), Attribute.Key);
	// RequestBody->SetNumberField(TEXT("id"), Attribute.Id);


	// Create request
	const FString ApiEndpoint = FString::Printf(TEXT("/groups/%d/modify_attribute"), GroupId);
	return SendRequest(ApiEndpoint, TEXT("PATCH"), Callback, JsonBody);
}

// FGuid UGroupsAPIHandler::DeleteAttribute(const int32 GroupId, const int32 AttributeId, const FGFUserData& UserData, const FGFApiCallback& Callback)
// {
// 	if (!VerifyUserData(UserData)) {
// 		return FGuid();
// 	}
// 	SetAuthHeader(UserData.AuthenticationToken);
//
// 	const FString ApiEndpoint = FString::Printf(TEXT("/groups/%d/attributes/%d"), GroupId, AttributeId);
// 	return SendRequest(ApiEndpoint, "DELETE", Callback);
// }

FGuid UGroupsAPIHandler::RespondToGroupJoinRequest(const int32 ConnectionId, const int32 UserId, EGFInviteRequestStatus Status, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	if (Status == EGFInviteRequestStatus::None) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid request status: None"));
		return FGuid();
	}

	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/group_connections/%d"), ConnectionId);
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();

	// Create the group_connection object
	TSharedPtr<FJsonObject> GroupConnectionObject = MakeShared<FJsonObject>();
	GroupConnectionObject->SetStringField("status", Status == EGFInviteRequestStatus::Accepted ? "accepted" : "declined");
	GroupConnectionObject->SetStringField("action_type", "update");

	// Add the main objects
	JsonObject->SetObjectField("group_connection", GroupConnectionObject);
	JsonObject->SetStringField("connection_type", "invite");

	return SendRequest(ApiEndpoint, "PUT", Callback, JsonObject);
}

FGuid UGroupsAPIHandler::FetchGroupAttributes(const int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/groups/%d/attributes"), GroupId);
	return SendRequest(ApiEndpoint, TEXT("GET"), Callback);
}