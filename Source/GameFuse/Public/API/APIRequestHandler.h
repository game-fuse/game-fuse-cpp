#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Delegates/Delegate.h"
#include "Library/GameFuseStructLibrary.h"

#include "ApiRequestHandler.generated.h"


/**
 * @brief BP Specific Callback Delegate. Only bound to the Delegate pin on a given node.
 * @param RepsonseData - The response data from the API request. See @FGFAPIResponse for response details.
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FBP_GFApiCallback, FGFAPIResponse, ResponseData);

/**
 * @brief CPP Multicast Delegate wraps the BP_ApiCallback and is bindable anywhere in CPP
 * @param RepsonseData - The response data from the API request. See @FGFAPIResponse for response details.
 */
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGFApiCallback, FGFAPIResponse, ResponseData);

/**
 * @brief UAPIRequestHandler - Centralized class to manage API requests
 */
UCLASS()
class GAMEFUSE_API UAPIRequestHandler : public UObject
{
	GENERATED_BODY()

public:

	// Sends an HTTP Request, returns unique Request ID
	FGuid SendRequest(const FString& Endpoint, const FString& HttpMethod, const FGFApiCallback& OnResponseReceived);

	// Handles the response received for the HTTP request
	void HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// Base URL for the API
	inline static FString BaseUrl = "https://gamefuse.co/api/v3";

protected:

	// Common headers for all requests
	TMap<FString, FString> DefaultHeaders;

	// Constructor to initialize default headers
	UAPIRequestHandler();

private:

	// Generates a unique Request ID
	static FGuid GenerateRequestId();


	// Map to store active requests and their data by Request ID
	TMap<FGuid, FHttpRequestPtr> ActiveRequests;

	// Map to store response delegates by Request ID
	TMap<FGuid, FGFApiCallback> ResponseDelegates;
};