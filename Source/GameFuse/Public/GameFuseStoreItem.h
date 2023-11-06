// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameFuseStoreItem.generated.h"

/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

UCLASS(Blueprintable)
class GAMEFUSE_API UGameFuseStoreItem : public UObject
{
	GENERATED_BODY()
	
public:

	FString Name;

	FString Category;

	FString Description;

	int32 Cost;

	int32 Id;

	FString IconUrl;

	UFUNCTION(BlueprintPure, Category = "GameFuse|StoreItem")
		FString GetName();

	UFUNCTION(BlueprintPure, Category = "GameFuse|StoreItem")
		FString GetCategory();

	UFUNCTION(BlueprintPure, Category = "GameFuse|StoreItem")
		FString GetDescription();

	UFUNCTION(BlueprintPure, Category = "GameFuse|StoreItem")
		int32 GetCost();

	UFUNCTION(BlueprintPure, Category = "GameFuse|StoreItem")
		int32 GetId();

	UFUNCTION(BlueprintPure, Category = "GameFuse|StoreItem")
		FString GetIconUrl();
};
