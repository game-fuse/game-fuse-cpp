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
TSharedPtr<FGFUserData> UserData2;
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
	UserData2 = MakeShared<FGFUserData>();
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
					if (!bSuccess) {
						AddErrorIfFalse(bSuccess, TEXT("Sign in request failed"));
						return;
					}
					TestTrue("User data is valid", UserData.Id > 0);
					TestEqual("Username matches", UserData.Username, UserData.Username);
					TestTrue("User is signed in", GameFuseUser->IsSignedIn());
					TestEqual("Internal last fetched user data matches", GameFuseUser->GetLastFetchedUserData().Id, UserData.Id);
					TestEqual("Internal current user data matches", GameFuseUser->GetCurrentUserData().Id, UserData.Id);
					TestEqual("Internal username matches", GameFuseUser->GetUsername(), UserData.Username);
					TestTrue("Authentication token is valid", !GameFuseUser->GetAuthenticationToken().IsEmpty());
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
					AddErrorIfFalse(bSuccess, TEXT("Add credits request failed"));
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
					AddErrorIfFalse(bSuccess, TEXT("Set credits request failed"));
					TestTrue("Set credits request succeeded", bSuccess);
					if (bSuccess) {
						TestEqual("Credits were set", UserData.Credits, 200);
						TestEqual("Internal credits match", GameFuseUser->GetCredits(), 200);
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->SetCredits(200, SetCreditsCallback)));
				ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
				return true;
			}));
		});

		It("creates and purchases a store item", [this]() {
			// Create store item with validation
			TSharedPtr<FGFStoreItem> TestStoreItem = MakeShared<FGFStoreItem>();
			TestStoreItem->Name = TEXT("Test Item");
			TestStoreItem->Description = TEXT("A test store item");
			TestStoreItem->Cost = 100;
			TestStoreItem->Category = TEXT("test");

			ADD_LATENT_AUTOMATION_COMMAND(FCreateStoreItem(TestAPIHandler, GameData, TestStoreItem, this, FGuid()));

			// Add credits and purchase item with proper validation
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
				FGFUserDataCallback AddCreditsCallback;
				AddCreditsCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
					AddInfo("BuyStoreItem 1 :: Add Credits");
					AddErrorIfFalse(bSuccess, "Add credits request failed");
					if (!bSuccess) {
						TestFalse("Add credits failed unexpectedly", true);
						return;
					}
					TestEqual("Credits were added", UserData.Credits, 200);
					TestTrue("User data is valid after credits update", UserData.Id > 0);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddCredits(200, AddCreditsCallback)));

				// Purchase store item
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
					FGFStoreItemsCallback PurchaseCallback;
					PurchaseCallback.BindLambda([this](bool bSuccess, const TArray<FGFStoreItem>& StoreItems) {
						AddInfo("BuyStoreItem 2 :: Purchase Store Item");
						AddErrorIfFalse(bSuccess, TEXT("Purchase store item request failed"));
						if (!bSuccess) {
							TestFalse("Purchase store item failed unexpectedly", true);
							return;
						}
						TestTrue("Purchase store item request succeeded", bSuccess);
						TestTrue("At least one store item returned", StoreItems.Num() > 0);
						if (StoreItems.Num() > 0) {
							const FGFStoreItem& StoreItem = StoreItems[0];
							TestTrue("Store item ID is valid", StoreItem.Id > 0);
							TestEqual("Store item cost matches", StoreItem.Cost, 100);
							TestEqual("Store item name matches", StoreItem.Name, TEXT("Test Item"));
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->PurchaseStoreItem(TestStoreItem->Id, PurchaseCallback)));

					// Verify purchased items
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFStoreItemsCallback FetchCallback;
						FetchCallback.BindLambda([this](bool bSuccess, const TArray<FGFStoreItem>& StoreItems) {
							AddInfo("BuyStoreItem 3 :: Verify Purchased Items");
							AddErrorIfFalse(bSuccess, TEXT("Fetch purchased items request failed"));
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
																		  GameFuseUser->FetchMyPurchasedStoreItems(FetchCallback)));
						ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
						return true;
					}));
					return true;
				}));
				return true;
			}));
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
					AddErrorIfFalse(bSuccess, "Set attribute request failed");
					if (!bSuccess) {
						TestFalse("Set attribute failed unexpectedly", true);
						return;
					}
					TestTrue("Set attribute request succeeded", bSuccess);
					TestTrue("Attributes array is valid", Attributes.Attributes.Num() > 0);
					if (Attributes.Attributes.Num() > 0) {
						TestEqual("Should have one attribute", Attributes.Attributes.Num(), 1);
						const FString* Value = Attributes.Attributes.Find("test_key");
						TestNotNull("Attribute value should exist", Value);
						if (Value) {
							TestEqual("Attribute value should match", *Value, "test_value");
						}
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
						if (!bSuccess) {
							TestFalse("Set batch attributes failed unexpectedly", true);
							return;
						}
						TestTrue("Set batch attributes request succeeded", bSuccess);

						TestEqual("Should have three attributes total", Attributes.Attributes.Num(), 3);
						TestEqual("First batch attribute should match", Attributes.Attributes["batch_key1"], "batch_value1");
						TestEqual("Second batch attribute should match", Attributes.Attributes["batch_key2"], "batch_value2");
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->SetAttributes(BatchAttributes, BatchSetCallback)));

					// Verify attributes
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFAttributesCallback FetchCallback;
						FetchCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
							AddInfo("SetAttribute 3 :: Verify All Attributes");
							if (!bSuccess) {
								AddError("Fetch attributes request failed");
								return;
							}
							TestTrue("Fetch attributes request succeeded", bSuccess);

							TestEqual("Should have three attributes", Attributes.Attributes.Num(), 3);
							TestEqual("Original attribute should exist", Attributes.Attributes["test_key"], "test_value");
							TestEqual("First batch attribute should exist", Attributes.Attributes["batch_key1"], "batch_value1");
							TestEqual("Second batch attribute should exist", Attributes.Attributes["batch_key2"], "batch_value2");
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->FetchMyAttributes(FetchCallback)));
						ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
						return true;
					}));
					return true;
				}));
				return true;
			}));
		});

		It("batch updates attributes", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// Create test attributes map
				TMap<FString, FString> TestAttributes;
				TestAttributes.Add("test_key1", "test_value1");
				TestAttributes.Add("test_key2", "test_value2");
				TestAttributes.Add("test_key3", "test_value3");

				FGFAttributesCallback SetAttributesCallback;
				SetAttributesCallback.BindLambda([this, TestAttributes](bool bSuccess, const FGFAttributeList& Attributes) {
					AddInfo("BatchAttributes 1 :: Set Attributes");
					AddErrorIfFalse(bSuccess, "Set attributes request failed");
					TestTrue("Set attributes request succeeded", bSuccess);
					if (bSuccess) {
						TestEqual("Should have three attributes", Attributes.Attributes.Num(), 3);
						const FString* Value1 = Attributes.Attributes.Find("test_key1");
						const FString* Value2 = Attributes.Attributes.Find("test_key2");
						const FString* Value3 = Attributes.Attributes.Find("test_key3");

						TestNotNull("First attribute should exist", Value1);
						TestNotNull("Second attribute should exist", Value2);
						TestNotNull("Third attribute should exist", Value3);

						if (Value1 && Value2 && Value3) {
							TestEqual("First attribute should match", *Value1, "test_value1");
							TestEqual("Second attribute should match", *Value2, "test_value2");
							TestEqual("Third attribute should match", *Value3, "test_value3");
						}
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->SetAttributes(TestAttributes, SetAttributesCallback)));

				// Verify attributes
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFAttributesCallback FetchCallback;
					FetchCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
						AddInfo("BatchAttributes 2 :: Verify Attributes");
						if (!bSuccess) {
							AddErrorIfFalse(bSuccess, "Fetch attributes request failed");
							return;
						}
						TestTrue("Fetch attributes request succeeded", bSuccess);
						TestEqual("Should have three attributes", Attributes.Attributes.Num(), 3);
						const FString* Value1 = Attributes.Attributes.Find("test_key1");
						const FString* Value2 = Attributes.Attributes.Find("test_key2");
						const FString* Value3 = Attributes.Attributes.Find("test_key3");

						TestNotNull("First attribute should exist", Value1);
						TestNotNull("Second attribute should exist", Value2);
						TestNotNull("Third attribute should exist", Value3);

						if (Value1 && Value2 && Value3) {
							TestEqual("First attribute should match", *Value1, "test_value1");
							TestEqual("Second attribute should match", *Value2, "test_value2");
							TestEqual("Third attribute should match", *Value3, "test_value3");
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchMyAttributes(FetchCallback)));
					ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
					return true;
				}));
				return true;
			}));
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
					if (!bSuccess) {
						TestFalse("Set attributes request failed", true);
						return;
					}
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
						if (!bSuccess) {
							AddErrorIfFalse(bSuccess, "Remove attribute request failed");
							return;
						}
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
							if (!bSuccess) {
								AddErrorIfFalse(bSuccess, "Fetch attributes request failed");
								return;
							}
							TestEqual("Should have one attribute", Attributes.Attributes.Num(), 1);
							TestEqual("Remaining attribute should match", Attributes.Attributes["test_key2"], "test_value2");
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->FetchMyAttributes(FetchCallback)));
						ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
						return true;
					}));
					return true;
				}));
				return true;
			}));
		});

		It("removes attributes in bulk", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// First set some attributes
				TMap<FString, FString> TestAttributes;
				TestAttributes.Add("test_key1", "test_value1");
				TestAttributes.Add("test_key2", "test_value2");
				TestAttributes.Add("test_key3", "test_value3");

				FGFAttributesCallback SetAttributesCallback;
				SetAttributesCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
					AddInfo("RemoveAttributesBulk 1 :: Set Initial Attributes");
					if (!bSuccess) {
						TestFalse("Set attributes request failed", true);
						return;
					}
					TestEqual("Should have three attributes", Attributes.Attributes.Num(), 3);
					TestEqual("First attribute should match", Attributes.Attributes["test_key1"], "test_value1");
					TestEqual("Second attribute should match", Attributes.Attributes["test_key2"], "test_value2");
					TestEqual("Third attribute should match", Attributes.Attributes["test_key3"], "test_value3");
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
															  GameFuseUser->SetAttributes(TestAttributes, SetAttributesCallback)));

				// Remove two attributes
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					TArray<FString> KeysToRemove;
					KeysToRemove.Add("test_key1");
					KeysToRemove.Add("test_key3");

					FGFAttributesCallback RemoveCallback;
					RemoveCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
						AddInfo("RemoveAttributesBulk 2 :: Remove Attributes");
						if (!bSuccess) {
							AddErrorIfFalse(bSuccess, "Remove attributes request failed");
							return;
						}
						TestEqual("Should have one attribute remaining", Attributes.Attributes.Num(), 1);
						TestEqual("Remaining attribute should match", Attributes.Attributes["test_key2"], "test_value2");
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
															  GameFuseUser->RemoveAttributes(KeysToRemove, RemoveCallback)));

					// Verify remaining attributes
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFAttributesCallback FetchCallback;
						FetchCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
							AddInfo("RemoveAttributesBulk 3 :: Verify Attributes");
							if (!bSuccess) {
								AddErrorIfFalse(bSuccess, "Fetch attributes request failed");
								return;
							}
							TestEqual("Should have one attribute", Attributes.Attributes.Num(), 1);
							TestEqual("Remaining attribute should match", Attributes.Attributes["test_key2"], "test_value2");
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
															  GameFuseUser->FetchMyAttributes(FetchCallback)));
						ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
						return true;
					}));
					return true;
				}));
				return true;
			}));
		});

		It("syncs local attributes", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// First set some local attributes
				GameFuseUser->SetAttributeLocal("local_key1", "local_value1");
				GameFuseUser->SetAttributeLocal("local_key2", "local_value2");
				GameFuseUser->SetAttributeLocal("local_key3", "local_value3");

				// Verify local attributes were set with proper null checks
				const TMap<FString, FString>& LocalAttributes = GameFuseUser->GetDirtyAttributes();
				TestEqual("Should have three local attributes", LocalAttributes.Num(), 3);
				TestEqual("Local attribute 1 should match", LocalAttributes["local_key1"], "local_value1");
				TestEqual("Local attribute 2 should match", LocalAttributes["local_key2"], "local_value2");
				TestEqual("Local attribute 3 should match", LocalAttributes["local_key3"], "local_value3");

				// Sync local attributes to server
				FGFAttributesCallback SyncCallback;
				SyncCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
					AddInfo("SyncLocal 1 :: Sync Local Attributes");
					if (!bSuccess) {
						AddErrorIfFalse(bSuccess, "Sync local attributes request failed");
						return;
					}
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
						if (!bSuccess) {
							AddErrorIfFalse(bSuccess, "Fetch attributes request failed");
							return;
						}
						TestEqual("Should have three attributes", Attributes.Attributes.Num(), 3);
						TestEqual("First attribute should match", Attributes.Attributes["local_key1"], "local_value1");
						TestEqual("Second attribute should match", Attributes.Attributes["local_key2"], "local_value2");
						TestEqual("Third attribute should match", Attributes.Attributes["local_key3"], "local_value3");
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchMyAttributes(FetchCallback)));
					ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
					return true;
				}));
				return true;
			}));
		});
	});

	Describe("GameFuseUser Multi-User Features", [this]() {
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

			// Create and sign in first user
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

			// Create second user
			ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, UserData2, this, FGuid()));
		});

		It("fetches other users attributes", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// Set attributes on primary user
				TMap<FString, FString> TestAttributes;
				TestAttributes.Add("test_key1", "test_value1");
				TestAttributes.Add("test_key2", "test_value2");

				FGFAttributesCallback SetAttributesCallback;
				SetAttributesCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
					AddInfo("FetchUserAttributes 1 :: Set Attributes");
					if (!bSuccess) {
						AddError("Set attributes request failed");
						return;
					}
					TestTrue("Set attributes request succeeded", bSuccess);
					TestTrue("Attributes should be valid", Attributes.Attributes.Num() > 0);
					if (Attributes.Attributes.Num() > 0) {
						TestEqual("Should have two attributes", Attributes.Attributes.Num(), 2);
						const FString* Value1 = Attributes.Attributes.Find("test_key1");
						const FString* Value2 = Attributes.Attributes.Find("test_key2");
						TestNotNull("First attribute should exist", Value1);
						TestNotNull("Second attribute should exist", Value2);
						if (Value1 && Value2) {
							TestEqual("First attribute value should match", *Value1, "test_value1");
							TestEqual("Second attribute value should match", *Value2, "test_value2");
						}
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->SetAttributes(TestAttributes, SetAttributesCallback)));

				// Verify attributes were set before signing in as second user
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFAttributesCallback VerifyCallback;
					VerifyCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
						AddInfo("FetchUserAttributes 2 :: Verify Attributes");
						TestTrue("Verify attributes request succeeded", bSuccess);
						if (bSuccess) {
							TestEqual("Should have two attributes", Attributes.Attributes.Num(), 2);
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchMyAttributes(VerifyCallback)));

					// Sign in as second user and fetch attributes from first user
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFUserDataCallback SignInCallback;
						SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
							AddInfo("FetchUserAttributes 3 :: Sign In Second User");
							TestTrue("Second user sign in succeeded", bSuccess);
							if (!bSuccess) {
								AddError(TEXT("Second user sign in failed"));
								return;
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

						// Fetch first users attributes
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFAttributesCallback FetchCallback;
							FetchCallback.BindLambda([this](bool bSuccess, const FGFAttributeList& Attributes) {
								AddInfo("FetchUserAttributes 4 :: Fetch First User Attributes");
								if (!bSuccess) {
									AddError("Fetch user attributes request failed");
									return;
								}
								TestTrue("Fetch user attributes request succeeded", bSuccess);
								TestTrue("Attributes should be valid", Attributes.Attributes.Num() > 0);
								if (Attributes.Attributes.Num() > 0) {
									TestEqual("Should have two attributes", Attributes.Attributes.Num(), 2);
									const FString* Value1 = Attributes.Attributes.Find("test_key1");
									const FString* Value2 = Attributes.Attributes.Find("test_key2");
									TestNotNull("First attribute should exist", Value1);
									TestNotNull("Second attribute should exist", Value2);
									if (Value1 && Value2) {
										TestEqual("First attribute value should match", *Value1, "test_value1");
										TestEqual("Second attribute value should match", *Value2, "test_value2");
									}
								}
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->FetchUserAttributes(UserData->Id, FetchCallback)));
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

		It("fetches other users leaderboard entries", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// Add leaderboard entry for first user
				FGFInternalSuccessCallback AddEntryCallback;
				AddEntryCallback.AddLambda([this](bool bSuccess) {
					AddInfo("FetchUserLeaderboard 1 :: Add Leaderboard Entry");
					TestTrue("Add leaderboard entry request succeeded", bSuccess);
					if (!bSuccess) {
						AddError(TEXT("Failed to add leaderboard entry"));
						return;
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddLeaderboardEntry("test_leaderboard", 1000, AddEntryCallback)));

				// Verify leaderboard entry was added before signing in as second user
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFLeaderboardEntriesCallback VerifyCallback;
					VerifyCallback.BindLambda([this](bool bSuccess, const TArray<FGFLeaderboardEntry>& Entries) {
						AddInfo("FetchUserLeaderboard 2 :: Verify Leaderboard Entry");
						TestTrue("Verify leaderboard entries request succeeded", bSuccess);
						if (bSuccess) {
							TestEqual("Should have one leaderboard entry", Entries.Num(), 1);
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchMyLeaderboardEntries(100, true, VerifyCallback)));

					// Sign in as second user
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFUserDataCallback SignInCallback;
						SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
							AddInfo("FetchUserLeaderboard 3 :: Sign In Second User");
							TestTrue("Second user sign in succeeded", bSuccess);
							if (!bSuccess) {
								AddError(TEXT("Second user sign in failed"));
								return;
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

						// Fetch first users leaderboard entries
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFLeaderboardEntriesCallback FetchCallback;
							FetchCallback.BindLambda([this](bool bSuccess, const TArray<FGFLeaderboardEntry>& Entries) {
								AddInfo("FetchUserLeaderboard 4 :: Fetch First User Leaderboard Entries");
								if (!bSuccess) {
									AddError("Fetch user leaderboard entries request failed");
									return;
								}
								TestTrue("Fetch user leaderboard entries request succeeded", bSuccess);
								TestEqual("Should have one leaderboard entry", Entries.Num(), 1);
								if (Entries.Num() > 0) {
									const FGFLeaderboardEntry& Entry = Entries[0];
									TestEqual("Leaderboard name matches", Entry.LeaderboardName, "test_leaderboard");
									TestEqual("Score matches", Entry.Score, 1000);
									TestEqual("User ID matches first user", Entry.GameUserId, UserData->Id);
								}
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->FetchUserLeaderboardEntries(UserData->Id, 100, true, FetchCallback)));
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

		It("fetches other users store items", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// Create store item
				TSharedPtr<FGFStoreItem> TestStoreItem = MakeShared<FGFStoreItem>();
				TestStoreItem->Name = TEXT("Test Item");
				TestStoreItem->Description = TEXT("A test store item");
				TestStoreItem->Cost = 100;
				TestStoreItem->Category = TEXT("test");

				ADD_LATENT_AUTOMATION_COMMAND(FCreateStoreItem(TestAPIHandler, GameData, TestStoreItem, this, FGuid()));

				// Add credits and purchase item for first user
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
					FGFUserDataCallback AddCreditsCallback;
					AddCreditsCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
						AddInfo("FetchUserStoreItems 1 :: Add Credits");
						TestTrue("Add credits request succeeded", bSuccess);
						if (!bSuccess) {
							AddError(TEXT("Failed to add credits"));
							return;
						}
						TestEqual("Credits were added", UserData.Credits, 200);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->AddCredits(200, AddCreditsCallback)));

					// Purchase store item
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestStoreItem]() -> bool {
						FGFStoreItemsCallback PurchaseCallback;
						PurchaseCallback.BindLambda([this](bool bSuccess, const TArray<FGFStoreItem>& StoreItems) {
							AddInfo("FetchUserStoreItems 2 :: Purchase Store Item");
							TestTrue("Purchase store item request succeeded", bSuccess);
							if (!bSuccess) {
								AddError(TEXT("Failed to purchase store item"));
								return;
							}
							TestEqual("Should have one purchased item", StoreItems.Num(), 1);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->PurchaseStoreItem(TestStoreItem->Id, PurchaseCallback)));

						// Verify purchase before signing in as second user
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFStoreItemsCallback VerifyCallback;
							VerifyCallback.BindLambda([this](bool bSuccess, const TArray<FGFStoreItem>& StoreItems) {
								AddInfo("FetchUserStoreItems 3 :: Verify Purchase");
								TestTrue("Verify purchased items request succeeded", bSuccess);
								if (bSuccess) {
									TestEqual("Should have one purchased item", StoreItems.Num(), 1);
								}
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->FetchMyPurchasedStoreItems(VerifyCallback)));

							// Sign in as second user
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
								FGFUserDataCallback SignInCallback;
								SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
									AddInfo("FetchUserStoreItems 4 :: Sign In Second User");
									TestTrue("Second user sign in succeeded", bSuccess);
									if (!bSuccess) {
										AddError(TEXT("Second user sign in failed"));
										return;
									}
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																				  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

								// Fetch first users store items
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
									FGFStoreItemsCallback FetchCallback;
									FetchCallback.BindLambda([this](bool bSuccess, const TArray<FGFStoreItem>& StoreItems) {
										AddInfo("FetchUserStoreItems 5 :: Fetch First User Store Items");
										if (!bSuccess) {
											AddError("Fetch user store items request failed");
											return;
										}
										TestTrue("Fetch user store items request succeeded", bSuccess);
										TestEqual("Should have one purchased item", StoreItems.Num(), 1);
										if (StoreItems.Num() > 0) {
											const FGFStoreItem& Item = StoreItems[0];
											TestEqual("Store item cost matches", Item.Cost, 100);
											TestEqual("Store item name matches", Item.Name, TEXT("Test Item"));
										}
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																					  GameFuseUser->FetchUserPurchasedStoreItems(UserData->Id, FetchCallback)));
									ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
									return true;
								}));
								return true;
							}));
							return true;
						}));
						return true;
					}));
					return true;
				}));
				return true;
			}));
		});

		It("fetches other users data", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// First user adds score
				FGFUserDataCallback AddScoreCallback;
				AddScoreCallback.BindLambda([this](bool bSuccess, const FGFUserData& User) {
					AddInfo("FetchUserData 1 :: Add Score for First User");
					TestTrue("Add score request succeeded for first user", bSuccess);
					if (!bSuccess) {
						AddError(TEXT("Failed to add score for first user"));
						return;
					}
					TestEqual("Score was added correctly for first user", User.Score, 1000);
					TestEqual("User ID matches first user", User.Id, UserData->Id);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddScore(1000, AddScoreCallback)));

				// Verify score was added before signing in as second user
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFUserDataCallback VerifyCallback;
					VerifyCallback.BindLambda([this](bool bSuccess, const FGFUserData& User) {
						AddInfo("FetchUserData 2 :: Verify Score for First User");
						TestTrue("Verify score request succeeded for first user", bSuccess);
						if (bSuccess) {
							TestEqual("Score should be 1000 for first user", User.Score, 1000);
						}
					});
					// Temporarily fetch current user to check score.
					// Note: This will be UserData (first user) as they are still signed in.
					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchUser(UserData->Id, VerifyCallback)));


					// Sign in as second user
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFUserDataCallback SignInCallback;
						SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& SignedInUser) {
							AddInfo("FetchUserData 3 :: Sign In Second User");
							TestTrue("Second user sign in succeeded", bSuccess);
							if (!bSuccess) {
								AddError(TEXT("Second user sign in failed"));
								return;
							}
							TestEqual("Signed in user ID matches second user", SignedInUser.Id, UserData2->Id);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

						// Fetch first user's data
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFUserDataCallback FetchCallback;
							FetchCallback.BindLambda([this](bool bSuccess, const FGFUserData& FetchedUser) {
								AddInfo("FetchUserData 4 :: Fetch First User Data");
								if (!bSuccess) {
									AddError("Fetch user data request failed");
									return;
								}
								TestTrue("Fetch user data request succeeded", bSuccess);
								TestEqual("Fetched User ID matches first user", FetchedUser.Id, UserData->Id);
								TestEqual("Fetched Username matches first user", FetchedUser.Username, UserData->Username);
								TestEqual("Fetched Score matches first user's score", FetchedUser.Score, 1000);
								
								// Verify that the last fetched user data contains the first user's data
								// while current user data still contains the second user's data
								TestEqual("Last fetched user data should contain first user", GameFuseUser->GetLastFetchedUserData().Id, UserData->Id);
								TestEqual("Current user data should still contain second user", GameFuseUser->GetCurrentUserData().Id, UserData2->Id);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->FetchUser(UserData->Id, FetchCallback)));
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

		It("maintains current user data when fetching other users", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// First user adds some data
				FGFUserDataCallback AddScoreCallback;
				AddScoreCallback.BindLambda([this](bool bSuccess, const FGFUserData& User) {
					AddInfo("CurrentUserDataTest 1 :: Add Score for First User");
					TestTrue("Add score request succeeded for first user", bSuccess);
					if (!bSuccess) {
						AddError(TEXT("Failed to add score for first user"));
						return;
					}
					TestEqual("Score was added correctly for first user", User.Score, 500);
					TestEqual("User ID matches first user", User.Id, UserData->Id);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddScore(500, AddScoreCallback)));

				// Verify current user data contains first user's data
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					TestEqual("Current user data should contain first user ID", GameFuseUser->GetCurrentUserData().Id, UserData->Id);
					TestEqual("Current user data should contain first user score", GameFuseUser->GetCurrentUserData().Score, 500);
					TestEqual("Last fetched user data should also contain first user ID", GameFuseUser->GetLastFetchedUserData().Id, UserData->Id);
					TestEqual("Last fetched user data should also contain first user score", GameFuseUser->GetLastFetchedUserData().Score, 500);

					// Sign in as second user
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFUserDataCallback SignInCallback;
						SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& SignedInUser) {
							AddInfo("CurrentUserDataTest 2 :: Sign In Second User");
							TestTrue("Second user sign in succeeded", bSuccess);
							if (!bSuccess) {
								AddError(TEXT("Second user sign in failed"));
								return;
							}
							TestEqual("Signed in user ID matches second user", SignedInUser.Id, UserData2->Id);
							
							// Verify current user data now contains second user's data
							TestEqual("Current user data should now contain second user ID", GameFuseUser->GetCurrentUserData().Id, UserData2->Id);
							TestEqual("Last fetched user data should also contain second user ID", GameFuseUser->GetLastFetchedUserData().Id, UserData2->Id);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

						// Fetch first user's data
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFUserDataCallback FetchCallback;
							FetchCallback.BindLambda([this](bool bSuccess, const FGFUserData& FetchedUser) {
								AddInfo("CurrentUserDataTest 3 :: Fetch First User Data");
								if (!bSuccess) {
									AddError("Fetch user data request failed");
									return;
								}
								TestTrue("Fetch user data request succeeded", bSuccess);
								TestEqual("Fetched User ID matches first user", FetchedUser.Id, UserData->Id);
								TestEqual("Fetched Score matches first user's score", FetchedUser.Score, 500);
								
								// Verify that the last fetched user data now contains the first user's data
								// while current user data still contains the second user's data
								TestEqual("Last fetched user data should contain first user", GameFuseUser->GetLastFetchedUserData().Id, UserData->Id);
								TestEqual("Last fetched user data should contain first user score", GameFuseUser->GetLastFetchedUserData().Score, 500);
								TestEqual("Current user data should still contain second user", GameFuseUser->GetCurrentUserData().Id, UserData2->Id);
								
								// Verify that current user data is not affected by the fetch operation
								TestNotEqual("Current user data should not be affected by fetch", GameFuseUser->GetCurrentUserData().Id, UserData->Id);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->FetchUser(UserData->Id, FetchCallback)));
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
	});
}

#endif