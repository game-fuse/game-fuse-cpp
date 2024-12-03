#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "API/TestAPIHandler.h"
#include "Library/GameFuseStructLibrary.h"
#include "GameFuseTestSuite.generated.h"

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
	FGuid CreateTestSession(const FGFApiCallback& Callback);
	FGuid CleanupTestSession(const FGFApiCallback& Callback);

	FGuid CreateTestUser(const FGFApiCallback& Callback);
	FGuid CreateTestStoreItem(const FGFApiCallback& Callback);

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

public:

	TObjectPtr<UTestAPIHandler> GetRequestHandler() const;

private:

	FGFGameData GameData;

	// Response handlers
	UFUNCTION()
	void HandleGameCreated(FGFAPIResponse Response);

	UFUNCTION()
	void HandleCleanupResponse(FGFAPIResponse Response);

	UFUNCTION()
	void HandleUserCreated(FGFAPIResponse Response);

	UFUNCTION()
	void HandleStoreItemCreated(FGFAPIResponse Response);
};