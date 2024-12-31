#if WITH_AUTOMATION_TESTS
#include "Library/GameFuseLog.h"
#include "Misc/AutomationTest.h"
#include "Subsystems/GameFuseManager.h"
#include "Subsystems/GameFuseUser.h"
#include "Commands/TestSuiteCommands.h"
#include "JsonObjectConverter.h"

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
            // Setup GameFuse before each test
            if (GameFuseManager->IsSetUp()) {
                UE_LOG(LogGameFuse, Warning, TEXT("Already have a game setup"));
            }

            // Clear any saved user data
            if (GameFuseUser) {
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

            // Create and sign in user
            TSharedPtr<FGFUserData> TestUserData = MakeShared<FGFUserData>();
            FString RandomGuid = FGuid::NewGuid().ToString();
            TestUserData->Username = FString::Printf(TEXT("user_%s"), *RandomGuid.Left(8));

            FGFApiCallback OnUserCreated;
            OnUserCreated.AddLambda([this, TestUserData](const FGFAPIResponse& Response) {
                TestTrue("Create user request succeeded", Response.bSuccess);
                if (!Response.bSuccess) {
                    AddError(FString::Printf(TEXT("Create User Request failed. Response: %s"), *Response.ResponseStr));
                    return;
                }

                bool bParseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, TestUserData.Get());
                TestTrue("Parse user data response", bParseSuccess);

                TestTrue("User ID should be valid", TestUserData->Id != 0);
                UE_LOG(LogGameFuse, Log, TEXT("TestUserData updated - ID: %d, Username: %s"), TestUserData->Id, *TestUserData->Username);

                FGFApiCallback SignInCallback;
                SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
                    UE_LOG(LogGameFuse, Log, TEXT("Sign in Response: %s"), *Response.ResponseStr);
                    TestTrue("Sign in request succeeded", Response.bSuccess);
                    if (!Response.bSuccess) {
                        AddError(FString::Printf(TEXT("Sign in failed: %s"), *Response.ResponseStr));
                    }
                });

                FGuid SignInRequestId = GameFuseUser->SignIn(TestUserData->Username + TEXT("@gamefuse.com"), TEXT("password"), SignInCallback);
                ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), SignInRequestId));
            });

            ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, TestUserData, OnUserCreated, this));
        });

        It("adds a leaderboard entry", [this]() {
            const FString LeaderboardName = TEXT("TestLeaderboard");
            const int32 Score = 1000;
            
            FGuid AddLeaderboardRequestId;
            ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, LeaderboardName, Score, &AddLeaderboardRequestId]() -> bool {
                if (!GameFuseUser->IsSignedIn()) {
                    return false;
                }

                FGFApiCallback Callback;
                Callback.AddLambda([this](const FGFAPIResponse& Response) {
                    TestTrue("Add leaderboard entry succeeded", Response.bSuccess);
                });
                
                AddLeaderboardRequestId = GameFuseUser->AddLeaderboardEntry(LeaderboardName, Score, Callback);
                return true;
            }));
            ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), AddLeaderboardRequestId));
        });

        It("adds a leaderboard entry with attributes", [this]() {
            const FString LeaderboardName = TEXT("TestLeaderboard");
            const int32 Score = 1000;
            TMap<FString, FString> ExtraAttributes;
            ExtraAttributes.Add(TEXT("Weapon"), TEXT("Sword"));
            ExtraAttributes.Add(TEXT("Level"), TEXT("5"));
            
            FGuid AddLeaderboardRequestId;
            ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, LeaderboardName, Score, ExtraAttributes, &AddLeaderboardRequestId]() -> bool {
                if (!GameFuseUser->IsSignedIn()) {
                    return false;
                }

                FGFApiCallback Callback;
                Callback.AddLambda([this](const FGFAPIResponse& Response) {
                    TestTrue("Add leaderboard entry with attributes succeeded", Response.bSuccess);
                });
                
                AddLeaderboardRequestId = GameFuseUser->AddLeaderboardEntryWithAttributes(LeaderboardName, Score, ExtraAttributes, Callback);
                return true;
            }));
            ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), AddLeaderboardRequestId));
        });

        It("clears a leaderboard entry", [this]() {
            const FString LeaderboardName = TEXT("TestLeaderboard");
            const int32 Score = 1500;
            
            // First add an entry to clear
            FGuid AddLeaderboardRequestId;
            ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, LeaderboardName, Score, &AddLeaderboardRequestId]() -> bool {
                if (!GameFuseUser->IsSignedIn()) {
                    return false;
                }

                FGFApiCallback Callback;
                Callback.AddLambda([this](const FGFAPIResponse& Response) {
                    TestTrue("Add leaderboard entry succeeded", Response.bSuccess);
                });
                
                AddLeaderboardRequestId = GameFuseUser->AddLeaderboardEntry(LeaderboardName, Score, Callback);
                return true;
            }));
            ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), AddLeaderboardRequestId));

            // Then clear it
            FGuid ClearLeaderboardRequestId;
            ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, LeaderboardName, &ClearLeaderboardRequestId]() -> bool {
                if (!GameFuseUser->IsSignedIn()) {
                    return false;
                }

                FGFApiCallback Callback;
                Callback.AddLambda([this](const FGFAPIResponse& Response) {
                    TestTrue("Clear leaderboard entry succeeded", Response.bSuccess);
                });
                
                ClearLeaderboardRequestId = GameFuseUser->ClearLeaderboardEntry(LeaderboardName, Callback);
                return true;
            }));
            ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), ClearLeaderboardRequestId));

            // Verify it's cleared by trying to fetch it
            FGuid FetchLeaderboardRequestId;
            ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, LeaderboardName, &FetchLeaderboardRequestId]() -> bool {
                if (!GameFuseUser->IsSignedIn()) {
                    return false;
                }

                FGFApiCallback Callback;
                Callback.AddLambda([this](const FGFAPIResponse& Response) {
                    TestTrue("Fetch leaderboard entries succeeded", Response.bSuccess);
                    
                    // Should have no entries after clearing
                    const TArray<FGFLeaderboardEntry>& Entries = GameFuseUser->GetLeaderboardEntries();
                    TestEqual("Leaderboard should be empty after clearing", Entries.Num(), 0);
                });
                
                FetchLeaderboardRequestId = GameFuseUser->FetchMyLeaderboardEntries(10, true, Callback);
                return true;
            }));
            ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), FetchLeaderboardRequestId));
        });

        It("clears a specific leaderboard entry while keeping others", [this]() {
            const FString LeaderboardName1 = TEXT("TestLeaderboard1");
            const FString LeaderboardName2 = TEXT("TestLeaderboard2");
            const int32 Score1 = 1500;
            const int32 Score2 = 2500;
            
            // First add two entries to different leaderboards
            FGuid AddLeaderboardRequestId1;
            ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, LeaderboardName1, Score1, &AddLeaderboardRequestId1]() -> bool {
                if (!GameFuseUser->IsSignedIn()) {
                    return false;
                }

                FGFApiCallback Callback;
                Callback.AddLambda([this](const FGFAPIResponse& Response) {
                    TestTrue("Add first leaderboard entry succeeded", Response.bSuccess);
                });
                
                AddLeaderboardRequestId1 = GameFuseUser->AddLeaderboardEntry(LeaderboardName1, Score1, Callback);
                return true;
            }));
            ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), AddLeaderboardRequestId1));

            FGuid AddLeaderboardRequestId2;
            ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, LeaderboardName2, Score2, &AddLeaderboardRequestId2]() -> bool {
                if (!GameFuseUser->IsSignedIn()) {
                    return false;
                }

                FGFApiCallback Callback;
                Callback.AddLambda([this](const FGFAPIResponse& Response) {
                    TestTrue("Add second leaderboard entry succeeded", Response.bSuccess);
                });
                
                AddLeaderboardRequestId2 = GameFuseUser->AddLeaderboardEntry(LeaderboardName2, Score2, Callback);
                return true;
            }));
            ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), AddLeaderboardRequestId2));

            // Verify both entries exist
            FGuid FetchBeforeClearRequestId;
            ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, Score1, Score2, &FetchBeforeClearRequestId]() -> bool {
                if (!GameFuseUser->IsSignedIn()) {
                    return false;
                }

                FGFApiCallback Callback;
                Callback.AddLambda([this, Score1, Score2](const FGFAPIResponse& Response) {
                    TestTrue("Fetch before clear succeeded", Response.bSuccess);
                    
                    const TArray<FGFLeaderboardEntry>& Entries = GameFuseUser->GetLeaderboardEntries();
                    TestEqual("Should have two entries", Entries.Num(), 2);
                    
                    bool bFoundScore1 = false;
                    bool bFoundScore2 = false;
                    
                    for (const FGFLeaderboardEntry& Entry : Entries)
                    {
                        if (Entry.Score == Score1)
                            bFoundScore1 = true;
                        if (Entry.Score == Score2)
                            bFoundScore2 = true;
                    }
                    
                    TestTrue("Should find first score", bFoundScore1);
                    TestTrue("Should find second score", bFoundScore2);
                });
                
                FetchBeforeClearRequestId = GameFuseUser->FetchMyLeaderboardEntries(10, true, Callback);
                return true;
            }));
            ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), FetchBeforeClearRequestId));

            // Clear only the first leaderboard
            FGuid ClearLeaderboardRequestId;
            ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, LeaderboardName1, &ClearLeaderboardRequestId]() -> bool {
                if (!GameFuseUser->IsSignedIn()) {
                    return false;
                }

                FGFApiCallback Callback;
                Callback.AddLambda([this](const FGFAPIResponse& Response) {
                    TestTrue("Clear first leaderboard entry succeeded", Response.bSuccess);
                });
                
                ClearLeaderboardRequestId = GameFuseUser->ClearLeaderboardEntry(LeaderboardName1, Callback);
                return true;
            }));
            ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), ClearLeaderboardRequestId));

            // Verify only second entry remains
            FGuid FetchAfterClearRequestId;
            ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, Score2, &FetchAfterClearRequestId]() -> bool {
                if (!GameFuseUser->IsSignedIn()) {
                    return false;
                }

                FGFApiCallback Callback;
                Callback.AddLambda([this, Score2](const FGFAPIResponse& Response) {
                    TestTrue("Fetch after clear succeeded", Response.bSuccess);
                    
                    const TArray<FGFLeaderboardEntry>& Entries = GameFuseUser->GetLeaderboardEntries();
                    TestEqual("Should have one entry remaining", Entries.Num(), 1);
                    
                    if (Entries.Num() > 0)
                    {
                        TestEqual("Remaining entry should be second score", Entries[0].Score, Score2);
                    }
                });
                
                FetchAfterClearRequestId = GameFuseUser->FetchMyLeaderboardEntries(10, true, Callback);
                return true;
            }));
            ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), FetchAfterClearRequestId));
        });

        It("fetches my leaderboard entries", [this]() {
            const FString LeaderboardName = TEXT("TestLeaderboard");
            const int32 Score = 2000;
            const int32 Limit = 10;
            const bool bOnePerUser = true;
            
            // First add some entries
            FGuid AddLeaderboardRequestId;
            ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, LeaderboardName, Score, &AddLeaderboardRequestId]() -> bool {
                if (!GameFuseUser->IsSignedIn()) {
                    return false;
                }

                FGFApiCallback Callback;
                Callback.AddLambda([this](const FGFAPIResponse& Response) {
                    TestTrue("Add leaderboard entry succeeded", Response.bSuccess);
                });
                
                AddLeaderboardRequestId = GameFuseUser->AddLeaderboardEntry(LeaderboardName, Score, Callback);
                return true;
            }));
            ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), AddLeaderboardRequestId));

            // Then fetch and verify
            FGuid FetchLeaderboardRequestId;
            ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, LeaderboardName, Score, Limit, bOnePerUser, &FetchLeaderboardRequestId]() -> bool {
                if (!GameFuseUser->IsSignedIn()) {
                    return false;
                }

                FGFApiCallback Callback;
                Callback.AddLambda([this, Score](const FGFAPIResponse& Response) {
                    TestTrue("Fetch leaderboard entries succeeded", Response.bSuccess);
                    
                    const TArray<FGFLeaderboardEntry>& Entries = GameFuseUser->GetLeaderboardEntries();
                    TestTrue("Should have at least one entry", Entries.Num() > 0);
                    
                    if (Entries.Num() > 0)
                    {
                        const FGFLeaderboardEntry& Entry = Entries[0];
                        TestEqual("Score should match what we added", Entry.Score, Score);
                    }
                });
                
                FetchLeaderboardRequestId = GameFuseUser->FetchMyLeaderboardEntries(Limit, bOnePerUser, Callback);
                return true;
            }));
            ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), FetchLeaderboardRequestId));
        });

        AfterEach([this]() {
            // Cleanup after each test
            if (GameFuseUser) {
                GameFuseUser->LogOut();
            }

            // Cleanup game
            FGuid CleanupRequestId;
            ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, CleanupRequestId));
            ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(TestAPIHandler, CleanupRequestId));
        });
    });
}

#endif