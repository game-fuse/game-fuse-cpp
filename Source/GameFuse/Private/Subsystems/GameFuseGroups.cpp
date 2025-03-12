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

void UGameFuseGroups::StoreBlueprintCallback(const FGuid& RequestId, const FBP_GFApiCallback& Callback)
{
	if (Callback.IsBound()) {
		BlueprintCallbacks.Add(RequestId, Callback);
	}
}

void UGameFuseGroups::ExecuteBlueprintCallback(const FGFAPIResponse& Response)
{
	if (BlueprintCallbacks.Contains(Response.RequestId)) {
		BlueprintCallbacks[Response.RequestId].ExecuteIfBound(Response);
		BlueprintCallbacks.Remove(Response.RequestId);
	}
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
		HandleGroupListResponse(Response, true);
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
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	FGFGroup Group;
	if (!GameFuseUtilities::ConvertJsonToGroup(Group, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse group from response"));
		if (GroupCallbacks.Contains(Response.RequestId)) {
			GroupCallbacks[Response.RequestId].ExecuteIfBound(FGFGroup());
			GroupCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	// Update cached data
	UserGroups.AddUnique(Group);
	AllGroups.AddUnique(Group);

	if (GroupCallbacks.Contains(Response.RequestId)) {
		GroupCallbacks[Response.RequestId].ExecuteIfBound(Group);
		GroupCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseGroups::HandleGroupListResponse(const FGFAPIResponse& Response, bool bIsUserGroups)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle group list response: %s"), *Response.ResponseStr);
		if (GroupListCallbacks.Contains(Response.RequestId)) {
			GroupListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFGroup>());
			GroupListCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	TArray<FGFGroup> Groups;
	if (!GameFuseUtilities::ConvertJsonToGroups(Groups, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse groups from response"));
		if (GroupListCallbacks.Contains(Response.RequestId)) {
			GroupListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFGroup>());
			GroupListCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	// Update cached data
	if (bIsUserGroups) {
		UserGroups = Groups;
	} else {
		AllGroups = Groups;
	}

	if (GroupListCallbacks.Contains(Response.RequestId)) {
		GroupListCallbacks[Response.RequestId].ExecuteIfBound(Groups);
		GroupListCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseGroups::HandleGroupConnectionResponse(const FGFAPIResponse& Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle group connection response: %s"), *Response.ResponseStr);
		if (GroupConnectionCallbacks.Contains(Response.RequestId)) {
			GroupConnectionCallbacks[Response.RequestId].ExecuteIfBound(FGFGroupConnection());
			GroupConnectionCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	FGFGroupConnection Connection;
	if (!GameFuseUtilities::ConvertJsonToGroupConnection(Connection, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse group connection from response"));
		if (GroupConnectionCallbacks.Contains(Response.RequestId)) {
			GroupConnectionCallbacks[Response.RequestId].ExecuteIfBound(FGFGroupConnection());
			GroupConnectionCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	if (GroupConnectionCallbacks.Contains(Response.RequestId)) {
		GroupConnectionCallbacks[Response.RequestId].ExecuteIfBound(Connection);
		GroupConnectionCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseGroups::HandleGroupActionResponse(const FGFAPIResponse& Response)
{
	if (GroupActionCallbacks.Contains(Response.RequestId)) {
		GroupActionCallbacks[Response.RequestId].ExecuteIfBound(Response.bSuccess);
		GroupActionCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseGroups::HandleGroupAttributeResponse(const FGFAPIResponse& Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle group attribute response: %s"), *Response.ResponseStr);
		if (GroupAttributeCallbacks.Contains(Response.RequestId)) {
			GroupAttributeCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFGroupAttribute>());
			GroupAttributeCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	TArray<FGFGroupAttribute> Attributes;
	if (!GameFuseUtilities::ConvertJsonToGroupAttributes(Attributes, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse group attributes from response"));
		if (GroupAttributeCallbacks.Contains(Response.RequestId)) {
			GroupAttributeCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFGroupAttribute>());
			GroupAttributeCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	if (GroupAttributeCallbacks.Contains(Response.RequestId)) {
		GroupAttributeCallbacks[Response.RequestId].ExecuteIfBound(Attributes);
		GroupAttributeCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseGroups::HandleFetchAttributesResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle fetch attributes response: %s"), *Response.ResponseStr);
		if (FetchAttributesCallbacks.Contains(Response.RequestId)) {
			FetchAttributesCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFGroupAttribute>());
			FetchAttributesCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	TArray<FGFGroupAttribute> Attributes;
	if (!GameFuseUtilities::ConvertJsonToGroupAttributes(Attributes, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse group attributes from response"));
		if (FetchAttributesCallbacks.Contains(Response.RequestId)) {
			FetchAttributesCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFGroupAttribute>());
			FetchAttributesCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	if (FetchAttributesCallbacks.Contains(Response.RequestId)) {
		FetchAttributesCallbacks[Response.RequestId].ExecuteIfBound(Attributes);
		FetchAttributesCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

// Blueprint API implementations
void UGameFuseGroups::BP_CreateGroup(const FGFGroup& Group, const FBP_GFApiCallback& Callback)
{
	FGFGroupCallback TypedCallback;
	FGuid RequestId = CreateGroup(Group, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_FetchGroup(const int32 GroupId, const FBP_GFApiCallback& Callback)
{
	FGFGroupCallback TypedCallback;
	FGuid RequestId = FetchGroup(GroupId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_FetchAllGroups(const FBP_GFApiCallback& Callback)
{
	FGFGroupListCallback TypedCallback;
	FGuid RequestId = FetchAllGroups(TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_RequestToJoinGroup(int32 GroupId, const FBP_GFApiCallback& Callback)
{
	FGFGroupConnectionCallback TypedCallback;
	FGuid RequestId = RequestToJoinGroup(GroupId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_DeleteGroup(const int32 GroupId, const FBP_GFApiCallback& Callback)
{
	FGFGroupActionCallback TypedCallback;
	FGuid RequestId = DeleteGroup(GroupId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_JoinGroup(const int32 GroupId, const FBP_GFApiCallback& Callback)
{
	FGFGroupActionCallback TypedCallback;
	FGuid RequestId = JoinGroup(GroupId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_LeaveGroup(const int32 GroupId, const FBP_GFApiCallback& Callback)
{
	FGFGroupActionCallback TypedCallback;
	FGuid RequestId = LeaveGroup(GroupId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_FetchUserGroups(const FBP_GFApiCallback& Callback)
{
	FGFGroupListCallback TypedCallback;
	FGuid RequestId = FetchUserGroups(TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_SearchGroups(const FString& Query, const FBP_GFApiCallback& Callback)
{
	FGFGroupListCallback TypedCallback;
	FGuid RequestId = SearchGroups(Query, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_AddAdmin(const int32 GroupId, const int32 UserId, const FBP_GFApiCallback& Callback)
{
	FGFGroupActionCallback TypedCallback;
	FGuid RequestId = AddAdmin(GroupId, UserId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_RemoveAdmin(const int32 GroupId, const int32 UserId, const FBP_GFApiCallback& Callback)
{
	FGFGroupActionCallback TypedCallback;
	FGuid RequestId = RemoveAdmin(GroupId, UserId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_AddAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, bool bOnlyCreatorCanEdit, const FBP_GFApiCallback& Callback)
{
	FGFGroupAttributeCallback TypedCallback;
	FGuid RequestId = AddAttribute(GroupId, Attribute, bOnlyCreatorCanEdit, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_UpdateGroupAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, const FBP_GFApiCallback& Callback)
{
	FGFGroupActionCallback TypedCallback;
	FGuid RequestId = UpdateGroupAttribute(GroupId, Attribute, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

// void UGameFuseGroups::BP_DeleteAttribute(const int32 GroupId, const int32 AttributeId, FBP_GFGroupCallback Callback)
// {
// 	FGFGroupActionCallback TypedCallback;
// 	TypedCallback.BindLambda([Callback](bool bSuccess) {
// 		Callback.ExecuteIfBound(bSuccess);
// 	});
// 	DeleteAttribute(GroupId, AttributeId, TypedCallback);
// }


void UGameFuseGroups::BP_FetchGroupAttributes(const int32 GroupId, const FBP_GFApiCallback& Callback)
{
	FGFGroupAttributeCallback TypedCallback;
	FGuid RequestId = FetchGroupAttributes(GroupId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_AcceptGroupJoinRequest(const int32 ConnectionId, const int32 UserId, const FBP_GFApiCallback& Callback)
{
	FGFGroupActionCallback TypedCallback;
	FGuid RequestId = RespondToGroupJoinRequest(ConnectionId, UserId, EGFInviteRequestStatus::Accepted, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseGroups::BP_DeclineGroupJoinRequest(const int32 ConnectionId, const int32 UserId, const FBP_GFApiCallback& Callback)
{
	FGFGroupActionCallback TypedCallback;
	FGuid RequestId = RespondToGroupJoinRequest(ConnectionId, UserId, EGFInviteRequestStatus::Declined, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

bool UGameFuseGroups::GetGroupById(const int32 GroupId, FGFGroup& OutGroup) const
{
	// First check in UserGroups
	for (const FGFGroup& Group : UserGroups)
	{
		if (Group.Id == GroupId)
		{
			OutGroup = Group;
			return true;
		}
	}

	// If not found in UserGroups, check in AllGroups
	for (const FGFGroup& Group : AllGroups)
	{
		if (Group.Id == GroupId)
		{
			OutGroup = Group;
			return true;
		}
	}

	// Group not found
	return false;
}