#if WITH_AUTOMATION_TESTS
#include "Library/GameFuseLog.h"
#include "Misc/AutomationTest.h"
#include "Subsystems/GameFuseManager.h"
#include "Subsystems/GameFuseUser.h"
#include "Commands/TestSuiteCommands.h"

BEGIN_DEFINE_SPEC(GameFuseUserSpec, "GameFuseTests.GameFuseUser",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UGameFuseManager* GameFuseManager;
	UGameFuseUser* GameFuseUser;
	UGameInstance* GameInstance;
	UTestAPIHandler* TestAPIHandler;
	TSharedPtr<FGFGameData> GameData;
	TSharedPtr<FGFUserData> UserData;
	bool bCleanupSuccess;
END_DEFINE_SPEC(GameFuseUserSpec);

void GameFuseUserSpec::Define()
{
	UE_LOG(LogGameFuse, Log, TEXT("GameFuseUserSpec::DEFINE was called"));
	// Setup
	GameInstance = NewObject<UGameInstance>();
	GameInstance->Init();

	// Get subsystems/ test api handler
	GameFuseManager = GameInstance->GetSubsystem<UGameFuseManager>();
	GameFuseUser = GameInstance->GetSubsystem<UGameFuseUser>();
	TestAPIHandler = NewObject<UTestAPIHandler>();

	//init testing data
	GameData = MakeShared<FGFGameData>();
	UserData = MakeShared<FGFUserData>();
	bCleanupSuccess = false;

	Describe("GameFuseUser Authentication", [this]() {
		BeforeEach([this]() {
			// Setup GameFuse before each test
			if (GameFuseManager->IsSetUp()) {
				// UE_LOG(LogGameFuse, Warning, TEXT("Already have a game setup"));
			}

			// Clear any saved user data
			if (GameFuseUser->IsSignedIn()) {
				GameFuseUser->LogOut();
			}

			// Create and setup game
			FGuid SetupGameRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FSetupGame(TestAPIHandler, GameData, GameFuseManager, this, FGuid()));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(TestAPIHandler, SetupGameRequestId));

			// Wait for GameFuseManager to be fully set up
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
				if (!GameFuseManager->IsSetUp()) {
				UE_LOG(LogGameFuse, Warning, TEXT("Waiting for GameFuseManager setup..."));
				return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("GameFuseManager setup complete"));
				return true;
				}));
		});

		It("adds credits to user", [this]() {
			// TSharedPtr<FGFUserData> TestUserData = MakeShared<FGFUserData>();
			// FString RandomGuid = FGuid::NewGuid().ToString();
			// TestUserData->Username = FString::Printf(TEXT("user_%s"), *RandomGuid.Left(8));

			// FGFApiCallback OnUserCreated;
			// OnUserCreated.AddLambda([this, TestUserData](const FGFAPIResponse& Response) {
			// 	TestTrue("Create user request succeeded", Response.bSuccess);
			// 	if (!Response.bSuccess) {
			// 		AddError(FString::Printf(TEXT("Create User Request failed. Response: %s"), *Response.ResponseStr));
			// 		return;
			// 	}
			//
			// 	bool bParseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, TestUserData.Get());
			// 	TestTrue("Parse user data response", bParseSuccess);
			//
			// 	TestTrue("User ID should be valid", TestUserData->Id != 0);
			// 	UE_LOG(LogGameFuse, Log, TEXT("TestUserData updated - ID: %d, Username: %s"), TestUserData->Id, *TestUserData->Username);
			//
			// 	FGFApiCallback SignInCallback;
			// 	SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
			// 		UE_LOG(LogGameFuse, Log, TEXT("Sign in Response: %s"), *Response.ResponseStr);
			// 		TestTrue("Sign in request succeeded", Response.bSuccess);
			// 		if (!Response.bSuccess) {
			// 			AddError(FString::Printf(TEXT("Sign in failed: %s"), *Response.ResponseStr));
			// 		}
			// 	});
			//
			// 	FGuid SignInRequestId = GameFuseUser->SignIn(TestUserData->Username + TEXT("@gamefuse.com"), TEXT("password"), SignInCallback);
			// 	ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), SignInRequestId));
			// });

			ADD_LATENT_AUTOMATION_COMMAND(FSetupUser(TestAPIHandler, GameData, UserData, GameFuseUser, this));

			FGuid AddCreditsRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, &AddCreditsRequestId]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
				return false;
				}

				FGFApiCallback AddCreditsCallback;
				AddCreditsCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Add credits Response: %s"), *Response.ResponseStr);
					TestTrue("Add credits request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
					AddError(FString::Printf(TEXT("Add credits failed: %s"), *Response.ResponseStr));
					}
					});

				AddCreditsRequestId = GameFuseUser->AddCredits(100, AddCreditsCallback);
				return true;
				}));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), AddCreditsRequestId));
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				TestTrue("credits are updated", GameFuseUser->GetCredits() == 100);
				return true;
				}
			));
			FGuid CleanupRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, CleanupRequestId));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(TestAPIHandler, CleanupRequestId));
		});

		It("sets credits for user", [this]() {
			// TSharedPtr<FGFUserData> TestUserData = MakeShared<FGFUserData>();
			// FString RandomGuid = FGuid::NewGuid().ToString();
			// TestUserData->Username = FString::Printf(TEXT("user_%s"), *RandomGuid.Left(8));
			//
			// FGFApiCallback OnUserCreated;
			// OnUserCreated.AddLambda([this, TestUserData](const FGFAPIResponse& Response) {
			// 	TestTrue("Create user request succeeded", Response.bSuccess);
			// 	if (!Response.bSuccess) {
			// 		AddError(FString::Printf(TEXT("Create User Request failed. Response: %s"), *Response.ResponseStr));
			// 		return;
			// 	}
			//
			// 	bool bParseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, TestUserData.Get());
			// 	TestTrue("Parse user data response", bParseSuccess);
			//
			// 	TestTrue("User ID should be valid", TestUserData->Id != 0);
			// 	UE_LOG(LogGameFuse, Log, TEXT("TestUserData updated - ID: %d, Username: %s"), TestUserData->Id, *TestUserData->Username);
			//
			// 	FGFApiCallback SignInCallback;
			// 	SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
			// 		UE_LOG(LogGameFuse, Log, TEXT("Sign in Response: %s"), *Response.ResponseStr);
			// 		TestTrue("Sign in request succeeded", Response.bSuccess);
			// 		if (!Response.bSuccess) {
			// 			AddError(FString::Printf(TEXT("Sign in failed: %s"), *Response.ResponseStr));
			// 		}
			// 	});
			//
			// 	FGuid SignInRequestId = GameFuseUser->SignIn(TestUserData->Username + TEXT("@gamefuse.com"), TEXT("password"), SignInCallback);
			// 	ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), SignInRequestId));
			// });

			ADD_LATENT_AUTOMATION_COMMAND(FSetupUser(TestAPIHandler, GameData, UserData, GameFuseUser, this));

			FGuid SetCreditsRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, &SetCreditsRequestId]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
				return false;
				}

				FGFApiCallback SetCreditsCallback;
				SetCreditsCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Set credits Response: %s"), *Response.ResponseStr);
					TestTrue("Set credits request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
					AddError(FString::Printf(TEXT("Set credits failed: %s"), *Response.ResponseStr));
					}
					});

				SetCreditsRequestId = GameFuseUser->SetCredits(200, SetCreditsCallback);
				return true;
				}));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), SetCreditsRequestId));

			FGuid CleanupRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, CleanupRequestId));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(TestAPIHandler, CleanupRequestId));
		});
	});

	Describe("GameFuseUser Store", [this]() {
		BeforeEach([this]() {
			// Setup GameFuse before each test
			if (GameFuseManager->IsSetUp()) {
				UE_LOG(LogGameFuse, Warning, TEXT("Already have a game setup"));
			}

			// Clear any saved user data
			if (GameFuseUser) {
				GameFuseUser->LogOut();
			}

			ADD_LATENT_AUTOMATION_COMMAND(FSetupGame(TestAPIHandler, GameData, GameFuseManager, this, FGuid()));


			// Wait for GameFuseManager to be fully set up
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
				if (!GameFuseManager->IsSetUp()) {
				UE_LOG(LogGameFuse, Warning, TEXT("Waiting for GameFuseManager setup..."));
				return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("GameFuseManager setup complete"));
				return true;
				}));
		});

		It("creates and purchases a store item", [this]() {


			ADD_LATENT_AUTOMATION_COMMAND(FSetupUser(TestAPIHandler, GameData, UserData, GameFuseUser, this));

			// Create store item
			TSharedPtr<FGFStoreItem> TestStoreItem = MakeShared<FGFStoreItem>();
			TestStoreItem->Name = TEXT("Test Item");
			TestStoreItem->Description = TEXT("A test store item");
			TestStoreItem->Cost = 100;
			TestStoreItem->Category = TEXT("test");

			FGuid CreateStoreItemRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FCreateStoreItem(TestAPIHandler, GameData, TestStoreItem, this, CreateStoreItemRequestId));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), CreateStoreItemRequestId));

			// Add credits to purchase item
			FGuid AddCreditsRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, &AddCreditsRequestId]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
				return false;
				}

				FGFApiCallback AddCreditsCallback;
				AddCreditsCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Add credits Response: %s"), *Response.ResponseStr);
					TestTrue("Add credits request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
					AddError(FString::Printf(TEXT("Add credits failed: %s"), *Response.ResponseStr));
					}
					});

				AddCreditsRequestId = GameFuseUser->AddCredits(200, AddCreditsCallback);
				return true;
				}));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), AddCreditsRequestId));

			// Purchase store item using item
			FGuid PurchaseItemRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, TestStoreItem, &PurchaseItemRequestId]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
				return false;
				}

				FGFApiCallback PurchaseCallback;
				PurchaseCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Purchase store item Response: %s"), *Response.ResponseStr);
					TestTrue("Purchase store item request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
					AddError(FString::Printf(TEXT("Purchase store item failed: %s"), *Response.ResponseStr));
					}
					});

				PurchaseItemRequestId = GameFuseUser->PurchaseStoreItem(*TestStoreItem, PurchaseCallback);
				return true;
				}));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), PurchaseItemRequestId));

			FGuid CleanupRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, CleanupRequestId));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(TestAPIHandler, CleanupRequestId));
		});

		It("purchases and removes store items using ID", [this]() {
			// TSharedPtr<FGFUserData> TestUserData = MakeShared<FGFUserData>();
			// FString RandomGuid = FGuid::NewGuid().ToString();
			// TestUserData->Username = FString::Printf(TEXT("user_%s"), *RandomGuid.Left(8));
			//
			// // Create and sign in user
			// FGFApiCallback OnUserCreated;
			// OnUserCreated.AddLambda([this, TestUserData](const FGFAPIResponse& Response) {
			// 	TestTrue("Create user request succeeded", Response.bSuccess);
			// 	if (!Response.bSuccess) {
			// 		AddError(FString::Printf(TEXT("Create User Request failed. Response: %s"), *Response.ResponseStr));
			// 		return;
			// 	}
			//
			// 	bool bParseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, TestUserData.Get());
			// 	TestTrue("Parse user data response", bParseSuccess);
			//
			// 	TestTrue("User ID should be valid", TestUserData->Id != 0);
			// 	UE_LOG(LogGameFuse, Log, TEXT("TestUserData updated - ID: %d, Username: %s"), TestUserData->Id, *TestUserData->Username);
			//
			// 	FGFApiCallback SignInCallback;
			// 	SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
			// 		UE_LOG(LogGameFuse, Log, TEXT("Sign in Response: %s"), *Response.ResponseStr);
			// 		TestTrue("Sign in request succeeded", Response.bSuccess);
			// 		if (!Response.bSuccess) {
			// 			AddError(FString::Printf(TEXT("Sign in failed: %s"), *Response.ResponseStr));
			// 		}
			// 	});
			//
			// 	FGuid SignInRequestId = GameFuseUser->SignIn(TestUserData->Username + TEXT("@gamefuse.com"), TEXT("password"), SignInCallback);
			// 	ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), SignInRequestId));
			// });

			ADD_LATENT_AUTOMATION_COMMAND(FSetupUser(TestAPIHandler, GameData, UserData, GameFuseUser, this));

			// Create store item
			TSharedPtr<FGFStoreItem> TestStoreItem = MakeShared<FGFStoreItem>();
			TestStoreItem->Name = TEXT("Test Item 2");
			TestStoreItem->Description = TEXT("Another test store item");
			TestStoreItem->Cost = 150;
			TestStoreItem->Category = TEXT("test2");

			FGuid CreateStoreItemRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FCreateStoreItem(TestAPIHandler, GameData, TestStoreItem, this, CreateStoreItemRequestId));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), CreateStoreItemRequestId));

			// Add credits to purchase item
			FGuid AddCreditsRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, &AddCreditsRequestId]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
				return false;
				}

				FGFApiCallback AddCreditsCallback;
				AddCreditsCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Add credits Response: %s"), *Response.ResponseStr);
					TestTrue("Add credits request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
					AddError(FString::Printf(TEXT("Add credits failed: %s"), *Response.ResponseStr));
					}
					});

				AddCreditsRequestId = GameFuseUser->AddCredits(200, AddCreditsCallback);
				return true;
				}));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), AddCreditsRequestId));

			// Purchase store item using item ID
			FGuid PurchaseItemRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, TestStoreItem, &PurchaseItemRequestId]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
				return false;
				}

				FGFApiCallback PurchaseCallback;
				PurchaseCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Purchase store item Response: %s"), *Response.ResponseStr);
					TestTrue("Purchase store item request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
					AddError(FString::Printf(TEXT("Purchase store item failed: %s"), *Response.ResponseStr));
					}
					});

				PurchaseItemRequestId = GameFuseUser->PurchaseStoreItemWithId(TestStoreItem->Id, PurchaseCallback);
				return true;
				}));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), PurchaseItemRequestId));

			// Remove store item using item ID
			FGuid RemoveItemRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, TestStoreItem, &RemoveItemRequestId]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
				return false;
				}

				FGFApiCallback RemoveCallback;
				RemoveCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Remove store item Response: %s"), *Response.ResponseStr);
					TestTrue("Remove store item request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
					AddError(FString::Printf(TEXT("Remove store item failed: %s"), *Response.ResponseStr));
					}
					});

				RemoveItemRequestId = GameFuseUser->RemoveStoreItemWithId(TestStoreItem->Id, RemoveCallback);
				return true;
				}));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), RemoveItemRequestId));

			FGuid CleanupRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, CleanupRequestId));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(TestAPIHandler, CleanupRequestId));
		});
	});
}

#endif