/**
 *  Copyright (c) 2024-09-30 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */
#pragma once

#include "CoreMinimal.h"
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

USTRUCT(BlueprintType, Category = "GameFuse| API")

struct FGFAPIResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|API")
	bool bSuccess = false;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|API")
	FString ResponseStr = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|API")
	FString RequestId = "";
	FGFAPIResponse() = default;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|API")
	int ResponseCode = 0;

	FGFAPIResponse(bool _bSuccess, const FString& _Response, const FString& _RequestId = "", int _ResponseCode = 0)
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
};