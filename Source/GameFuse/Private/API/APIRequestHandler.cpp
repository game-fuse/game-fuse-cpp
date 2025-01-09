#include "API/APIRequestHandler.h"

#include "Interfaces/IHttpResponse.h"
#include "HttpModule.h"

#include "Library/GameFuseLog.h"
#include "Library/GameFuseUtilities.h"


UAPIRequestHandler::UAPIRequestHandler()
{
	// // Initialize default headers
	CommonHeaders.Add(TEXT("Content-Type"), TEXT("application/json"));
	CommonHeaders.Add(TEXT("Accept"), TEXT("application/json"));
}


bool UAPIRequestHandler::VerifyUserData(const FGFUserData& UserData)
{
	if (UserData.Id == 0) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid user ID: %d"), UserData.Id);
		return false;
	}
	return true;
}

bool UAPIRequestHandler::VerifyGameData(const FGFGameData& GameData)
{
	if (GameData.Id == 0) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid game ID: %d"), GameData.Id);
		return false;
	}
	return true;
}

FGuid UAPIRequestHandler::SendRequest(const FString& Endpoint, const FString& HttpMethod, const FGFApiCallback& OnResponseReceived, const TSharedPtr<FJsonObject>& Body)
{

	// Error Checking
	if (!OnResponseReceived.IsBound()) {
		UE_LOG(LogGameFuse, Error, TEXT("OnResponseReceived is not bound"));
		return FGuid();
	}

	if (Endpoint.IsEmpty() || HttpMethod.IsEmpty()) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid input parameters for SendRequest"));
		return FGuid();
	}


	// Generate unique ID for the request
	FGuid RequestId = GenerateRequestId();


	// Construct full URL
	FString URL = BaseUrl + Endpoint;

	// Create HTTP Request
	FHttpRequestPtr HttpRequest = FHttpModule::Get().CreateRequest();

	if (!HttpRequest.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to create HTTP request"));
		return RequestId;
	}

	HttpRequest->SetURL(URL);
	HttpRequest->SetVerb(HttpMethod);

	// Serialize JSON object and set as request body if provided
	if (Body.IsValid()) {
		FString RequestBody;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RequestBody);
		FJsonSerializer::Serialize(Body.ToSharedRef(), Writer);
		HttpRequest->SetContentAsString(RequestBody);
	}

	// Add Default Headers
	AddCommonHeaders(HttpRequest);

	//Capture request in the lambda to prevent collection before handle response is called.
	HttpRequest->OnProcessRequestComplete().BindLambda([this, RequestId](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
		HandleResponse(Request, Response, bWasSuccessful, RequestId);
	});

	UE_LOG(LogGameFuse, Log, TEXT("Sending Request [%s] to endpoint: %s"), *RequestId.ToString(), *Endpoint);

	//Store in maps for retrieval in response
	// Add to ActiveRequests map
	ActiveRequests.Add(RequestId, HttpRequest);

	// Store the response delegate
	if (OnResponseReceived.IsBound()) {
		ResponseDelegates.Add(RequestId, OnResponseReceived);
	} else {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid RequestId or OnResponseReceived callback, request not sent"));
		return RequestId;
	}

	// Execute request asynchronously
	HttpRequest->ProcessRequest();

	return RequestId;
}

void UAPIRequestHandler::SetAuthHeader(const FString& AuthToken)
{
	CommonHeaders.Add(TEXT("authentication-token"), AuthToken);
}

void UAPIRequestHandler::HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, const bool bWasSuccessful, const FGuid& RequestId)
{
	//error checking
	if (!ActiveRequests.Contains(RequestId)) {
		UE_LOG(LogGameFuse, Log, TEXT("Got response without an active request"));
	}

	if (!RequestId.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Request not found"));
		return;
	}

	if (!Response.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid response for request:"));
		GameFuseUtilities::LogRequest(Request);
		return;
	}


	bool bSuccessfulAndValid = bWasSuccessful && Response.IsValid();

	int ResponseCode = Response->GetResponseCode();
	bool bIsGoodResponse = ResponseCode >= 200 && ResponseCode < 300;


	// Retrieve and execute the response delegate
	if (ResponseDelegates.Contains(RequestId)) {
		const FGFApiCallback& Delegate = ResponseDelegates[RequestId];
		FString ResponseContent = bSuccessfulAndValid ? Response->GetContentAsString() : TEXT("Request failed or invalid response");

		Delegate.Broadcast(FGFAPIResponse(bSuccessfulAndValid && bIsGoodResponse, ResponseContent, RequestId.ToString()));
		ResponseDelegates.Remove(RequestId);
	}


	if (bSuccessfulAndValid) {

		if (bIsGoodResponse) {
			UE_LOG(LogTemp, Log, TEXT("Request %s succeeded"), *RequestId.ToString());
			GameFuseUtilities::LogResponse(Response);
		} else {

			UE_LOG(LogTemp, Error, TEXT("Request %s failed"), *RequestId.ToString());
			GameFuseUtilities::LogRequest(Request);
			GameFuseUtilities::LogResponse(Response);
		}
	} else {
		// Handle failure case here
		UE_LOG(LogTemp, Error, TEXT("Request %s failed"), *RequestId.ToString());
		GameFuseUtilities::LogRequest(Request);
	}

	// Remove from ActiveRequests map
	ActiveRequests.Remove(RequestId);
}

void UAPIRequestHandler::AddCommonHeaders(FHttpRequestPtr HttpRequest)
{

	for (auto Header : CommonHeaders) {

		if (Header.Key.IsEmpty() || Header.Value.IsEmpty()) {
			UE_LOG(LogGameFuse, Error, TEXT("Header Key or Value is empty"));
			continue;
		}
		HttpRequest->SetHeader(Header.Key, Header.Value);
	}
}

// Generate a unique ID for the request
FGuid UAPIRequestHandler::GenerateRequestId()
{
	return FGuid::NewGuid();
}