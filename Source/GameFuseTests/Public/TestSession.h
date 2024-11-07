#pragma once

#include "CoreMinimal.h"
#include "JsonObjectConverter.h"
#include "TestSuiteAPIManager.h"
#include "UObject/Object.h"
#include "TestSession.generated.h"


DECLARE_DELEGATE_OneParam(FGameCreatedDelegate, UTestSession*);
DECLARE_DELEGATE_TwoParams(FUserCreatedDelegate, const FGFUserData&, const uint8 ResponseCode);
DECLARE_DELEGATE_TwoParams(FStoreItemCreatedDelegate, const FGFStoreItem&, const uint8 ResponseCode);


UCLASS()
class GAMEFUSETESTS_API UTestSession : public UObject
{
	GENERATED_BODY()

public:

	static void CreateTestSession(FGameCreatedDelegate OnCreated);

	void CreateTestUser(int GameId, const FString& Username, const FString& Email, const FUserCreatedDelegate& Callback);
	void CreateTestStoreItem(int32 GameId, const FString& Name, const FString& Description, const FString& Category, int32 cost, const FStoreItemCreatedDelegate& Callback);


	void Cleanup(FDoneDelegate OnCleanupComplete);
	const FGFGameData& GetGameData() const;

private:

	void Initialize(FDoneDelegate OnInitialized);
	bool HandleAPIResponse(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);

	UPROPERTY()
	TObjectPtr<UTestSuiteAPIManager> TestAPIManager;
	FGFGameData GameData;
};