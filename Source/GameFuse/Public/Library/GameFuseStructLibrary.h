/**
 *  Copyright (c) 2024-09-30 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */
#pragma once

#include "CoreMinimal.h"
#include "GameFuseEnumLibrary.h"
#include "GameFuseStructLibrary.generated.h"

// Add this new struct to the file
USTRUCT(BlueprintType, Category = "GameFuse|GameData")
struct GAMEFUSE_API FGFGameData
{
	GENERATED_BODY()

	/** Unique database ID of the game from GameFuse dashboard */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|GameData")
	int32 Id = 0;

	/** API token of the game found on your GameFuse.co dashboard */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|GameData")
	FString Token = "";

	/** Name of the game as configured in GameFuse dashboard */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|GameData")
	FString Name = "";

	/** Game description as configured in GameFuse dashboard */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|GameData")
	FString Description = "";

	/** Server timestamp when the game data was retrieved */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|GameData")
	FString ServerTime = "";

	bool operator==(const FGFGameData& Other) const
	{
		return Id == Other.Id && Token == Other.Token && Name == Other.Name && Description == Other.Description;
	}
};

USTRUCT(BlueprintType, Category = "GameFuse|UserData")
struct GAMEFUSE_API FGFUserData
{
	GENERATED_BODY()

	/** Unique database ID of the user from GameFuse */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	int32 Id = 0;

	/** Username of the user account */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	FString Username = "";

	/** Whether the user is currently signed in to GameFuse */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	bool bSignedIn = false;

	/** Total number of times the user has logged into the game */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	int32 NumberOfLogins = 0;

	/** Authentication token used for user session management and API requests */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	FString AuthenticationToken = "";

	/** User's current score that can be modified with add_score API calls */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	int32 Score = 0;

	/** User's current credits balance for in-game store purchases */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	int32 Credits = 0;

	/** Date and time of the user's last login in YYYY-MM-DD format */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	FString LastLogin = "0000-00-00";

	bool operator==(const FGFUserData& Other) const
	{
		return Id == Other.Id && Username == Other.Username;
	}
};


USTRUCT(BlueprintType, Category = "GameFuse|StoreItem")
struct GAMEFUSE_API FGFStoreItem
{
	GENERATED_BODY()
	FGFStoreItem() = default;

	/** Unique database ID of the store item */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|StoreItem")
	int32 Id = 0;

	/** Display name of the store item */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|StoreItem")
	FString Name = "";

	/** Category classification for organizing store items */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|StoreItem")
	FString Category = "";

	/** Detailed description of the store item and its effects */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|StoreItem")
	FString Description = "";

	/** Cost of the item in credits required for purchase */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|StoreItem")
	int32 Cost = 0;

	/** URL to the icon image for displaying the store item */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|StoreItem")
	FString IconUrl = "";

	bool operator==(const FGFStoreItem& Other) const
	{
		return Name == Other.Name &&
		Category == Other.Category &&
		Description == Other.Description &&
		Cost == Other.Cost &&
		Id == Other.Id;
	}
};

USTRUCT(BlueprintType, Category = "GameFuse|LeaderboardItem")
struct GAMEFUSE_API FGFLeaderboardEntry
{
	GENERATED_BODY()

	FGFLeaderboardEntry() = default;

	/** Name of the leaderboard this entry belongs to */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	FString LeaderboardName = "";

	/** Username of the player for this leaderboard entry */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	FString Username = "";

	/** Score achieved by the player for this leaderboard entry */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	int32 Score = 0;

	/** GameFuse user ID of the player who achieved this score */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	int32 GameUserId = 0;

	/** Additional custom data associated with this leaderboard entry */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	TMap<FString, FString> Metadata;

	/** Date and time when this leaderboard entry was created */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	FString DateTime = "";
};

USTRUCT(BlueprintType, Category = "GameFuse|Leaderboard")
struct GAMEFUSE_API FGFLeaderboard
{
	GENERATED_BODY()

	FGFLeaderboard() = default;

	FGFLeaderboard(FString Name)
	{
		this->Name = Name;
		this->Entries = TArray<FGFLeaderboardEntry>();
	}

	/** Name identifier of the leaderboard */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	FString Name = "";

	/** Array of leaderboard entries sorted by rank */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	TArray<FGFLeaderboardEntry> Entries;
};

USTRUCT(BlueprintType)
struct GAMEFUSE_API FGFAttributeList
{
	GENERATED_BODY()

	/** Key-value pairs of custom user attributes for storing game-specific data */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Attributes")
	TMap<FString, FString> Attributes;

	bool operator==(const FGFAttributeList& Other) const
	{
		if (Attributes.Num() != Other.Attributes.Num()) {
			return false;
		}

		for (const auto& Pair : Attributes) {
			const FString* OtherValue = Other.Attributes.Find(Pair.Key);
			if (!OtherValue || *OtherValue != Pair.Value) {
				return false;
			}
		}
		return true;
	}
};

