#if WITH_AUTOMATION_TESTS
#include "Library/GameFuseLog.h"
#include "Misc/AutomationTest.h"
#include "Subsystems/GameFuseManager.h"
#include "Subsystems/GameFuseUser.h"
#include "Subsystems/GameFuseFriends.h"
#include "Commands/TestSuiteCommands.h"

BEGIN_DEFINE_SPEC(GameFuseFriendsSpec, "GameFuseTests.GameFuseFriends",
				  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
UGameFuseManager* GameFuseManager;
UGameFuseUser* GameFuseUser;
UGameFuseFriends* GameFuseFriends;
UGameInstance* GameInstance;
UTestAPIHandler* TestAPIHandler;
TSharedPtr<FGFGameData> GameData;
TSharedPtr<FGFUserData> UserData1;
TSharedPtr<FGFUserData> UserData2;
bool bCleanupSuccess;
END_DEFINE_SPEC(GameFuseFriendsSpec);

void GameFuseFriendsSpec::Define()
{
	UE_LOG(LogGameFuse, Log, TEXT("GameFuseFriends::DEFINE was called"));
	// Setup
	GameInstance = NewObject<UGameInstance>();
	GameInstance->Init();

	// Get subsystems/ test api handler
	GameFuseManager = GameInstance->GetSubsystem<UGameFuseManager>();
	GameFuseUser = GameInstance->GetSubsystem<UGameFuseUser>();
	GameFuseFriends = GameInstance->GetSubsystem<UGameFuseFriends>();
	TestAPIHandler = NewObject<UTestAPIHandler>();

	// init testing data
	GameData = MakeShared<FGFGameData>();
	UserData1 = MakeShared<FGFUserData>();
	UserData2 = MakeShared<FGFUserData>();
	bCleanupSuccess = false;

	Describe("GameFuseFriends", [this]() {
		// creates a game and 2 users to facilitate friend request testing
		// user 1 is signed in, user 2 is just created
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
			ADD_LATENT_AUTOMATION_COMMAND(FSetupUser(TestAPIHandler, GameData, UserData1, GameFuseUser, this));

			// Wait for first user to be fully signed in
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
					UE_LOG(LogGameFuse, Warning, TEXT("Waiting for first user signin..."));
					return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("First user signed in successfully"));
				return true;
			}));

			// Create second user
			ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, UserData2, this, FGuid()));
		});

		It("sends and accepts a friend request", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFFriendRequestCallback SendCallback;
				SendCallback.BindLambda([this](const FGFFriendRequest& Request) {
					AddInfo("SendFriendRequest 1 :: Send Request");
					TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);
					TestEqual("Request OtherUser Id", Request.OtherUser.Id, UserData2->Id);
					TestEqual("Request OtherUser Username", Request.OtherUser.Username, UserData2->Username);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																  GameFuseFriends->SendFriendRequest(UserData2->Username, SendCallback)));

				// Verify the request was sent
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFFriendRequestsCallback OutgoingCallback;
					OutgoingCallback.BindLambda([this](const TArray<FGFFriendRequest>& Requests) {
						AddInfo("SendFriendRequest 2 :: Verify Outgoing Requests");
						TestEqual("Should have exactly one outgoing request", Requests.Num(), 1);
						if (Requests.Num() != 1) {
							AddError(FString::Printf(TEXT("Expected 1 outgoing request, got %d"), Requests.Num()));
							return;
						}

						// Verify outgoing request details
						const FGFFriendRequest& Request = Requests[0];
						TestEqual("Outgoing request OtherUser Id", Request.OtherUser.Id, UserData2->Id);
						TestEqual("Outgoing request OtherUser Username", Request.OtherUser.Username, UserData2->Username);
						TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																	  GameFuseFriends->FetchOutgoingFriendRequests(OutgoingCallback)));

					// Sign in second user to accept request
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFApiCallback SignInCallback;
						SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
							AddInfo("SendFriendRequest 3 :: Sign In Second User");
							TestTrue("Second user sign in succeeded", Response.bSuccess);
							if (!Response.bSuccess) {
								AddError(FString::Printf(TEXT("Second user sign in failed: %s"), *Response.ResponseStr));
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

						// Fetch incoming requests after sign in
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFFriendRequestsCallback FetchCallback;
							FetchCallback.BindLambda([this](const TArray<FGFFriendRequest>& IncomingRequests) {
								AddInfo("SendFriendRequest 4 :: Fetch Incoming Requests");
								TestEqual("Should have exactly one incoming request", IncomingRequests.Num(), 1);
								if (IncomingRequests.Num() != 1) {
									AddError(FString::Printf(TEXT("Expected 1 incoming request, got %d"), IncomingRequests.Num()));
									return;
								}

								// Verify incoming request details
								const FGFFriendRequest& Request = IncomingRequests[0];
								TestEqual("Incoming request OtherUser Id", Request.OtherUser.Id, UserData1->Id);
								TestEqual("Incoming request OtherUser Username", Request.OtherUser.Username, UserData1->Username);
								TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																			  GameFuseFriends->FetchIncomingFriendRequests(FetchCallback)));

							// Accept the friend request
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
								const TArray<FGFFriendRequest>& IncomingRequests = GameFuseFriends->GetIncomingRequests();
								if (IncomingRequests.Num() != 1) {
									return true;
								}

								FGFFriendActionCallback AcceptCallback;
								AcceptCallback.BindLambda([this](bool bSuccess) {
									AddInfo("SendFriendRequest 5 :: Accept Request");
									TestTrue("Accept friend request succeeded", bSuccess);
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																				  GameFuseFriends->AcceptFriendRequest(IncomingRequests[0].FriendshipId, AcceptCallback)));

								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
									// Verify friendship was established
									FGFFriendsCallback FriendsCallback;
									FriendsCallback.BindLambda([this](const TArray<FGFUserData>& Friends) {
										AddInfo("SendFriendRequest 6 :: Verify Friends List");
										TestEqual("Should have exactly one friend", Friends.Num(), 1);
										if (Friends.Num() != 1) {
											AddError(FString::Printf(TEXT("Expected 1 friend, got %d"), Friends.Num()));
											return;
										}

										// Verify friend details
										const FGFUserData& Friend = Friends[0];
										TestEqual("Friend Id", Friend.Id, UserData1->Id);
										TestEqual("Friend Username", Friend.Username, UserData1->Username);
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																					  GameFuseFriends->FetchFriendsList(FriendsCallback)));
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

		It("sends and declines a friend request", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFFriendRequestCallback SendCallback;
				SendCallback.BindLambda([this](const FGFFriendRequest& Request) {
					AddInfo("DeclineFriendRequest 1 :: Send Request");
					TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);
					TestEqual("Request OtherUser Id", Request.OtherUser.Id, UserData2->Id);
					TestEqual("Request OtherUser Username", Request.OtherUser.Username, UserData2->Username);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																  GameFuseFriends->SendFriendRequest(UserData2->Username, SendCallback)));

				// Verify the request was sent
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFFriendRequestsCallback OutgoingCallback;
					OutgoingCallback.BindLambda([this](const TArray<FGFFriendRequest>& Requests) {
						AddInfo("DeclineFriendRequest 2 :: Verify Outgoing Requests");
						TestEqual("Should have exactly one outgoing request", Requests.Num(), 1);
						if (Requests.Num() != 1) {
							AddError(FString::Printf(TEXT("Expected 1 outgoing request, got %d"), Requests.Num()));
							return;
						}

						// Verify outgoing request details
						const FGFFriendRequest& Request = Requests[0];
						TestEqual("Outgoing request OtherUser Id", Request.OtherUser.Id, UserData2->Id);
						TestEqual("Outgoing request OtherUser Username", Request.OtherUser.Username, UserData2->Username);
						TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																	  GameFuseFriends->FetchOutgoingFriendRequests(OutgoingCallback)));

					// Sign in second user to decline request
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFApiCallback SignInCallback;
						SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
							AddInfo("DeclineFriendRequest 3 :: Sign In Second User");
							TestTrue("Second user sign in succeeded", Response.bSuccess);
							if (!Response.bSuccess) {
								AddError(FString::Printf(TEXT("Second user sign in failed: %s"), *Response.ResponseStr));
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

						// Fetch incoming requests after sign in
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFFriendRequestsCallback FetchCallback;
							FetchCallback.BindLambda([this](const TArray<FGFFriendRequest>& IncomingRequests) {
								AddInfo("DeclineFriendRequest 4 :: Fetch Incoming Requests");
								TestEqual("Should have exactly one incoming request", IncomingRequests.Num(), 1);
								if (IncomingRequests.Num() != 1) {
									AddError(FString::Printf(TEXT("Expected 1 incoming request, got %d"), IncomingRequests.Num()));
									return;
								}

								// Verify incoming request details
								const FGFFriendRequest& Request = IncomingRequests[0];
								TestEqual("Incoming request OtherUser Id", Request.OtherUser.Id, UserData1->Id);
								TestEqual("Incoming request OtherUser Username", Request.OtherUser.Username, UserData1->Username);
								TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																			  GameFuseFriends->FetchIncomingFriendRequests(FetchCallback)));

							// Decline the friend request
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
								const TArray<FGFFriendRequest>& IncomingRequests = GameFuseFriends->GetIncomingRequests();
								if (IncomingRequests.Num() != 1) {
									return true;
								}

								FGFFriendActionCallback DeclineCallback;
								DeclineCallback.BindLambda([this](bool bSuccess) {
									AddInfo("DeclineFriendRequest 5 :: Decline Request");
									TestTrue("Decline friend request succeeded", bSuccess);
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																				  GameFuseFriends->DeclineFriendRequest(IncomingRequests[0].FriendshipId, DeclineCallback)));

								// Verify request was removed
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
									FGFFriendRequestsCallback VerifyCallback;
									VerifyCallback.BindLambda([this](const TArray<FGFFriendRequest>& Requests) {
										AddInfo("DeclineFriendRequest 6 :: Verify Request Removed");
										TestEqual("Should have no incoming requests", Requests.Num(), 0);
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																					  GameFuseFriends->FetchIncomingFriendRequests(VerifyCallback)));
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

		It("sends and cancels a friend request", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFFriendRequestCallback SendCallback;
				SendCallback.BindLambda([this](const FGFFriendRequest& Request) {
					AddInfo("CancelFriendRequest 1 :: Send Request");
					TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);
					TestEqual("Request OtherUser Id", Request.OtherUser.Id, UserData2->Id);
					TestEqual("Request OtherUser Username", Request.OtherUser.Username, UserData2->Username);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																  GameFuseFriends->SendFriendRequest(UserData2->Username, SendCallback)));

				// Verify the request was sent
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFFriendRequestsCallback OutgoingCallback;
					OutgoingCallback.BindLambda([this](const TArray<FGFFriendRequest>& Requests) {
						AddInfo("CancelFriendRequest 2 :: Verify Outgoing Requests");
						TestEqual("Should have exactly one outgoing request", Requests.Num(), 1);
						if (Requests.Num() != 1) {
							AddError(FString::Printf(TEXT("Expected 1 outgoing request, got %d"), Requests.Num()));
							return;
						}

						// Verify outgoing request details
						const FGFFriendRequest& Request = Requests[0];
						TestEqual("Outgoing request OtherUser Id", Request.OtherUser.Id, UserData2->Id);
						TestEqual("Outgoing request OtherUser Username", Request.OtherUser.Username, UserData2->Username);
						TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);

						// Cancel the request
						FGFFriendActionCallback CancelCallback;
						CancelCallback.BindLambda([this](bool bSuccess) {
							AddInfo("CancelFriendRequest 3 :: Cancel Request");
							TestTrue("Cancel friend request succeeded", bSuccess);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																		  GameFuseFriends->CancelFriendRequest(Request.FriendshipId, CancelCallback)));

						// Verify request was removed
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFFriendRequestsCallback VerifyCallback;
							VerifyCallback.BindLambda([this](const TArray<FGFFriendRequest>& Requests) {
								AddInfo("CancelFriendRequest 4 :: Verify Request Removed");
								TestEqual("Should have no outgoing requests", Requests.Num(), 0);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																			  GameFuseFriends->FetchOutgoingFriendRequests(VerifyCallback)));
							return true;
						}));
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																	  GameFuseFriends->FetchOutgoingFriendRequests(OutgoingCallback)));
					return true;
				}));
				return true;
			}));
		});

		It("unfriends a player", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFFriendRequestCallback SendCallback;
				SendCallback.BindLambda([this](const FGFFriendRequest& Request) {
					AddInfo("UnfriendPlayer 1 :: Send Request");
					TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);
					TestEqual("Request OtherUser Id", Request.OtherUser.Id, UserData2->Id);
					TestEqual("Request OtherUser Username", Request.OtherUser.Username, UserData2->Username);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																  GameFuseFriends->SendFriendRequest(UserData2->Username, SendCallback)));

				// Verify the request was sent
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFFriendRequestsCallback OutgoingCallback;
					OutgoingCallback.BindLambda([this](const TArray<FGFFriendRequest>& Requests) {
						AddInfo("UnfriendPlayer 2 :: Verify Outgoing Requests");
						TestEqual("Should have exactly one outgoing request", Requests.Num(), 1);
						TestEqual("Callback matches internal state", Requests.Num(), GameFuseFriends->GetOutgoingRequests().Num());

						if (Requests.Num() != 1) {
							AddError(FString::Printf(TEXT("Expected 1 outgoing request, got %d"), Requests.Num()));
							return;
						}

						// Verify outgoing request details and internal state
						const FGFFriendRequest& Request = Requests[0];
						const TArray<FGFFriendRequest>& InternalRequests = GameFuseFriends->GetOutgoingRequests();

						TestEqual("Outgoing request OtherUser Id", Request.OtherUser.Id, UserData2->Id);
						TestEqual("Outgoing request OtherUser Username", Request.OtherUser.Username, UserData2->Username);
						TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);

						// Verify internal state matches callback data
						TestEqual("Internal request matches callback request", InternalRequests[0], Request);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																	  GameFuseFriends->FetchOutgoingFriendRequests(OutgoingCallback)));

					// Sign in second user to accept request
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFApiCallback SignInCallback;
						SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
							AddInfo("UnfriendPlayer 3 :: Sign In Second User");
							TestTrue("Second user sign in succeeded", Response.bSuccess);
							if (!Response.bSuccess) {
								AddError(FString::Printf(TEXT("Second user sign in failed: %s"), *Response.ResponseStr));
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

						// Fetch incoming requests after sign in
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFFriendRequestsCallback FetchCallback;
							FetchCallback.BindLambda([this](const TArray<FGFFriendRequest>& IncomingRequests) {
								AddInfo("UnfriendPlayer 4 :: Fetch Incoming Requests");
								TestEqual("Should have exactly one incoming request", IncomingRequests.Num(), 1);
								TestEqual("Callback matches internal state", IncomingRequests.Num(), GameFuseFriends->GetIncomingRequests().Num());

								if (IncomingRequests.Num() != 1) {
									AddError(FString::Printf(TEXT("Expected 1 incoming request, got %d"), IncomingRequests.Num()));
									return;
								}

								// Verify incoming request details and internal state
								const FGFFriendRequest& Request = IncomingRequests[0];
								const TArray<FGFFriendRequest>& InternalRequests = GameFuseFriends->GetIncomingRequests();

								TestEqual("Incoming request OtherUser Id", Request.OtherUser.Id, UserData1->Id);
								TestEqual("Incoming request OtherUser Username", Request.OtherUser.Username, UserData1->Username);
								TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);

								// Verify internal state matches callback data
								TestEqual("Internal request matches callback request", InternalRequests[0], Request);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																			  GameFuseFriends->FetchIncomingFriendRequests(FetchCallback)));

							// Accept the friend request
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
								const TArray<FGFFriendRequest>& IncomingRequests = GameFuseFriends->GetIncomingRequests();
								if (IncomingRequests.Num() != 1) {
									return true;
								}

								FGFFriendActionCallback AcceptCallback;
								AcceptCallback.BindLambda([this](bool bSuccess) {
									AddInfo("UnfriendPlayer 5 :: Accept Request");
									TestTrue("Accept friend request succeeded", bSuccess);
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																				  GameFuseFriends->AcceptFriendRequest(IncomingRequests[0].FriendshipId, AcceptCallback)));

								// Verify friendship was established and unfriend
								FGFFriendsCallback FriendsCallback;
								FriendsCallback.BindLambda([this](const TArray<FGFUserData>& Friends) {
									AddInfo("UnfriendPlayer 6 :: Verify Friends List");
									TestEqual("Should have exactly one friend", Friends.Num(), 1);
									TestEqual("Callback friends count matches internal state", Friends.Num(), GameFuseFriends->GetFriendsList().Num());

									if (Friends.Num() != 1) {
										AddError(FString::Printf(TEXT("Expected 1 friend, got %d"), Friends.Num()));
										return;
									}

									// Verify friend details and unfriend
									const FGFUserData& Friend = Friends[0];
									const TArray<FGFUserData>& InternalFriends = GameFuseFriends->GetFriendsList();

									TestEqual("Friend Id", Friend.Id, UserData1->Id);
									TestEqual("Friend Username", Friend.Username, UserData1->Username);

									// Verify internal state matches callback data
									TestEqual("Internal friends list contains the same friend", InternalFriends[0], Friend);

									// Unfriend the player
									FGFFriendActionCallback UnfriendCallback;
									UnfriendCallback.BindLambda([this](bool bSuccess) {
										AddInfo("UnfriendPlayer 7 :: Unfriend Player");
										TestTrue("Unfriend player succeeded", bSuccess);
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																					  GameFuseFriends->UnfriendPlayer(Friend.Id, UnfriendCallback)));

									// Verify friend was removed
									ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
										FGFFriendsCallback VerifyCallback;
										VerifyCallback.BindLambda([this](const TArray<FGFUserData>& VerifyFriends) {
											AddInfo("UnfriendPlayer 8 :: Verify Empty Friends List");
											TestEqual("Should have no friends after unfriending", VerifyFriends.Num(), 0);
											TestEqual("Internal friends list should be empty", GameFuseFriends->GetFriendsList().Num(), 0);
											TestEqual("Callback matches internal state", VerifyFriends, GameFuseFriends->GetFriendsList());
										});
										ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																						  GameFuseFriends->FetchFriendsList(VerifyCallback)));
										return true;
									}));
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																				  GameFuseFriends->FetchFriendsList(FriendsCallback)));
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
	});
}

#endif