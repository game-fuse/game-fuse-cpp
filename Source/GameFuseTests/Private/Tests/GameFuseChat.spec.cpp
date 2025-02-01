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
	// todo: add test for message pages and limits
	// todo: test chat page limits
	// todo: add test for message read status, and read_by
	// todo: send message to existing chat
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
						TestFalse("Message is not read", InitialMessage.bRead);
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
						TestFalse("Message is not read", InitialMessage.bRead);
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
																		  GameFuseChat->FetchAllChats(FetchCallback)));

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
																				  GameFuseChat->FetchAllChats(FetchCallback)));
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