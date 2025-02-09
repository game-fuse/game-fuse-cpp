#pragma once

#include "CoreMinimal.h"
#include "Interfaces/IHttpRequest.h"
#include "Delegates/Delegate.h"
#include "Dom/JsonObject.h"

#include "Library/GameFuseStructLibrary.h"

#include "ApiRequestHandler.generated.h"


DECLARE_DYNAMIC_DELEGATE_OneParam(FGFSuccessCallback, bool, bSuccess);

// Multicast delegate for internal success callbacks
DECLARE_MULTICAST_DELEGATE_OneParam(FGFInternalSuccessCallback, bool);

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


	static bool VerifyUserData(const FGFUserData& UserData);
	static bool VerifyGameData(const FGFGameData& GameData);

	// Sends an HTTP request with the specified parameters
	FGuid SendRequest(const FString& Endpoint, const FString& HttpMethod, const FGFApiCallback& OnResponseReceived, const TSharedPtr<FJsonObject>& Body = nullptr);

	// Sends an HTTP request with an internal success callback
	FGuid SendRequest(const FString& Endpoint, const FString& HttpMethod, const FGFApiCallback& OnResponseReceived, const FGFInternalSuccessCallback& InternalCallback, const TSharedPtr<FJsonObject>& Body = nullptr);

protected:

	void SetAuthHeader(const FString& AuthToken);

private:

	// Generates a unique Request ID
	FGuid GenerateRequestId();

	// Map to store active requests and their data by Request ID
	TMap<FGuid, TSharedPtr<IHttpRequest, ESPMode::ThreadSafe>> ActiveRequests;

	// Map to store response delegates by Request ID
	TMap<FGuid, FGFApiCallback> ResponseDelegates;

	// Map to store internal success callbacks by Request ID
	TMap<FGuid, FGFInternalSuccessCallback> InternalSuccessCallbacks;

	// Handles the response received for the HTTP request
	void HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful, const FGuid& RequestId);

	// Base URL for the API
	inline static FString BaseUrl = "https://gamefuse.co/api/v3";
};