/**
 * Represents a message in a chat
 */
USTRUCT(BlueprintType)
struct GAMEFUSE_API FGFMessage
{
	GENERATED_BODY()

	/** The unique identifier of the message */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Chat")
	int32 Id = 0;

	/** The message text content */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFuse|Chat")
	FString Text;

	/** The ID of the user who sent the message */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Chat")
	int32 UserId = 0;

	/** When the message was created */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Chat")
	FDateTime CreatedAt;

	/** List of user IDs who have read the message */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Chat")
	TArray<int32> ReadBy;

	/** Whether the current user has read the message */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Chat")
	bool bRead = false;

	bool operator==(const FGFMessage& Other) const
	{
		return Id == Other.Id
			&& Text == Other.Text
			&& UserId == Other.UserId
			&& CreatedAt == Other.CreatedAt
			&& ReadBy == Other.ReadBy
			&& bRead == Other.bRead;
	}
};

/**
 * Represents a chat (both direct and group chats)
 */
USTRUCT(BlueprintType)
struct GAMEFUSE_API FGFChat
{
	GENERATED_BODY()

	/** The unique identifier of the chat */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Chat")
	int32 Id = 0;

	/** The ID of the user who created the chat */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Chat")
	int32 CreatorId = 0;

	/** The type of creator (User, etc.) */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Chat")
	FString CreatorType;

	/** List of messages in the chat */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Chat")
	TArray<FGFMessage> Messages;

	/** List of users participating in the chat */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Chat")
	TArray<FGFUserData> Participants;

	bool operator==(const FGFChat& Other) const
	{
		return Id == Other.Id
			&& CreatorId == Other.CreatorId
			&& CreatorType == Other.CreatorType
			&& Messages == Other.Messages
			&& Participants == Other.Participants;
	}
};

/**
 * Represents a group attribute
 */
USTRUCT(BlueprintType)
struct GAMEFUSE_API FGFGroupAttribute
{
	GENERATED_BODY()

	/** The unique identifier of the attribute */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Groups")
	int32 Id = 0;

	/** The key name of the attribute for identification */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFuse|Groups")
	FString Key;

	/** The value stored for this attribute */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFuse|Groups")
	FString Value;

	/**
	 * When creating/updating an attribute: Set this to the target group's ID
	 * When receiving an attribute from the server: Contains the ID of the user who created the attribute
	 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFuse|Groups", meta=(DisplayName="Creator/Group ID"))
	int32 CreatorId = 0;

	/** Whether the attribute can be edited by non-admin members. Read-only, set via bOnlyCreatorCanEdit parameter when creating */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Groups")
	bool bCanEdit = false;

	bool operator==(const FGFGroupAttribute& Other) const
	{
		return Id == Other.Id
			&& Key == Other.Key
			&& Value == Other.Value
			&& CreatorId == Other.CreatorId
			&& bCanEdit == Other.bCanEdit;
	}
};

USTRUCT(BlueprintType)
struct GAMEFUSE_API FGFGroupConnection
{
	GENERATED_BODY()

	/** Unique identifier for this group connection */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFuse|Groups")
	int32 Id;

	/** Current status of the invite or join request */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFuse|Groups")
	EGFInviteRequestStatus Status;

	/** User data for the user in this group connection */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFuse|Groups")
	FGFUserData User;

	FGFGroupConnection() :
		Id(0), Status(EGFInviteRequestStatus::None)
	{
	}

	bool operator==(const FGFGroupConnection& Other) const
	{
		return Id == Other.Id &&
		Status == Other.Status &&
		User == Other.User;
	}
};

USTRUCT(BlueprintType, Category = "GameFuse|Groups")
struct GAMEFUSE_API FGFGroup
{
	GENERATED_BODY()

	/** Unique identifier of the group */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	int32 Id = 0;

	/** Display name of the group */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	FString Name = "";

	/** Type classification of the group (e.g., "clan", "guild", "team") */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	FString GroupType = "";

	/** Maximum number of members allowed in this group */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	int32 MaxGroupSize = 0;

	/** Whether users can automatically join this group without approval */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	bool bCanAutoJoin = false;

	/** Whether the group only accepts members through invitations */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	bool bIsInviteOnly = false;

	/** Whether this group appears in search results */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	bool bSearchable = true;

	/** Whether only admins can create group attributes */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	bool bAdminsOnlyCanCreateAttributes = false;

	/** Current number of members in the group */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	int32 MemberCount = 0;

	/** Array of all group members */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	TArray<FGFUserData> Members;

	/** Array of group administrators with elevated permissions */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	TArray<FGFUserData> Admins;

