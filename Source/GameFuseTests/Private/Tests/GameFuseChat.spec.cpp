#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Engine/GameInstance.h"
#include "Subsystems/GameFuseUser.h"
#include "Subsystems/GameFuseChat.h"
#include "Commands/TestSuiteCommands.h"
#include "Library/GameFuseStructLibrary.h"
#include "Subsystems/GameFuseManager.h"
#include "Library/GameFuseLog.h"

BEGIN_DEFINE_SPEC(GameFuseChatSpec, "GameFuseTests.GameFuseChat",
				  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
UGameFuseManager* GameFuseManager;
UGameFuseUser* GameFuseUser;
UGameFuseChat* GameFuseChat;
UGameInstance* GameInstance;
UTestAPIHandler* TestAPIHandler;
TSharedPtr<FGFGameData> GameData;
TSharedPtr<FGFUserData> UserData1;
TSharedPtr<FGFUserData> UserData2;
TSharedPtr<FGFUserData> UserData3;
bool bCleanupSuccess;
FGFChat ChatToVerify;
END_DEFINE_SPEC(GameFuseChatSpec);

void GameFuseChatSpec::Define()
{
	UE_LOG(LogGameFuse, Log, TEXT("GameFuseChat::DEFINE was called"));
	// Setup
	GameInstance = NewObject<UGameInstance>();
	GameInstance->Init();

	// Get subsystems/ test api handler
	GameFuseManager = GameInstance->GetSubsystem<UGameFuseManager>();
	GameFuseUser = GameInstance->GetSubsystem<UGameFuseUser>();
	GameFuseChat = GameInstance->GetSubsystem<UGameFuseChat>();
	TestAPIHandler = NewObject<UTestAPIHandler>();

	// init testing data
	GameData = MakeShared<FGFGameData>();
	UserData1 = MakeShared<FGFUserData>();
	UserData2 = MakeShared<FGFUserData>();
	UserData3 = MakeShared<FGFUserData>();
	bCleanupSuccess = false;

	Describe("GameFuseChat", [this]() {
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

			// Create third user for group chat testing
			ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, UserData3, this, FGuid()));
		});

		It("creates a chat with initial message", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFChatCallback CreateCallback;
				CreateCallback.BindLambda([this](const FGFChat& Chat) {
					AddInfo("CreateChat :: Create Chat with Message");
					TestTrue("Chat has valid id", Chat.Id > 0);
					TestEqual("Chat creator id matches user", Chat.CreatorId, UserData1->Id);
					TestEqual("Chat has correct creator type", Chat.CreatorType, "user");
					TestTrue("Chat has participants", Chat.Participants.Num() == 2);

					// Verify initial message
					if (Chat.Messages.Num() > 0) {
						const FGFMessage& InitialMessage = Chat.Messages[0];
						TestEqual("Initial message text matches", InitialMessage.Text, "Hello! Let's chat!");
						TestEqual("Message sender id matches", InitialMessage.UserId, UserData1->Id);
						TestFalse("Initial message is unread", InitialMessage.bRead);
					}
				});

				// Create array of usernames for the chat
				TArray<FString> Usernames;
				Usernames.Add(UserData2->Username);

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																  GameFuseChat->CreateChat(Usernames, "Hello! Let's chat!", CreateCallback)));
				return true;
			}));
		});

		It("creates a group chat with three users", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFChatCallback CreateCallback;
				CreateCallback.BindLambda([this](const FGFChat& Chat) {
					AddInfo("CreateGroupChat :: Create Chat with Message");
					TestTrue("Chat has valid id", Chat.Id > 0);
					TestEqual("Chat creator id matches user", Chat.CreatorId, UserData1->Id);
					TestEqual("Chat creator type", Chat.CreatorType, "user");
					TestEqual("Chat has three participants", Chat.Participants.Num(), 3);

					// Store chat ID for later verification
					ChatToVerify = Chat;

					// Verify participants include all three users
					bool bFoundUser1 = false;
					bool bFoundUser2 = false;
					bool bFoundUser3 = false;

					for (const FGFUserData& Participant : Chat.Participants) {
						if (Participant.Id == UserData1->Id) bFoundUser1 = true;
						if (Participant.Id == UserData2->Id) bFoundUser2 = true;
						if (Participant.Id == UserData3->Id) bFoundUser3 = true;
					}

					TestTrue("First user is in participants", bFoundUser1);
					TestTrue("Second user is in participants", bFoundUser2);
					TestTrue("Third user is in participants", bFoundUser3);

					// Verify initial message
					if (Chat.Messages.Num() > 0) {
						const FGFMessage& InitialMessage = Chat.Messages[0];
						TestEqual("Initial message text matches", InitialMessage.Text, "Welcome to the group chat!");
						TestEqual("Message sender id matches", InitialMessage.UserId, UserData1->Id);
					}
				});

				// Create array of usernames for the group chat
				TArray<FString> Usernames;
				Usernames.Add(UserData2->Username);
				Usernames.Add(UserData3->Username);

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																  GameFuseChat->CreateChat(Usernames, "Welcome to the group chat!", CreateCallback)));

				// Sign in second user and verify they can see the chat
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFApiCallback SignInCallback;
					SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("CreateGroupChat :: Sign In Second User");
						TestTrue("Second user sign in succeeded", Response.bSuccess);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

					// Fetch chats for second user
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFChatListCallback FetchCallback;
						FetchCallback.BindLambda([this](const TArray<FGFChat>& Chats) {
							AddInfo("CreateGroupChat :: Verify Second User Can See Chat");
							bool bFoundChat = false;
							for (const FGFChat& Chat : Chats) {
								if (Chat.Id == ChatToVerify.Id) {
									bFoundChat = true;
									TestEqual("Chat has same creator", Chat.CreatorId, UserData1->Id);
									TestEqual("Chat has same participants count", Chat.Participants.Num(), 3);
									if (Chat.Messages.Num() > 0) {
										TestEqual("Initial message matches", Chat.Messages[0].Text, "Welcome to the group chat!");
									}
									break;
								}
							}
							TestTrue("Second user can see the group chat", bFoundChat);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																		  GameFuseChat->FetchAllChats(1)));

						// Sign in third user and verify they can see the chat
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFApiCallback SignInCallback;
							SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
								AddInfo("CreateGroupChat :: Sign In Third User");
								TestTrue("Third user sign in succeeded", Response.bSuccess);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->SignIn(UserData3->Username + "@gamefuse.com", "password", SignInCallback)));

							// Fetch chats for third user
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
								FGFChatListCallback FetchCallback;
								FetchCallback.BindLambda([this](const TArray<FGFChat>& Chats) {
									AddInfo("CreateGroupChat :: Verify Third User Can See Chat");
									bool bFoundChat = false;
									for (const FGFChat& Chat : Chats) {
										if (Chat.Id == ChatToVerify.Id) {
											bFoundChat = true;
											TestEqual("Chat has same creator", Chat.CreatorId, UserData1->Id);
											TestEqual("Chat has same participants count", Chat.Participants.Num(), 3);
											if (Chat.Messages.Num() > 0) {
												TestEqual("Initial message matches", Chat.Messages[0].Text, "Welcome to the group chat!");
											}
											break;
										}
									}
									TestTrue("Third user can see the group chat", bFoundChat);
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																				  GameFuseChat->FetchAllChats(1)));
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

		It("sends a message to an existing chat", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// First create a chat
				FGFChatCallback CreateCallback;
				CreateCallback.BindLambda([this](const FGFChat& Chat) {
					AddInfo("SendMessage :: Create Initial Chat");
					TestTrue("Chat has valid id", Chat.Id > 0);
					ChatToVerify = Chat;
				});

				TArray<FString> Usernames;
				Usernames.Add(UserData2->Username);

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																  GameFuseChat->CreateChat(Usernames, "Initial message", CreateCallback)));

				// Sign in second user to send a message
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFApiCallback SignInCallback;
					SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("SendMessage :: Sign In Second User");
						TestTrue("Second user sign in succeeded", Response.bSuccess);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

					// Send a message as second user
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFMessageCallback SendCallback;
						SendCallback.BindLambda([this](const FGFMessage& Message) {
							AddInfo("SendMessage :: Send Reply Message");
							TestEqual("Message text matches", Message.Text, "Reply from User 2");
							TestEqual("Message sender id matches", Message.UserId, UserData2->Id);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																		  GameFuseChat->SendMessage(ChatToVerify.Id, "Reply from User 2", SendCallback)));

						// Fetch the chat to verify both messages
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFChatListCallback FetchCallback;
							FetchCallback.BindLambda([this](const TArray<FGFChat>& Chats) {
								AddInfo("SendMessage :: Verify Both Messages");
								bool bFoundChat = false;
								for (const FGFChat& Chat : Chats) {
									if (Chat.Id == ChatToVerify.Id) {
										bFoundChat = true;
										TestEqual("Chat has two messages", Chat.Messages.Num(), 2);
										if (Chat.Messages.Num() == 2) {
											// messages are in reverse order (0 is newest)
											FGFMessage InitialMessage = Chat.Messages[1];
											FGFMessage ReplyMessage = Chat.Messages[0];
											TestEqual("First message is initial message", InitialMessage.Text, "Initial message");
											TestEqual("First message sender is User 1", InitialMessage.UserId, UserData1->Id);
											TestEqual("Second message is reply", ReplyMessage.Text, "Reply from User 2");
											TestEqual("Second message sender is User 2", ReplyMessage.UserId, UserData2->Id);
										}
										break;
									}
								}
								TestTrue("Found chat with both messages", bFoundChat);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																			  GameFuseChat->FetchAllChats(1)));
							return true;
						}));
						return true;
					}));
					return true;
				}));
				return true;
			}));
		});

		It("fetches chats with pagination", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// Create multiple chats to test pagination
				FGFChatCallback CreateCallback1;
				CreateCallback1.BindLambda([this](const FGFChat& Chat) {
					AddInfo("Pagination :: Create First Chat");
					TestTrue("First chat has valid id", Chat.Id > 0);
				});

				TArray<FString> Usernames;
				Usernames.Add(UserData2->Username);

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																  GameFuseChat->CreateChat(Usernames, "Chat 1", CreateCallback1)));

				// Create second chat
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, Usernames]() -> bool {
					FGFChatCallback CreateCallback2;
					CreateCallback2.BindLambda([this](const FGFChat& Chat) {
						AddInfo("Pagination :: Create Second Chat");
						TestTrue("Second chat has valid id", Chat.Id > 0);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																	  GameFuseChat->CreateChat(Usernames, "Chat 2", CreateCallback2)));

					// Fetch first page
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFChatListCallback FetchCallback1;
						FetchCallback1.BindLambda([this](const TArray<FGFChat>& Chats) {
							AddInfo("Pagination :: Fetch First Page");
							TestTrue("First page has chats", Chats.Num() > 0);
							for (const FGFChat& Chat : Chats) {
								TestTrue("Chat has valid id", Chat.Id > 0);
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																		  GameFuseChat->FetchAllChats(1)));

						// Fetch second page
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFChatListCallback FetchCallback2;
							FetchCallback2.BindLambda([this](const TArray<FGFChat>& Chats) {
								AddInfo("Pagination :: Fetch Second Page");
								// Note: Second page might be empty if all chats fit on first page
								for (const FGFChat& Chat : Chats) {
									TestTrue("Chat has valid id", Chat.Id > 0);
								}
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																			  GameFuseChat->FetchAllChats(2)));
							return true;
						}));
						return true;
					}));
					return true;
				}));
				return true;
			}));
		});

		It("fetches messages with pagination", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// First create a chat
				FGFChatCallback CreateCallback;
				CreateCallback.BindLambda([this](const FGFChat& Chat) {
					AddInfo("FetchMessages :: Create Initial Chat");
					TestTrue("Chat has valid id", Chat.Id > 0);
					ChatToVerify = Chat;
				});

				TArray<FString> Usernames;
				Usernames.Add(UserData2->Username);

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																  GameFuseChat->CreateChat(Usernames, "Initial message", CreateCallback)));

				// Sign in second user to send multiple messages
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFApiCallback SignInCallback;
					SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("FetchMessages :: Sign In Second User");
						TestTrue("Second user sign in succeeded", Response.bSuccess);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

					// Send first message
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFMessageCallback SendCallback1;
						SendCallback1.BindLambda([this](const FGFMessage& Message) {
							AddInfo("FetchMessages :: Send First Message");
							TestEqual("Message text matches", Message.Text, "Message 1");
							TestEqual("Message sender id matches", Message.UserId, UserData2->Id);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																		  GameFuseChat->SendMessage(ChatToVerify.Id, "Message 1", SendCallback1)));

						// Send second message
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							FGFMessageCallback SendCallback2;
							SendCallback2.BindLambda([this](const FGFMessage& Message) {
								AddInfo("FetchMessages :: Send Second Message");
								TestEqual("Message text matches", Message.Text, "Message 2");
								TestEqual("Message sender id matches", Message.UserId, UserData2->Id);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																			  GameFuseChat->SendMessage(ChatToVerify.Id, "Message 2", SendCallback2)));

							// Fetch first page of messages
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
								FGFMessageListCallback FetchCallback1;
								FetchCallback1.BindLambda([this](const TArray<FGFMessage>& Messages) {
									AddInfo("FetchMessages :: Fetch First Page");
									TestTrue("First page has messages", Messages.Num() > 0);
									TestEqual("Callback matches internal state", Messages, GameFuseChat->GetChatMessages());

									for (const FGFMessage& Message : Messages) {
										TestTrue("Message has valid id", Message.Id > 0);
									}
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																				  GameFuseChat->FetchMessages(ChatToVerify.Id, FetchCallback1, 1)));

								// Fetch second page
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
									FGFMessageListCallback FetchCallback2;
									FetchCallback2.BindLambda([this](const TArray<FGFMessage>& Messages) {
										AddInfo("FetchMessages :: Fetch Second Page");
										// Note: Second page might be empty if all messages fit on first page
										TestEqual("Callback matches internal state", Messages, GameFuseChat->GetChatMessages());

										for (const FGFMessage& Message : Messages) {
											TestTrue("Message has valid id", Message.Id > 0);
											TestTrue("Message is in chat messages", GameFuseChat->GetChatMessages().Contains(Message));
										}
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																					  GameFuseChat->FetchMessages(ChatToVerify.Id, FetchCallback2, 2)));
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

		It("marks messages as read", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// First create a chat
				FGFChatCallback CreateCallback;
				CreateCallback.BindLambda([this](const FGFChat& Chat) {
					AddInfo("MarkAsRead :: Create Initial Chat");
					TestTrue("Chat has valid id", Chat.Id > 0);
					ChatToVerify = Chat;

					// Verify initial message
					if (Chat.Messages.Num() > 0) {
						const FGFMessage& InitialMessage = Chat.Messages[0];
						TestEqual("Initial message text matches", InitialMessage.Text, "Initial message");
						TestEqual("Message sender id matches", InitialMessage.UserId, UserData1->Id);
					}
				});

				TArray<FString> Usernames;
				Usernames.Add(UserData2->Username);

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																  GameFuseChat->CreateChat(Usernames, "Initial message", CreateCallback)));

				// Sign in second user to send a message
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFApiCallback SignInCallback;
					SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
						AddInfo("MarkAsRead :: Sign In Second User");
						TestTrue("Second user sign in succeeded", Response.bSuccess);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

					// Verify initial message is unread for second user
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFChatListCallback FetchCallback;
						FetchCallback.BindLambda([this](const TArray<FGFChat>& Chats) {
							AddInfo("MarkAsRead :: Verify Initial Message Unread");
							bool bFoundChat = false;
							for (const FGFChat& Chat : Chats) {
								if (Chat.Id == ChatToVerify.Id) {
									bFoundChat = true;
									TestEqual("Chat has one message", Chat.Messages.Num(), 1);
									if (Chat.Messages.Num() > 0) {
										TestFalse("Initial message should be unread for second user", Chat.Messages[0].bRead);
									}
									break;
								}
							}
							TestTrue("Found chat with unread message", bFoundChat);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																		  GameFuseChat->FetchAllChats(1)));

						// Mark message as read
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																			  GameFuseChat->MarkMessageAsRead(ChatToVerify.Messages[0].Id, FGFSuccessCallback())));

							// Send a reply message
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
								FGFMessageCallback SendCallback;
								SendCallback.BindLambda([this](const FGFMessage& Message) {
									AddInfo("MarkAsRead :: Send Reply Message");
									TestEqual("Message text matches", Message.Text, "Reply from User 2");
									TestEqual("Message sender id matches", Message.UserId, UserData2->Id);
									TestTrue("Message is read by sender", Message.bRead);
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																				  GameFuseChat->SendMessage(ChatToVerify.Id, "Reply from User 2", SendCallback)));

								// Sign back in as first user
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
									FGFApiCallback SignInCallback;
									SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
										AddInfo("MarkAsRead :: Sign In First User");
										TestTrue("First user sign in succeeded", Response.bSuccess);
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																					  GameFuseUser->SignIn(UserData1->Username + "@gamefuse.com", "password", SignInCallback)));

									// Verify second message is unread
									ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
										FGFChatListCallback FetchCallback;
										FetchCallback.BindLambda([this](const TArray<FGFChat>& Chats) {
											AddInfo("MarkAsRead :: Verify Reply Message Unread");
											bool bFoundChat = false;
											for (const FGFChat& Chat : Chats) {
												if (Chat.Id == ChatToVerify.Id) {
													bFoundChat = true;
													TestEqual("Chat has two messages", Chat.Messages.Num(), 2);
													if (Chat.Messages.Num() == 2) {
														TestTrue("Initial message is read", Chat.Messages[1].bRead);
														TestFalse("Reply message should be unread", Chat.Messages[0].bRead);


														ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																										  GameFuseChat->MarkMessageAsRead(Chat.Messages[0].Id, FGFSuccessCallback())));
													}
													break;
												}
											}
											TestTrue("Found chat with unread reply", bFoundChat);
										});

										ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseChat->GetRequestHandler(),
																						  GameFuseChat->FetchAllChats(1)));
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