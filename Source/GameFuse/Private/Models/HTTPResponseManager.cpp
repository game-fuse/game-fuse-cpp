// Fill out your copyright notice in the Description page of Project Settings.


#include "Models/HTTPResponseManager.h"


void UHTTPResponseManager::OnHttpResponseReceivedManager(FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
{
    const int32 ResponseCode = Response->GetResponseCode();
    const FString ResponseStr = Response->GetContentAsString();

    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Request Failed"));
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(bWasSuccessful, "Game Fuse HTTP Request Failed");
        return;
    }
    
    if (ResponseCode == 200)
    {
        UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  HTTP Request Succeed"));
        
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(bWasSuccessful, ResponseStr);
    }
    else
    {
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(bWasSuccessful, ResponseStr);
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Request Returned Status Code %d"), ResponseCode);
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Response : %s"), *ResponseStr);
    }
}