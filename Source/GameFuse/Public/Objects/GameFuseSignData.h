/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "Library/GameFuseStructLibrary.h"
#include "GameFuseSignData.generated.h"

UCLASS(Blueprintable, Category = "GameFuse")
class GAMEFUSE_API UGameFuseSaveData : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|SaveData")
	FGFUserData UserData;
};