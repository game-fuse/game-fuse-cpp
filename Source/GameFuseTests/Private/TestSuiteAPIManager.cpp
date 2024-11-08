#include "TestSuiteAPIManager.h"


UTestSuiteAPIManager::UTestSuiteAPIManager()
{
	const FString ServiceKeyName = FPlatformMisc::GetEnvironmentVariable(TEXT("GAMEFUSE_TEST_SERVICE_KEY"));
	const FString ServiceKeyToken = FPlatformMisc::GetEnvironmentVariable(TEXT("GAMEFUSE_TEST_SERVICE_TOKEN"));

	RequestManager->SetHeader(TEXT("service-key-token"), *ServiceKeyToken);
	RequestManager->SetHeader(TEXT("service-key-name"), *ServiceKeyName);
	RequestManager->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
}

void UTestSuiteAPIManager::LogRequestInfo(TSharedRef<IHttpRequest> HttpRequest)
{

	UE_LOG(LogGameFuse, Log, TEXT("=========   URL   ========= \n %s"), *RequestManager->GetURL());
	UE_LOG(LogGameFuse, Log, TEXT("========= HEADERS ========="))
	for (const FString& currHeader : HttpRequest->GetAllHeaders()) {
		UE_LOG(LogGameFuse, Log, TEXT("%s"), *currHeader);
	}
}

void UTestSuiteAPIManager::LogRequestInfo(const FHttpRequestPtr& HttpRequest)
{

	UE_LOG(LogGameFuse, Log, TEXT("=========   URL   ========= \n %s"), *RequestManager->GetURL());
	UE_LOG(LogGameFuse, Log, TEXT("========= HEADERS ========="))
	for (const FString& currHeader : HttpRequest->GetAllHeaders()) {
		UE_LOG(LogGameFuse, Log, TEXT("%s"), *currHeader);
	}
}

void UTestSuiteAPIManager::CreateGame(FDefaultCallback Callback)
{
	RequestManager->SetURL(FString::Printf(TEXT("%s/create_game"), *BaseURL));
	RequestManager->SetVerb("POST");

	LogRequestInfo(RequestManager);

	RequestManager->OnProcessRequestComplete().BindLambda(Callback);
	RequestManager->ProcessRequest();
}

void UTestSuiteAPIManager::CreateUser(int32 GameId, const FString& Username, const FString& Email, FDefaultCallback Callback)
{
	RequestManager->SetURL(FString::Printf(TEXT("%s/create_user?game_id=%i&username=%s&email=%s"), *BaseURL, GameId, *Username, *Email));
	RequestManager->SetVerb("POST");

	LogRequestInfo(RequestManager);

	RequestManager->OnProcessRequestComplete().BindLambda(Callback);
	RequestManager->ProcessRequest();
}

void UTestSuiteAPIManager::CreateStoreItem(int32 GameId, const FString& Name, const FString& Description, const FString& Category, int32 cost, FDefaultCallback Callback)
{
	RequestManager->SetURL(FString::Printf(TEXT("%s/create_store_item"), *BaseURL));
	RequestManager->SetVerb("POST");

	RequestManager->OnProcessRequestComplete().BindLambda(Callback);
	RequestManager->ProcessRequest();
}

void UTestSuiteAPIManager::CreateStoreItem(int32 GameId, const FGFStoreItem& StoreItem, FDefaultCallback Callback)
{
	CreateStoreItem(GameId, StoreItem.Name, StoreItem.Description, StoreItem.Category, StoreItem.Cost, Callback);
}

void UTestSuiteAPIManager::CleanUpTestData(int32 GameId, FDefaultCallback Callback)
{
	RequestManager->SetURL(FString::Printf(TEXT("%s/clean_up_test?game_id=%i"), *BaseURL, GameId));
	RequestManager->SetVerb("DELETE");

	LogRequestInfo(RequestManager);


	RequestManager->OnProcessRequestComplete().BindLambda(Callback);
	RequestManager->ProcessRequest();

}