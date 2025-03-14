#include "Tests/AutomationCommon.h"
#if WITH_AUTOMATION_TESTS

#include "Subsystems/GameFuseRounds.h"
#include "Commands/TestSuiteCommands.h"
#include "Library/GameFuseLog.h"
#include "Library/GameFuseStructLibrary.h"
#include "Misc/AutomationTest.h"
#include "Subsystems/GameFuseManager.h"
#include "Subsystems/GameFuseUser.h"

BEGIN_DEFINE_SPEC(GameFuseRoundsSpec, "GameFuseTests.GameFuseRounds",
				  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
UGameFuseManager* GameFuseManager;
UGameFuseRounds* GameFuseRounds;
UGameFuseUser* GameFuseUser;
UGameInstance* GameInstance;
UTestAPIHandler* TestAPIHandler;
TSharedPtr<FGFGameData> GameData;
TSharedPtr<FGFUserData> UserData;

bool bCleanupSuccess;
END_DEFINE_SPEC(GameFuseRoundsSpec);

void GameFuseRoundsSpec::Define()
{
	UE_LOG(LogGameFuse, Log, TEXT("GameFuseRoundsSpec::DEFINE was called"));

	// Setup
	GameInstance = NewObject<UGameInstance>();
	GameInstance->Init();

	// Get subsystems and test api handler
	GameFuseManager = GameInstance->GetSubsystem<UGameFuseManager>();
	GameFuseRounds = GameInstance->GetSubsystem<UGameFuseRounds>();
	GameFuseUser = GameInstance->GetSubsystem<UGameFuseUser>();
	TestAPIHandler = NewObject<UTestAPIHandler>();

	// Init testing data
	GameData = MakeShared<FGFGameData>();
	UserData = MakeShared<FGFUserData>();

	Describe("GameFuseRounds Basic Operations", [this]() {
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

		It("creates a game round", [this]() {
			TSharedPtr<FGFGameRound> RoundData = MakeShared<FGFGameRound>();
			RoundData->Score = 100;
			RoundData->StartTime = FDateTime::Now();
			RoundData->EndTime = RoundData->StartTime + FTimespan::FromMinutes(1);
			RoundData->GameType = "SinglePlayer";

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData]() -> bool {
				FGFGameRoundCallback TypedCallback;
				TypedCallback.BindLambda([this](const FGFGameRound& _RoundData) {
					AddInfo("CreateGameRound 1 :: Create Basic Round");
					TestTrue("has good id", _RoundData.Id != 0);
					TestTrue("has good score", _RoundData.Score == 100);
					TestTrue("has good game type", _RoundData.GameType == "SinglePlayer");
					TestTrue("has valid start time", _RoundData.StartTime != FDateTime());
					TestTrue("has valid end time", _RoundData.EndTime != FDateTime());
					TestTrue("keeps end time difference", _RoundData.EndTime - _RoundData.StartTime == FTimespan::FromMinutes(1));
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*RoundData, TypedCallback)));
				return true;
			}));
		});

		It("creates a game round with metadata", [this]() {
			TSharedPtr<FGFGameRound> RoundData = MakeShared<FGFGameRound>();
			RoundData->Score = 100;
			RoundData->StartTime = FDateTime::Now();
			RoundData->EndTime = RoundData->StartTime + FTimespan::FromMinutes(1);
			RoundData->GameType = "SinglePlayer";

			RoundData->Metadata.Add("key1", "value1");
			RoundData->Metadata.Add("key2", "value2");

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData]() -> bool {
				FGFGameRoundCallback TypedCallback;
				TypedCallback.BindLambda([this](const FGFGameRound& _RoundData) {
					AddInfo("CreateGameRound 1 :: Create Round with Metadata");
					AddErrorIfFalse(!_RoundData.Metadata.IsEmpty(), "metadata should be present");
					TestTrue("metadata has the right number of keys", _RoundData.Metadata.Num() == 2);

					TestTrue("metadata has the right key", _RoundData.Metadata.Contains("key1"));
					TestTrue("metadata has the right value", _RoundData.Metadata["key1"] == "value1");
				});
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*RoundData, TypedCallback)));
				return true;
			}));
		});

		It("creates a multiplayer game round", [this]() {
			TSharedPtr<FGFGameRound> OriginalRoundData = MakeShared<FGFGameRound>();
			OriginalRoundData->Score = 100;
			OriginalRoundData->StartTime = FDateTime::Now();
			OriginalRoundData->EndTime = OriginalRoundData->StartTime + FTimespan::FromMinutes(1);
			OriginalRoundData->GameType = "Multiplayer";
			OriginalRoundData->bMultiplayer = true;
			OriginalRoundData->Place = 10;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, OriginalRoundData]() -> bool {
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), GameFuseUser->SetCredits(888, FGFUserDataCallback())));
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, OriginalRoundData]() -> bool {
					FGFGameRoundCallback TypedCallback;
					TypedCallback.BindLambda([this, OriginalRoundData](const FGFGameRound& _RoundData) {
						AddInfo("CreateGameRound 1 :: Create Multiplayer Round");
						TestTrue("has good id", _RoundData.Id != 0);
						TestTrue("has good score", _RoundData.Score == 100);
						TestTrue("has good multiplayer game round id", _RoundData.MultiplayerGameRoundId != 0);

						TestTrue("has round rankings", !_RoundData.Rankings.IsEmpty());

						if (!_RoundData.Rankings.IsEmpty()) {
							const FGFGameRoundRanking& Ranking = _RoundData.Rankings[0];
							TestTrue("has good ranking place", Ranking.Place == 10);
							TestTrue("has good ranking score", Ranking.Score == 100);

							TestTrue("has good ranking user id", Ranking.User.Id == UserData->Id);
							TestTrue("has good credits", Ranking.User.Credits == 888);
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*OriginalRoundData, TypedCallback)));
					return true;
				}));
				return true;
			}));
		});

		It("adds multiple players to 1 GameRound", [this]() {
			TSharedPtr<FGFUserData> OtherUser = MakeShared<FGFUserData>();
			ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, OtherUser, this, FGuid()));

			TSharedPtr<FGFGameRound> OriginalRoundData = MakeShared<FGFGameRound>();
			OriginalRoundData->GameUserId = UserData->Id;
			OriginalRoundData->Score = 100;
			OriginalRoundData->StartTime = FDateTime::Now();
			OriginalRoundData->EndTime = OriginalRoundData->StartTime + FTimespan::FromMinutes(1);
			OriginalRoundData->GameType = "Multiplayer";
			OriginalRoundData->bMultiplayer = true;
			OriginalRoundData->Place = 1;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, OriginalRoundData, OtherUser]() -> bool {
				FGFGameRoundCallback TypedCallback;
				TypedCallback.BindLambda([this, OriginalRoundData](const FGFGameRound& _RoundData) {
					AddInfo("OnGameRoundResponse 1");
					TestTrue("has good id", _RoundData.Id != 0);
					TestTrue("has good score", _RoundData.Score == 100);
					TestTrue("has good multiplayer game round id", _RoundData.MultiplayerGameRoundId != 0);

					OriginalRoundData->MultiplayerGameRoundId = _RoundData.MultiplayerGameRoundId;
					TestTrue("updates original round data with multiplayer game round id", OriginalRoundData->MultiplayerGameRoundId == _RoundData.MultiplayerGameRoundId);
					TestTrue("has round rankings", !_RoundData.Rankings.IsEmpty());
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*OriginalRoundData, TypedCallback)));

				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, OriginalRoundData, OtherUser]() -> bool {
					TSharedPtr<FGFGameRound> SecondPlayerRoundData = MakeShared<FGFGameRound>();
					TestTrue("has updated original multiplayer game round id", OriginalRoundData->MultiplayerGameRoundId != 0);
					TestTrue("Other User has good id", OtherUser->Id != 0);

					SecondPlayerRoundData->MultiplayerGameRoundId = OriginalRoundData->MultiplayerGameRoundId;
					SecondPlayerRoundData->GameUserId = OtherUser->Id;
					SecondPlayerRoundData->Score = 50;
					SecondPlayerRoundData->StartTime = FDateTime::Now();
					SecondPlayerRoundData->EndTime = SecondPlayerRoundData->StartTime + FTimespan::FromMinutes(1);
					SecondPlayerRoundData->GameType = "Multiplayer";
					SecondPlayerRoundData->Place = 10;

					FGFGameRoundCallback SecondPlayerTypedCallback;
					SecondPlayerTypedCallback.BindLambda([this, SecondPlayerRoundData](const FGFGameRound& _RoundData) {
						AddInfo("OnGameRoundResponse 2");

						TestTrue("still has good multiplayer game round id", _RoundData.MultiplayerGameRoundId == SecondPlayerRoundData->MultiplayerGameRoundId);
						TestTrue("has good id", _RoundData.Id != 0);
						TestTrue("has lower score", _RoundData.Score == 50);
						TestTrue("has arbitrary place", _RoundData.Place == 10);

						int NumRankings = _RoundData.Rankings.Num();
						TestTrue("has 2 rankings", NumRankings == 2);
					});
					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*SecondPlayerRoundData, *OtherUser, SecondPlayerTypedCallback)));
					return true;
				}));
				return true;
			}));
		});
		// ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));

		It("updates game rounds", [this]() {
			TSharedPtr<FGFGameRound> RoundData = MakeShared<FGFGameRound>();
			RoundData->Score = 100;
			RoundData->Place = 2;
			RoundData->StartTime = FDateTime::Now();
			RoundData->EndTime = RoundData->StartTime + FTimespan::FromMinutes(1);
			RoundData->GameType = "SinglePlayer";

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData]() -> bool {
				FGFGameRoundCallback TypedCallback;
				TypedCallback.BindLambda([this, RoundData](const FGFGameRound& _RoundData) {
					AddInfo("UpdateGameRound 1 :: Create Initial Round");
					TestTrue("has good id", _RoundData.Id != 0);
					TestTrue("has good score", _RoundData.Score == 100);
					TestTrue("has good game type", _RoundData.GameType == "SinglePlayer");
					TestTrue("has valid start time", _RoundData.StartTime != FDateTime());
					TestTrue("has valid end time", _RoundData.EndTime != FDateTime());
					TestTrue("keeps end time difference", _RoundData.EndTime - _RoundData.StartTime == FTimespan::FromMinutes(1));

					RoundData->Id = _RoundData.Id;
				});
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*RoundData, TypedCallback)));

				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData]() -> bool {
					RoundData->Score = 200;
					RoundData->Place = 1;
					RoundData->GameType = "SinglePlayerUpdated";
					RoundData->EndTime = RoundData->StartTime + FTimespan::FromMinutes(2);

					TestTrue("has updated round id", RoundData->Id != 0);

					FGFGameRoundCallback UpdateTypedCallback;
					UpdateTypedCallback.BindLambda([this, RoundData](const FGFGameRound& _RoundData) {
						AddInfo("UpdateGameRound 2 :: Verify Updated Round");
						TestTrue("has good id", _RoundData.Id != 0);
						TestTrue("has updated score", _RoundData.Score == 200);
						TestTrue("has updated place", _RoundData.Place == 1);
						TestTrue("has good game type", _RoundData.GameType == "SinglePlayerUpdated");
						TestTrue("has updated end time", _RoundData.EndTime - _RoundData.StartTime == FTimespan::FromMinutes(2));
					});
					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->UpdateGameRound(RoundData->Id, *RoundData, UpdateTypedCallback)));
					return true;
				}));

				return true;
			}));
		});

		It("deletes a game round", [this]() {
			TSharedPtr<FGFGameRound> RoundData = MakeShared<FGFGameRound>();
			RoundData->Score = 100;
			RoundData->StartTime = FDateTime::Now();
			RoundData->EndTime = RoundData->StartTime + FTimespan::FromMinutes(1);
			RoundData->GameType = "SinglePlayer";

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData]() -> bool {
				FGFGameRoundCallback TypedCallback;
				TypedCallback.BindLambda([this, RoundData](const FGFGameRound& _RoundData) {
					AddInfo("DeleteGameRound 1 :: Create Round");
					TestTrue("has good id", _RoundData.Id != 0);
					RoundData->Id = _RoundData.Id;
				});
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->CreateGameRound(*RoundData, TypedCallback)));

				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData]() -> bool {
					FGFGameRoundActionCallback TypedCallback;
					TypedCallback.BindLambda([this, RoundData](bool bSuccess) {
						AddInfo("DeleteGameRound 2 :: Delete Round");
						AddErrorIfFalse(bSuccess, FString::Printf(TEXT("Failed to delete round with id %d"), RoundData->Id));
						TestTrue("deleted round", bSuccess);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(), GameFuseRounds->DeleteGameRound(RoundData->Id, TypedCallback)));
					return true;
				}));

				return true;
			}));
		});

		xIt("fetches a specific game round", [this]() {
			// todo:: fix fetching a specific game round

			TSharedPtr<FGFGameRound> RoundData = MakeShared<FGFGameRound>();
			RoundData->Score = 100;
			RoundData->StartTime = FDateTime::Now();
			RoundData->EndTime = RoundData->StartTime + FTimespan::FromMinutes(1);
			RoundData->GameType = "MultiPlayer";
			RoundData->bMultiplayer = true;
			RoundData->GameUserId = UserData->Id;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData]() -> bool {
				FGFGameRoundCallback CreateCallback;
				CreateCallback.BindLambda([this, RoundData](const FGFGameRound& _RoundData) {
					AddInfo("FetchGameRound 1 :: Create Round");
					RoundData->Id = _RoundData.Id;
					RoundData->MultiplayerGameRoundId = _RoundData.MultiplayerGameRoundId;
					TestTrue("Created round has valid id", _RoundData.Id != 0);
					TestTrue("has multiplayer game round id", _RoundData.MultiplayerGameRoundId != 0);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(),
																  GameFuseRounds->CreateGameRound(*RoundData, CreateCallback)));


				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData]() -> bool {
					FGFGameRoundCallback FetchCallback;
					FetchCallback.BindLambda([this, RoundData](const FGFGameRound& FetchedRound) {
						AddInfo("FetchGameRound 2 :: Verify Fetched Round");
						TestEqual("Fetched round has correct ID", FetchedRound.Id, RoundData->Id);
						TestEqual("Fetched round has correct score", FetchedRound.Score, RoundData->Score);
						TestEqual("Fetched round has correct game type", FetchedRound.GameType, RoundData->GameType);
						TestTrue("Fetched round has multiplayer game round id", FetchedRound.MultiplayerGameRoundId != 0);
						TestTrue("Fetched round has rankings", !FetchedRound.Rankings.IsEmpty());

						if (!FetchedRound.Rankings.IsEmpty()) {
							const FGFGameRoundRanking& Ranking = FetchedRound.Rankings[0];
							TestEqual("Ranking has correct user id", Ranking.User.Id, UserData->Id);
							TestEqual("Ranking has correct score", Ranking.Score, RoundData->Score);
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(),
																	  GameFuseRounds->FetchGameRound(RoundData->Id, FetchCallback)));
					return true;
				}));
				return true;
			}));
		});

		It("gets a users game rounds", [this]() {
			TSharedPtr<FGFGameRound> RoundData_1 = MakeShared<FGFGameRound>();
			RoundData_1->Score = 100;
			RoundData_1->StartTime = FDateTime::Now();
			RoundData_1->EndTime = RoundData_1->StartTime + FTimespan::FromMinutes(1);
			RoundData_1->GameType = "SinglePlayer";

			TSharedPtr<FGFGameRound> RoundData_2 = MakeShared<FGFGameRound>();
			RoundData_2->Score = 200; // Different score to distinguish from RoundData_1
			RoundData_2->StartTime = FDateTime::Now();
			RoundData_2->EndTime = RoundData_2->StartTime + FTimespan::FromMinutes(1);
			RoundData_2->GameType = "SinglePlayer";

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData_1, RoundData_2]() -> bool {
				FGFGameRoundCallback CreateCallback1;
				CreateCallback1.BindLambda([this, RoundData_1, RoundData_2](const FGFGameRound& _RoundData) {
					AddInfo("GetUserRounds 1 :: Create First Round");
					RoundData_1->Id = _RoundData.Id;
					TestTrue("Round 1 has valid id", _RoundData.Id != 0);
					AddErrorIfFalse(_RoundData.Id > 0, "Round 1 has valid id");
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(),
																  GameFuseRounds->CreateGameRound(*RoundData_1, CreateCallback1)));

				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData_1, RoundData_2]() -> bool {
					FGFGameRoundCallback CreateCallback2;
					CreateCallback2.BindLambda([this, RoundData_1, RoundData_2](const FGFGameRound& _RoundData) {
						AddInfo("GetUserRounds 2 :: Create Second Round");
						RoundData_2->Id = _RoundData.Id;
						TestTrue("Round 2 has valid id", _RoundData.Id != 0);
						AddErrorIfFalse(_RoundData.Id > 0, "Round 2 has valid id");
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(),
																	  GameFuseRounds->CreateGameRound(*RoundData_2, CreateCallback2)));

					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, RoundData_1, RoundData_2]() -> bool {
						FGFGameRoundListCallback FetchCallback;
						FetchCallback.BindLambda([this, RoundData_1, RoundData_2](const TArray<FGFGameRound>& Rounds) {
							AddInfo("GetUserRounds 3 :: Verify User Rounds");
							TestEqual("Should have exactly 2 rounds", Rounds.Num(), 2);
							TestEqual("Internal storage has correct number of rounds", GameFuseRounds->GetUserRounds().Num(), 2);

							// Verify internal storage matches callback data
							TestEqual("Internal storage matches callback data", Rounds, GameFuseRounds->GetUserRounds());

							// Find both rounds in the array (order may not be guaranteed)
							bool bFoundRound1 = false;
							bool bFoundRound2 = false;

							for (const FGFGameRound& Round : Rounds) {
								if (Round.Id == RoundData_1->Id) {
									bFoundRound1 = true;
									TestEqual("Round 1 score matches", Round.Score, RoundData_1->Score);
									TestEqual("Round 1 game type matches", Round.GameType, RoundData_1->GameType);
								} else if (Round.Id == RoundData_2->Id) {
									bFoundRound2 = true;
									TestEqual("Round 2 score matches", Round.Score, RoundData_2->Score);
									TestEqual("Round 2 game type matches", Round.GameType, RoundData_2->GameType);
								}
							}

							TestTrue("Found Round 1 in response", bFoundRound1);
							TestTrue("Found Round 2 in response", bFoundRound2);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseRounds->GetRequestHandler(),
																		  GameFuseRounds->FetchUserGameRounds(FetchCallback)));
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