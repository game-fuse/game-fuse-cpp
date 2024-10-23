#if WITH_AUTOMATION_TESTS

#include "JsonObjectConverter.h"
#include "Models/GameFuseUtilities.h"
#include "TestSuiteAPIManager.h"
#include "GameFuseTestsUtilities.h"

#include "Library/GameFuseStructLibrary.h"
#include "Misc/AutomationTest.h"

BEGIN_DEFINE_SPEC(TestSuiteAPI, "GameFuseTests.TestSuiteAPI", EAutomationTestFlags::ProductFilter | EAutomationTestFlags::ApplicationContextMask)

	// Declare Variables Here (basically a header)
	FGFGameData GameData;

END_DEFINE_SPEC(TestSuiteAPI);

void TestSuiteAPI::Define()
{
	Describe("Test Environment", [this]() {

		LatentBeforeEach([this](const FDoneDelegate& Done) {
			GameData = FGFGameData();
			UTestSuiteAPIManager::CreateGame([this, Done](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bWasSuccessful) {
				AddErrorIfFalse(bWasSuccessful, FString::Printf(TEXT("Connection failed with Response: %s"), *HttpResponse->GetContentAsString()));

				TestTrue("Create Game success", bWasSuccessful);
				const FString ResponseStr = HttpResponse->GetContentAsString();
				const int ResponseCode = HttpResponse->GetResponseCode();
				FJsonObjectConverter::JsonObjectStringToUStruct(ResponseStr, &GameData);

				TestTrue("GameData ID is not default", GameData.Id != 0);
				AddInfo(FString::Printf(TEXT("====== Created Game ID: %d"), GameData.Id));
				Done.Execute();
			});
		});

		LatentAfterEach([this](const FDoneDelegate& Done) {
			AddErrorIfFalse(GameData.Id != 0, "Game was not setup properly");
			UTestSuiteAPIManager::CleanUpTestData(GameData.Id, [this, Done](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bWasSuccessful) {
				AddErrorIfFalse(bWasSuccessful, FString::Printf(TEXT("Connection failed with Response: %s"), *HttpResponse->GetContentAsString()));
				TestTrue("cleans up game data", bWasSuccessful);
				AddInfo(FString::Printf(TEXT("====== Deleted Game ID: %d"), GameData.Id));
				Done.Execute();
			});
		});
		//
		// LatentIt("Creates a Game", EAsyncExecution::TaskGraph, [this](const FDoneDelegate& Done) {
		// 	UTestSuiteAPIManager::CreateGame([this, Done](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bWasSuccessful) {
		// 		AddErrorIfFalse(bWasSuccessful, FString::Printf(TEXT("Connection failed with Response: %s"), *HttpResponse->GetContentAsString()));
		//
		// 		const FString ResponseStr = HttpResponse->GetContentAsString();
		// 		const int ResponseCode = HttpResponse->GetResponseCode();
		// 		FJsonObjectConverter::JsonObjectStringToUStruct(ResponseStr, &GameData);
		//
		// 		TestTrue("GameData ID is not default", GameData.Id != 0);
		// 		Done.Execute();
		// 	});
		// });

		LatentIt("Creates a User", [this](const FDoneDelegate& Done) {
			AddErrorIfFalse(GameData.Id != 0, "Game was not setup properly");
			UTestSuiteAPIManager::CreateUser(GameData.Id, TEXT("Username"), TEXT("test_email@test.com"), [this, Done](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bWasSuccessful) {
				const FString ResponseStr = HttpResponse->GetContentAsString();


				AddErrorIfFalse(bWasSuccessful, FString::Printf(TEXT("Connection failed with Response: %s"), *ResponseStr));
				FGFUserData UserData;
				FJsonObjectConverter::JsonObjectStringToUStruct(ResponseStr, &UserData);

				TestTrue("User ID is not default", UserData.Id != 0);
				Done.Execute();
			});
		});
	});
	//
	// Describe("Fail Cases", [this]() {
	// 	LatentIt("Fails with bad ID", [this](const FDoneDelegate& Done) {
	// 		UTestSuiteAPIManager::CleanUpTestData(0, [this, Done](FHttpRequestPtr HttpRequest, FHttpResponsePtr HttpResponse, bool bWasSuccessful) {
	// 			const int32 ResponseCode = HttpResponse->GetResponseCode();
	//
	// 			TestTrue("Response code is 404", ResponseCode == 404);
	//
	// 			Done.Execute();
	// 		});
	// 	});
	// });
}

#endif