#pragma once

#include "CoreMinimal.h"
#include "API/APIRequestHandler.h"
#include "Library/GameFuseStructLibrary.h"
#include "Library/GameFuseEnumLibrary.h"
#include "FriendsAPIHandler.generated.h"

/**
 * API Handler for GameFuse Friends functionality
 */
UCLASS()
class GAMEFUSE_API UFriendsAPIHandler : public UAPIRequestHandler
{
	GENERATED_BODY()

public:
	// Send a friend request
	FGuid SendFriendRequest(const FString& Username, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Accept or decline a friend request
	FGuid RespondToFriendRequest(int32 FriendshipId, EGFInviteRequestStatus Status, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Cancel a friend request
	FGuid CancelFriendRequest(int32 FriendshipId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Unfriend a player
	FGuid UnfriendPlayer(int32 UserId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Get all friendship data
	FGuid GetFriendshipData(const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Get friends list
	FGuid GetFriendsList(const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Get outgoing friend requests
	FGuid GetOutgoingFriendRequests(const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Get incoming friend requests
	FGuid GetIncomingFriendRequests(const FGFUserData& UserData, const FGFApiCallback& Callback);
}; 