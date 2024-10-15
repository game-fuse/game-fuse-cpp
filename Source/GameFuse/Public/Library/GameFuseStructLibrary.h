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
struct FGFLeaderboardItem
{
	GENERATED_BODY()

	FGFLeaderboardItem() = default;

	UPROPERTY(BlueprintReadOnly)
	FString LeaderboardName = "";

	UPROPERTY(BlueprintReadOnly)
	int32 Score = 0;

	UPROPERTY(BlueprintReadOnly)
	FString Username = "";

	UPROPERTY(BlueprintReadOnly)
	int32 GameUserId = 0;

	UPROPERTY(BlueprintReadOnly)
	FString ExtraAttributes = "";

	UPROPERTY(BlueprintReadOnly)
	FString DateTime = "";

};