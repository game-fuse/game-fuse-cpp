// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "Containers/UnrealString.h"
#include "HTTPResponseManager.generated.h"

// DECLARE_DELEGATE_TwoParams(FGameFuseAPIResponseCallback, bool /* bSuccess */, FString /* ResponseString */);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FGameFuseAPIResponseCallback, bool, bSuccess, const FString&, ResponseString);


UCLASS()
class GAMEFUSE_API UHTTPResponseManager : public UObject
{
	GENERATED_BODY()

protected:

	static void OnHttpResponseReceivedManagerStatic(FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful, const FGameFuseAPIResponseCallback* CompletionCallback);
	static void OnHttpResponseReceivedManagerUser(FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful, const FGameFuseAPIResponseCallback CompletionCallback);
	
	inline static const FString BaseURL = "https://gamefuse.co/api/v2";
	inline static TSharedRef<IHttpRequest> RequestManager = FHttpModule::Get().CreateRequest();
	
};
