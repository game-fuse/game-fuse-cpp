/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFuseLeaderboardItem.generated.h"

UCLASS(Blueprintable, Category = "GameFuse")
class GAMEFUSE_API UGameFuseLeaderboardItem : public UObject
{
	GENERATED_BODY()

public:
	
	FString LeaderboardName;

	int32 Score;

	FString Username;

	int32 GameUserId;

	FString ExtraAttributes;
	
	FString DateTime;

	
	UGameFuseLeaderboardItem();

	UFUNCTION(BlueprintPure, Category = "GameFuse|LeaderboardItem")
	FString GetUsername();

	UFUNCTION(BlueprintPure, Category = "GameFuse|LeaderboardItem")
	int32 GetScore();

	UFUNCTION(BlueprintPure, Category = "GameFuse|LeaderboardItem")
	FString GetLeaderboardName();

	UFUNCTION(BlueprintPure, Category = "GameFuse|LeaderboardItem")
	FString GetExtraAttributes();

	UFUNCTION(BlueprintPure, Category = "GameFuse|LeaderboardItem")
	FString GetTimestamp();

};
