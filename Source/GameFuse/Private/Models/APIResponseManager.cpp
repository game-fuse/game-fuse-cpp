/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "Models/APIResponseManager.h"


void UHTTPResponseManager::OnHttpResponseReceivedManager(FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
{
    const int32 ResponseCode = Response->GetResponseCode();
    const FString ResponseStr = Response->GetContentAsString();

    if (!bWasSuccessful || !Response.IsValid())
    {
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Request Failed"));
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(false, "Game Fuse HTTP Request Failed");
        return;
    }
    
    if (ResponseCode == 200)
    {
        UE_LOG(LogTemp, Display, TEXT("LogGameFuse :  HTTP Request Succeed"));
        
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(true, ResponseStr);
    }
    else
    {
        if (CompletionCallback.IsBound()) CompletionCallback.Execute(false, ResponseStr);
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Request Returned Status Code %d"), ResponseCode);
        UE_LOG(LogTemp, Error, TEXT("LogGameFuse :  HTTP Response : %s"), *ResponseStr);
    }
}