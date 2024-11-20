#include "API/APIRequestHandler.h"
#include "HttpModule.h"
#include "Library/GameFuseLog.h"
#include "Interfaces/IHttpResponse.h"


UAPIRequestHandler::UAPIRequestHandler()
{
	// Initialize default headers
	DefaultHeaders.Add(TEXT("Content-Type"), TEXT("application/json"));
	DefaultHeaders.Add(TEXT("Accept"), TEXT("application/json"));
}

FGuid UAPIRequestHandler::SendRequest(const FString& Endpoint, const FString& HttpMethod, /* const FString& RequestBody,*/
                                      const FGFApiCallback& OnResponseReceived)
{
	// Generate unique ID for the request
	FGuid RequestId = GenerateRequestId();

	// Construct full URL
	FString URL = BaseUrl + Endpoint;

	// Create HTTP Request
	FHttpRequestPtr HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(HttpMethod);

	// Request Body not used for Gamefuse API
	// HttpRequest->SetContentAsString(RequestBody);

	// Add Default Headers
	for (const TPair<FString, FString>& Header : DefaultHeaders)
	{
		HttpRequest->SetHeader(Header.Key, Header.Value);
	}

	// Bind to response callback using direct reference
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAPIRequestHandler::HandleResponse);
	UE_LOG(LogGameFuse, Log, TEXT("Sending Request to endpoint: %s"), *Endpoint);
	// Add to ActiveRequests map
	ActiveRequests.Add(RequestId, HttpRequest);

	// Store the response delegate
	ResponseDelegates.Add(RequestId, OnResponseReceived);

	// Execute request asynchronously
	HttpRequest->ProcessRequest();

	return RequestId;
}

void UAPIRequestHandler::HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogGameFuse, Log, TEXT("Response received"));

	FGuid RequestId;
	for (const auto& Pair : ActiveRequests)
	{
		if (Pair.Value == Request)
		{
			RequestId = Pair.Key;
			break;
		}
	}


	// Remove from ActiveRequests map
	if (RequestId.IsValid())
	{
		ActiveRequests.Remove(RequestId);
	}
	else
	{
		UE_LOG(LogGameFuse, Warning, TEXT("Request Id not found"));
	}
	bool bSuccessfulAndValid = bWasSuccessful && Response.IsValid();

	int ResponseCode = Response->GetResponseCode();
	bool bIsGoodResponse = ResponseCode >= 200 && ResponseCode < 300;


	// Retrieve and execute the response delegate
	if (ResponseDelegates.Contains(RequestId))
	{
		const FGFApiCallback& Delegate = ResponseDelegates[RequestId];
		FString ResponseContent = bSuccessfulAndValid ? Response->GetContentAsString() : TEXT("Request failed or invalid response");

		Delegate.Broadcast(FGFAPIResponse(bSuccessfulAndValid && bIsGoodResponse, ResponseContent, RequestId.ToString()));
		ResponseDelegates.Remove(RequestId);
	}

	if (bSuccessfulAndValid)
	{

		if (!bIsGoodResponse)
		{
			UE_LOG(LogTemp, Warning, TEXT("Request %s failed with response: %s"), *RequestId.ToString(), *Response->GetContentAsString());

		}
		else
		{
			UE_LOG(LogTemp, Log, TEXT("Request %s succeeded: %s"), *RequestId.ToString(), *Response->GetContentAsString());
		}
	}
	else
	{
		// Handle failure case here
		UE_LOG(LogTemp, Error, TEXT("Request %s failed"), *RequestId.ToString());
	}
}

FGuid UAPIRequestHandler::GenerateRequestId()
{
	return FGuid::NewGuid();
}