	/** Custom attributes associated with this group */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	TArray<FGFGroupAttribute> Attributes;

	/** Pending requests to join this group */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	TArray<FGFGroupConnection> JoinRequests;

	/** Pending invitations sent by this group */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	TArray<FGFGroupConnection> Invites;

	bool operator==(const FGFGroup& Other) const
	{
		return Id == Other.Id && Name == Other.Name;
	}
};

USTRUCT(BlueprintType, Category = "GameFuse| API")
struct GAMEFUSE_API FGFAPIResponse
{
	GENERATED_BODY()

	/** Whether the API request was successful */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|API")
	bool bSuccess = false;

	/** Raw response string from the GameFuse API */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|API")
	FString ResponseStr = "";

	/** Unique identifier for tracking this specific API request */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|API")
	FGuid RequestId;
	FGFAPIResponse() = default;

	/** HTTP response code from the API request (200, 401, 500, etc.) */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|API")
	int ResponseCode = 0;

	FGFAPIResponse(bool _bSuccess, const FString& _Response, const FGuid& _RequestId = FGuid(), int _ResponseCode = 0)
	{
		bSuccess = _bSuccess;
		ResponseStr = _Response;
		RequestId = _RequestId;
		ResponseCode = _ResponseCode;
	}
};

// Game Round Rankings User Data
USTRUCT(BlueprintType, Category = "GameFuse|GameRound")

struct GAMEFUSE_API FGFGameRoundRanking
{
	GENERATED_BODY()

	/** Final placement/rank of the user in the game round (1st, 2nd, 3rd, etc.) */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 Place = 0;

	/** Score achieved by the user in this game round */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 Score = 0;

	/** When the user started participating in this game round */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	FDateTime StartTime;

	/** When the user finished participating in this game round */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	FDateTime EndTime;

	/** User data for the player in this ranking */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	FGFUserData User;

	bool operator==(const FGFGameRoundRanking& Other) const
	{
		return Place == Other.Place && Score == Other.Score && StartTime == Other.StartTime && EndTime == Other.EndTime && User == Other.User;
	}
};

// Main Game Round Structure
USTRUCT(BlueprintType, Category = "GameFuse|GameRound")

struct GAMEFUSE_API FGFGameRound
{
	GENERATED_BODY()

	/**
	 * The ID of the game round. Will be set by the server when creating a new round.
	 * For updates, this should match the existing round's ID.
	 */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 Id = 0;

	/** The GameFuse user ID of the player who participated in this round */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 GameUserId = 0;

	/** When this game round started */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	FDateTime StartTime;

	/** When this game round ended */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	FDateTime EndTime;

	/** Final score achieved in this game round */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 Score = 0;

	/** Final placement/rank in this game round (-1 if not set) */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 Place = -1;

	/** Type or category of game (e.g., "deathmatch", "racing", "puzzle") */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	FString GameType = "";

	/** ID linking to a multiplayer game round if this is part of a multiplayer session */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 MultiplayerGameRoundId = -1;

	/** Custom key-value data associated with this game round */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	TMap<FString, FString> Metadata;

	/** Whether this is a multiplayer game round involving multiple players */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	bool bMultiplayer = false;

	/** Rankings of all players if this is a multiplayer round */
	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	TArray<FGFGameRoundRanking> Rankings;

	// Constructor for easy initialization
	FGFGameRound()
	{}

	bool operator==(const FGFGameRound& Other) const
	{
		if (Id != Other.Id || GameUserId != Other.GameUserId || StartTime != Other.StartTime || EndTime != Other.EndTime || GameType != Other.GameType || MultiplayerGameRoundId != Other.MultiplayerGameRoundId || bMultiplayer != Other.bMultiplayer) {
			return false;
		}

		// not comparing rankings

		// Compare Metadata
		for (const auto& Pair : Metadata) {
			const FString* OtherValue = Other.Metadata.Find(Pair.Key);
			if (!OtherValue || *OtherValue != Pair.Value) {
				return false;
			}
		}

		return true;
	}
};

USTRUCT(BlueprintType)
struct GAMEFUSE_API FGFFriendRequest
{
	GENERATED_BODY()

	/** Unique identifier for this friendship/friend request */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Friends")
	int32 FriendshipId = 0;

	/** User data for the other user in this friend relationship */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Friends")
	FGFUserData OtherUser;

	/** Current status of the friend request (pending, accepted, etc.) */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Friends")
	EGFInviteRequestStatus Status = EGFInviteRequestStatus::None;

	/** When this friend request was created */
	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Friends")
	FDateTime RequestCreatedAt;

	bool operator==(const FGFFriendRequest& Other) const
	{
		return FriendshipId == Other.FriendshipId &&
		OtherUser == Other.OtherUser &&
		Status == Other.Status;
	}
};