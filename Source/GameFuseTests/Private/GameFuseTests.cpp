#include "GameFuseTests.h"
#include "Library/GameFuseLog.h"
#include "Misc/AutomationTest.h"
#include "Subsystems/GameFuseManager.h"

#define LOCTEXT_NAMESPACE "FGameFuseTestsModule"

void FGameFuseTestsModule::StartupModule()
{
	FAutomationTestFramework::Get().OnBeforeAllTestsEvent.AddLambda([this]() {
		UE_LOG(LogGameFuse, Log, TEXT("GameFuse ====> OnBeforeAllTestsEvent"));

		GameInstance = NewObject<UGameInstance>();
		GameInstance->Init();
		GameFuseManager = GameInstance->GetSubsystem<UGameFuseManager>();
		GameData = MakeShared<FGFGameData>();

		TestAPIHandler = NewObject<UTestAPIHandler>();
	});

	FAutomationTestFramework::Get().OnAfterAllTestsEvent.AddLambda([]() {
		UE_LOG(LogGameFuse, Log, TEXT("GameFuse ====> OnAfterAllTestsEvent"));
	});

	FAutomationTestFramework::Get().OnTestStartEvent.AddLambda([](FAutomationTestBase* Test) {
		if (Test != nullptr) {
			UE_LOG(LogGameFuse, Log, TEXT("Starting test: %s"), *Test->GetTestFullName());
		}
	});

	FAutomationTestFramework::Get().OnTestEndEvent.AddLambda([](FAutomationTestBase* Test) {
		if (Test != nullptr) {
			UE_LOG(LogGameFuse, Log, TEXT("Ending test: %s"), *Test->GetTestFullName());
		}
	});
}

void FGameFuseTestsModule::ShutdownModule()
{}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGameFuseTestsModule, GameFuseTests)