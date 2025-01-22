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
				FGFApiCallback SendCallback;
				SendCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("SendFriendRequest 1 :: Send Request");
					TestTrue("Send friend request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Send friend request failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																  GameFuseFriends->SendFriendRequest(UserData2->Username, SendCallback)));

				// Verify the request was sent
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFApiCallback OutgoingCallback;
					OutgoingCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("SendFriendRequest 2 :: Verify Outgoing Requests");
						TestTrue("Get outgoing requests succeeded", Response.bSuccess);
						if (!Response.bSuccess) {
							AddError(FString::Printf(TEXT("Get outgoing requests failed: %s"), *Response.ResponseStr));
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																	  GameFuseFriends->GetOutgoingFriendRequests(OutgoingCallback)));

					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						const TArray<FGFFriendRequest>& Requests = GameFuseFriends->GetOutgoingRequests();
						TestEqual("Should have exactly one outgoing request", Requests.Num(), 1);
						if (Requests.Num() != 1) {
							AddError(FString::Printf(TEXT("Expected 1 outgoing request, got %d"), Requests.Num()));
							return true;
						}
						
						// Verify outgoing request details
						const FGFFriendRequest& Request = Requests[0];
						TestEqual("Outgoing request OriginUserId", Request.OriginUserId, UserData2->Id);
						TestEqual("Outgoing request OriginUsername", Request.OriginUsername, UserData2->Username);
						TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);

						// Sign in second user to accept request
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
							FGFApiCallback FetchCallback;
							FetchCallback.AddLambda([this](const FGFAPIResponse& Response) {
								AddInfo("SendFriendRequest 4 :: Fetch Incoming Requests");
								TestTrue("Fetch incoming requests succeeded", Response.bSuccess);
								if (!Response.bSuccess) {
									AddError(FString::Printf(TEXT("Fetch incoming requests failed: %s"), *Response.ResponseStr));
								}
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																			  GameFuseFriends->GetIncomingFriendRequests(FetchCallback)));

							// Accept the friend request
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
								const TArray<FGFFriendRequest>& IncomingRequests = GameFuseFriends->GetIncomingRequests();
								TestEqual("Should have exactly one incoming request", IncomingRequests.Num(), 1);
								if (IncomingRequests.Num() != 1) {
									AddError(FString::Printf(TEXT("Expected 1 incoming request, got %d"), IncomingRequests.Num()));
									return true;
								}

								// Verify incoming request details
								const FGFFriendRequest& Request = IncomingRequests[0];
								TestEqual("Incoming request OriginUserId", Request.OriginUserId, UserData1->Id);
								TestEqual("Incoming request OriginUsername", Request.OriginUsername, UserData1->Username);
								TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);

								FGFApiCallback AcceptCallback;
								AcceptCallback.AddLambda([this](const FGFAPIResponse& Response) {
									AddInfo("SendFriendRequest 5 :: Accept Request");
									TestTrue("Accept friend request succeeded", Response.bSuccess);
									if (!Response.bSuccess) {
										AddError(FString::Printf(TEXT("Accept friend request failed: %s"), *Response.ResponseStr));
									}
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																				  GameFuseFriends->AcceptFriendRequest(IncomingRequests[0].FriendshipId, AcceptCallback)));

								// Verify friendship was established
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
									FGFApiCallback FriendsCallback;
									FriendsCallback.AddLambda([this](const FGFAPIResponse& Response) {
										AddInfo("SendFriendRequest 6 :: Verify Friends List");
										TestTrue("Get friends list succeeded", Response.bSuccess);
										if (!Response.bSuccess) {
											AddError(FString::Printf(TEXT("Get friends list failed: %s"), *Response.ResponseStr));
										}
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																					  GameFuseFriends->GetFriendsList(FriendsCallback)));

									ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
										const TArray<FGFUserData>& Friends = GameFuseFriends->GetFriends();
										TestEqual("Should have exactly one friend", Friends.Num(), 1);
										if (Friends.Num() != 1) {
											AddError(FString::Printf(TEXT("Expected 1 friend, got %d"), Friends.Num()));
											return true;
										}

										// Verify friend details
										const FGFUserData& Friend = Friends[0];
										TestEqual("Friend Id", Friend.Id, UserData1->Id);
										TestEqual("Friend Username", Friend.Username, UserData1->Username);
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

		It("sends and declines a friend request", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFApiCallback SendCallback;
				SendCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("DeclineFriendRequest 1 :: Send Request");
					TestTrue("Send friend request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Send friend request failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																  GameFuseFriends->SendFriendRequest(UserData2->Username, SendCallback)));

				// Verify the request was sent
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFApiCallback OutgoingCallback;
					OutgoingCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("DeclineFriendRequest 2 :: Verify Outgoing Requests");
						TestTrue("Get outgoing requests succeeded", Response.bSuccess);
						if (!Response.bSuccess) {
							AddError(FString::Printf(TEXT("Get outgoing requests failed: %s"), *Response.ResponseStr));
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																	  GameFuseFriends->GetOutgoingFriendRequests(OutgoingCallback)));

					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						const TArray<FGFFriendRequest>& Requests = GameFuseFriends->GetOutgoingRequests();
						TestEqual("Should have exactly one outgoing request", Requests.Num(), 1);
						if (Requests.Num() != 1) {
							AddError(FString::Printf(TEXT("Expected 1 outgoing request, got %d"), Requests.Num()));
							return true;
						}

						// Verify outgoing request details
						const FGFFriendRequest& Request = Requests[0];
						TestEqual("Outgoing request OriginUserId", Request.OriginUserId, UserData2->Id);
						TestEqual("Outgoing request OriginUsername", Request.OriginUsername, UserData2->Username);
						TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);

						// Sign in second user to decline request
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
							FGFApiCallback FetchCallback;
							FetchCallback.AddLambda([this](const FGFAPIResponse& Response) {
								AddInfo("DeclineFriendRequest 4 :: Fetch Incoming Requests");
								TestTrue("Fetch incoming requests succeeded", Response.bSuccess);
								if (!Response.bSuccess) {
									AddError(FString::Printf(TEXT("Fetch incoming requests failed: %s"), *Response.ResponseStr));
								}
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																			  GameFuseFriends->GetIncomingFriendRequests(FetchCallback)));

							// Decline the friend request
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
								const TArray<FGFFriendRequest>& IncomingRequests = GameFuseFriends->GetIncomingRequests();
								TestEqual("Should have exactly one incoming request", IncomingRequests.Num(), 1);
								if (IncomingRequests.Num() != 1) {
									AddError(FString::Printf(TEXT("Expected 1 incoming request, got %d"), IncomingRequests.Num()));
									return true;
								}

								// Verify incoming request details
								const FGFFriendRequest& Request = IncomingRequests[0];
								TestEqual("Incoming request OriginUserId", Request.OriginUserId, UserData1->Id);
								TestEqual("Incoming request OriginUsername", Request.OriginUsername, UserData1->Username);
								TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);

								FGFApiCallback DeclineCallback;
								DeclineCallback.AddLambda([this](const FGFAPIResponse& Response) {
									AddInfo("DeclineFriendRequest 5 :: Decline Request");
									TestTrue("Decline friend request succeeded", Response.bSuccess);
									if (!Response.bSuccess) {
										AddError(FString::Printf(TEXT("Decline friend request failed: %s"), *Response.ResponseStr));
									}
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																				  GameFuseFriends->DeclineFriendRequest(IncomingRequests[0].FriendshipId, DeclineCallback)));

								// Verify request was removed
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
									FGFApiCallback VerifyCallback;
									VerifyCallback.AddLambda([this](const FGFAPIResponse& Response) {
										AddInfo("DeclineFriendRequest 6 :: Verify Request Removed");
										TestTrue("Get incoming requests succeeded", Response.bSuccess);
										if (!Response.bSuccess) {
											AddError(FString::Printf(TEXT("Get incoming requests failed: %s"), *Response.ResponseStr));
										}
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																					  GameFuseFriends->GetIncomingFriendRequests(VerifyCallback)));

									ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
										TestEqual("Should have no incoming requests", GameFuseFriends->GetIncomingRequests().Num(), 0);
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

		It("sends and cancels a friend request", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFApiCallback SendCallback;
				SendCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("CancelFriendRequest 1 :: Send Request");
					TestTrue("Send friend request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Send friend request failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																  GameFuseFriends->SendFriendRequest(UserData2->Username, SendCallback)));

				// Verify the request was sent
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					const TArray<FGFFriendRequest>& OutgoingRequests = GameFuseFriends->GetOutgoingRequests();
					TestEqual("Should have exactly one outgoing request", OutgoingRequests.Num(), 1);
					if (OutgoingRequests.Num() != 1) {
						AddError(FString::Printf(TEXT("Expected 1 outgoing request, got %d"), OutgoingRequests.Num()));
						return true;
					}

					// Verify outgoing request details
					const FGFFriendRequest& Request = OutgoingRequests[0];
					TestEqual("Outgoing request OriginUserId", Request.OriginUserId, UserData2->Id);
					TestEqual("Outgoing request OriginUsername", Request.OriginUsername, UserData2->Username);
					TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);

					FGFApiCallback CancelCallback;
					CancelCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("CancelFriendRequest 2 :: Cancel Request");
						TestTrue("Cancel friend request succeeded", Response.bSuccess);
						if (!Response.bSuccess) {
							AddError(FString::Printf(TEXT("Cancel friend request failed: %s"), *Response.ResponseStr));
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																	  GameFuseFriends->CancelFriendRequest(Request.FriendshipId, CancelCallback)));

					// Verify request was removed
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFApiCallback VerifyCallback;
						VerifyCallback.AddLambda([this](const FGFAPIResponse& Response) {
							AddInfo("CancelFriendRequest 3 :: Verify Request Removed");
							TestTrue("Get outgoing requests succeeded", Response.bSuccess);
							if (!Response.bSuccess) {
								AddError(FString::Printf(TEXT("Get outgoing requests failed: %s"), *Response.ResponseStr));
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																		  GameFuseFriends->GetOutgoingFriendRequests(VerifyCallback)));

						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							TestEqual("Should have no outgoing requests", GameFuseFriends->GetOutgoingRequests().Num(), 0);
							return true;
						}));
						return true;
					}));
					return true;
				}));
				return true;
			}));
		});

		It("unfriends a player", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFApiCallback SendCallback;
				SendCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("UnfriendPlayer 1 :: Send Request");
					TestTrue("Send friend request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Send friend request failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																  GameFuseFriends->SendFriendRequest(UserData2->Username, SendCallback)));

				// Verify the request was sent
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFApiCallback OutgoingCallback;
					OutgoingCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("UnfriendPlayer 2 :: Verify Outgoing Requests");
						TestTrue("Get outgoing requests succeeded", Response.bSuccess);
						if (!Response.bSuccess) {
							AddError(FString::Printf(TEXT("Get outgoing requests failed: %s"), *Response.ResponseStr));
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																	  GameFuseFriends->GetOutgoingFriendRequests(OutgoingCallback)));

					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						const TArray<FGFFriendRequest>& Requests = GameFuseFriends->GetOutgoingRequests();
						TestEqual("Should have exactly one outgoing request", Requests.Num(), 1);
						if (Requests.Num() != 1) {
							AddError(FString::Printf(TEXT("Expected 1 outgoing request, got %d"), Requests.Num()));
							return true;
						}

						// Verify outgoing request details
						const FGFFriendRequest& Request = Requests[0];
						TestEqual("Outgoing request OriginUserId", Request.OriginUserId, UserData2->Id);
						TestEqual("Outgoing request OriginUsername", Request.OriginUsername, UserData2->Username);
						TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);

						// Sign in second user to accept request
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
							FGFApiCallback FetchCallback;
							FetchCallback.AddLambda([this](const FGFAPIResponse& Response) {
								AddInfo("UnfriendPlayer 4 :: Fetch Incoming Requests");
								TestTrue("Fetch incoming requests succeeded", Response.bSuccess);
								if (!Response.bSuccess) {
									AddError(FString::Printf(TEXT("Fetch incoming requests failed: %s"), *Response.ResponseStr));
								}
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																			  GameFuseFriends->GetIncomingFriendRequests(FetchCallback)));

							// Accept the friend request
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
								const TArray<FGFFriendRequest>& IncomingRequests = GameFuseFriends->GetIncomingRequests();
								TestEqual("Should have exactly one incoming request", IncomingRequests.Num(), 1);
								if (IncomingRequests.Num() != 1) {
									AddError(FString::Printf(TEXT("Expected 1 incoming request, got %d"), IncomingRequests.Num()));
									return true;
								}

								// Verify incoming request details
								const FGFFriendRequest& Request = IncomingRequests[0];
								TestEqual("Incoming request OriginUserId", Request.OriginUserId, UserData1->Id);
								TestEqual("Incoming request OriginUsername", Request.OriginUsername, UserData1->Username);
								TestTrue("FriendshipId should be valid", Request.FriendshipId > 0);

								FGFApiCallback AcceptCallback;
								AcceptCallback.AddLambda([this](const FGFAPIResponse& Response) {
									AddInfo("UnfriendPlayer 5 :: Accept Request");
									TestTrue("Accept friend request succeeded", Response.bSuccess);
									if (!Response.bSuccess) {
										AddError(FString::Printf(TEXT("Accept friend request failed: %s"), *Response.ResponseStr));
									}
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																				  GameFuseFriends->AcceptFriendRequest(IncomingRequests[0].FriendshipId, AcceptCallback)));

								// Verify friendship was established and unfriend
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
									FGFApiCallback FriendsCallback;
									FriendsCallback.AddLambda([this](const FGFAPIResponse& Response) {
										AddInfo("UnfriendPlayer 6 :: Verify Friends List");
										TestTrue("Get friends list succeeded", Response.bSuccess);
										if (!Response.bSuccess) {
											AddError(FString::Printf(TEXT("Get friends list failed: %s"), *Response.ResponseStr));
										}
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																					  GameFuseFriends->GetFriendsList(FriendsCallback)));

									ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
										const TArray<FGFUserData>& Friends = GameFuseFriends->GetFriends();
										TestEqual("Should have exactly one friend", Friends.Num(), 1);
										if (Friends.Num() != 1) {
											AddError(FString::Printf(TEXT("Expected 1 friend, got %d"), Friends.Num()));
											return true;
										}

										// Verify friend details and unfriend
										const FGFUserData& Friend = Friends[0];
										TestEqual("Friend Id", Friend.Id, UserData1->Id);
										TestEqual("Friend Username", Friend.Username, UserData1->Username);

										FGFApiCallback UnfriendCallback;
										UnfriendCallback.AddLambda([this](const FGFAPIResponse& Response) {
											AddInfo("UnfriendPlayer 7 :: Unfriend Player");
											TestTrue("Unfriend player succeeded", Response.bSuccess);
											if (!Response.bSuccess) {
												AddError(FString::Printf(TEXT("Unfriend player failed: %s"), *Response.ResponseStr));
											}
										});

										ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																						  GameFuseFriends->UnfriendPlayer(Friend.Id, UnfriendCallback)));

										// Verify friend was removed
										ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
											FGFApiCallback VerifyCallback;
											VerifyCallback.AddLambda([this](const FGFAPIResponse& Response) {
												AddInfo("UnfriendPlayer 8 :: Verify Friend Removed");
												TestTrue("Get friends list succeeded", Response.bSuccess);
												if (!Response.bSuccess) {
													AddError(FString::Printf(TEXT("Get friends list failed: %s"), *Response.ResponseStr));
												}
											});

											ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseFriends->GetRequestHandler(),
																							  GameFuseFriends->GetFriendsList(VerifyCallback)));

											ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
												TestEqual("Should have no friends", GameFuseFriends->GetFriends().Num(), 0);
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
					return true;
				}));
				return true;
			}));
		});
	});
}

#endif