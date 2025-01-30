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

	// Get a specific group
	FGuid GetGroup(int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Delete a group
	FGuid DeleteGroup(int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Join a group
	FGuid JoinGroup(const int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Leave a group
	FGuid LeaveGroup(const int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Get all groups the user is a member of
	FGuid GetUserGroups(const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Search for groups
	FGuid SearchGroups(const FString& Query, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Add a user as admin
	FGuid AddAdmin(const int32 GroupId, const int32 UserId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Remove a user as admin
	FGuid RemoveAdmin(const int32 GroupId, const int32 UserId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Add an attribute to a group
	FGuid AddAttribute(const int32 GroupId, const FString& Key, const FString& Value, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Update a group attribute
	FGuid UpdateAttribute(const int32 GroupId, const int32 AttributeId, const FString& Value, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Delete a group attribute
	FGuid DeleteAttribute(const int32 GroupId, const int32 AttributeId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	FGuid GetAllGroups(const FGFUserData& UserData, const FGFApiCallback& Callback);
	FGuid RequestToJoinGroup(int32 GroupId, const FGFUserData& UserData, const FGFApiCallback& Callback);
};