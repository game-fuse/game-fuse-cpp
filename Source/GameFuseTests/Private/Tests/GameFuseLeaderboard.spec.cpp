#if WITH_AUTOMATION_TESTS
#include "Library/GameFuseLog.h"
#include "Misc/AutomationTest.h"
#include "Subsystems/GameFuseManager.h"
#include "Subsystems/GameFuseUser.h"
#include "Commands/TestSuiteCommands.h"

BEGIN_DEFINE_SPEC(GameFuseLeaderboard, "GameFuseTests.GameFuseLeaderboard",
				  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
UGameFuseManager* GameFuseManager;
UGameFuseUser* GameFuseUser;
UGameInstance* GameInstance;
UTestAPIHandler* TestAPIHandler;
TSharedPtr<FGFGameData> GameData;
TSharedPtr<FGFUserData> UserData;
bool bCleanupSuccess;
END_DEFINE_SPEC(GameFuseLeaderboard);

void GameFuseLeaderboard::Define()
{
	UE_LOG(LogGameFuse, Log, TEXT("GameFuseLeaderboard::DEFINE was called"));

	// Setup
	GameInstance = NewObject<UGameInstance>();
	GameInstance->Init();

	// Get subsystems and test api handler
	GameFuseManager = GameInstance->GetSubsystem<UGameFuseManager>();
	GameFuseUser = GameInstance->GetSubsystem<UGameFuseUser>();
	TestAPIHandler = NewObject<UTestAPIHandler>();

	// Init testing data
	GameData = MakeShared<FGFGameData>();
	UserData = MakeShared<FGFUserData>();
	bCleanupSuccess = false;

	Describe("GameFuse Leaderboard", [this]() {
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

			ADD_LATENT_AUTOMATION_COMMAND(FSetupGame(TestAPIHandler, GameData, GameFuseManager, this, FGuid()));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				if (!GameFuseManager->IsSetUp()) {
					UE_LOG(LogGameFuse, Warning, TEXT("Waiting for GameFuseManager setup..."));
					return false;
				}
				UE_LOG(LogGameFuse, Log, TEXT("GameFuseManager setup complete"));
				return true;
			}));

			ADD_LATENT_AUTOMATION_COMMAND(FSetupUser(TestAPIHandler, GameData, UserData, GameFuseUser, this));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
					UE_LOG(LogGameFuse, Warning, TEXT("Waiting for user signin..."));
					return false;
				}
				UE_LOG(LogGameFuse, Log, TEXT("User signed in successfully"));
				return true;
			}));
		});

		It("adds a leaderboard entry", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFInternalSuccessCallback AddEntryCallback;
				AddEntryCallback.AddLambda([this](bool bSuccess) {
					AddInfo("AddLeaderboardEntry 1 :: Add Entry");
					TestTrue("Add leaderboard entry request succeeded", bSuccess);
					if (!bSuccess) {
						AddError(TEXT("Add leaderboard entry failed"));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddLeaderboardEntry("Test Leaderboard", 100, TMap<FString, FString>(), AddEntryCallback)));

				// Verify the entry was added
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFLeaderboardEntriesCallback FetchCallback;
					FetchCallback.BindLambda([this](bool bSuccess, const TArray<FGFLeaderboardEntry>& Entries) {
						AddInfo("AddLeaderboardEntry 2 :: Fetch Entries");
						TestTrue("Fetch entries request succeeded", bSuccess);
						if (!bSuccess) {
							AddError(TEXT("Failed to fetch leaderboard entries"));
							return;
						}
						TestEqual("Should have exactly one entry", Entries.Num(), 1);
						if (Entries.Num() > 0) {
							TestEqual("Entry score should match", Entries[0].Score, 100);
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchMyLeaderboardEntries(10, false, FetchCallback)));
					ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
					return true;
				}));
				return true;
			}));
		});

		It("adds a leaderboard entry with metadata", [this]() {
			const FString LeaderboardName = TEXT("TestLeaderboard");
			constexpr int32 Score = 1000;
			TMap<FString, FString> Metadata;
			Metadata.Add(TEXT("Weapon"), TEXT("Sword"));
			Metadata.Add(TEXT("Level"), TEXT("5"));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName, Score, Metadata]() -> bool {
				FGFInternalSuccessCallback AddCallback;
				AddCallback.AddLambda([this](bool bSuccess) {
					AddInfo("AddLeaderboardEntry 1 :: Add Entry With Metadata");
					TestTrue("Add leaderboard entry with metadata succeeded", bSuccess);
					if (!bSuccess) {
						AddError(TEXT("Add leaderboard entry with metadata failed"));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddLeaderboardEntry(LeaderboardName, Score, Metadata, AddCallback)));

				// Verify the entry was added and metadata is correct
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score, Metadata]() -> bool {
					FGFLeaderboardEntriesCallback FetchCallback;
					FetchCallback.BindLambda([this, Score, Metadata](bool bSuccess, const TArray<FGFLeaderboardEntry>& Entries) {
						AddInfo("AddLeaderboardEntry 2 :: Fetch Entries");
						TestTrue("Fetch entries request succeeded", bSuccess);
						if (!bSuccess) {
							AddError(TEXT("Failed to fetch leaderboard entries"));
							return;
						}
						TestTrue("Should have at least one entry", Entries.Num() > 0);
						if (Entries.Num() > 0) {
							const FGFLeaderboardEntry& Entry = Entries[0];
							TestEqual("Score should match what we added", Entry.Score, Score);

							// Verify metadata exists and matches
							TestTrue("Should have weapon metadata", Entry.Metadata.Contains(TEXT("Weapon")));
							TestTrue("Should have level metadata", Entry.Metadata.Contains(TEXT("Level")));

							if (Entry.Metadata.Contains(TEXT("Weapon"))) {
								TestEqual("Weapon metadata should match", Entry.Metadata[TEXT("Weapon")], Metadata[TEXT("Weapon")]);
							}
							if (Entry.Metadata.Contains(TEXT("Level"))) {
								TestEqual("Level metadata should match", Entry.Metadata[TEXT("Level")], Metadata[TEXT("Level")]);
							}
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchMyLeaderboardEntries(10, false, FetchCallback)));
					ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));
					return true;
				}));
				return true;
			}));
		});

		It("clears a leaderboard entry", [this]() {
			const FString LeaderboardName = TEXT("TestLeaderboard");
			constexpr int32 Score = 1500;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName, Score]() -> bool {
				FGFInternalSuccessCallback AddCallback;
				AddCallback.AddLambda([this](bool bSuccess) {
					AddInfo("ClearLeaderboardEntry 1 :: Add Entry");
					TestTrue("Add leaderboard entry succeeded", bSuccess);
					if (!bSuccess) {
						AddError(TEXT("Add leaderboard entry failed"));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddLeaderboardEntry(LeaderboardName, Score, TMap<FString, FString>(), AddCallback)));

				// Verify entry was added
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score, LeaderboardName]() -> bool {
					FGFLeaderboardEntriesCallback FetchCallback;
					FetchCallback.BindLambda([this, Score](bool bSuccess, const TArray<FGFLeaderboardEntry>& Entries) {
						AddInfo("ClearLeaderboardEntry 2 :: Fetch After Add");
						TestTrue("Fetch entries request succeeded", bSuccess);
						if (!bSuccess) {
							AddError(TEXT("Failed to fetch leaderboard entries"));
							return;
						}
						TestTrue("Should have one entry before clearing", Entries.Num() > 0);
						if (Entries.Num() > 0) {
							TestEqual("Score should match what we added", Entries[0].Score, Score);
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchMyLeaderboardEntries(10, false, FetchCallback)));

					// Clear the entry
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName]() -> bool {
						FGFInternalSuccessCallback ClearCallback;
						ClearCallback.AddLambda([this](bool bSuccess) {
							AddInfo("ClearLeaderboardEntry 3 :: Clear Entry");
							TestTrue("Clear leaderboard entry succeeded", bSuccess);
							if (!bSuccess) {
								AddError(TEXT("Clear leaderboard entry failed"));
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->ClearLeaderboardEntry(LeaderboardName, ClearCallback)));

						// Verify entry was cleared
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFLeaderboardEntriesCallback VerifyCallback;
							VerifyCallback.BindLambda([this](bool bSuccess, const TArray<FGFLeaderboardEntry>& Entries) {
								AddInfo("ClearLeaderboardEntry 4 :: Verify Clear");
								TestTrue("Fetch after clear succeeded", bSuccess);
								if (!bSuccess) {
									AddError(TEXT("Failed to fetch leaderboard entries after clear"));
									return;
								}
								TestEqual("Leaderboard should be empty after clearing", Entries.Num(), 0);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->FetchMyLeaderboardEntries(10, false, VerifyCallback)));
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

		It("clears a specific leaderboard entry while keeping others", [this]() {
			const FString LeaderboardName1 = TEXT("TestLeaderboard1");
			const FString LeaderboardName2 = TEXT("TestLeaderboard2");
			constexpr int32 Score1 = 1500;
			constexpr int32 Score2 = 2500;
			TMap<FString, FString> Metadata;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName1, LeaderboardName2, Score1, Score2, Metadata]() -> bool {
				FGFInternalSuccessCallback AddCallback1;
				AddCallback1.AddLambda([this](bool bSuccess) {
					AddInfo("ClearSpecificEntry 1 :: Add First Entry");
					TestTrue("Add first leaderboard entry succeeded", bSuccess);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddLeaderboardEntry(LeaderboardName1, Score1, Metadata, AddCallback1)));

				// Verify first entry was added
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName1, LeaderboardName2, Score1, Metadata]() -> bool {
					FGFLeaderboardEntriesCallback VerifyFirstCallback;
					VerifyFirstCallback.BindLambda([this, Score1](bool bSuccess, const TArray<FGFLeaderboardEntry>& Entries) {
						AddInfo("ClearSpecificEntry 2 :: Fetch After First Add");
						TestTrue("Fetch after first add succeeded", bSuccess);
						if (!bSuccess) {
							AddError(TEXT("Failed to fetch entries after first add"));
							return;
						}
						TestEqual("Should have one entry after first add", Entries.Num(), 1);
						if (Entries.Num() > 0) {
							TestEqual("First score should match", Entries[0].Score, Score1);
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchMyLeaderboardEntries(10, true, VerifyFirstCallback)));

					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score1]() -> bool {
						const TArray<FGFLeaderboardEntry>& Entries = GameFuseUser->GetLeaderboardEntries();
						TestEqual("Should have one entry after first add", Entries.Num(), 1);
						if (Entries.Num() > 0) {
							TestEqual("First score should match", Entries[0].Score, Score1);
						}
						return true;
					}));

					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName1, LeaderboardName2, Score2, Metadata]() -> bool {
						FGFInternalSuccessCallback AddCallback2;
						AddCallback2.AddLambda([this](bool bSuccess) {
							AddInfo("ClearSpecificEntry 2 :: Add Second Entry");
							TestTrue("Add second leaderboard entry succeeded", bSuccess);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->AddLeaderboardEntry(LeaderboardName2, Score2, Metadata, AddCallback2)));

						// Verify both entries exist
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName1, Score1, Score2]() -> bool {
							FGFLeaderboardEntriesCallback VerifyBothCallback;
							VerifyBothCallback.BindLambda([this, Score1, Score2](bool bSuccess, const TArray<FGFLeaderboardEntry>& Entries) {
								AddInfo("ClearSpecificEntry 3 :: Fetch After Second Add");
								TestTrue("Fetch after second add succeeded", bSuccess);
								if (!bSuccess) {
									AddError(TEXT("Failed to fetch entries after second add"));
									return;
								}
								TestEqual("Should have two entries", Entries.Num(), 2);
								bool bFoundScore1 = false;
								bool bFoundScore2 = false;
								for (const FGFLeaderboardEntry& Entry : Entries) {
									if (Entry.Score == Score1) bFoundScore1 = true;
									if (Entry.Score == Score2) bFoundScore2 = true;
								}
								TestTrue("Should find first score", bFoundScore1);
								TestTrue("Should find second score", bFoundScore2);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->FetchMyLeaderboardEntries(10, true, VerifyBothCallback)));

							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName1]() -> bool {
								FGFInternalSuccessCallback ClearCallback;
								ClearCallback.AddLambda([this](bool bSuccess) {
									AddInfo("ClearSpecificEntry 3 :: Clear First Entry");
									TestTrue("Clear first leaderboard entry succeeded", bSuccess);
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																				  GameFuseUser->ClearLeaderboardEntry(LeaderboardName1, ClearCallback)));

								// Verify only second entry remains
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score2]() -> bool {
									FGFLeaderboardEntriesCallback FinalVerifyCallback;
									FinalVerifyCallback.BindLambda([this, Score2](bool bSuccess, const TArray<FGFLeaderboardEntry>& Entries) {
										AddInfo("ClearSpecificEntry 4 :: Verify After Clear");
										TestTrue("Fetch after clear succeeded", bSuccess);
										if (!bSuccess) {
											AddError(TEXT("Failed to fetch entries after clear"));
											return;
										}
										TestEqual("Should have one entry remaining", Entries.Num(), 1);
										if (Entries.Num() > 0) {
											TestEqual("Remaining entry should be second score", Entries[0].Score, Score2);
										}
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																					  GameFuseUser->FetchMyLeaderboardEntries(10, true, FinalVerifyCallback)));
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

		It("fetches my leaderboard entries", [this]() {
			const FString LeaderboardName = TEXT("TestLeaderboard");
			constexpr int32 Score = 2000;
			TMap<FString, FString> Metadata;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName, Score, Metadata]() -> bool {
				FGFInternalSuccessCallback AddCallback;
				AddCallback.AddLambda([this](bool bSuccess) {
					AddInfo("FetchLeaderboardEntries 1 :: Add Entry");
					TestTrue("Add leaderboard entry succeeded", bSuccess);
					if (!bSuccess) {
						AddError("Add leaderboard entry failed");
						return;
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddLeaderboardEntry(LeaderboardName, Score, AddCallback)));

				// Verify entry was added
				FGFLeaderboardEntriesCallback FetchCallback;
				FetchCallback.BindLambda([this](bool bSuccess, const TArray<FGFLeaderboardEntry>& Entries) {
					AddInfo("FetchLeaderboardEntries :: Verify Entries");
					TestTrue("Fetch succeeded", bSuccess);
					if (!bSuccess) {
						AddError(TEXT("Failed to fetch leaderboard entries"));
						return;
					}
					TestTrue("Should have at least one entry", Entries.Num() > 0);
					if (Entries.Num() > 0) {
						TestEqual("Score should match what was added", Entries[0].Score, Score);
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->FetchMyLeaderboardEntries(10, false, FetchCallback)));
				return true;
			}));
		});

		It("clears all leaderboard entries", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// First add a test entry
				FGFInternalSuccessCallback AddCallback;
				AddCallback.AddLambda([this](bool bSuccess) {
					AddInfo("ClearLeaderboardEntries 1 :: Add Entry");
					TestTrue("Add leaderboard entry request succeeded", bSuccess);
					if (!bSuccess) {
						AddError(TEXT("Add leaderboard entry failed"));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddLeaderboardEntry("TestLeaderboard", 100, TMap<FString, FString>(), AddCallback)));

				// Verify the entry was added
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFLeaderboardEntriesCallback VerifyCallback;
					VerifyCallback.BindLambda([this](bool bSuccess, const TArray<FGFLeaderboardEntry>& Entries) {
						AddInfo("ClearLeaderboardEntries 2 :: Verify Entry Added");
						TestTrue("Fetch entries request succeeded", bSuccess);
						if (!bSuccess) {
							AddError(TEXT("Failed to fetch leaderboard entries"));
							return;
						}
						TestEqual("Should have exactly one entry", Entries.Num(), 1);
						if (Entries.Num() > 0) {
							TestEqual("Entry score should match", Entries[0].Score, 100);
							TestEqual("Entry leaderboard name should match", Entries[0].LeaderboardName, TEXT("TestLeaderboard"));
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchMyLeaderboardEntries(10, false, VerifyCallback)));

					// Now clear all entries
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFInternalSuccessCallback ClearCallback;
						ClearCallback.AddLambda([this](bool bSuccess) {
							AddInfo("ClearLeaderboardEntries 3 :: Clear All");
							TestTrue("Clear leaderboard entries request succeeded", bSuccess);
							if (!bSuccess) {
								AddError(TEXT("Clear leaderboard entries failed"));
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->ClearLeaderboardEntry("TestLeaderboard", ClearCallback)));

						// Verify all entries were cleared
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFLeaderboardEntriesCallback FetchCallback;
							FetchCallback.BindLambda([this](bool bSuccess, const TArray<FGFLeaderboardEntry>& Entries) {
								AddInfo("ClearLeaderboardEntries 4 :: Verify Clear");
								TestTrue("Fetch after clear succeeded", bSuccess);
								if (!bSuccess) {
									AddError(TEXT("Failed to fetch leaderboard entries after clear"));
									return;
								}
								TestEqual("Should have no entries", Entries.Num(), 0);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->FetchMyLeaderboardEntries(10, false, FetchCallback)));
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