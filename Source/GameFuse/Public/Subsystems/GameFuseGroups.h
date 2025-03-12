#pragma once

#include "CoreMinimal.h"
#include "GameFuseUser.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Library/GameFuseStructLibrary.h"
#include "API/GroupsAPIHandler.h"
#include "GameFuseGroups.generated.h"

// Single-cast delegates for C++ callbacks
DECLARE_DELEGATE_OneParam(FGFGroupCallback, const FGFGroup&);
DECLARE_DELEGATE_OneParam(FGFGroupListCallback, const TArray<FGFGroup>&);
DECLARE_DELEGATE_OneParam(FGFGroupConnectionCallback, const FGFGroupConnection&);
DECLARE_DELEGATE_OneParam(FGFGroupAttributeCallback, const TArray<FGFGroupAttribute>&);
DECLARE_DELEGATE_OneParam(FGFGroupActionCallback, bool);

// Blueprint callback is now using the standard FBP_GFApiCallback

UCLASS()
class GAMEFUSE_API UGameFuseGroups : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// C++ API
	FGuid CreateGroup(const FGFGroup& Group, FGFGroupCallback TypedCallback);
	FGuid FetchGroup(const int32 GroupId, FGFGroupCallback TypedCallback);
	FGuid FetchAllGroups(FGFGroupListCallback TypedCallback);
	FGuid RequestToJoinGroup(int32 GroupId, FGFGroupConnectionCallback TypedCallback);
	FGuid DeleteGroup(const int32 GroupId, FGFGroupActionCallback TypedCallback);
	FGuid JoinGroup(const int32 GroupId, FGFGroupActionCallback TypedCallback);
	FGuid LeaveGroup(const int32 GroupId, FGFGroupActionCallback TypedCallback);
	FGuid FetchUserGroups(FGFGroupListCallback TypedCallback);
	FGuid SearchGroups(const FString& Query, FGFGroupListCallback TypedCallback);
	FGuid AddAdmin(const int32 GroupId, const int32 UserId, FGFGroupActionCallback TypedCallback);
	FGuid RemoveAdmin(const int32 GroupId, const int32 UserId, FGFGroupActionCallback TypedCallback);
	FGuid AddAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, bool bOnlyCreatorCanEdit, FGFGroupAttributeCallback TypedCallback);
	FGuid UpdateGroupAttribute(int32 GroupId, const FGFGroupAttribute& Attribute, FGFGroupActionCallback UntypedCallback);
	// FGuid DeleteAttribute(const int32 GroupId, const int32 AttributeId, FGFGroupActionCallback TypedCallback);
	FGuid FetchGroupAttributes(const int32 GroupId, FGFGroupAttributeCallback TypedCallback);
	FGuid RespondToGroupJoinRequest(const int32 ConnectionId, const int32 UserId, EGFInviteRequestStatus Status, FGFGroupActionCallback TypedCallback);

	// Blueprint API
	UFUNCTION(BlueprintCallable, DisplayName = "Create Group", Category = "GameFuse|Groups")
	void BP_CreateGroup(const FGFGroup& Group, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Group", Category = "GameFuse|Groups")
	void BP_FetchGroup(const int32 GroupId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Fetch All Groups", Category = "GameFuse|Groups")
	void BP_FetchAllGroups(const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Request To Join Group", Category = "GameFuse|Groups")
	void BP_RequestToJoinGroup(int32 GroupId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Delete Group", Category = "GameFuse|Groups")
	void BP_DeleteGroup(const int32 GroupId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Join Group", Category = "GameFuse|Groups")
	void BP_JoinGroup(const int32 GroupId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Leave Group", Category = "GameFuse|Groups")
	void BP_LeaveGroup(const int32 GroupId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Fetch User Groups", Category = "GameFuse|Groups")
	void BP_FetchUserGroups(const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Search Groups", Category = "GameFuse|Groups")
	void BP_SearchGroups(const FString& Query, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Add Admin", Category = "GameFuse|Groups")
	void BP_AddAdmin(const int32 GroupId, const int32 UserId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Remove Admin", Category = "GameFuse|Groups")
	void BP_RemoveAdmin(const int32 GroupId, const int32 UserId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Add Attribute", Category = "GameFuse|Groups")
	void BP_AddAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, bool bOnlyCreatorCanEdit, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Update Group Attribute", Category = "GameFuse|Groups")
	void BP_UpdateGroupAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, const FBP_GFApiCallback& Callback);

	// UFUNCTION(BlueprintCallable, DisplayName = "Delete Attribute", Category = "GameFuse|Groups")
	// void BP_DeleteAttribute(const int32 GroupId, const int32 AttributeId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Attributes", Category = "GameFuse|Groups")
	void BP_FetchAttributes(const int32 GroupId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Group Attributes", Category = "GameFuse|Groups")
	void BP_FetchGroupAttributes(const int32 GroupId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Accept Group Join Request", Category = "GameFuse|Groups")
	void BP_AcceptGroupJoinRequest(const int32 ConnectionId, const int32 UserId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Decline Group Join Request", Category = "GameFuse|Groups")
	void BP_DeclineGroupJoinRequest(const int32 ConnectionId, const int32 UserId, const FBP_GFApiCallback& Callback);

	// Getters for cached data
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	const TArray<FGFGroup>& GetUserGroups() const
	{
		return UserGroups;
	}

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	const TArray<FGFGroup>& GetAllGroups() const
	{
		return AllGroups;
	}

	TObjectPtr<UGroupsAPIHandler> GetRequestHandler() const
	{
		return RequestHandler;
	}

private:

	UPROPERTY()
	TObjectPtr<UGroupsAPIHandler> RequestHandler;

	// Cached group data
	TArray<FGFGroup> UserGroups;
	TArray<FGFGroup> AllGroups;

	// Internal response handlers
	void HandleGroupResponse(const FGFAPIResponse& Response);
	void HandleGroupListResponse(const FGFAPIResponse& Response, bool bIsUserGroups = false);
	void HandleGroupConnectionResponse(const FGFAPIResponse& Response);
	void HandleGroupActionResponse(const FGFAPIResponse& Response);
	void HandleGroupAttributeResponse(const FGFAPIResponse& Response);
	void HandleFetchAttributesResponse(FGFAPIResponse Response);

	// User callbacks storage
	TMap<FGuid, FGFGroupCallback> GroupCallbacks;
	TMap<FGuid, FGFGroupListCallback> GroupListCallbacks;
	TMap<FGuid, FGFGroupConnectionCallback> GroupConnectionCallbacks;
	TMap<FGuid, FGFGroupActionCallback> GroupActionCallbacks;
	TMap<FGuid, FGFGroupAttributeCallback> GroupAttributeCallbacks;
	TMap<FGuid, FGFGroupAttributeCallback> FetchAttributesCallbacks;

	/** Map to store blueprint callbacks by request ID */
	TMap<FGuid, FBP_GFApiCallback> BlueprintCallbacks;

	/**
	 * @brief Stores the blueprint callback in the BlueprintCallbacks map
	 * @param RequestId The request ID to associate with the callback
	 * @param Callback The blueprint callback to store
	 */
	void StoreBlueprintCallback(const FGuid& RequestId, const FBP_GFApiCallback& Callback);

	/**
	 * @brief Executes the blueprint callback associated with the given request ID
	 * @param Response The API response to pass to the callback
	 */
	void ExecuteBlueprintCallback(const FGFAPIResponse& Response);
};