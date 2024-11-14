// Fill out your copyright notice in the Description page of Project Settings.


#include "Objects/GameFuseAsyncAction.h"

void UGameFuseAsyncAction::Activate()
{
	Super::Activate();
}

UGameFuseAsyncAction* UGameFuseAsyncAction::CreateAsyncAction()
{
	UGameFuseAsyncAction* Action = NewObject<UGameFuseAsyncAction>();

	return Action;
}

void UGameFuseAsyncAction::HandleResponse(bool bSuccess, const FString& Response)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(Response);
	}
	else
	{
		OnFailure.Broadcast(Response);
	}
}