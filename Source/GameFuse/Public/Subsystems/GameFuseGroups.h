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
	/**
	 * Creates a new group
	 * @param Group The group data to create
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid CreateGroup(const FGFGroup& Group, FGFGroupCallback TypedCallback);
	
	/**
	 * Fetches a specific group by ID
	 * @param GroupId The ID of the group to fetch
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid FetchGroup(const int32 GroupId, FGFGroupCallback TypedCallback);
	
	/**
	 * Fetches all available groups
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid FetchAllGroups(FGFGroupListCallback TypedCallback);
	
	/**
	 * Requests to join a group
	 * @param GroupId The ID of the group to join
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid RequestToJoinGroup(int32 GroupId, FGFGroupConnectionCallback TypedCallback);
	
	/**
	 * Invites a user to join a group
	 * @param GroupId The ID of the group to invite the user to
	 * @param UserIdToInvite The ID of the user to invite
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid InviteGroupMember(int32 GroupId, int32 UserIdToInvite, FGFGroupConnectionCallback TypedCallback);
	
	/**
	 * Deletes a group (admin only)
	 * @param GroupId The ID of the group to delete
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid DeleteGroup(const int32 GroupId, FGFGroupActionCallback TypedCallback);
	
	/**
	 * Joins a group directly (if allowed)
	 * @param GroupId The ID of the group to join
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid JoinGroup(const int32 GroupId, FGFGroupActionCallback TypedCallback);
	
	/**
	 * Leaves a group
	 * @param GroupId The ID of the group to leave
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid LeaveGroup(const int32 GroupId, FGFGroupActionCallback TypedCallback);
	
	/**
	 * Fetches groups for the current user
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid FetchMyGroups(FGFGroupListCallback TypedCallback);
	
	/**
	 * Searches for groups by query, filling the Fetched groups data
	 * @param Query The search query
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid SearchGroups(const FString& Query, FGFGroupListCallback TypedCallback);
	
	/**
	 * Adds a user as admin to a group
	 * @param GroupId The ID of the group
	 * @param UserId The ID of the user to make admin
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid AddAdmin(const int32 GroupId, const int32 UserId, FGFGroupActionCallback TypedCallback);
	
	/**
	 * Removes admin status from a user in a group
	 * @param GroupId The ID of the group
	 * @param UserId The ID of the user to remove admin status from
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid RemoveAdmin(const int32 GroupId, const int32 UserId, FGFGroupActionCallback TypedCallback);
	
	/**
	 * Adds an attribute to a group
	 * @param GroupId The ID of the group
	 * @param Attribute The attribute to add
	 * @param bOthersCanEdit Whether other users can edit this attribute
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid AddAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, bool bOthersCanEdit, FGFGroupAttributeCallback TypedCallback);
	
	/**
	 * Updates a group attribute
	 * @param GroupId The ID of the group
	 * @param Attribute The updated attribute data
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid UpdateGroupAttribute(int32 GroupId, const FGFGroupAttribute& Attribute, FGFGroupActionCallback TypedCallback);
	// FGuid DeleteAttribute(const int32 GroupId, const int32 AttributeId, FGFGroupActionCallback TypedCallback);
	
	/**
	 * Fetches attributes for a group
	 * @param GroupId The ID of the group
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid FetchGroupAttributes(const int32 GroupId, FGFGroupAttributeCallback TypedCallback);
	
	/**
	 * Responds to a group join request (accept/decline)
	 * @param ConnectionId The ID of the connection request
	 * @param UserId The ID of the user making the request
	 * @param Status The response status (accept/decline)
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid RespondToGroupJoinRequest(const int32 ConnectionId, const int32 UserId, EGFInviteRequestStatus Status, FGFGroupActionCallback TypedCallback);

	// Blueprint API
	/**
	 * Creates a new group (Blueprint version)
	 * @param Group The group data to create
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Create Group", Category = "GameFuse|Groups")
	void BP_CreateGroup(const FGFGroup& Group, const FBP_GFApiCallback& Callback);

	/**
	 * Fetches a specific group by ID (Blueprint version)
	 * @param GroupId The ID of the group to fetch
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Group", Category = "GameFuse|Groups")
	void BP_FetchGroup(const int32 GroupId, const FBP_GFApiCallback& Callback);

	/**
	 * Fetches all available groups (Blueprint version)
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch All Groups", Category = "GameFuse|Groups")
	void BP_FetchAllGroups(const FBP_GFApiCallback& Callback);

	/**
	 * Requests to join a group (Blueprint version)
	 * @param GroupId The ID of the group to join
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Request To Join Group", Category = "GameFuse|Groups")
	void BP_RequestToJoinGroup(int32 GroupId, const FBP_GFApiCallback& Callback);

	/**
	 * Invites a user to join a group (Blueprint version)
	 * @param GroupId The ID of the group to invite the user to
	 * @param UserIdToInvite The ID of the user to invite
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Invite Group Member", Category = "GameFuse|Groups")
	void BP_InviteGroupMember(int32 GroupId, int32 UserIdToInvite, const FBP_GFApiCallback& Callback);

	/**
	 * Deletes a group (admin only) (Blueprint version)
	 * @param GroupId The ID of the group to delete
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Delete Group", Category = "GameFuse|Groups")
	void BP_DeleteGroup(const int32 GroupId, const FBP_GFApiCallback& Callback);

	/**
	 * Joins a group directly (if allowed) (Blueprint version)
	 * @param GroupId The ID of the group to join
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Join Group", Category = "GameFuse|Groups")
	void BP_JoinGroup(const int32 GroupId, const FBP_GFApiCallback& Callback);

	/**
	 * Leaves a group (Blueprint version)
	 * @param GroupId The ID of the group to leave
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Leave Group", Category = "GameFuse|Groups")
	void BP_LeaveGroup(const int32 GroupId, const FBP_GFApiCallback& Callback);

	/**
	 * Fetches groups for the current user (Blueprint version)
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch My Groups", Category = "GameFuse|Groups")
	void BP_FetchMyGroups(const FBP_GFApiCallback& Callback);

	/**
	 * Searches for groups by query (Blueprint version)
	 * @param Query The search query
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Search Groups", Category = "GameFuse|Groups")
	void BP_SearchGroups(const FString& Query, const FBP_GFApiCallback& Callback);

	/**
	 * Adds a user as admin to a group (Blueprint version)
	 * @param GroupId The ID of the group
	 * @param UserId The ID of the user to make admin
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Add Admin", Category = "GameFuse|Groups")
	void BP_AddAdmin(const int32 GroupId, const int32 UserId, const FBP_GFApiCallback& Callback);

	/**
	 * Removes admin status from a user in a group (Blueprint version)
	 * @param GroupId The ID of the group
	 * @param UserId The ID of the user to remove admin status from
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Remove Admin", Category = "GameFuse|Groups")
	void BP_RemoveAdmin(const int32 GroupId, const int32 UserId, const FBP_GFApiCallback& Callback);

	/**
	 * Adds an attribute to a group (Blueprint version)
	 * @param GroupId The ID of the group
	 * @param Attribute The attribute to add
	 * @param bOthersCanEdit Whether other users can edit this attribute
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Add Attribute", Category = "GameFuse|Groups")
	void BP_AddAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, bool bOthersCanEdit, const FBP_GFApiCallback& Callback);

	/**
	 * Updates a group attribute (Blueprint version)
	 * @param GroupId The ID of the group
	 * @param Attribute The updated attribute data
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Update Group Attribute", Category = "GameFuse|Groups")
	void BP_UpdateGroupAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, const FBP_GFApiCallback& Callback);

	// UFUNCTION(BlueprintCallable, DisplayName = "Delete Attribute", Category = "GameFuse|Groups")
	// void BP_DeleteAttribute(const int32 GroupId, const int32 AttributeId, const FBP_GFApiCallback& Callback);

	/**
	 * Fetches attributes for a group (Blueprint version)
	 * @param GroupId ID of group
	 * @param Callback Callback to execute when the request is complete
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Group Attributes", Category = "GameFuse|Groups")
	void BP_FetchGroupAttributes(const int32 GroupId, const FBP_GFApiCallback& Callback);

	/**
	 * Accepts a group join request (Blueprint version)
	 * @param ConnectionId The ID of the connection request
	 * @param UserId The ID of the user making the request
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Accept Group Join Request", Category = "GameFuse|Groups")
	void BP_AcceptGroupJoinRequest(const int32 ConnectionId, const int32 UserId, const FBP_GFApiCallback& Callback);

	/**
	 * Declines a group join request (Blueprint version)
	 * @param ConnectionId The ID of the connection request
	 * @param UserId The ID of the user making the request
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Decline Group Join Request", Category = "GameFuse|Groups")
	void BP_DeclineGroupJoinRequest(const int32 ConnectionId, const int32 UserId, const FBP_GFApiCallback& Callback);

	// Getters for cached data
	/**
	 * Gets the cached list of user groups, use FetchMyGroups to fill this
	 * @return The last fetched user groups
	 */
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	const TArray<FGFGroup>& GetMyGroups() const
	{
		return MyGroups;
	}

	/**
	 * Gets the cached list of fetched groups, usually filled by Search Groups or Fetch All Groups
	 * @return The last fetched list of groups
	 */
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	const TArray<FGFGroup>& GetFetchedGroups() const
	{
		return FetchedGroups;
	}

	/**
	 * Retrieves a specific group by its ID from the cached groups
	 * @param GroupId The ID of the group to find
	 * @param OutGroup The found group (if successful)
	 * @return True if the group was found, false otherwise
	 */
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Groups")
	bool GetGroupById(const int32 GroupId, FGFGroup& OutGroup) const;

	/**
	 * Gets the request handler for direct API access
	 * @return Pointer to the groups API handler
	 */
	TObjectPtr<UGroupsAPIHandler> GetRequestHandler() const
	{
		return RequestHandler;
	}

