#include "Subsystems/GameFuseTestSuite.h"
#include "JsonObjectConverter.h"
#include "Library/GameFuseLog.h"

void UGameFuseTestSuite::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogGameFuse, Log, TEXT("GameFuseTestSuite Initialized"));
	APIHandler = NewObject<UTestAPIHandler>(this);

	FGFApiCallback Callback;
	Callback.AddDynamic(this, &UGameFuseTestSuite::HandleGameCreated);
	APIHandler->CreateGame(Callback);
}

void UGameFuseTestSuite::Deinitialize()
{
	Super::Deinitialize();
}

FGuid UGameFuseTestSuite::CreateTestSession(const FGFApiCallback& Callback)
{
	// Create a new test game
	FGFApiCallback ApiCallback;
	ApiCallback.AddDynamic(this, &UGameFuseTestSuite::HandleGameCreated);

	// Call API to create game
	return APIHandler->CreateGame(ApiCallback);
}

TObjectPtr<UTestAPIHandler> UGameFuseTestSuite::GetRequestHandler() const
{
	return APIHandler;
}

void UGameFuseTestSuite::HandleGameCreated(FGFAPIResponse Response)
{

	UE_LOG(LogGameFuse, Log, TEXT("Handle game created responded"));
	if (Response.bSuccess) {
		FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, &GameData);

	} else {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to create test game"));

	}
}

FGuid UGameFuseTestSuite::CleanupTestSession(const FGFApiCallback& Callback)
{
	if (GameData.Id == 0) {
		return FGuid();
	}

	FGFApiCallback ApiCallback;
	ApiCallback.AddDynamic(this, &UGameFuseTestSuite::HandleCleanupResponse);

	// Call API to cleanup game
	return APIHandler->CleanUpTestData(GameData.Id, ApiCallback);
}

FGuid UGameFuseTestSuite::CreateTestUser(const FGFApiCallback& Callback)
{
	if (GameData.Id == 0) {
		return FGuid();
	}
	FGFApiCallback UserCallback;
	UserCallback.AddDynamic(this, &UGameFuseTestSuite::HandleUserCreated);

	// Call API to create test user
	return APIHandler->CreateUser(GameData.Id, TEXT("Username"), TEXT("test_email@test.com"), UserCallback);
}

FGuid UGameFuseTestSuite::CreateTestStoreItem(const FGFApiCallback& Callback)
{
	if (GameData.Id == 0) {
		return FGuid();
	}

	FGFApiCallback StoreCallback;
	StoreCallback.AddDynamic(this, &UGameFuseTestSuite::HandleStoreItemCreated);

	// Call API to create test store item
	return APIHandler->CreateStoreItem(GameData.Id, TEXT("Test Item"), TEXT("Test Description"), TEXT("Test Category"), 100, StoreCallback);
}

void UGameFuseTestSuite::HandleCleanupResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogTemp, Error, TEXT("Test Game was not cleaned up successfully. GameID : %d"), GameData.Id);
	}

	GameData = FGFGameData();
}

void UGameFuseTestSuite::HandleUserCreated(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogTemp, Error, TEXT("Test User was not created successfully. GameID : %d"), GameData.Id);
	}

}

void UGameFuseTestSuite::HandleStoreItemCreated(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogTemp, Error, TEXT("Test Store Item was not created successfully. GameID : %d"), GameData.Id);
	}

}