#include "Subsystems/GameFuseGroups.h"
#include "Library/GameFuseLog.h"
#include "Subsystems/GameFuseUser.h"
#include "Library/GameFuseUtilities.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Engine/GameInstance.h"

void UGameFuseGroups::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RequestHandler = NewObject<UGroupsAPIHandler>();
}

void UGameFuseGroups::Deinitialize()
{
	RequestHandler = nullptr;
	Super::Deinitialize();
}

FGuid UGameFuseGroups::CreateGroup(const FGFGroup& Group, FGFGroupCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to create a group"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupResponse(Response);
	});

	FGuid RequestId = RequestHandler->CreateGroup(Group, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseGroups::FetchGroup(const int32 GroupId, FGFGroupCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to fetch group"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupResponse(Response);
	});

	FGuid RequestId = RequestHandler->FetchGroup(GroupId, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseGroups::FetchAllGroups(FGFGroupListCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to fetch all groups"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupListResponse(Response);
	});

	FGuid RequestId = RequestHandler->FetchAllGroups(GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupListCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseGroups::RequestToJoinGroup(int32 GroupId, FGFGroupConnectionCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to request to join a group"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupConnectionResponse(Response);
	});

	FGuid RequestId = RequestHandler->RequestToJoinGroup(GroupId, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupConnectionCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseGroups::DeleteGroup(const int32 GroupId, FGFGroupActionCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to delete group"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->DeleteGroup(GroupId, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupActionCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseGroups::JoinGroup(const int32 GroupId, FGFGroupActionCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to join group"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->JoinGroup(GroupId, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupActionCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseGroups::LeaveGroup(const int32 GroupId, FGFGroupActionCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to leave group"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->LeaveGroup(GroupId, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupActionCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseGroups::FetchUserGroups(FGFGroupListCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to fetch user groups"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupListResponse(Response);
	});

	FGuid RequestId = RequestHandler->FetchUserGroups(GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupListCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseGroups::SearchGroups(const FString& Query, FGFGroupListCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to search groups"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupListResponse(Response);
	});

	FGuid RequestId = RequestHandler->SearchGroups(Query, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupListCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseGroups::AddAdmin(const int32 GroupId, const int32 UserId, FGFGroupActionCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to add admin"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->AddAdmin(GroupId, UserId, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupActionCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseGroups::RemoveAdmin(const int32 GroupId, const int32 UserId, FGFGroupActionCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to remove admin"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->RemoveAdmin(GroupId, UserId, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupActionCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseGroups::AddAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, bool bOnlyCreatorCanEdit, FGFGroupAttributeCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to add attribute"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupAttributeResponse(Response);
	});

	FGuid RequestId = RequestHandler->AddAttribute(GroupId, Attribute, bOnlyCreatorCanEdit, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupAttributeCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseGroups::UpdateGroupAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, FGFGroupActionCallback UntypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to update attribute"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->UpdateGroupAttribute(GroupId, Attribute, GameFuseUser->GetUserData(), InternalCallback);
	if (UntypedCallback.IsBound()) {
		GroupActionCallbacks.Add(RequestId, UntypedCallback);
	}
	return RequestId;
}

// FGuid UGameFuseGroups::DeleteAttribute(const int32 GroupId, const int32 AttributeId, FGFGroupActionCallback TypedCallback)
// {
// 	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
// 	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
// 		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to delete attribute"));
// 		return FGuid();
// 	}
//
// 	FGFApiCallback InternalCallback;
// 	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
// 		HandleGroupActionResponse(Response);
// 	});
//
// 	FGuid RequestId = RequestHandler->DeleteAttribute(GroupId, AttributeId, GameFuseUser->GetUserData(), InternalCallback);
// 	if (TypedCallback.IsBound()) {
// 		GroupActionCallbacks.Add(RequestId, TypedCallback);
// 	}
// 	return RequestId;
// }

FGuid UGameFuseGroups::RespondToGroupJoinRequest(const int32 ConnectionId, const int32 UserId, EGFInviteRequestStatus Status, FGFGroupActionCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to respond to group join request"));
		return FGuid();
	}

	if (Status == EGFInviteRequestStatus::None) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid request status: None"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->RespondToGroupJoinRequest(ConnectionId, UserId, Status, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupActionCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseGroups::FetchGroupAttributes(const int32 GroupId, FGFGroupAttributeCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to fetch attributes"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGroupAttributeResponse(Response);
	});

	FGuid RequestId = RequestHandler->FetchGroupAttributes(GroupId, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		GroupAttributeCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

void UGameFuseGroups::HandleGroupResponse(const FGFAPIResponse& Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle group response: %s"), *Response.ResponseStr);
		if (GroupCallbacks.Contains(Response.RequestId)) {
			GroupCallbacks[Response.RequestId].ExecuteIfBound(FGFGroup());
			GroupCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	FGFGroup Group;
	if (!GameFuseUtilities::ConvertJsonToGroup(Group, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse group"));
		if (GroupCallbacks.Contains(Response.RequestId)) {
			GroupCallbacks[Response.RequestId].ExecuteIfBound(FGFGroup());
			GroupCallbacks.Remove(Response.RequestId);
		}
		return;
	}
	// update cached data
	AllGroups.AddUnique(Group);
	if (Group.Members.Contains(GetGameInstance()->GetSubsystem<UGameFuseUser>()->GetUserData())) {
		UserGroups.AddUnique(Group);
	}


	if (GroupCallbacks.Contains(Response.RequestId)) {
		GroupCallbacks[Response.RequestId].ExecuteIfBound(Group);
		GroupCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseGroups::HandleGroupListResponse(const FGFAPIResponse& Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle group list response: %s"), *Response.ResponseStr);
		if (GroupListCallbacks.Contains(Response.RequestId)) {
			GroupListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFGroup>());
			GroupListCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	TArray<FGFGroup> Groups;
	if (!GameFuseUtilities::ConvertJsonArrayToGroups(Groups, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse groups list"));
		if (GroupListCallbacks.Contains(Response.RequestId)) {
			GroupListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFGroup>());
			GroupListCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	// Update cached data
	AllGroups = Groups;

	if (GroupListCallbacks.Contains(Response.RequestId)) {
		GroupListCallbacks[Response.RequestId].ExecuteIfBound(Groups);
		GroupListCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseGroups::HandleGroupConnectionResponse(const FGFAPIResponse& Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle group connection: %s"), *Response.ResponseStr);
		if (GroupConnectionCallbacks.Contains(Response.RequestId)) {
			GroupConnectionCallbacks[Response.RequestId].ExecuteIfBound(FGFGroupConnection());
			GroupConnectionCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	FGFGroupConnection Connection;
	if (!GameFuseUtilities::ConvertJsonToGroupConnection(Connection, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse group connection response"));
		if (GroupConnectionCallbacks.Contains(Response.RequestId)) {
			GroupConnectionCallbacks[Response.RequestId].ExecuteIfBound(FGFGroupConnection());
			GroupConnectionCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (GroupConnectionCallbacks.Contains(Response.RequestId)) {
		GroupConnectionCallbacks[Response.RequestId].ExecuteIfBound(Connection);
		GroupConnectionCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseGroups::HandleGroupActionResponse(const FGFAPIResponse& Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle group action response: %s"), *Response.ResponseStr);
	}

	if (GroupActionCallbacks.Contains(Response.RequestId)) {
		GroupActionCallbacks[Response.RequestId].ExecuteIfBound(Response.bSuccess);
		GroupActionCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseGroups::HandleGroupAttributeResponse(const FGFAPIResponse& Response)
{

	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle group attribute response: %s"), *Response.ResponseStr);
		if (GroupAttributeCallbacks.Contains(Response.RequestId)) {
			TArray<FGFGroupAttribute> EmptyAttributes;
			GroupAttributeCallbacks[Response.RequestId].ExecuteIfBound(EmptyAttributes);
			GroupAttributeCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	// Parse the attributes array from the response
	TArray<FGFGroupAttribute> Attributes;
	if (!GameFuseUtilities::ConvertJsonToGroupAttributeResponse(Attributes, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse group attributes response"));
		if (GroupAttributeCallbacks.Contains(Response.RequestId)) {
			TArray<FGFGroupAttribute> EmptyAttributes;
			GroupAttributeCallbacks[Response.RequestId].ExecuteIfBound(EmptyAttributes);
			GroupAttributeCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	// Execute the callback with the parsed attributes
	if (GroupAttributeCallbacks.Contains(Response.RequestId)) {
		GroupAttributeCallbacks[Response.RequestId].ExecuteIfBound(Attributes);
		GroupAttributeCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseGroups::HandleFetchAttributesResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to fetch group attributes: %s"), *Response.ResponseStr);
		if (FetchAttributesCallbacks.Contains(Response.RequestId)) {
			FetchAttributesCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFGroupAttribute>());
			FetchAttributesCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	TArray<FGFGroupAttribute> Attributes;
	if (!GameFuseUtilities::ConvertJsonToGroupAttributeResponse(Attributes, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse group attributes"));
		if (FetchAttributesCallbacks.Contains(Response.RequestId)) {
			FetchAttributesCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFGroupAttribute>());
			FetchAttributesCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (FetchAttributesCallbacks.Contains(Response.RequestId)) {
		FetchAttributesCallbacks[Response.RequestId].ExecuteIfBound(Attributes);
		FetchAttributesCallbacks.Remove(Response.RequestId);
	}
}

// Blueprint API implementations
void UGameFuseGroups::BP_CreateGroup(const FGFGroup& Group, FBP_GFGroupCallback Callback)
{
	FGFGroupCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const FGFGroup& CreatedGroup) {
		Callback.ExecuteIfBound(CreatedGroup.Id > 0);
	});
	CreateGroup(Group, TypedCallback);
}

void UGameFuseGroups::BP_FetchGroup(const int32 GroupId, FBP_GFGroupCallback Callback)
{
	FGFGroupCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const FGFGroup& Group) {
		Callback.ExecuteIfBound(Group.Id > 0);
	});
	FetchGroup(GroupId, TypedCallback);
}

void UGameFuseGroups::BP_FetchAllGroups(FBP_GFGroupCallback Callback)
{
	FGFGroupListCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFGroup>& Groups) {
		Callback.ExecuteIfBound(!Groups.IsEmpty());
	});
	FetchAllGroups(TypedCallback);
}

void UGameFuseGroups::BP_RequestToJoinGroup(int32 GroupId, FBP_GFGroupCallback Callback)
{
	FGFGroupConnectionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const FGFGroupConnection& Connection) {
		Callback.ExecuteIfBound(Connection.Id > 0);
	});
	RequestToJoinGroup(GroupId, TypedCallback);
}

void UGameFuseGroups::BP_DeleteGroup(const int32 GroupId, FBP_GFGroupCallback Callback)
{
	FGFGroupActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		Callback.ExecuteIfBound(bSuccess);
	});
	DeleteGroup(GroupId, TypedCallback);
}

void UGameFuseGroups::BP_JoinGroup(const int32 GroupId, FBP_GFGroupCallback Callback)
{
	FGFGroupActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		Callback.ExecuteIfBound(bSuccess);
	});
	JoinGroup(GroupId, TypedCallback);
}

void UGameFuseGroups::BP_LeaveGroup(const int32 GroupId, FBP_GFGroupCallback Callback)
{
	FGFGroupActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		Callback.ExecuteIfBound(bSuccess);
	});
	LeaveGroup(GroupId, TypedCallback);
}

void UGameFuseGroups::BP_FetchUserGroups(FBP_GFGroupCallback Callback)
{
	FGFGroupListCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFGroup>& Groups) {
		Callback.ExecuteIfBound(!Groups.IsEmpty());
	});
	FetchUserGroups(TypedCallback);
}

void UGameFuseGroups::BP_SearchGroups(const FString& Query, FBP_GFGroupCallback Callback)
{
	FGFGroupListCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFGroup>& Groups) {
		Callback.ExecuteIfBound(!Groups.IsEmpty());
	});
	SearchGroups(Query, TypedCallback);
}

void UGameFuseGroups::BP_AddAdmin(const int32 GroupId, const int32 UserId, FBP_GFGroupCallback Callback)
{
	FGFGroupActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		Callback.ExecuteIfBound(bSuccess);
	});
	AddAdmin(GroupId, UserId, TypedCallback);
}

void UGameFuseGroups::BP_RemoveAdmin(const int32 GroupId, const int32 UserId, FBP_GFGroupCallback Callback)
{
	FGFGroupActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		Callback.ExecuteIfBound(bSuccess);
	});
	RemoveAdmin(GroupId, UserId, TypedCallback);
}

void UGameFuseGroups::BP_AddAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, bool bOnlyCreatorCanEdit, FBP_GFGroupCallback Callback)
{
	FGFGroupAttributeCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFGroupAttribute>& Attributes) {
		Callback.ExecuteIfBound(!Attributes.IsEmpty());
	});
	AddAttribute(GroupId, Attribute, bOnlyCreatorCanEdit, TypedCallback);
}

