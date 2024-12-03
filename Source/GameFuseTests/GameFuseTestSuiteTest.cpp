#include "Kismet/GameplayStatics.h"
#include "Misc/AutomationTest.h"

#include "Library/GameFuseLog.h"
#include "Subsystems/GameFuseTestSuite.h"
#include "Commands/WaitForFGFResponse.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(GameFuseTestSuiteTest, "GameFuseTests.GameFuseTestSuiteTest", EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)

bool GameFuseTestSuiteTest::RunTest(const FString& Parameters)
{
	UGameInstance* GameInstance = NewObject<UGameInstance>();
	GameInstance->Init();
	UGameFuseTestSuite* GameFuseTestSuite = GameInstance->GetSubsystem<UGameFuseTestSuite>();

	if (!GameFuseTestSuite) {
		UE_LOG(LogGameFuse, Error, TEXT("No GameFuseTestSuite found"));
		return false;
	}

	// Example of using the WaitForFGFResponse command
	FGFAPIResponse Response;
	FGFApiCallback Callback;
	FGuid RequestId = GameFuseTestSuite->CreateTestSession(Callback);

	ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseTestSuite->GetRequestHandler(), RequestId, Response));

	return true;
}