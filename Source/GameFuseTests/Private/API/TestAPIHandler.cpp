#include "API/TestAPIHandler.h"
#include "Dom/JsonObject.h"
#include "HttpModule.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "GenericPlatform/GenericPlatformHttp.h"

UTestAPIHandler::UTestAPIHandler()
{
	const FString ServiceKeyName = FPlatformMisc::GetEnvironmentVariable(TEXT("GAMEFUSE_TEST_SERVICE_KEY"));
	const FString ServiceKeyToken = FPlatformMisc::GetEnvironmentVariable(TEXT("GAMEFUSE_TEST_SERVICE_TOKEN"));

	CommonHeaders.Add(TEXT("service-key-token"), *ServiceKeyToken);
	CommonHeaders.Add(TEXT("service-key-name"), *ServiceKeyName);
}

FGuid UTestAPIHandler::CreateGame(const FGFApiCallback& Callback)
{
	return SendRequest(TEXT("/test_suite/create_game"), TEXT("POST"), Callback);
}

FGuid UTestAPIHandler::CreateUser(int32 GameId, const FString& Username, const FString& Email, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/test_suite/create_user?game_id=%d&username=%s&email=%s"),
	                                            GameId, *Username, *Email);
	return SendRequest(ApiEndpoint, TEXT("POST"), Callback);
}

FGuid UTestAPIHandler::CreateStoreItem(int32 GameId, const FGFStoreItem& Item, const FGFApiCallback& Callback)
{
	const FString EncodedName = FGenericPlatformHttp::UrlEncode(Item.Name);
	const FString EncodedDescription = FGenericPlatformHttp::UrlEncode(Item.Description);
	const FString EncodedCategory = FGenericPlatformHttp::UrlEncode(Item.Category);
	const FString ApiEndpoint = FString::Printf(TEXT("/test_suite/create_store_item?game_id=%d&name=%s&description=%s&category=%s&cost=%d"),
	                                            GameId, *EncodedName, *EncodedDescription, *EncodedCategory, Item.Cost);
	return SendRequest(ApiEndpoint, TEXT("POST"), Callback);
}

FGuid UTestAPIHandler::CleanupGame(int32 GameId, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/test_suite/clean_up_test?game_id=%d"), GameId);
	return SendRequest(ApiEndpoint, TEXT("DELETE"), Callback);
}