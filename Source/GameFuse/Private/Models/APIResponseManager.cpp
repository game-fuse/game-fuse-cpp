/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "Models/APIResponseManager.h"
// moved to GameFuse.cpp
// DEFINE_LOG_CATEGORY(LogGameFuse);

void UHTTPResponseManager::OnHttpResponseReceivedManager(FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		const FString RequestStr = Request->GetURL();
		UE_LOG(LogGameFuse, Error, TEXT("HTTP Request Failed : %s"), *RequestStr);
		if (CompletionCallback.IsBound())
		{
			CompletionCallback.Execute(false, "Game Fuse HTTP Request Failed");
		}
		return;
	}

	const int32 ResponseCode = Response->GetResponseCode();
	const FString ResponseStr = Response->GetContentAsString();


	if (ResponseCode == 200)
	{
		UE_LOG(LogGameFuse, Log, TEXT("HTTP Request Succeed"));

		if (CompletionCallback.IsBound())
		{
			CompletionCallback.Execute(true, ResponseStr);
		}
	}
	else
	{
		if (CompletionCallback.IsBound())
		{
			CompletionCallback.Execute(false, ResponseStr);
		}
		UE_LOG(LogGameFuse, Error, TEXT("HTTP Request Returned Status Code %d"), ResponseCode);
		UE_LOG(LogGameFuse, Error, TEXT("HTTP Response : %s"), *ResponseStr);
	}
}