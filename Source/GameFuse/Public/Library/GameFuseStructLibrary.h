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


	/*
	 * Only checks critical user values, Token, Score, Credits and Login Details are NOT included
	 */
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
		return Name == Other.Name && Category == Other.Category &&
		Description == Other.Description && Cost == Other.Cost &&
		Id == Other.Id && IconUrl == Other.IconUrl;
	}

};

USTRUCT(BlueprintType, Category = "GameFuse|LeaderboardItem")
struct FGFLeaderboardEntry
{
	GENERATED_BODY()

	FGFLeaderboardEntry() = default;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|LeaderboardItem")
	FString LeaderboardName = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|LeaderboardItem")
	FString Username = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|LeaderboardItem")
	int32 Score = 0;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|LeaderboardItem")
	int32 GameUserId = 0;

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|LeaderboardItem")
	FString ExtraAttributes = "";

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|LeaderboardItem")
	FString DateTime = "";

	bool operator==(const FGFLeaderboardEntry& Other) const
	{
		return LeaderboardName == Other.LeaderboardName && Username == Other.Username &&
		Score == Other.Score && GameUserId == Other.GameUserId &&
		ExtraAttributes == Other.ExtraAttributes && DateTime == Other.DateTime;
	}
};

/**
 * Wrapper Struct allows TMap<FString, TArray<FGFLeaderboardEntry>> to be used
 *
 ***/
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