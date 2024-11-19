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

	UPROPERTY(BlueprintReadOnly)
	int32 Id = 0;

	UPROPERTY(BlueprintReadOnly)
	FString Token = "";

	UPROPERTY(BlueprintReadOnly)
	FString Name = "";

	UPROPERTY(BlueprintReadOnly)
	FString Description = "";

};

USTRUCT(BlueprintType, Category = "GameFuse|UserData")
struct FGFUserData
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	int32 Id = 0;

	UPROPERTY(BlueprintReadOnly)
	FString Username = "";

	UPROPERTY(BlueprintReadOnly)
	bool bSignedIn = false;

	UPROPERTY(BlueprintReadOnly)
	int32 NumberOfLogins = 0;

	UPROPERTY(BlueprintReadOnly)
	FString AuthenticationToken = "";

	UPROPERTY(BlueprintReadOnly)
	int32 Score = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Credits = 0;

	UPROPERTY(BlueprintReadOnly)
	FString LastLogin = "0000-00-00";

};


USTRUCT(BlueprintType, Category = "GameFuse|StoreItem")
struct FGFStoreItem
{
	GENERATED_BODY()
	FGFStoreItem() = default;

	UPROPERTY(BlueprintReadOnly)
	FString Name = "";

	UPROPERTY(BlueprintReadOnly)
	FString Category = "";

	UPROPERTY(BlueprintReadOnly)
	FString Description = "";

	UPROPERTY(BlueprintReadOnly)
	int32 Cost = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 Id = 0;

	UPROPERTY(BlueprintReadOnly)
	FString IconUrl = "";

};

USTRUCT(BlueprintType, Category = "GameFuse|LeaderboardItem")
struct FGFLeaderboardEntry
{
	GENERATED_BODY()

	FGFLeaderboardEntry() = default;

	UPROPERTY(BlueprintReadOnly)
	FString LeaderboardName = "";

	UPROPERTY(BlueprintReadOnly)
	FString Username = "";

	UPROPERTY(BlueprintReadOnly)
	int32 Score = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 GameUserId = 0;

	UPROPERTY(BlueprintReadOnly)
	FString ExtraAttributes = "";

	UPROPERTY(BlueprintReadOnly)
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


	UPROPERTY(BlueprintReadOnly)
	FString Name = "";

	UPROPERTY(BlueprintReadOnly)
	TArray<FGFLeaderboardEntry> Entries;
};

USTRUCT(BlueprintType, Category = "GameFuse| API", DisplayName = "API Response")
struct FGFAPIResponse
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite)
	bool bSuccess = false;

	UPROPERTY(BlueprintReadWrite)
	FString ResponseStr = "";

	UPROPERTY(BlueprintReadWrite)
	FString RequestId;
	FGFAPIResponse() = default;

	FGFAPIResponse(bool _bSuccess, const FString& _Response, const FString& _RequestId)
	{
		bSuccess = _bSuccess;
		ResponseStr = _Response;
		RequestId = _RequestId;
	}
};