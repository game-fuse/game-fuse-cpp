// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameFuseSaveData.generated.h"

/**
 * 
 */
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
