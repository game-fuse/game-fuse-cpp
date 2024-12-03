#include "API/TestAPIHandler.h"


UTestAPIHandler::UTestAPIHandler()
{
	const FString ServiceKeyName = FPlatformMisc::GetEnvironmentVariable(TEXT("GAMEFUSE_TEST_SERVICE_KEY"));
	const FString ServiceKeyToken = FPlatformMisc::GetEnvironmentVariable(TEXT("GAMEFUSE_TEST_SERVICE_TOKEN"));

	CommonHeaders.Add(TEXT("service-key-token"), *ServiceKeyToken);
	CommonHeaders.Add(TEXT("service-key-name"), *ServiceKeyName);
}


FGuid UTestAPIHandler::CreateGame(const FGFApiCallback& Callback)
{
	return SendRequest(TEXT("/create_game"), "POST", Callback);
}

FGuid UTestAPIHandler::CreateUser(int32 GameId, const FString& Username, const FString& Email, const FGFApiCallback& Callback)
{
	FString ApiEndpoint = FString::Printf(TEXT("/create_user?game_id=%i&username=%s&email=%s"), GameId, *Username, *Email);
	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UTestAPIHandler::CreateStoreItem(int32 GameId, const FString& Name, const FString& Description, const FString& Category, int32 Cost, const FGFApiCallback& Callback)
{
	FString ApiEndpoint = FString::Printf(TEXT("/create_store_item?game_id=%i&name=%s&description=%s&category=%s&cost=%i"), GameId, *Name, *Description, *Category, Cost);
	return SendRequest(ApiEndpoint, "POST", Callback);
}

FGuid UTestAPIHandler::CreateStoreItem(int32 GameId, const FGFStoreItem& StoreItem, const FGFApiCallback& Callback)
{
	return CreateStoreItem(GameId, StoreItem.Name, StoreItem.Description, StoreItem.Category, StoreItem.Cost, Callback);
}

FGuid UTestAPIHandler::CleanUpTestData(int32 GameId, const FGFApiCallback& Callback)
{
	FString ApiEndpoint = FString::Printf(TEXT("/clean_up_test?game_id=%i"), GameId);
	return SendRequest(ApiEndpoint, "DELETE", Callback);

}