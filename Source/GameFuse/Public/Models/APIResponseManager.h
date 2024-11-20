// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "Containers/UnrealString.h"

#include "APIResponseManager.generated.h"

// DECLARE_DELEGATE_TwoParams(FGameFuseAPIResponseCallback, bool /* bSuccess */, FString /* ResponseStr */);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FGameFuseAPIResponseCallback, bool, bSuccess, const FString&, ResponseString);



UCLASS()
class GAMEFUSE_API UHTTPResponseManager : public UObject
{
	GENERATED_BODY()

public:

	inline static FGameFuseAPIResponseCallback CompletionCallback;

protected:

	static void OnHttpResponseReceivedManager(FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful);

	inline static const FString BaseURL = "https://gamefuse.co/api/v2";
	inline static TSharedRef<IHttpRequest> RequestManager = FHttpModule::Get().CreateRequest();

};