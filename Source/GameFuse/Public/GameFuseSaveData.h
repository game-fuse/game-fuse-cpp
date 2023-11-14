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
#include "GameFuseSaveData.generated.h"

UCLASS(Blueprintable, Category = "GameFuse")
class GAMEFUSE_API UGameFuseSaveData : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly, Category = "GameFuse|SaveData")
        int32 NumberOfLogins = 0;
    UPROPERTY(BlueprintReadOnly, Category = "GameFuse|SaveData")
        FString LastLogin;
    UPROPERTY(BlueprintReadOnly, Category = "GameFuse|SaveData")
        FString AuthenticationToken;
    UPROPERTY(BlueprintReadOnly, Category = "GameFuse|SaveData")
        FString Username;
    UPROPERTY(BlueprintReadOnly, Category = "GameFuse|SaveData")
        int32 Score = 0;
    UPROPERTY(BlueprintReadOnly, Category = "GameFuse|SaveData")
        int32 Credits = 0;
    UPROPERTY(BlueprintReadOnly, Category = "GameFuse|SaveData")
        int32 Id = 0;

};
