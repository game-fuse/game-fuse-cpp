// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "UObject/NoExportTypes.h"
#include "Interfaces/IHttpRequest.h"
#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"
#include "Containers/UnrealString.h"

#include "APIRequestManager.generated.h"

// DECLARE_DELEGATE_TwoParams(FGameFuseAPIResponseCallback, bool /* bSuccess */, FString /* ResponseString */);
DECLARE_DYNAMIC_DELEGATE_TwoParams(FGameFuseAPIResponseCallback, bool, bSuccess, const FString&, ResponseString);

//this was conveniently used in every class in the source, probably better to move to a dedicated GameFuseLog header
DECLARE_LOG_CATEGORY_EXTERN(LogGameFuse, Log, All);




UCLASS()
class GAMEFUSE_API UAPIRequestManager : public UObject
{
	GENERATED_BODY()

public:


	FGameFuseAPIResponseCallback CompletionCallback;

	static UAPIRequestManager* CreateRequest();
	void CleanupRequest();
	TSharedRef<IHttpRequest> GetRequest();
	void OnHttpResponseReceivedManager(FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful);

protected:


	
	inline static const FString BaseURL = "https://gamefuse.co/api/v2";
	TSharedRef<IHttpRequest> Request;



};

