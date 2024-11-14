#include "Models/APIRequestHandler.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"

UAPIRequestHandler::UAPIRequestHandler()
{
	// Initialize default headers
	DefaultHeaders.Add(TEXT("Content-Type"), TEXT("application/json"));
	DefaultHeaders.Add(TEXT("Accept"), TEXT("application/json"));
}

FGuid UAPIRequestHandler::SendRequest(const FString& Endpoint, const FString& HttpMethod, const FString& RequestBody, FOnApiResponseReceived OnResponseReceived)
{
	// Generate unique ID for the request
	FGuid RequestId = GenerateRequestId();

	// Construct full URL
	FString URL = BaseUrl + Endpoint;

	// Create HTTP Request
	TSharedRef<IHttpRequest, ESPMode::ThreadSafe> HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(HttpMethod);
	HttpRequest->SetContentAsString(RequestBody);

	// Add Default Headers
	for (const TPair<FString, FString>& Header : DefaultHeaders)
	{
		HttpRequest->SetHeader(Header.Key, Header.Value);
	}

	// Bind to response callback using direct reference
	HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAPIRequestHandler::HandleResponse);

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

	// Retrieve and execute the response delegate
	if (ResponseDelegates.Contains(RequestId))
	{
		FOnApiResponseReceived Delegate = ResponseDelegates[RequestId];
		FString ResponseContent = bWasSuccessful && Response.IsValid() ? Response->GetContentAsString() : TEXT("Request failed or invalid response");
		Delegate.ExecuteIfBound(bWasSuccessful && Response.IsValid(), ResponseContent, RequestId.ToString());
		ResponseDelegates.Remove(RequestId);
	}

	if (bWasSuccessful && Response.IsValid())
	{
		// Handle success case here (e.g., call a delegate)
		UE_LOG(LogTemp, Log, TEXT("Request %s succeeded: %s"), *RequestId.ToString(), *Response->GetContentAsString());
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