private:

	UPROPERTY()
	TObjectPtr<UGroupsAPIHandler> RequestHandler;

	// Cached group data
	TArray<FGFGroup> MyGroups;

	/**
	 * Cached groups fetched from the API, usually filled by SearchGroups or FetchAllGroups
	 */
	TArray<FGFGroup> FetchedGroups;

	// Internal response handlers
	/**
	 * Handles responses for single group operations
	 * @param Response The API response to process
	 */
	void HandleGroupResponse(const FGFAPIResponse& Response);
	
	/**
	 * Handles responses for group list operations
	 * @param Response The API response to process
	 * @param bIsUserGroups Whether this is for user groups or all groups
	 */
	void HandleGroupListResponse(const FGFAPIResponse& Response, bool bIsUserGroups = false);
	
	/**
	 * Handles responses for group connection operations
	 * @param Response The API response to process
	 */
	void HandleGroupConnectionResponse(const FGFAPIResponse& Response);
	
	/**
	 * Handles responses for group action operations
	 * @param Response The API response to process
	 */
	void HandleGroupActionResponse(const FGFAPIResponse& Response);
	
	/**
	 * Handles responses for group attribute operations
	 * @param Response The API response to process
	 */
	void HandleGroupAttributeResponse(const FGFAPIResponse& Response);
	
	/**
	 * Handles responses for fetching group attributes
	 * @param Response The API response to process
	 */
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