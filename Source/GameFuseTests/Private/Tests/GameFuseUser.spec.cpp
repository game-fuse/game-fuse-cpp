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
				if (!GameFuseUser->IsSignedIn()) {
					UE_LOG(LogGameFuse, Warning, TEXT("User was not signed in"));
					return false; // Keep waiting
				}
				return true;
			}));
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFApiCallback SetAttributeCallback;
				SetAttributeCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Set attribute Response: %s"), *Response.ResponseStr);
					TestTrue("Set attribute request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Set attribute failed: %s"), *Response.ResponseStr));
					}
				});

				// Test setting a single attribute
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->SetAttribute("test_key", "test_value", SetAttributeCallback)));

				// Test setting multiple attributes in batch
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					TMap<FString, FString> BatchAttributes;
					BatchAttributes.Add("batch_key1", "batch_value1");
					BatchAttributes.Add("batch_key2", "batch_value2");

					FGFApiCallback BatchSetCallback;
					BatchSetCallback.AddLambda([this](const FGFAPIResponse& Response) {
						TestTrue("Batch set attributes request succeeded", Response.bSuccess);
						if (!Response.bSuccess) {
							AddError(FString::Printf(TEXT("Batch set attributes failed: %s"), *Response.ResponseStr));
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->SetAttribute("batch_key1", "batch_value1", BatchSetCallback)));

					// Fetch attributes to verify
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFApiCallback FetchAttributesCallback;
						FetchAttributesCallback.AddLambda([this](const FGFAPIResponse& Response) {
							TestTrue("Fetch attributes request succeeded", Response.bSuccess);
							if (!Response.bSuccess) {
								AddError(FString::Printf(TEXT("Fetch attributes failed: %s"), *Response.ResponseStr));
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->FetchAttributes(FetchAttributesCallback)));

						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							// Verify all attributes were set correctly
							TestTrue("single attribute was set", GameFuseUser->GetAttributeValue("test_key") == "test_value");
							TestTrue("batch attribute 1 was set", GameFuseUser->GetAttributeValue("batch_key1") == "batch_value1");
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

		It("batch updates attributes", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// Create test attributes map
				TMap<FString, FString> TestAttributes;
				TestAttributes.Add("test_key1", "test_value1");
				TestAttributes.Add("test_key2", "test_value2");
				TestAttributes.Add("test_key3", "test_value3");

				FGFApiCallback SetAttributesCallback;
				SetAttributesCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("BatchAttributes 1 :: Set Attributes");
					TestTrue("Set attributes request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Set attributes failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), 
					GameFuseUser->SetAttributes(TestAttributes, SetAttributesCallback)));

				// Fetch attributes to verify
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestAttributes]() -> bool {
					FGFApiCallback FetchCallback;
					FetchCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("BatchAttributes 2 :: Fetch Attributes");
						TestTrue("Fetch attributes request succeeded", Response.bSuccess);
						if (!Response.bSuccess) {
							AddError(FString::Printf(TEXT("Fetch attributes failed: %s"), *Response.ResponseStr));
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
						GameFuseUser->FetchAttributes(FetchCallback)));

					// Verify attributes
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, TestAttributes]() -> bool {
						AddInfo("BatchAttributes 3 :: Verify Attributes");
						const TMap<FString, FString>& StoredAttributes = GameFuseUser->GetAttributes();
						
						TestEqual("Should have correct number of attributes", StoredAttributes.Num(), TestAttributes.Num());
						
						for (const auto& Pair : TestAttributes)
						{
							const FString* StoredValue = StoredAttributes.Find(Pair.Key);
							TestNotNull(*FString::Printf(TEXT("Should find attribute %s"), *Pair.Key), StoredValue);
							if (StoredValue)
							{
								TestEqual(*FString::Printf(TEXT("Attribute %s should have correct value"), *Pair.Key),
									*StoredValue, Pair.Value);
							}
						}

						// Clean up
						ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
						return true;
					}));
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

				FGFApiCallback SetAttributesCallback;
				SetAttributesCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("RemoveAttributes 1 :: Set Initial Attributes");
					TestTrue("Set attributes request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Set attributes failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
					GameFuseUser->SetAttributes(TestAttributes, SetAttributesCallback)));

				// Remove one attribute
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFApiCallback RemoveCallback;
					RemoveCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("RemoveAttributes 2 :: Remove Attribute");
						TestTrue("Remove attribute request succeeded", Response.bSuccess);
						if (!Response.bSuccess) {
							AddError(FString::Printf(TEXT("Remove attribute failed: %s"), *Response.ResponseStr));
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
						GameFuseUser->RemoveAttribute("test_key1", RemoveCallback)));

					// Fetch to verify
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFApiCallback FetchCallback;
						FetchCallback.AddLambda([this](const FGFAPIResponse& Response) {
							AddInfo("RemoveAttributes 3 :: Fetch Attributes");
							TestTrue("Fetch attributes request succeeded", Response.bSuccess);
							if (!Response.bSuccess) {
								AddError(FString::Printf(TEXT("Fetch attributes failed: %s"), *Response.ResponseStr));
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
							GameFuseUser->FetchAttributes(FetchCallback)));

						// Verify attributes
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							AddInfo("RemoveAttributes 4 :: Verify Attributes");
							const TMap<FString, FString>& StoredAttributes = GameFuseUser->GetAttributes();
							
							TestEqual("Should have one attribute remaining", StoredAttributes.Num(), 1);
							TestNull("Removed attribute should not exist", StoredAttributes.Find("test_key1"));
							TestNotNull("Remaining attribute should exist", StoredAttributes.Find("test_key2"));
							
							if (const FString* RemainingValue = StoredAttributes.Find("test_key2"))
							{
								TestEqual("Remaining attribute should have correct value", *RemainingValue, "test_value2");
							}

							// Clean up
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

		It("syncs local attributes", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// First set some local attributes
				FGFApiCallback SetLocalCallback;
				SetLocalCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("SyncLocal 1 :: Set Local Attributes");
					TestTrue("Set local attributes succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Set local attributes failed: %s"), *Response.ResponseStr));
					}
				});

				// Set multiple local attributes
				GameFuseUser->SetAttributeLocal("local_key1", "local_value1", SetLocalCallback);
				GameFuseUser->SetAttributeLocal("local_key2", "local_value2", SetLocalCallback);
				GameFuseUser->SetAttributeLocal("local_key3", "local_value3", SetLocalCallback);

				// Verify local attributes were set
				const TMap<FString, FString>& LocalAttributes = GameFuseUser->GetDirtyAttributes();
				TestEqual("Should have three local attributes", LocalAttributes.Num(), 3);
				TestEqual("Local attribute 1 should have correct value", LocalAttributes.FindRef("local_key1"), "local_value1");
				TestEqual("Local attribute 2 should have correct value", LocalAttributes.FindRef("local_key2"), "local_value2");
				TestEqual("Local attribute 3 should have correct value", LocalAttributes.FindRef("local_key3"), "local_value3");

				// Sync local attributes to server
				FGFApiCallback SyncCallback;
				SyncCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("SyncLocal 2 :: Sync Local Attributes");
					TestTrue("Sync local attributes succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Sync local attributes failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
					GameFuseUser->SyncLocalAttributes(SyncCallback)));

				// Fetch attributes to verify sync
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFApiCallback FetchCallback;
					FetchCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("SyncLocal 3 :: Fetch Attributes");
						TestTrue("Fetch attributes succeeded", Response.bSuccess);
						if (!Response.bSuccess) {
							AddError(FString::Printf(TEXT("Fetch attributes failed: %s"), *Response.ResponseStr));
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
						GameFuseUser->FetchAttributes(FetchCallback)));

					// Verify synced attributes
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						AddInfo("SyncLocal 4 :: Verify Synced Attributes");
						const TMap<FString, FString>& StoredAttributes = GameFuseUser->GetAttributes();
						
						TestEqual("Should have three synced attributes", StoredAttributes.Num(), 3);
						TestEqual("Synced attribute 1 should have correct value", StoredAttributes.FindRef("local_key1"), "local_value1");
						TestEqual("Synced attribute 2 should have correct value", StoredAttributes.FindRef("local_key2"), "local_value2");
						TestEqual("Synced attribute 3 should have correct value", StoredAttributes.FindRef("local_key3"), "local_value3");

						// Clean up
						ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
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