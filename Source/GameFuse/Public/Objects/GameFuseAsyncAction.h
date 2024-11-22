// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "GameFuseAsyncAction.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameFuseSuccess, const FString&, Response);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameFuseFailure, const FString&, ErrorMessage);

UCLASS()
class UGameFuseAsyncAction : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
public:

	virtual void Activate() override;


	static UGameFuseAsyncAction* CreateAsyncAction();
	UPROPERTY(BlueprintAssignable)
	FGameFuseSuccess OnSuccess;

	UPROPERTY(BlueprintAssignable)
	FGameFuseFailure OnFailure;

	UFUNCTION()
	void HandleResponse(bool bSuccess, const FString& Response);
};