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

				TestSession->Cleanup(FGameCleanupDelegate::CreateLambda([this, Done](const uint8 ResponseCode) {
					TestTrue("Test Session was cleaned up successfully", ResponseCode == 200);
					Done.ExecuteIfBound();
				}));

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
			TestNotNull("Test Session exists", TestSession.Get());
			TestSession->CreateTestUser(0, TEXT("Username"), TEXT("test_email@test.com"), FUserCreatedDelegate::CreateLambda([this, Done](const FGFUserData& NewUser, const uint8 ResponseCode) {
				TestEqual("Response code should be 404", ResponseCode, 404);
				TestEqual("Returned User should be default", NewUser, FGFUserData());
				Done.ExecuteIfBound();
			}));
		});

		LatentAfterEach([this](const FDoneDelegate& Done) {
			if (TestSession) {
				TestSession->Cleanup(FGameCleanupDelegate::CreateLambda([this, Done](const uint8 ResponseCode) {
					TestTrue("Test Session was cleaned up successfully", ResponseCode == 200);
					AddErrorIfFalse(ResponseCode == 200, "Test Session was not cleaned up successfully. GameID : " + FString::FromInt(GameData.Id));
					Done.ExecuteIfBound();
				}));
			} else {
				Done.ExecuteIfBound();
			}
		});
	});

	Describe("Store Item Operations", [this]() {
		LatentBeforeEach([this](const FDoneDelegate& Done) {
			UTestSession::CreateTestSession(FGameCreatedDelegate::CreateLambda([this, Done](UTestSession* CreatedSession) {
				TestSession = CreatedSession;
				GameData = CreatedSession->GetGameData();
				Done.ExecuteIfBound();
			}));
		});

		LatentAfterEach([this](const FDoneDelegate& Done) {
			if (TestSession) {
				TestSession->Cleanup(FGameCleanupDelegate::CreateLambda([this, Done](const uint8 ResponseCode) {
					TestTrue("Test Session was cleaned up successfully", ResponseCode == 200);
					AddErrorIfFalse(ResponseCode == 200, "Test Session was not cleaned up successfully. GameID : " + FString::FromInt(GameData.Id));
					Done.ExecuteIfBound();
				}));
			} else {
				Done.ExecuteIfBound();
			}
		});

		LatentIt("Creates a Store Item", [this](const FDoneDelegate& Done) {
			TestNotNull("Test Session exists", TestSession.Get());
			TestSession->CreateTestStoreItem(GameData.Id, TEXT("Test Item"), TEXT("Test Description"), TEXT("Test Category"), 100, FStoreItemCreatedDelegate::CreateLambda([this, Done](const FGFStoreItem& NewItem, const uint8 ResponseCode) {
				TestEqual("Response code should be 200", ResponseCode, 200);
				TestNotEqual("Store Item is not default", NewItem, FGFStoreItem());
				Done.ExecuteIfBound();
			}));
		});
	});
}

#endif // WITH_AUTOMATION_TESTS