void UGameFuseGroups::BP_UpdateGroupAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, FBP_GFGroupCallback Callback)
{
	FGFGroupActionCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		Callback.ExecuteIfBound(bSuccess);
	});
	UpdateGroupAttribute(GroupId, Attribute, TypedCallback);
}

// void UGameFuseGroups::BP_DeleteAttribute(const int32 GroupId, const int32 AttributeId, FBP_GFGroupCallback Callback)
// {
// 	FGFGroupActionCallback TypedCallback;
// 	TypedCallback.BindLambda([Callback](bool bSuccess) {
// 		Callback.ExecuteIfBound(bSuccess);
// 	});
// 	DeleteAttribute(GroupId, AttributeId, TypedCallback);
// }

void UGameFuseGroups::BP_FetchAttributes(const int32 GroupId, FBP_GFGroupCallback Callback)
{
	FGFGroupAttributeCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFGroupAttribute>& Attributes) {
		Callback.ExecuteIfBound(!Attributes.IsEmpty());
	});
	FetchGroupAttributes(GroupId, TypedCallback);
}

void UGameFuseGroups::BP_FetchGroupAttributes(const int32 GroupId, FBP_GFGroupCallback Callback)
{
	FGFGroupAttributeCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFGroupAttribute>& Attributes) {
		Callback.ExecuteIfBound(!Attributes.IsEmpty());
	});
	FetchGroupAttributes(GroupId, TypedCallback);
}