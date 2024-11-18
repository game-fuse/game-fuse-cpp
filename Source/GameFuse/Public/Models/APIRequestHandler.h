#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Delegates/Delegate.h"
#include "ApiRequestHandler.generated.h"

/**
 * Delegate to handle API request responses
 */
DECLARE_DYNAMIC_DELEGATE_ThreeParams(FOnApiResponseReceived, bool, bSuccess, FString, ResponseContent, FString, RequestId);

/**
 * UAPIRequestHandler - Centralized class to manage API requests
 */
UCLASS()
class GAMEFUSE_API UAPIRequestHandler : public UObject
{
	GENERATED_BODY()

public:

	// Sends an HTTP Request, returns unique Request ID
	FGuid SendRequest(const FString& Endpoint, const FString& HttpMethod, FOnApiResponseReceived OnResponseReceived = FOnApiResponseReceived());

	// Handles the response received for the HTTP request
	void HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	// Base URL for the API
	inline static FString BaseUrl = "https://gamefuse.co/api/v2";

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
	TMap<FGuid, FOnApiResponseReceived> ResponseDelegates;
};