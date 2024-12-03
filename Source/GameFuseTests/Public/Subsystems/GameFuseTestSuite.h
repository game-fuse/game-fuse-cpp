#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "API/TestAPIHandler.h"
#include "Library/GameFuseStructLibrary.h"
#include "GameFuseTestSuite.generated.h"

DECLARE_DELEGATE_OneParam(FGameCreatedDelegate, const FGFGameData&);

/**
 * Subsystem to handle GameFuse test suite functionality
 */
UCLASS()
class GAMEFUSETESTS_API UGameFuseTestSuite : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	// Initialize and cleanup
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Test game management
	void CreateTestSession(const FGameCreatedDelegate& OnCreated);
	void CleanupTestSession(const FDoneDelegate& Done);

	void CreateTestUser(const FDoneDelegate& Done);
	void CreateTestStoreItem(const FDoneDelegate& Done);
	void CreateInvalidTestUser(const FDoneDelegate& Done);

	// Getters
	const FGFGameData& GetTestSession() const
	{
		return GameData;
	}

	const FGFGameData& GetGameData() const
	{
		return GameData;
	}

private:

	UPROPERTY()
	TObjectPtr<UTestAPIHandler> APIHandler;
	FGFGameData GameData;
	FDoneDelegate PendingDone;
	FGameCreatedDelegate PendingGameCreated;

	// Response handlers
	UFUNCTION()
	void HandleGameCreated(FGFAPIResponse Response);

	UFUNCTION()
	void HandleCleanupResponse(FGFAPIResponse Response);

	UFUNCTION()
	void HandleUserCreated(FGFAPIResponse Response);

	UFUNCTION()
	void HandleInvalidUserCreated(FGFAPIResponse Response);

	UFUNCTION()
	void HandleStoreItemCreated(FGFAPIResponse Response);
};