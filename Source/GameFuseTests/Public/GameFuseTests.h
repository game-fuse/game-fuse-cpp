#pragma once

#include "CoreMinimal.h"
#include "API/TestAPIHandler.h"
#include "Modules/ModuleManager.h"
#include "Subsystems/GameFuseManager.h"

class FGameFuseTestsModule : public IModuleInterface
{
public:

	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	UGameInstance* GameInstance;
	UGameFuseManager* GameFuseManager;
	TSharedPtr<FGFGameData> GameData;
	TObjectPtr<UTestAPIHandler> TestAPIHandler;


	bool isSetUp = false;
};