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

	// init testing data
	GameData = MakeShared<FGFGameData>();
	UserData = MakeShared<FGFUserData>();
	bCleanupSuccess = false;

	Describe("GameFuseUser Authentication", [this]() {
		BeforeEach([this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				if (GameFuseManager->IsSetUp()) {
					UE_LOG(LogGameFuse, Warning, TEXT("Game was already Setup"));
					GameFuseManager->ClearGameData();
					return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("GameFuseManager cleanup complete"));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				if (GameFuseUser->IsSignedIn()) {
					UE_LOG(LogGameFuse, Warning, TEXT("User was already Signed in"));
					GameFuseUser->LogOut();
					return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("GameFuseUser cleanup complete"));
				return true;
			}));
			// Create and setup game
			ADD_LATENT_AUTOMATION_COMMAND(FSetupGame(TestAPIHandler, GameData, GameFuseManager, this, FGuid()));


			// Wait for GameFuseManager to be fully set up
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				if (!GameFuseManager->IsSetUp()) {
					UE_LOG(LogGameFuse, Warning, TEXT("Waiting for GameFuseManager setup..."));
					return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("GameFuseManager setup complete"));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, UserData, this, FGuid()));
		});

		It("signs in a user", [this] {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFApiCallback SignInCallback;
				SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Sign in Response: %s"), *Response.ResponseStr);
					TestTrue("Sign in request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Sign in failed: %s"), *Response.ResponseStr));
					}
				});
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->SignIn(UserData->Username + "@gamefuse.com", "password", SignInCallback)));
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					TestTrue("user id signed in", GameFuseUser->IsSignedIn());
					return true;
				}));
				return true;
			}));
		});
	});

	Describe("GameFuseUser Store", [this]() {
		BeforeEach([this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				if (GameFuseManager->IsSetUp()) {
					UE_LOG(LogGameFuse, Warning, TEXT("Game was already Setup"));
					GameFuseManager->ClearGameData();
					return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("GameFuseManager cleanup complete"));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				if (GameFuseUser->IsSignedIn()) {
					UE_LOG(LogGameFuse, Warning, TEXT("User was already Signed in"));
					GameFuseUser->LogOut();
					return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("GameFuseUser cleanup complete"));
				return true;
			}));
			// Create and setup game
			ADD_LATENT_AUTOMATION_COMMAND(FSetupGame(TestAPIHandler, GameData, GameFuseManager, this, FGuid()));


			// Wait for GameFuseManager to be fully set up
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				if (!GameFuseManager->IsSetUp()) {
					UE_LOG(LogGameFuse, Warning, TEXT("Waiting for GameFuseManager setup..."));
					return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("GameFuseManager setup complete"));
				return true;
			}));

			// Create and sign in user

			ADD_LATENT_AUTOMATION_COMMAND(FSetupUser(TestAPIHandler, GameData, UserData, GameFuseUser, this));

			// Wait for user to be fully signed in
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
					UE_LOG(LogGameFuse, Warning, TEXT("Waiting for user signin..."));
					return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("User signed in successfully"));
				return true;
			}));
		});

		It("adds credits to user", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFApiCallback AddCreditsCallback;
				AddCreditsCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Add credits Response: %s"), *Response.ResponseStr);
					TestTrue("Add credits request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Add credits failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->AddCredits(100, AddCreditsCallback)));
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					TestTrue("credits are updated", GameFuseUser->GetCredits() == 100);
					return true;
				}));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
		});

		It("sets credits for user", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFApiCallback SetCreditsCallback;
				SetCreditsCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Set credits Response: %s"), *Response.ResponseStr);
					TestTrue("Set credits request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Set credits failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->SetCredits(200, SetCreditsCallback)));
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					TestTrue("credits are updated", GameFuseUser->GetCredits() == 200);
					return true;
				}));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
		});

		It("creates and purchases a store item", [this]() {
			// Create store item
			TSharedPtr<FGFStoreItem> TestStoreItem = MakeShared<FGFStoreItem>();
			TestStoreItem->Name = TEXT("Test Item");
			TestStoreItem->Description = TEXT("A test store item");
			TestStoreItem->Cost = 100;
			TestStoreItem->Category = TEXT("test");

			ADD_LATENT_AUTOMATION_COMMAND(FCreateStoreItem(TestAPIHandler, GameData, TestStoreItem, this, FGuid()));

			// Add credits to purchase item

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
				FGFApiCallback AddCreditsCallback;
				AddCreditsCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("BuyStoreItem 1 :: Add Credits");
					UE_LOG(LogGameFuse, Log, TEXT("Add credits Response: %s"), *Response.ResponseStr);
					TestTrue("Add credits request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Add credits failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->AddCredits(200, AddCreditsCallback)));

				// Purchase store item using item struct
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
					FGFApiCallback PurchaseCallback;
					PurchaseCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("BuyStoreItem 2 :: Purchase Store Item");
						TestTrue("Purchase store item request succeeded", Response.bSuccess);
						if (!Response.bSuccess) {
							AddError(FString::Printf(TEXT("Purchase store item failed: %s"), *Response.ResponseStr));
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->PurchaseStoreItem(*TestStoreItem, PurchaseCallback)));

					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
						FGFApiCallback FetchStoreItemsCallback;
						FetchStoreItemsCallback.AddLambda([this](const FGFAPIResponse& Response) {
							AddInfo("BuyStoreItem 3 :: Get Purchased Store Items");
							TestTrue("Get store item request succeeded", Response.bSuccess);
							if (!Response.bSuccess) {
								AddError(FString::Printf(TEXT("Get store item failed: %s"), *Response.ResponseStr));
							}
						});
						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->FetchPurchasedStoreItems(FetchStoreItemsCallback)));

						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
							AddInfo("BuyStoreItem 4 :: Test Local Store Items");
							AddErrorIfFalse(GameFuseUser->GetPurchasedStoreItems().Num() == 1, "User should have 1 purchased item");
							TestTrue("fetches the purchased item", GameFuseUser->GetPurchasedStoreItems().Num() == 1);

							// test returned data
							FGFStoreItem& InternalItemData = GameFuseUser->GetPurchasedStoreItems()[0];
							TestTrue("has good internal Id", InternalItemData.Id > 0);
							TestTrue("matches internal Name ", InternalItemData.Name == TestStoreItem->Name);
							TestTrue("matches internal Description ", InternalItemData.Description == TestStoreItem->Description);
							TestTrue("matches internal Cost ", InternalItemData.Cost == TestStoreItem->Cost);
							TestTrue("matches internal Category ", InternalItemData.Category == TestStoreItem->Category);
							ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));

							return true;
						}));
						return true;
					}));
					return true;
				}));
				return true;
			}));
		});

		It("purchases and removes store items using ID", [this]() {
			// Create store item
			TSharedPtr<FGFStoreItem> TestStoreItem = MakeShared<FGFStoreItem>();
			TestStoreItem->Name = TEXT("Test Item 2");
			TestStoreItem->Description = TEXT("Another test store item");
			TestStoreItem->Cost = 150;
			TestStoreItem->Category = TEXT("test2");


			ADD_LATENT_AUTOMATION_COMMAND(FCreateStoreItem(TestAPIHandler, GameData, TestStoreItem, this, FGuid()));


			// Add credits to purchase item
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
				FGFApiCallback AddCreditsCallback;
				AddCreditsCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("RemoveStoreItem 1 :: Add Credits");
					TestTrue("Add credits request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Add credits failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->AddCredits(200, AddCreditsCallback)));

				// Purchase store item
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
					FGFApiCallback PurchaseCallback;
					PurchaseCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("RemoveStoreItem 2 :: Purchase Store Item");
						TestTrue("Purchase store item request succeeded", Response.bSuccess);
						if (!Response.bSuccess) {
							AddError(FString::Printf(TEXT("Purchase store item failed: %s"), *Response.ResponseStr));
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->PurchaseStoreItemWithId(TestStoreItem->Id, PurchaseCallback)));

					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
						FGFApiCallback RemoveCallback;
						RemoveCallback.AddLambda([this](const FGFAPIResponse& Response) {
							AddInfo("RemoveStoreItem 3 :: Remove Store Item");
							TestTrue("Remove store item request succeeded", Response.bSuccess);
							if (!Response.bSuccess) {
								AddError(FString::Printf(TEXT("Remove store item failed: %s"), *Response.ResponseStr));
							}
						});
						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->RemoveStoreItemWithId(TestStoreItem->Id, RemoveCallback)));

						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
							TestTrue("purchased item was removed", GameFuseUser->GetPurchasedStoreItems().Num() == 0);
							FGFApiCallback FetchStoreItemsCallback;
							FetchStoreItemsCallback.AddLambda([this](const FGFAPIResponse& Response) {
								AddInfo("RemoveStoreItem 4 :: Get Purchased Items");
								TestTrue("Get store item request succeeded", Response.bSuccess);
								if (!Response.bSuccess) {
									AddError(FString::Printf(TEXT("Get store item failed: %s"), *Response.ResponseStr));
								}
							});
							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->FetchPurchasedStoreItems(FetchStoreItemsCallback)));

							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
								AddInfo("RemoveStoreItem 5 :: Test Remaining Items");
								TestTrue("has removed purchased from local and server", GameFuseUser->GetPurchasedStoreItems().Num() == 0);
								return true;
							}));
							ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
							return true;
						}));

						return true;
					}));
					return true;
				}));
				return true;
			}));

			// // Purchase store item using item ID
			// ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
			//
			//
			// 	ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->PurchaseStoreItemWithId(TestStoreItem->Id, PurchaseCallback)));
			// 	return true;
			// }));

			// Remove store item using item ID
		});
	});
}

#endif