#pragma once

#include "CoreMinimal.h"
#include "API/APIRequestHandler.h"
#include "Library/GameFuseStructLibrary.h"
#include "Library/GameFuseEnumLibrary.h"
#include "GroupsAPIHandler.generated.h"

/**
 * API Handler for GameFuse Groups functionality
 */
UCLASS()
class GAMEFUSE_API UGroupsAPIHandler : public UAPIRequestHandler
{
	GENERATED_BODY()

public:

	// Create a new group
	FGuid CreateGroup(const FGFGroup& Group, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Fetch a specific group
	FGuid FetchGroup(int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Delete a group
	FGuid DeleteGroup(int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Join a group
	FGuid JoinGroup(const int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Leave a group
	FGuid LeaveGroup(const int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Fetch all groups the user is a member of
	FGuid FetchUserGroups(const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Search for groups
	FGuid SearchGroups(const FString& Query, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Add a user as admin
	FGuid AddAdmin(const int32 GroupId, const int32 UserId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Remove a user as admin
	FGuid RemoveAdmin(const int32 GroupId, const int32 UserId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	/**
	 * Add an attribute to a group
	 * @param GroupId - The ID of the group to add the attribute to
	 * @param Attribute - The attribute to add, GroupId and bCanEdit are read only and ignored for this request
	 * @param bOnlyCreatorCanEdit - Whether only the creator can edit this attribute
	 * @param UserData - The user data of the requester
	 * @param Callback - The callback to handle the response
	 */
	FGuid AddAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, bool bOnlyCreatorCanEdit, const FGFUserData& UserData, const FGFApiCallback& Callback);

	/**
	 * Fetch all attributes for a group
	 * @param GroupId - The ID of the group to fetch attributes for
	 * @param UserData - The user data of the requester
	 * @param Callback - The callback to handle the response
	 */
	FGuid FetchGroupAttributes(const int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	/**
	 * Updates an existing group attribute
	 * @param GroupId The ID of the group
	 * @param Attribute The attribute to update, must have valid Id and new Value
	 * @param UserData The user data for authentication
	 * @param Callback The callback to handle the response
	 * @return Request ID
	 */
	FGuid UpdateGroupAttribute(const int32 GroupId, const FGFGroupAttribute& Attribute, const FGFUserData& UserData, FGFApiCallback Callback);

	// Delete a group attribute
	// FGuid DeleteAttribute(const int32 GroupId, const int32 AttributeId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid FetchAllGroups(const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid RequestToJoinGroup(int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Respond to a group join request
	FGuid RespondToGroupJoinRequest(const int32 ConnectionId, const int32 UserId, EGFInviteRequestStatus Status, const FGFUserData& UserData, const FGFApiCallback& Callback);
};