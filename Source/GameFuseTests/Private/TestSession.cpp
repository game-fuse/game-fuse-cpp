#include "TestSession.h"

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
		if (!HandleAPIResponse(Request, Response, bWasSuccessful)) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to create test user."));
			FGFUserData NewUser;
			TSharedPtr<FJsonObject> JsonObject;
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
			FJsonSerializer::Deserialize(Reader, JsonObject);
			FJsonObjectConverter::JsonObjectToUStruct(JsonObject.ToSharedRef(), &NewUser);
			Callback.ExecuteIfBound(NewUser, Response->GetResponseCode());
		}
	});
}

void UTestSession::CreateTestStoreItem(int32 GameId, const FString& Name, const FString& Description, const FString& Category, int32 cost, const FStoreItemCreatedDelegate& Callback)
{
	TestAPIManager->CreateStoreItem(GameId, Name, Description, Category, cost, [this, Callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
		if (!HandleAPIResponse(Request, Response, bWasSuccessful)) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to create test store item."));
			Callback.ExecuteIfBound(FGFStoreItem(), 200);
		}
	});
}




void UTestSession::Initialize(FDoneDelegate OnInitialized)
{
	TestAPIManager->CreateGame([this, OnInitialized](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
		if (!HandleAPIResponse(Request, Response, bWasSuccessful)) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to initialize TestSession."));
		}
		OnInitialized.ExecuteIfBound();
	});
}

bool UTestSession::HandleAPIResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response) {
		UE_LOG(LogTemp, Warning, TEXT("API Call Failed: "));
		UTestSuiteAPIManager::LogRequestInfo(Request);
		return false;
	}

	const FString ResponseStr = Response->GetContentAsString();
	if (!FJsonObjectConverter::JsonObjectStringToUStruct(ResponseStr, &GameData)) {
		UE_LOG(LogTemp, Warning, TEXT("Failed to parse JSON response."));
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

	UE_LOG(LogTemp, Warning, TEXT("Cleaning up test data"));
	TestAPIManager->CleanUpTestData(GameData.Id, [this, OnCleanupComplete](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful) {
		if (!HandleAPIResponse(Request, Response, bWasSuccessful)) {
			UE_LOG(LogTemp, Warning, TEXT("Failed to cleanup TestSession."));
		}
		OnCleanupComplete.ExecuteIfBound();
	});
}

const FGFGameData& UTestSession::GetGameData() const
{
	return GameData;
}