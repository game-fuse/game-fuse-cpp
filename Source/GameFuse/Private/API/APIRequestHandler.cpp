#include "API/APIRequestHandler.h"
#include "HttpModule.h"
#include "Library/GameFuseLog.h"
#include "Interfaces/IHttpResponse.h"
#include "Models/GameFuseUtilities.h"


UAPIRequestHandler::UAPIRequestHandler()
{
	// Initialize default headers
	CommonHeaders.Add(TEXT("Content-Type"), TEXT("application/json"));
	CommonHeaders.Add(TEXT("Accept"), TEXT("application/json"));
}

FGuid UAPIRequestHandler::SendRequest(const FString& Endpoint, const FString& HttpMethod, /* const FString& RequestBody,*/
                                      const FGFApiCallback& OnResponseReceived)
{
	// Generate unique ID for the request
	FGuid RequestId = GenerateRequestId();

	// Construct full URL
	FString URL = BaseUrl + Endpoint;

	UE_LOG(LogGameFuse, Log, TEXT("RequestId: %s"), *RequestId.ToString());
	UE_LOG(LogGameFuse, Log, TEXT("OnResponseReceived: %i"), OnResponseReceived.IsBound());

	// Create HTTP Request
	FHttpRequestPtr HttpRequest = FHttpModule::Get().CreateRequest();
	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(HttpMethod);

	// Request Body not used for Gamefuse API
	// HttpRequest->SetContentAsString(RequestBody);

	// Add Default Headers
	for (const TPair<FString, FString>& Header : CommonHeaders)
	{
		HttpRequest->SetHeader(Header.Key, Header.Value);
	}

	// Bind to response callback using direct reference
	// HttpRequest->OnProcessRequestComplete().BindUObject(this, &UAPIRequestHandler::HandleResponse);
	//Capture request in the lambda to prevent collection before handle response is called.
	HttpRequest->OnProcessRequestComplete().BindLambda([this, RequestId](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
		HandleResponse(Request, Response, bWasSuccessful, RequestId);
	});


	UE_LOG(LogGameFuse, Log, TEXT("Sending Request to endpoint: %s"), *Endpoint);
	// Add to ActiveRequests map
	ActiveRequests.Add(RequestId, HttpRequest);

	// Store the response delegate
	if (RequestId.IsValid() && OnResponseReceived.IsBound())
	{
		ResponseDelegates.Add(RequestId, OnResponseReceived);
	}
	else
	{
		UE_LOG(LogGameFuse, Error, TEXT("Invalid RequestId or OnResponseReceived callback, request not sent"));
		return RequestId;
	}

	// Execute request asynchronously
	HttpRequest->ProcessRequest();

	return RequestId;
}

void UAPIRequestHandler::HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, const bool bWasSuccessful, const FGuid& RequestId)
{
	UE_LOG(LogGameFuse, Log, TEXT("Response received"));
	GameFuseUtilities::LogRequest(Request);
	GameFuseUtilities::LogResponse(Response);
	// FGuid RequestId;
	// for (const auto& Pair : ActiveRequests)
	// {
	// 	if (Pair.Value == Request)
	// 	{
	// 		RequestId = Pair.Key;
	// 		break;
	// 	}
	// }

	if (!ActiveRequests.Contains(RequestId))
	{
		UE_LOG(LogGameFuse, Log, TEXT("Got response without an active request"));
	}

	if (!RequestId.IsValid())
	{
		UE_LOG(LogGameFuse, Error, TEXT("Request Id not found"));


		return;
	}


	// Remove from ActiveRequests map
	ActiveRequests.Remove(RequestId);

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
			// GameFuseUtilities::LogRequest(Request);
			// GameFuseUtilities::LogResponse(Response);
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
		// GameFuseUtilities::LogRequest(Request);
	}
}

void UAPIRequestHandler::AddCommonHeader(const FString& Key, const FString& Value)
{
	if (CommonHeaders.Contains(Key))
	{
		UE_LOG(LogGameFuse, Warning, TEXT("Header %s already exists. Overwriting."), *Key);
	}
	CommonHeaders.Add(Key, Value);
}

FGuid UAPIRequestHandler::GenerateRequestId()
{
	return FGuid::NewGuid();
}