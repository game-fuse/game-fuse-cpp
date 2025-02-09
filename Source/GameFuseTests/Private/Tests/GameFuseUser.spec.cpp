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
				FGFUserDataCallback SignInCallback;
				SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
					AddInfo("SignIn :: Verify Response");
					TestTrue("User data is valid", UserData.Id > 0);
					TestEqual("Username matches", UserData.Username, UserData.Username);

					TestTrue("User is signed in", GameFuseUser->IsSignedIn());
					TestEqual("Internal user data matches", GameFuseUser->GetUserData().Id, UserData.Id);
					TestEqual("Internal username matches", GameFuseUser->GetUsername(), UserData.Username);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->SignIn(UserData->Username + "@gamefuse.com", "password", SignInCallback)));

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
				FGFUserDataCallback AddCreditsCallback;
				AddCreditsCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
					AddInfo("AddCredits 1 :: Verify Credits Added");
					TestTrue("Add credits request succeeded", bSuccess);
					if (bSuccess) {
						TestEqual("Credits were updated", UserData.Credits, 100);
						TestEqual("Internal credits match", GameFuseUser->GetCredits(), 100);
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddCredits(100, AddCreditsCallback)));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
		});

		It("sets credits for user", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFUserDataCallback SetCreditsCallback;
				SetCreditsCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
					AddInfo("SetCredits 1 :: Verify Credits Set");
					TestTrue("Set credits request succeeded", bSuccess);
					if (bSuccess) {
						TestEqual("Credits were set", UserData.Credits, 200);
						TestEqual("Internal credits match", GameFuseUser->GetCredits(), 200);
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->SetCredits(200, SetCreditsCallback)));
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

			// Add credits and purchase item
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
				FGFUserDataCallback AddCreditsCallback;
				AddCreditsCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
					AddInfo("BuyStoreItem 1 :: Add Credits");
					TestEqual("Credits were added", UserData.Credits, 200);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddCredits(200, AddCreditsCallback)));

				// Purchase store item
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
					FGFStoreItemsCallback PurchaseCallback;
					PurchaseCallback.BindLambda([this](bool bSuccess, const TArray<FGFStoreItem>& StoreItems) {
						AddInfo("BuyStoreItem 2 :: Purchase Store Item");
						TestTrue("Purchase store item request succeeded", bSuccess);
						if (bSuccess) {
							TestTrue("At least one store item returned", StoreItems.Num() > 0);
							if (StoreItems.Num() > 0) {
								const FGFStoreItem& StoreItem = StoreItems[0];
								TestTrue("Store item ID is valid", StoreItem.Id > 0);
								TestEqual("Store item cost matches", StoreItem.Cost, 100);
							}
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->PurchaseStoreItem(TestStoreItem->Id, PurchaseCallback)));

					// Verify purchased items
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFStoreItemsCallback FetchCallback;
						FetchCallback.BindLambda([this](bool bSuccess, const TArray<FGFStoreItem>& StoreItems) {
							AddInfo("BuyStoreItem 3 :: Verify Purchased Items");
							TestTrue("Fetch purchased items request succeeded", bSuccess);
							if (bSuccess) {
								TestEqual("Should have one purchased item", StoreItems.Num(), 1);
								if (StoreItems.Num() == 1) {
									const FGFStoreItem& Item = StoreItems[0];
									TestEqual("Store item cost matches", Item.Cost, 100);
									TestEqual("Store item name matches", Item.Name, TEXT("Test Item"));
								}
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->FetchPurchasedStoreItems(FetchCallback)));
						return true;
					}));
					return true;
				}));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
		});

		It("purchases and removes store items using ID", [this]() {
			// Create store item
			TSharedPtr<FGFStoreItem> TestStoreItem = MakeShared<FGFStoreItem>();
			TestStoreItem->Name = TEXT("Test Item 2");
			TestStoreItem->Description = TEXT("Another test store item");
			TestStoreItem->Cost = 150;
			TestStoreItem->Category = TEXT("test2");

			ADD_LATENT_AUTOMATION_COMMAND(FCreateStoreItem(TestAPIHandler, GameData, TestStoreItem, this, FGuid()));

			// Add credits and purchase item
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
				FGFUserDataCallback AddCreditsCallback;
				AddCreditsCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
					AddInfo("RemoveStoreItem 1 :: Add Credits");
					TestEqual("Credits were added", UserData.Credits, 200);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddCredits(200, AddCreditsCallback)));

				// Purchase and remove store item
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
					FGFStoreItemsCallback PurchaseCallback;
					PurchaseCallback.BindLambda([this](bool bSuccess, const TArray<FGFStoreItem>& StoreItems) {
						AddInfo("RemoveStoreItem 2 :: Purchase Store Item");
						TestTrue("At least one store item returned", StoreItems.Num() > 0);
						if (StoreItems.Num() > 0) {
							const FGFStoreItem& StoreItem = StoreItems[0];
							TestTrue("Store item ID is valid", StoreItem.Id > 0);
							TestEqual("Store item cost matches", StoreItem.Cost, 150);
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->PurchaseStoreItem(TestStoreItem->Id, PurchaseCallback)));

					// Remove store item
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
						FGFStoreItemsCallback RemoveCallback;
						RemoveCallback.BindLambda([this](bool bSuccess, const TArray<FGFStoreItem>& StoreItems) {
							AddInfo("RemoveStoreItem 3 :: Remove Store Item");
							TestEqual("Should have no store items", StoreItems.Num(), 0);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->RemoveStoreItem(TestStoreItem->Id, RemoveCallback)));
						return true;
					}));
					return true;
				}));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
		});
	});

	Describe("GameFuseUser Attributes", [this]() {
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

		It("sets and fetches attributes", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFAttributesCallback SetAttributeCallback;
				SetAttributeCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
					AddInfo("SetAttribute 1 :: Set Single Attribute");
					TestTrue("Set attribute request succeeded", bSuccess);
					if (bSuccess) {
						TestEqual("Should have one attribute", Attributes.Attributes.Num(), 1);
						TestEqual("Attribute value should match", Attributes.Attributes["test_key"], "test_value");
					}
				});

				// Set single attribute
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->SetAttribute("test_key", "test_value", SetAttributeCallback)));

				// Set batch attributes
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					TMap<FString, FString> BatchAttributes;
					BatchAttributes.Add("batch_key1", "batch_value1");
					BatchAttributes.Add("batch_key2", "batch_value2");

					FGFAttributesCallback BatchSetCallback;
					BatchSetCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
						AddInfo("SetAttribute 2 :: Set Batch Attributes");
						TestTrue("Set batch attributes request succeeded", bSuccess);
						if (bSuccess) {
							TestEqual("Should have three attributes total", Attributes.Attributes.Num(), 3);
							TestEqual("First batch attribute should match", Attributes.Attributes["batch_key1"], "batch_value1");
							TestEqual("Second batch attribute should match", Attributes.Attributes["batch_key2"], "batch_value2");
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->SetAttributes(BatchAttributes, BatchSetCallback)));

					// Verify attributes
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFAttributesCallback FetchCallback;
						FetchCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
							AddInfo("SetAttribute 3 :: Verify All Attributes");
							TestTrue("Fetch attributes request succeeded", bSuccess);
							if (bSuccess) {
								TestEqual("Should have three attributes", Attributes.Attributes.Num(), 3);
								TestEqual("Original attribute should exist", Attributes.Attributes["test_key"], "test_value");
								TestEqual("First batch attribute should exist", Attributes.Attributes["batch_key1"], "batch_value1");
								TestEqual("Second batch attribute should exist", Attributes.Attributes["batch_key2"], "batch_value2");
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->FetchAttributes(FetchCallback)));
						return true;
					}));
					return true;
				}));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
		});

		It("batch updates attributes", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// Create test attributes map
				TMap<FString, FString> TestAttributes;
				TestAttributes.Add("test_key1", "test_value1");
				TestAttributes.Add("test_key2", "test_value2");
				TestAttributes.Add("test_key3", "test_value3");

				FGFAttributesCallback SetAttributesCallback;
				SetAttributesCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
					AddInfo("BatchAttributes 1 :: Set Attributes");
					TestEqual("Should have three attributes", Attributes.Attributes.Num(), 3);
					TestEqual("First attribute should match", Attributes.Attributes["test_key1"], "test_value1");
					TestEqual("Second attribute should match", Attributes.Attributes["test_key2"], "test_value2");
					TestEqual("Third attribute should match", Attributes.Attributes["test_key3"], "test_value3");
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->SetAttributes(TestAttributes, SetAttributesCallback)));

				// Verify attributes
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFAttributesCallback FetchCallback;
					FetchCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
						AddInfo("BatchAttributes 2 :: Verify Attributes");
						TestEqual("Should have three attributes", Attributes.Attributes.Num(), 3);
						TestEqual("First attribute should exist", Attributes.Attributes["test_key1"], "test_value1");
						TestEqual("Second attribute should exist", Attributes.Attributes["test_key2"], "test_value2");
						TestEqual("Third attribute should exist", Attributes.Attributes["test_key3"], "test_value3");
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchAttributes(FetchCallback)));
					return true;
				}));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
		});

		It("removes attributes", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// First set some attributes
				TMap<FString, FString> TestAttributes;
				TestAttributes.Add("test_key1", "test_value1");
				TestAttributes.Add("test_key2", "test_value2");

				FGFAttributesCallback SetAttributesCallback;
				SetAttributesCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
					AddInfo("RemoveAttributes 1 :: Set Initial Attributes");
					TestEqual("Should have two attributes", Attributes.Attributes.Num(), 2);
					TestEqual("First attribute should match", Attributes.Attributes["test_key1"], "test_value1");
					TestEqual("Second attribute should match", Attributes.Attributes["test_key2"], "test_value2");
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->SetAttributes(TestAttributes, SetAttributesCallback)));

				// Remove one attribute
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFAttributesCallback RemoveCallback;
					RemoveCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
						AddInfo("RemoveAttributes 2 :: Remove Attribute");
						TestEqual("Should have one attribute remaining", Attributes.Attributes.Num(), 1);
						TestEqual("Remaining attribute should match", Attributes.Attributes["test_key2"], "test_value2");
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->RemoveAttribute("test_key1", RemoveCallback)));

					// Verify remaining attributes
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFAttributesCallback FetchCallback;
						FetchCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
							AddInfo("RemoveAttributes 3 :: Verify Attributes");
							TestEqual("Should have one attribute", Attributes.Attributes.Num(), 1);
							TestEqual("Remaining attribute should match", Attributes.Attributes["test_key2"], "test_value2");
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->FetchAttributes(FetchCallback)));
						return true;
					}));
					return true;
				}));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
		});

		It("syncs local attributes", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// First set some local attributes
				GameFuseUser->SetAttributeLocal("local_key1", "local_value1");
				GameFuseUser->SetAttributeLocal("local_key2", "local_value2");
				GameFuseUser->SetAttributeLocal("local_key3", "local_value3");

				// Verify local attributes were set
				const TMap<FString, FString>& LocalAttributes = GameFuseUser->GetDirtyAttributes();
				TestEqual("Should have three local attributes", LocalAttributes.Num(), 3);
				TestEqual("Local attribute 1 should match", LocalAttributes["local_key1"], "local_value1");
				TestEqual("Local attribute 2 should match", LocalAttributes["local_key2"], "local_value2");
				TestEqual("Local attribute 3 should match", LocalAttributes["local_key3"], "local_value3");

				// Sync local attributes to server
				FGFAttributesCallback SyncCallback;
				SyncCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
					AddInfo("SyncLocal 1 :: Sync Local Attributes");
					TestEqual("Should have three attributes", Attributes.Attributes.Num(), 3);
					TestEqual("First attribute should match", Attributes.Attributes["local_key1"], "local_value1");
					TestEqual("Second attribute should match", Attributes.Attributes["local_key2"], "local_value2");
					TestEqual("Third attribute should match", Attributes.Attributes["local_key3"], "local_value3");
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->SyncLocalAttributes(SyncCallback)));

				// Verify synced attributes
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFAttributesCallback FetchCallback;
					FetchCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
						AddInfo("SyncLocal 2 :: Verify Synced Attributes");
						TestEqual("Should have three attributes", Attributes.Attributes.Num(), 3);
						TestEqual("First attribute should match", Attributes.Attributes["local_key1"], "local_value1");
						TestEqual("Second attribute should match", Attributes.Attributes["local_key2"], "local_value2");
						TestEqual("Third attribute should match", Attributes.Attributes["local_key3"], "local_value3");
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchAttributes(FetchCallback)));
					return true;
				}));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
		});
	});
}

#endif