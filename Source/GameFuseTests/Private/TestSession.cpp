#include "TestSession.h"
struct FLogCategoryLogGameFuse LogGameFuse;

void UTestSession::CreateTestSession(FGameCreatedDelegate OnCreated)
{
	UTestSession* Session = NewObject<UTestSession>();
	Session->TestAPIManager = NewObject<UTestSuiteAPIManager>();
	Session->Initialize(FDoneDelegate::CreateLambda([Session, OnCreated]() {
		OnCreated.ExecuteIfBound(Session);
	}));
}

void UTestSession::CreateTestUser(const int GameId, const FString& Username, const FString& Email, const FUserCreatedDelegate& Callback)
{
	TestAPIManager->CreateUser(GameId, Username, Email, [this, Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
		if (!CheckValidResponse(Request, Response, bWasSuccessful)) {
			Callback.ExecuteIfBound(FGFUserData(), 0);
		}
		if (Response->GetResponseCode() < 200 || Response->GetResponseCode() >= 300) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to create test user. Response: %s"), *Response->GetContentAsString());
			Callback.ExecuteIfBound(FGFUserData(), Response->GetResponseCode());
			return;
		}

		FGFUserData NewUser;
		if (!FJsonObjectConverter::JsonObjectStringToUStruct(Response->GetContentAsString(), &NewUser)) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to create test user."));
		}
		Callback.ExecuteIfBound(NewUser, Response->GetResponseCode());
	});
}


void UTestSession::CreateTestStoreItem(int32 GameId, const FString& Name, const FString& Description, const FString& Category, int32 cost, const FStoreItemCreatedDelegate& Callback)
{
	TestAPIManager->CreateStoreItem(GameId, Name, Description, Category, cost, [this, Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
		if (!CheckValidResponse(Request, Response, bWasSuccessful)) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to create test store item."));
		}
		Callback.ExecuteIfBound(FGFStoreItem(), 200);
	});
}




void UTestSession::Initialize(FDoneDelegate OnInitialized)
{
	TestAPIManager->CreateGame([this, OnInitialized](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
		if (!CheckValidResponse(Request, Response, bWasSuccessful)) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to initialize TestSession."));
			OnInitialized.ExecuteIfBound();
			return false;
		}

		if (Response->GetResponseCode() < 200 || Response->GetResponseCode() >= 300) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to initialize TestSession."));
			UTestSuiteAPIManager::LogRequestInfo(Request);
			OnInitialized.ExecuteIfBound();
			return false;
		}

		const FString ResponseStr = Response->GetContentAsString();
		if (!FJsonObjectConverter::JsonObjectStringToUStruct(ResponseStr, &GameData)) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to parse JSON GameData response."));
			OnInitialized.ExecuteIfBound();
			return false;
		}
		OnInitialized.ExecuteIfBound();
		return true;
	});
}

bool UTestSession::CheckValidResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response) {
		UE_LOG(LogTemp, Warning, TEXT("API Call Failed: "));
		UTestSuiteAPIManager::LogRequestInfo(Request);
		return false;
	}

	return true;
}


void UTestSession::Cleanup(FDoneDelegate OnCleanupComplete)
{
	if (!TestAPIManager) {
		UE_LOG(LogTemp, Warning, TEXT("Test API is null. Nothing to clean up."));
		OnCleanupComplete.ExecuteIfBound();
		return;
	}

	UE_LOG(LogTemp, Display, TEXT("Cleaning up test data for GameId : %i"), GameData.Id);
	TestAPIManager->CleanUpTestData(GameData.Id, [this, OnCleanupComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
		if (!CheckValidResponse(Request, Response, bWasSuccessful)) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to cleanup TestSession."));
		}
		OnCleanupComplete.ExecuteIfBound();
	});
}

const FGFGameData& UTestSession::GetGameData() const
{
	return GameData;
}