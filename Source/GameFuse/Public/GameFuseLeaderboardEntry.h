// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFuseLeaderboardEntry.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAMEFUSE_API UGameFuseLeaderboardEntry : public UObject
{
	GENERATED_BODY()

public:
	
	FString LeaderboardName;

	int32 Score;

	FString Username;

	int32 GameUserId;

	FString ExtraAttributes;
	
	FString DateTime;
	
	UGameFuseLeaderboardEntry();

	UFUNCTION(BlueprintPure, Category = "GameFuse|StoreItem")
	FString GetUsername();

	UFUNCTION(BlueprintPure, Category = "GameFuse|StoreItem")
	int32 GetScore();

	UFUNCTION(BlueprintPure, Category = "GameFuse|StoreItem")
	FString GetLeaderboardName();

	UFUNCTION(BlueprintPure, Category = "GameFuse|StoreItem")
	FString GetExtraAttributes();

	UFUNCTION(BlueprintPure, Category = "GameFuse|StoreItem")
	FString GetTimestamp();

};
