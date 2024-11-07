#if WITH_AUTOMATION_TESTS

#include "TestSession.h"
#include "Library/GameFuseStructLibrary.h"
#include "Misc/AutomationTest.h"

BEGIN_DEFINE_SPEC(TestSuiteAPI, "GameFuseTests.TestSuiteAPI", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)
	TObjectPtr<UTestSession> TestSession;
	FGFGameData GameData;
END_DEFINE_SPEC(TestSuiteAPI)

void TestSuiteAPI::Define()
{
	Describe("TestSession", [this]() {
		LatentIt("Creates a test session successfully", [this](const FDoneDelegate& Done) {
			UTestSession::CreateTestSession(FGameCreatedDelegate::CreateLambda([this, Done](UTestSession* CreatedSession) {
				TestSession = CreatedSession;
				TestNotNull("Test Session was created", TestSession.Get());
				TestTrue("Test Session has a valid ID", TestSession->GetGameData().Id != 0);
				Done.ExecuteIfBound();
			}));
		});
	});

	Describe("User Operations", [this]() {
		LatentBeforeEach([this](const FDoneDelegate& Done) {
			UTestSession::CreateTestSession(FGameCreatedDelegate::CreateLambda([this, Done](UTestSession* CreatedSession) {
				TestSession = CreatedSession;
				GameData = CreatedSession->GetGameData();
				Done.ExecuteIfBound();
			}));
		});

		LatentIt("Creates a User", [this](const FDoneDelegate& Done) {
			TestNotNull("Test Session exists", TestSession.Get());
			TestSession->CreateTestUser(GameData.Id, TEXT("Username"), TEXT("test_email@test.com"), FUserCreatedDelegate::CreateLambda([this, Done](const FGFUserData& NewUser, const uint8 ResponseCode) {
				TestEqual("Request was successful", ResponseCode, 200);
				TestNotEqual("UserData is not default", NewUser, FGFUserData());
				Done.ExecuteIfBound();
			}));
		});

		LatentIt("Fails with invalid game ID", [this](const FDoneDelegate& Done) {
			TestSession->CreateTestUser(0, TEXT("Username"), TEXT("test_email@test.com"), FUserCreatedDelegate::CreateLambda([this, Done](const FGFUserData& NewUser, const uint8 ResponseCode) {
				TestEqual("Response code should be 404", ResponseCode, 404);
				TestEqual("Returned User should be default", NewUser, FGFUserData());
				Done.ExecuteIfBound();
			}));
		});

		LatentAfterEach([this](const FDoneDelegate& Done) {
			if (TestSession) {
				TestSession->Cleanup(Done);
			} else {
				Done.ExecuteIfBound();
			}
		});
	});
}

#endif // WITH_AUTOMATION_TESTS