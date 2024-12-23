#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Delegates/Delegate.h"
#include "Dom/JsonObject.h"

#include "Library/GameFuseStructLibrary.h"

#include "ApiRequestHandler.generated.h"


/**
 * @brief BP Specific Callback Delegate. Only bound to the Delegate pin on a given node.
 * @param ResponseData - The response data from the API request. See @FGFAPIResponse for response details.
 */
DECLARE_DYNAMIC_DELEGATE_OneParam(FBP_GFApiCallback, FGFAPIResponse, ResponseData);

/**
 * @brief CPP Multicast Delegate wraps the BP_ApiCallback and is bindable anywhere in CPP
 * @param ResponseData - The response data from the API request. See @FGFAPIResponse for response details.
 */
DECLARE_MULTICAST_DELEGATE_OneParam(FGFApiCallback, FGFAPIResponse);

/**
 * @brief UAPIRequestHandler - Centralized class to manage API requests
 */

UCLASS()
class GAMEFUSE_API UAPIRequestHandler : public UObject
{
	GENERATED_BODY()

public:

	// Constructor to initialize default headers
	UAPIRequestHandler();

	void AddCommonHeaders(FHttpRequestPtr HttpRequest);

	// Common headers for all requests
	UPROPERTY()
	TMap<FString, FString> CommonHeaders;

	// Checks if a request is still active
	bool IsRequestActive(const FGuid& RequestId) const
	{
		return ActiveRequests.Contains(RequestId);
	}

	int GetNumActiveRequests() const
	{
		return ActiveRequests.Num();
	}

protected:

	// Sends an HTTP Request, optionally with a JSON object as the body, returns unique Request ID
	FGuid SendRequest(const FString& Endpoint, const FString& HttpMethod, const FGFApiCallback& OnResponseReceived, const TSharedPtr<FJsonObject, ESPMode::ThreadSafe>& Body = nullptr);

private:

	// Generates a unique Request ID
	static FGuid GenerateRequestId();

	// Map to store active requests and their data by Request ID
	TMap<FGuid, TSharedPtr<IHttpRequest, ESPMode::ThreadSafe>> ActiveRequests;

	// Map to store response delegates by Request ID
	TMap<FGuid, FGFApiCallback> ResponseDelegates;

	// Handles the response received for the HTTP request
	void HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, const FGuid& RequestId);

	// Base URL for the API
	inline static FString BaseUrl = "https://gamefuse.co/api/v3";
};