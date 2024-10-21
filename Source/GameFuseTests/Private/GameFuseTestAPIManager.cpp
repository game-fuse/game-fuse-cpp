#include "GameFuseTestAPIManager.h"

struct FLogCategoryLogGameFuse LogGameFuse;

UGameFuseTestAPIManager::UGameFuseTestAPIManager()
{
	const FString ServiceKeyName = FPlatformMisc::GetEnvironmentVariable(TEXT("GAMEFUSE_TEST_SERVICE_KEY"));
	const FString ServiceKeyToken = FPlatformMisc::GetEnvironmentVariable(TEXT("GAMEFUSE_TEST_SERVICE_TOKEN"));

	RequestManager->SetHeader(TEXT("service-key-token"), *ServiceKeyToken);
	RequestManager->SetHeader(TEXT("service-key-name"), *ServiceKeyName);
	RequestManager->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
}

static void HandleResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	UE_LOG(LogGameFuse, Log, TEXT("Response : %s"), *Response->GetContentAsString());
}

void UGameFuseTestAPIManager::CreateGame()
{
	RequestManager->SetURL(FString::Printf(TEXT("%s/create_game"), *BaseURL));
	RequestManager->SetVerb("POST");


	// RequestManager->OnProcessRequestComplete().BindLambda(HandleResponse);
	RequestManager->ProcessRequest();
}

void UGameFuseTestAPIManager::OnStatusCodeReceived(TSharedPtr<IHttpRequest> HttpRequest, int I)
{
	UE_LOG(LogGameFuse, Log, TEXT("StatusCode : %d"), I);
}

void UGameFuseTestAPIManager::CleanUpTestData(int32 GameId)
{
	UE_LOG(LogGameFuse, Log, TEXT("CleanUpTestData. Headers: "));
	//print all headers
	for (auto Header : RequestManager->GetAllHeaders())
	{
		UE_LOG(LogGameFuse, Log, TEXT("%s"), *Header);
	}


	RequestManager->SetURL(FString::Printf(TEXT("%s/clean_up_test?game_id=%i"), *BaseURL, GameId));


	RequestManager->SetVerb("DELETE");


	UE_LOG(LogGameFuse, Log, TEXT("%s"), *RequestManager->GetURL());
	auto InFunctor = [&](
	FHttpRequestPtr pRequest,
	FHttpResponsePtr pResponse,
	bool connectedSuccessfully) {
		HandleResponse(pRequest, pResponse, connectedSuccessfully);
	};
	RequestManager->OnProcessRequestComplete().BindLambda(InFunctor);
	RequestManager->OnStatusCodeReceived().BindStatic(&UGameFuseTestAPIManager::OnStatusCodeReceived);

	RequestManager->ProcessRequest();
}