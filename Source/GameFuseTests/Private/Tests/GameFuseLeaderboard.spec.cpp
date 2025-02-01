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
				const FString LeaderboardName = TEXT("TestLeaderboard");
				constexpr int32 Score = 1000;
				TMap<FString, FString> Metadata;
				FGFApiCallback Callback;
				Callback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("AddLeaderboardEntry 1 :: Add Entry");
					TestTrue("Add leaderboard entry succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Add leaderboard entry failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddLeaderboardEntry(LeaderboardName, Score, Metadata, Callback)));

				// Verify internal state after adding entry
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score]() -> bool {
					FGFApiCallback FetchCallback;
					FetchCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("AddLeaderboardEntry 2 :: Fetch Entries");
						TestTrue("Fetch after add succeeded", Response.bSuccess);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchMyLeaderboardEntries(10, true, FetchCallback)));

					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score]() -> bool {
						const TArray<FGFLeaderboardEntry>& Entries = GameFuseUser->GetLeaderboardEntries();
						TestTrue("Should have at least one entry", Entries.Num() > 0);
						if (Entries.Num() > 0) {
							TestEqual("Score should match what we added", Entries[0].Score, Score);
						}
						return true;
					}));
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
				FGFApiCallback AddCallback;
				AddCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("AddLeaderboardEntry 1 :: Add Entry With Metadata");
					TestTrue("Add leaderboard entry with metadata succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Add leaderboard entry with metadata failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddLeaderboardEntry(LeaderboardName, Score, Metadata, AddCallback)));

				// Verify the entry was added and metadata is correct
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score, Metadata]() -> bool {
					FGFApiCallback FetchCallback;
					FetchCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("AddLeaderboardEntry 2 :: Fetch Entry");
						TestTrue("Fetch after add succeeded", Response.bSuccess);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchMyLeaderboardEntries(10, true, FetchCallback)));

					// Verify the fetched data
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score, Metadata]() -> bool {
						const TArray<FGFLeaderboardEntry>& Entries = GameFuseUser->GetLeaderboardEntries();
						TestTrue("Should have at least one entry", Entries.Num() > 0);

						if (Entries.Num() > 0) {
							const FGFLeaderboardEntry& Entry = Entries[0];
							TestEqual("Score should match what we added", Entry.Score, Score);

							// Verify metadata exists
							TestTrue("Should have weapon metadata", Entry.Metadata.Contains(TEXT("Weapon")));
							TestTrue("Should have level metadata", Entry.Metadata.Contains(TEXT("Level")));

							// Only compare metadata if they exist
							AddErrorIfFalse(Entry.Metadata.Contains(TEXT("Weapon")), "Missing Weapon metadata");
							AddErrorIfFalse(Entry.Metadata.Contains(TEXT("Level")), "Missing Level metadata");
							TestEqual("Weapon metadata should match", Entry.Metadata[TEXT("Weapon")], Metadata[TEXT("Weapon")]);
							TestEqual("Level metadata should match", Entry.Metadata[TEXT("Level")], Metadata[TEXT("Level")]);
						}
						return true;
					}));
					return true;
				}));
				return true;
			}));
		});

		It("clears a leaderboard entry", [this]() {
			const FString LeaderboardName = TEXT("TestLeaderboard");
			constexpr int32 Score = 1500;
			TMap<FString, FString> Metadata;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName, Score, Metadata]() -> bool {
				FGFApiCallback AddCallback;
				AddCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("ClearLeaderboardEntry 1 :: Add Entry");
					TestTrue("Add leaderboard entry succeeded", Response.bSuccess);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddLeaderboardEntry(LeaderboardName, Score, Metadata, AddCallback)));

				// Verify entry was added
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName, Score]() -> bool {
					FGFApiCallback VerifyAddCallback;
					VerifyAddCallback.AddLambda([this](const FGFAPIResponse& Response) {
						TestTrue("Fetch after add succeeded", Response.bSuccess);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchMyLeaderboardEntries(10, true, VerifyAddCallback)));

					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score]() -> bool {
						const TArray<FGFLeaderboardEntry>& Entries = GameFuseUser->GetLeaderboardEntries();
						TestTrue("Should have one entry before clearing", Entries.Num() > 0);
						if (Entries.Num() > 0) {
							TestEqual("Score should match what we added", Entries[0].Score, Score);
						}
						return true;
					}));

					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName]() -> bool {
						FGFApiCallback ClearCallback;
						ClearCallback.AddLambda([this](const FGFAPIResponse& Response) {
							AddInfo("ClearLeaderboardEntry 2 :: Clear Entry");
							TestTrue("Clear leaderboard entry succeeded", Response.bSuccess);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->ClearLeaderboardEntry(LeaderboardName, ClearCallback)));

						// Verify entry was cleared
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFApiCallback FetchCallback;
							FetchCallback.AddLambda([this](const FGFAPIResponse& Response) {
								AddInfo("ClearLeaderboardEntry 3 :: Fetch Entries");
								TestTrue("Fetch leaderboard entries succeeded", Response.bSuccess);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->FetchMyLeaderboardEntries(10, true, FetchCallback)));

							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
								TestEqual("Leaderboard should be empty after clearing", GameFuseUser->GetLeaderboardEntries().Num(), 0);
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

		It("clears a specific leaderboard entry while keeping others", [this]() {
			const FString LeaderboardName1 = TEXT("TestLeaderboard1");
			const FString LeaderboardName2 = TEXT("TestLeaderboard2");
			constexpr int32 Score1 = 1500;
			constexpr int32 Score2 = 2500;
			TMap<FString, FString> Metadata;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName1, LeaderboardName2, Score1, Score2, Metadata]() -> bool {
				FGFApiCallback AddCallback1;
				AddCallback1.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("ClearSpecificEntry 1 :: Add First Entry");
					TestTrue("Add first leaderboard entry succeeded", Response.bSuccess);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddLeaderboardEntry(LeaderboardName1, Score1, Metadata, AddCallback1)));

				// Verify first entry was added
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName1, LeaderboardName2, Score1, Metadata]() -> bool {
					FGFApiCallback VerifyFirstCallback;
					VerifyFirstCallback.AddLambda([this](const FGFAPIResponse& Response) {
						TestTrue("Fetch after first add succeeded", Response.bSuccess);
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
						FGFApiCallback AddCallback2;
						AddCallback2.AddLambda([this](const FGFAPIResponse& Response) {
							AddInfo("ClearSpecificEntry 2 :: Add Second Entry");
							TestTrue("Add second leaderboard entry succeeded", Response.bSuccess);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->AddLeaderboardEntry(LeaderboardName2, Score2, Metadata, AddCallback2)));

						// Verify both entries exist
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName1, Score1, Score2]() -> bool {
							FGFApiCallback VerifyBothCallback;
							VerifyBothCallback.AddLambda([this](const FGFAPIResponse& Response) {
								TestTrue("Fetch after second add succeeded", Response.bSuccess);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->FetchMyLeaderboardEntries(10, true, VerifyBothCallback)));

							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score1, Score2]() -> bool {
								const TArray<FGFLeaderboardEntry>& Entries = GameFuseUser->GetLeaderboardEntries();
								TestEqual("Should have two entries", Entries.Num(), 2);
								bool bFoundScore1 = false;
								bool bFoundScore2 = false;
								for (const FGFLeaderboardEntry& Entry : Entries) {
									if (Entry.Score == Score1) bFoundScore1 = true;
									if (Entry.Score == Score2) bFoundScore2 = true;
								}
								TestTrue("Should find first score", bFoundScore1);
								TestTrue("Should find second score", bFoundScore2);
								return true;
							}));

							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName1]() -> bool {
								FGFApiCallback ClearCallback;
								ClearCallback.AddLambda([this](const FGFAPIResponse& Response) {
									AddInfo("ClearSpecificEntry 3 :: Clear First Entry");
									TestTrue("Clear first leaderboard entry succeeded", Response.bSuccess);
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																				  GameFuseUser->ClearLeaderboardEntry(LeaderboardName1, ClearCallback)));

								// Verify only second entry remains
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score2]() -> bool {
									FGFApiCallback FetchCallback;
									FetchCallback.AddLambda([this](const FGFAPIResponse& Response) {
										AddInfo("ClearSpecificEntry 4 :: Fetch Entries");
										TestTrue("Fetch after clear succeeded", Response.bSuccess);
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																					  GameFuseUser->FetchMyLeaderboardEntries(10, true, FetchCallback)));

									ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score2]() -> bool {
										const TArray<FGFLeaderboardEntry>& Entries = GameFuseUser->GetLeaderboardEntries();
										TestEqual("Should have one entry remaining", Entries.Num(), 1);
										if (Entries.Num() > 0) {
											TestEqual("Remaining entry should be second score", Entries[0].Score, Score2);
										}
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
				return true;
			}));
		});

		It("fetches my leaderboard entries", [this]() {
			const FString LeaderboardName = TEXT("TestLeaderboard");
			constexpr int32 Score = 2000;
			TMap<FString, FString> Metadata;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, LeaderboardName, Score, Metadata]() -> bool {
				FGFApiCallback AddCallback;
				AddCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("FetchLeaderboardEntries 1 :: Add Entry");
					TestTrue("Add leaderboard entry succeeded", Response.bSuccess);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->AddLeaderboardEntry(LeaderboardName, Score, Metadata, AddCallback)));

				// Verify entry was added
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score]() -> bool {
					FGFApiCallback FetchCallback;
					FetchCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("FetchLeaderboardEntries 2 :: Fetch Entries");
						TestTrue("Fetch leaderboard entries succeeded", Response.bSuccess);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->FetchMyLeaderboardEntries(10, true, FetchCallback)));

					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Score]() -> bool {
						const TArray<FGFLeaderboardEntry>& Entries = GameFuseUser->GetLeaderboardEntries();
						TestTrue("Should have at least one entry", Entries.Num() > 0);
						if (Entries.Num() > 0) {
							TestEqual("Score should match what we added", Entries[0].Score, Score);
						}
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