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

struct FGFGameData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|GameData")
	int32 Id = 0;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|GameData")
	FString Token = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|GameData")
	FString Name = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|GameData")
	FString Description = "";

	bool operator==(const FGFGameData& Other) const
	{
		return Id == Other.Id && Token == Other.Token && Name == Other.Name && Description == Other.Description;
	}
};

USTRUCT(BlueprintType, Category = "GameFuse|UserData")

struct FGFUserData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	int32 Id = 0;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	FString Username = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	bool bSignedIn = false;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	int32 NumberOfLogins = 0;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	FString AuthenticationToken = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	int32 Score = 0;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	int32 Credits = 0;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|UserData")
	FString LastLogin = "0000-00-00";

	bool operator==(const FGFUserData& Other) const
	{
		return Id == Other.Id && Username == Other.Username;
	}
};


USTRUCT(BlueprintType, Category = "GameFuse|StoreItem")

struct FGFStoreItem
{
	GENERATED_BODY()
	FGFStoreItem() = default;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|StoreItem")
	FString Name = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|StoreItem")
	FString Category = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|StoreItem")
	FString Description = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|StoreItem")
	int32 Cost = 0;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|StoreItem")
	int32 Id = 0;

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

struct FGFLeaderboardEntry
{
	GENERATED_BODY()

	FGFLeaderboardEntry() = default;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	FString LeaderboardName = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	FString Username = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	int32 Score = 0;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	int32 GameUserId = 0;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	TMap<FString, FString> ExtraAttributes;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	FString DateTime = "";
};

USTRUCT(BlueprintType, Category = "GameFuse|Leaderboard")

struct FGFLeaderboard
{
	GENERATED_BODY()

	FGFLeaderboard() = default;

	FGFLeaderboard(FString Name)
	{
		this->Name = Name;
		this->Entries = TArray<FGFLeaderboardEntry>();
	}


	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	FString Name = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Leaderboard")
	TArray<FGFLeaderboardEntry> Entries;
};

USTRUCT(BlueprintType, Category = "GameFuse|Groups")
struct FGFGroupAttribute
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	int32 Id = 0;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	FString Key = "";

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	FString Value = "";

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	int32 CreatorId = 0;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	bool bCanEdit = false;
};

USTRUCT(BlueprintType, Category = "GameFuse|Groups")
struct FGFGroup
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	int32 Id = 0;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	FString Name = "";

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	FString GroupType = "";

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	int32 MaxGroupSize = 0;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	bool bCanAutoJoin = false;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	bool bIsInviteOnly = false;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	bool bSearchable = true;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	bool bAdminsOnlyCanCreateAttributes = false;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	int32 MemberCount = 0;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	TArray<FGFUserData> Members;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	TArray<FGFUserData> Admins;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|Groups")
	TArray<FGFGroupAttribute> Attributes;

	bool operator==(const FGFGroup& Other) const
	{
		return Id == Other.Id && Name == Other.Name;
	}
};

USTRUCT(BlueprintType)
struct GAMEFUSE_API FGFGroupConnection
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFuse|Groups")
	int32 Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFuse|Groups")
	FString Status;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameFuse|Groups")
	FGFUserData User;

	FGFGroupConnection()
		: Id(0)
		, Status("")
	{
	}

	bool operator==(const FGFGroupConnection& Other) const
	{
		return Id == Other.Id && 
			   Status == Other.Status && 
			   User == Other.User;
	}
};

USTRUCT(BlueprintType, Category = "GameFuse| API")

struct FGFAPIResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|API")
	bool bSuccess = false;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|API")
	FString ResponseStr = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|API")
	FGuid RequestId;
	FGFAPIResponse() = default;

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

struct FGFGameRoundRanking
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 Place = 0;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 Score = 0;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	FDateTime StartTime;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	FDateTime EndTime;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	FGFUserData User;

	bool operator==(const FGFGameRoundRanking& Other) const
	{
		return Place == Other.Place && Score == Other.Score && StartTime == Other.StartTime && EndTime == Other.EndTime && User == Other.User;
	}
};

// Main Game Round Structure
USTRUCT(BlueprintType, Category = "GameFuse|GameRound")

struct FGFGameRound
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 Id = 0;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 GameUserId = 0;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	FDateTime StartTime;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	FDateTime EndTime;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 Score = 0;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 Place = -1;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	FString GameType = "";

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	int32 MultiplayerGameRoundId = -1;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	TMap<FString, FString> Metadata;

	UPROPERTY(BlueprintReadWrite, Category = "GameFuse|GameRound")
	bool bMultiplayer = false;

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

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Friends")
	int32 FriendshipId = 0;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Friends")
	FGFUserData OtherUser;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Friends")
	EGFFriendRequestStatus Status = EGFFriendRequestStatus::None;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|Friends")
	FDateTime RequestCreatedAt;

	bool operator==(const FGFFriendRequest& Other) const
	{
		return FriendshipId == Other.FriendshipId &&
		OtherUser == Other.OtherUser &&
		Status == Other.Status;
	}
};