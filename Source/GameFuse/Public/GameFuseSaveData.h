// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GameFuseSaveData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class GAMEFUSE_API UGameFuseSaveData : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadOnly)
        int32 NumberOfLogins = 0;
    UPROPERTY(BlueprintReadOnly)
        FString LastLogin;
    UPROPERTY(BlueprintReadOnly)
        FString AuthenticationToken;
    UPROPERTY(BlueprintReadOnly)
        FString Username;
    UPROPERTY(BlueprintReadOnly)
        int32 Score = 0;
    UPROPERTY(BlueprintReadOnly)
        int32 Credits = 0;
    UPROPERTY(BlueprintReadOnly)
        int32 Id = 0;

};
