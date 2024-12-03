#include "Subsystems/GameFuseTestSuite.h"
#include "JsonObjectConverter.h"
#include "Library/GameFuseLog.h"

void UGameFuseTestSuite::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	UE_LOG(LogGameFuse, Log, TEXT("GameFuseTestSuite Initialized"));
	APIHandler = NewObject<UTestAPIHandler>();
}

void UGameFuseTestSuite::Deinitialize()
{
	// FDoneDelegate CleanupFinished;
	// CleanupFinished.BindLambda([this]() {
	// 	UE_LOG(LogGameFuse, Log, TEXT("GameFuseTestSuite CleanedUp"));
	// });
	// CleanupTestSession(CleanupFinished);
	Super::Deinitialize();
}

void UGameFuseTestSuite::CreateTestSession(const FGameCreatedDelegate& OnCreated)
{
	// Create a new test game
	FGFApiCallback ApiCallback;
	ApiCallback.AddDynamic(this, &UGameFuseTestSuite::HandleGameCreated);
	PendingGameCreated = OnCreated;

	// Call API to create game
	APIHandler->CreateGame(ApiCallback);
}

void UGameFuseTestSuite::HandleGameCreated(FGFAPIResponse Response)
{
	if (Response.bSuccess && FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, &GameData)) {
		PendingGameCreated.ExecuteIfBound(GameData);
	} else {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to create test game"));
		PendingGameCreated.ExecuteIfBound(FGFGameData());
	}
}

void UGameFuseTestSuite::CleanupTestSession(const FDoneDelegate& Done)
{
	if (GameData.Id == 0) {
		Done.ExecuteIfBound();
		return;
	}

	PendingDone = Done;
	FGFApiCallback ApiCallback;
	ApiCallback.AddDynamic(this, &UGameFuseTestSuite::HandleCleanupResponse);

	// Call API to cleanup game
	APIHandler->CleanUpTestData(GameData.Id, ApiCallback);
}

void UGameFuseTestSuite::CreateTestUser(const FDoneDelegate& Done)
{
	if (GameData.Id == 0) {
		Done.ExecuteIfBound();
		return;
	}

	PendingDone = Done;
	FGFApiCallback UserCallback;
	UserCallback.AddDynamic(this, &UGameFuseTestSuite::HandleUserCreated);

	// Call API to create test user
	APIHandler->CreateUser(GameData.Id, TEXT("Username"), TEXT("test_email@test.com"), UserCallback);
}

void UGameFuseTestSuite::CreateTestStoreItem(const FDoneDelegate& Done)
{
	if (GameData.Id == 0) {
		Done.ExecuteIfBound();
		return;
	}

	PendingDone = Done;
	FGFApiCallback StoreCallback;
	StoreCallback.AddDynamic(this, &UGameFuseTestSuite::HandleStoreItemCreated);

	// Call API to create test store item
	APIHandler->CreateStoreItem(GameData.Id, TEXT("Test Item"), TEXT("Test Description"), TEXT("Test Category"), 100, StoreCallback);
}

void UGameFuseTestSuite::CreateInvalidTestUser(const FDoneDelegate& Done)
{
	if (GameData.Id == 0) {
		Done.ExecuteIfBound();
		return;
	}

	PendingDone = Done;
	FGFApiCallback UserCallback;
	UserCallback.AddDynamic(this, &UGameFuseTestSuite::HandleInvalidUserCreated);

	// Call API to create test user with invalid game ID
	APIHandler->CreateUser(0, TEXT("Username"), TEXT("test_email@test.com"), UserCallback);
}

void UGameFuseTestSuite::HandleCleanupResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogTemp, Error, TEXT("Test Game was not cleaned up successfully. GameID : %d"), GameData.Id);
	}

	GameData = FGFGameData();
	PendingDone.ExecuteIfBound();
}

void UGameFuseTestSuite::HandleUserCreated(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogTemp, Error, TEXT("Test User was not created successfully. GameID : %d"), GameData.Id);
	}

	PendingDone.ExecuteIfBound();
}

void UGameFuseTestSuite::HandleInvalidUserCreated(FGFAPIResponse Response)
{
	if (Response.bSuccess) {
		UE_LOG(LogTemp, Error, TEXT("Test User was created with invalid game ID"));
	}

	PendingDone.ExecuteIfBound();
}

void UGameFuseTestSuite::HandleStoreItemCreated(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogTemp, Error, TEXT("Test Store Item was not created successfully. GameID : %d"), GameData.Id);
	}

	PendingDone.ExecuteIfBound();
}