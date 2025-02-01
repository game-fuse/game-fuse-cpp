#include "Library/GameFuseLog.h"
#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Engine/GameInstance.h"
#include "Subsystems/GameFuseUser.h"
#include "Subsystems/GameFuseGroups.h"
#include "Commands/TestSuiteCommands.h"
#include "Library/GameFuseStructLibrary.h"
#include "Subsystems/GameFuseManager.h"

BEGIN_DEFINE_SPEC(FGameFuseGroupsSpec, "GameFuseTests.GameFuseGroups",
				  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
UGameFuseManager* GameFuseManager;
UGameFuseGroups* GameFuseGroups;
UGameFuseUser* GameFuseUser;
UGameInstance* GameInstance;
UTestAPIHandler* TestAPIHandler;
TSharedPtr<FGFGameData> GameData;
TSharedPtr<FGFUserData> UserData1;
TSharedPtr<FGFUserData> UserData2;
TSharedPtr<FGFGroupConnection> TestConnectionData;
int32 ConnectionId;
bool bCleanupSuccess;
END_DEFINE_SPEC(FGameFuseGroupsSpec);

void FGameFuseGroupsSpec::Define()
{
	UE_LOG(LogGameFuse, Log, TEXT("GameFuseGroupsSpec::DEFINE was called"));

	// Setup
	GameInstance = NewObject<UGameInstance>();
	GameInstance->Init();

	// Get subsystems and test api handler
	GameFuseManager = GameInstance->GetSubsystem<UGameFuseManager>();
	GameFuseUser = GameInstance->GetSubsystem<UGameFuseUser>();
	GameFuseGroups = GameInstance->GetSubsystem<UGameFuseGroups>();
	TestAPIHandler = NewObject<UTestAPIHandler>();

	// Init testing data
	GameData = MakeShared<FGFGameData>();
	UserData1 = MakeShared<FGFUserData>();
	UserData2 = MakeShared<FGFUserData>();
	TestConnectionData = MakeShared<FGFGroupConnection>();
	// TODO:: before each works outside of a describe block?? can update others to reduce repetition
	// TODO: add test for manage group membership requests


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

	It("creates a group", [this]() {
		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
			if (!GameFuseUser->IsSignedIn()) {
				UE_LOG(LogGameFuse, Warning, TEXT("creates a group :: Waiting for first user signin..."));
				return false; // Keep waiting
			}
			UE_LOG(LogGameFuse, Log, TEXT("creates a group :: First user signed in successfully"));
			return true;
		}));
		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
			FGFGroup GroupData;
			GroupData.Name = "Test Group";
			GroupData.GroupType = "Test";
			GroupData.MaxGroupSize = 10;
			GroupData.bCanAutoJoin = true;
			GroupData.bIsInviteOnly = false;
			GroupData.bSearchable = true;

			FGFGroupCallback TypedCallback;
			TypedCallback.BindLambda([this](const FGFGroup& CreatedGroup) {
				AddInfo("CreateGroup :: Create and Verify Group");
				TestTrue("Group has valid id", CreatedGroup.Id != 0);
				TestEqual("Group has correct name", CreatedGroup.Name, "Test Group");
				TestEqual("Group has correct type", CreatedGroup.GroupType, "Test");
				TestEqual("Group has correct max size", CreatedGroup.MaxGroupSize, 10);
				TestTrue("Group can auto join", CreatedGroup.bCanAutoJoin);
				TestFalse("Group is not invite only", CreatedGroup.bIsInviteOnly);
				TestTrue("Group is searchable", CreatedGroup.bSearchable);

				// Verify internal state matches callback data
				const TArray<FGFGroup>& AllGroups = GameFuseGroups->GetAllGroups();
				TestTrue("Group is stored internally", AllGroups.Contains(CreatedGroup));
			});

			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
															  GameFuseGroups->CreateGroup(GroupData, TypedCallback)));
			return true;
		}));
	});

	It("fetches all groups", [this]() {
		// First create two test groups
		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
			// Create first group
			FGFGroup Group1Data;
			Group1Data.Name = "Test Group 1 for FetchAll";
			Group1Data.GroupType = "Test";
			Group1Data.MaxGroupSize = 10;
			Group1Data.bCanAutoJoin = true;
			Group1Data.bSearchable = true;

			FGFGroupCallback CreateCallback1;
			CreateCallback1.BindLambda([this](const FGFGroup& CreatedGroup) {
				AddInfo("FetchAllGroups 1 :: Create First Group");
				TestTrue("Created group 1 has valid id", CreatedGroup.Id != 0);
				TestEqual("Created group 1 has correct name", CreatedGroup.Name, "Test Group 1 for FetchAll");
			});

			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
															  GameFuseGroups->CreateGroup(Group1Data, CreateCallback1)));

			// Create second group with different settings
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFGroup Group2Data;
				Group2Data.Name = "Test Group 2 for FetchAll";
				Group2Data.GroupType = "Clan";
				Group2Data.MaxGroupSize = 20;
				Group2Data.bCanAutoJoin = false;
				Group2Data.bIsInviteOnly = true;
				Group2Data.bSearchable = true;

				FGFGroupCallback CreateCallback2;
				CreateCallback2.BindLambda([this](const FGFGroup& CreatedGroup) {
					AddInfo("FetchAllGroups 2 :: Create Second Group");
					TestTrue("Created group 2 has valid id", CreatedGroup.Id != 0);
					TestEqual("Created group 2 has correct name", CreatedGroup.Name, "Test Group 2 for FetchAll");
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
															  GameFuseGroups->CreateGroup(Group2Data, CreateCallback2)));

				// After creating both groups, fetch all groups to verify
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
					FGFGroupListCallback FetchCallback;
					FetchCallback.BindLambda([this](const TArray<FGFGroup>& Groups) {
						AddInfo("FetchAllGroups 3 :: Verify Groups List");
						TestTrue("Has at least two groups", Groups.Num() >= 2);
						TestEqual("Internal storage matches callback data", Groups, GameFuseGroups->GetAllGroups());

						// Find our created groups in the list
						bool bFoundGroup1 = false;
						bool bFoundGroup2 = false;
						for (const FGFGroup& Group : Groups) {
							TestTrue("Each group has valid id", Group.Id != 0);
							TestFalse("Each group has name", Group.Name.IsEmpty());
							TestFalse("Each group has type", Group.GroupType.IsEmpty());

							if (Group.Name == "Test Group 1 for FetchAll") {
								bFoundGroup1 = true;
								TestEqual("Group 1 has correct type", Group.GroupType, "Test");
								TestEqual("Group 1 has correct max size", Group.MaxGroupSize, 10);
								TestTrue("Group 1 can auto join", Group.bCanAutoJoin);
								TestTrue("Group 1 is searchable", Group.bSearchable);
							}
							else if (Group.Name == "Test Group 2 for FetchAll") {
								bFoundGroup2 = true;
								TestEqual("Group 2 has correct type", Group.GroupType, "Clan");
								TestEqual("Group 2 has correct max size", Group.MaxGroupSize, 20);
								TestFalse("Group 2 cannot auto join", Group.bCanAutoJoin);
								TestTrue("Group 2 is invite only", Group.bIsInviteOnly);
								TestTrue("Group 2 is searchable", Group.bSearchable);
							}
						}
						TestTrue("First created group was found in list", bFoundGroup1);
						TestTrue("Second created group was found in list", bFoundGroup2);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																  GameFuseGroups->FetchAllGroups(FetchCallback)));
					return true;
				}));
				return true;
			}));
			return true;
		}));
	});

	It("requests to join a public group", [this]() {
		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
			// First create a test group
			TSharedPtr<FGFGroup> GroupData = MakeShared<FGFGroup>();
			GroupData->Name = "Test Group for Joining";
			GroupData->GroupType = "Test";
			GroupData->MaxGroupSize = 10;
			GroupData->bCanAutoJoin = true;
			GroupData->bSearchable = true;

			FGFGroupCallback CreateCallback;
			CreateCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
				AddInfo("JoinGroup :: Create Group");
				AddErrorIfFalse(CreatedGroup.Id != 0, "Failed to create group");
				TestTrue("Created group has valid id", CreatedGroup.Id != 0);
				TestEqual("Created group has correct name", CreatedGroup.Name, "Test Group for Joining");
				TestTrue("Created group can auto join", CreatedGroup.bCanAutoJoin);

				GroupData->Id = CreatedGroup.Id;
			});

			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
															  GameFuseGroups->CreateGroup(*GroupData, CreateCallback)));

			// Sign in second user before attempting to join
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
				FGFApiCallback SignInCallback;
				SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("JoinGroup :: Sign In Second User");
					TestTrue("Second user sign in succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Second user sign in failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

				// After signing in, attempt to join the group
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
					// After creating group, attempt to join it
					FGFGroupConnectionCallback JoinCallback;
					JoinCallback.BindLambda([this, GroupData](const FGFGroupConnection& Connection) {
						AddInfo("JoinGroup :: Request to Join");
						AddErrorIfFalse(Connection.Id != 0, "Failed to join group");
						TestTrue("Connection has valid id", Connection.Id != 0);
						TestEqual("Connection has correct user id", Connection.User.Id, UserData2->Id);
						TestNotEqual("Connection has status", Connection.Status, EGFInviteRequestStatus::None);

						// Verify the connection was successful
						TestTrue("Connection status indicates success",
								 Connection.Status == EGFInviteRequestStatus::Pending ||
								 Connection.Status == EGFInviteRequestStatus::Accepted);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																	  GameFuseGroups->RequestToJoinGroup(GroupData->Id, JoinCallback)));
					return true;
				}));
				return true;
			}));
			return true;
		}));
	});

	It("accepts a request to join a group", [this] {
		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
			// First create a test group with invite only
			TSharedPtr<FGFGroup> GroupData = MakeShared<FGFGroup>();
			GroupData->Name = "Test Group for Join Request Accept";
			GroupData->GroupType = "Test";
			GroupData->MaxGroupSize = 10;
			GroupData->bCanAutoJoin = false;
			GroupData->bIsInviteOnly = true;
			GroupData->bSearchable = true;

			FGFGroupCallback CreateCallback;
			CreateCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
				AddInfo("AcceptJoinRequest 1 :: Create Group");
				TestTrue("Created group has valid id", CreatedGroup.Id != 0);
				TestEqual("Created group has correct name", CreatedGroup.Name, "Test Group for Join Request Accept");
				TestFalse("Created group cannot auto join", CreatedGroup.bCanAutoJoin);
				TestTrue("Created group is invite only", CreatedGroup.bIsInviteOnly);

				GroupData->Id = CreatedGroup.Id;
			});

			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
															  GameFuseGroups->CreateGroup(*GroupData, CreateCallback)));

			// Sign in second user to request joining
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
				FGFApiCallback SignInCallback;
				SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("AcceptJoinRequest 2 :: Sign In Second User");
					TestTrue("Second user sign in succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Second user sign in failed: %s"), *Response.ResponseStr));
					}
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

				// After signing in, request to join the group
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
					FGFGroupConnectionCallback RequestCallback;
					RequestCallback.BindLambda([this](const FGFGroupConnection& Connection) {
						AddInfo("AcceptJoinRequest 3 :: Request to Join");
						TestTrue("Connection has valid id", Connection.Id != 0);
						TestEqual("Connection has correct user id", Connection.User.Id, UserData2->Id);
						TestEqual("Connection status is pending", Connection.Status, EGFInviteRequestStatus::Pending);

						// Store the connection data for later use
						TestConnectionData = MakeShared<FGFGroupConnection>(Connection);
						UE_LOG(LogGameFuse, Log, TEXT("Stored connection data - ID: %d, User ID: %d"), TestConnectionData->Id, TestConnectionData->User.Id);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																	  GameFuseGroups->RequestToJoinGroup(GroupData->Id, RequestCallback)));

					// Sign back in as first user to accept the request
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFApiCallback SignInCallback;
						SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
							AddInfo("AcceptJoinRequest 4 :: Sign In First User");
							TestTrue("First user sign in succeeded", Response.bSuccess);
							if (!Response.bSuccess) {
								AddError(FString::Printf(TEXT("First user sign in failed: %s"), *Response.ResponseStr));
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->SignIn(UserData1->Username + "@gamefuse.com", "password", SignInCallback)));

						// Accept the join request using the stored connection data
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							if (!TestConnectionData.IsValid()) {
								AddError("Connection data is not valid");
								return true;
							}

							UE_LOG(LogGameFuse, Log, TEXT("Using connection data - ID: %d, User ID: %d"), TestConnectionData->Id, TestConnectionData->User.Id);

							FGFGroupActionCallback AcceptCallback;
							AcceptCallback.BindLambda([this](bool bSuccess) {
								AddInfo("AcceptJoinRequest 5 :: Accept Request");
								TestTrue("Accept join request succeeded", bSuccess);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																			  GameFuseGroups->RespondToGroupJoinRequest(TestConnectionData->Id, TestConnectionData->User.Id, EGFInviteRequestStatus::Accepted, AcceptCallback)));
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

	It("declines a request to join a group", [this]() {
		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
			// First create a test group with invite only
			TSharedPtr<FGFGroup> GroupData = MakeShared<FGFGroup>();
			GroupData->Name = "Test Group for Join Request Decline";
			GroupData->GroupType = "Test";
			GroupData->MaxGroupSize = 10;
			GroupData->bCanAutoJoin = false;
			GroupData->bIsInviteOnly = true;
			GroupData->bSearchable = true;

			FGFGroupCallback CreateCallback;
			CreateCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
				AddInfo("DeclineJoinRequest 1 :: Create Group");
				TestTrue("Created group has valid id", CreatedGroup.Id != 0);
				TestEqual("Created group has correct name", CreatedGroup.Name, "Test Group for Join Request Decline");
				TestFalse("Created group cannot auto join", CreatedGroup.bCanAutoJoin);
				TestTrue("Created group is invite only", CreatedGroup.bIsInviteOnly);

				GroupData->Id = CreatedGroup.Id;
			});

			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
															  GameFuseGroups->CreateGroup(*GroupData, CreateCallback)));

			// Sign in second user to request joining
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
				FGFApiCallback SignInCallback;
				SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
					AddInfo("DeclineJoinRequest 2 :: Sign In Second User");
					TestTrue("Second user sign in succeeded", Response.bSuccess);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

				// After signing in, request to join the group
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
					FGFGroupConnectionCallback RequestCallback;
					RequestCallback.BindLambda([this](const FGFGroupConnection& Connection) {
						AddInfo("DeclineJoinRequest 3 :: Request to Join");
						TestTrue("Connection has valid id", Connection.Id != 0);
						TestEqual("Connection has correct user id", Connection.User.Id, UserData2->Id);
						TestEqual("Connection status is pending", Connection.Status, EGFInviteRequestStatus::Pending);

						// Store the connection data for later use
						TestConnectionData = MakeShared<FGFGroupConnection>(Connection);
						UE_LOG(LogGameFuse, Log, TEXT("Stored connection data - ID: %d, User ID: %d"), TestConnectionData->Id, TestConnectionData->User.Id);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																	  GameFuseGroups->RequestToJoinGroup(GroupData->Id, RequestCallback)));

					// Sign back in as first user to decline the request
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFApiCallback SignInCallback;
						SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
							AddInfo("DeclineJoinRequest 4 :: Sign In First User");
							TestTrue("First user sign in succeeded", Response.bSuccess);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->SignIn(UserData1->Username + "@gamefuse.com", "password", SignInCallback)));

						// Decline the join request using the stored connection data
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							if (!TestConnectionData.IsValid()) {
								AddError("Connection data is not valid");
								return true;
							}

							UE_LOG(LogGameFuse, Log, TEXT("Using connection data - ID: %d, User ID: %d"), TestConnectionData->Id, TestConnectionData->User.Id);

							FGFGroupActionCallback DeclineCallback;
							DeclineCallback.BindLambda([this](bool bSuccess) {
								AddInfo("DeclineJoinRequest 5 :: Decline Request");
								TestTrue("Decline join request succeeded", bSuccess);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																			  GameFuseGroups->RespondToGroupJoinRequest(TestConnectionData->Id, TestConnectionData->User.Id, EGFInviteRequestStatus::Declined, DeclineCallback)));
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


	Describe("Group Attributes", [this]() {
		It("creates and fetches group attributes", [this]() {
			TSharedPtr<FGFGroup> GroupData = MakeShared<FGFGroup>();
			GroupData->Name = TEXT("Stormwind Raiders");
			GroupData->GroupType = TEXT("Clan");
			GroupData->MaxGroupSize = 50;
			GroupData->bCanAutoJoin = false;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
				FGFGroupCallback CreateGroupCallback;
				CreateGroupCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
					AddInfo("CreateAndFetchAttributes 1 :: Create Group");
					TestTrue("Group created successfully", CreatedGroup.Id > 0);
					GroupData->Id = CreatedGroup.Id;
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																  GameFuseGroups->CreateGroup(*GroupData, CreateGroupCallback)));

				// After creating clan, add clan level (admin-only editable)
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
					TSharedPtr<FGFGroupAttribute> ClanLevelAttribute = MakeShared<FGFGroupAttribute>();
					ClanLevelAttribute->Key = TEXT("clan_level");
					ClanLevelAttribute->Value = TEXT("10");
					ClanLevelAttribute->CreatorId = GroupData->Id; // Used as group ID when creating

					FGFGroupAttributeCallback AddLevelCallback;
					AddLevelCallback.BindLambda([this, ClanLevelAttribute](const TArray<FGFGroupAttribute>& Attributes) {
						AddInfo("CreateAndFetchAttributes 2 :: Add Attribute 1");
						TestTrue("attribute 1 added successfully", Attributes.Num() > 0);
						if (Attributes.Num() > 0) {
							const FGFGroupAttribute& Attribute = Attributes[0];
							TestEqual("has correct key", Attribute.Key, TEXT("clan_level"));
							TestEqual("has correct value", Attribute.Value, TEXT("10"));
							TestEqual("has correct creator ID", Attribute.CreatorId, UserData1->Id); // CreatorId is the creating user's ID in response
							TestTrue("admin can edit", Attribute.bCanEdit);

							ClanLevelAttribute->Id = Attribute.Id;
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																	  GameFuseGroups->AddAttribute(GroupData->Id, *ClanLevelAttribute, true, AddLevelCallback)));

					// After adding level, add motto
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
						FGFGroupAttribute ClanMottoAttribute;
						ClanMottoAttribute.Key = TEXT("clan_motto");
						ClanMottoAttribute.Value = TEXT("For Honor and Glory!");
						ClanMottoAttribute.CreatorId = GroupData->Id; // Used as group ID when creating

						FGFGroupAttributeCallback AddMottoCallback;
						AddMottoCallback.BindLambda([this](const TArray<FGFGroupAttribute>& Attributes) {
							AddInfo("CreateAndFetchAttributes 3 :: Add Attribute 2");
							TestTrue("attribute added successfully", Attributes.Num() > 0);
							if (Attributes.Num() > 0) {
								const FGFGroupAttribute& Attribute = Attributes[0];
								TestEqual("attribute has correct key", Attribute.Key, TEXT("clan_motto"));
								TestEqual("attribute has correct value", Attribute.Value, TEXT("For Honor and Glory!"));
								TestEqual("has correct creator ID", Attribute.CreatorId, UserData1->Id); // CreatorId is the creating user's ID in response
								TestTrue("attribute is member-editable", Attribute.bCanEdit);
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																		  GameFuseGroups->AddAttribute(GroupData->Id, ClanMottoAttribute, false, AddMottoCallback)));

						// After setting attributes, fetch the clan to verify
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
							FGFGroupAttributeCallback FetchCallback;
							FetchCallback.BindLambda([this](const TArray<FGFGroupAttribute>& Attributes) {
								AddInfo("CreateAndFetchAttributes 4 :: Verify Group Attributes");
								TestTrue("Group has attributes", Attributes.Num() > 0);
								TestEqual("Group has correct number of attributes", Attributes.Num(), 2);

								// Verify attribute values and metadata
								bool bFoundLevel = false;
								bool bFoundMotto = false;

								for (const auto& Attribute : Attributes) {
									TestTrue("Attribute has valid ID", Attribute.Id > 0);
									TestEqual("Creator ID matches user ID", Attribute.CreatorId, UserData1->Id);

									if (Attribute.Key == TEXT("clan_level")) {
										bFoundLevel = true;
										TestEqual("attribute 1 has correct value", Attribute.Value, TEXT("10"));
										TestTrue("attribute 1 is admin-only editable", Attribute.bCanEdit); // still the same user, TODO: add another test for different user to check if it's admin-only
									} else if (Attribute.Key == TEXT("clan_motto")) {
										bFoundMotto = true;
										TestEqual("attribute 2 has correct value", Attribute.Value, TEXT("For Honor and Glory!"));
										TestTrue("attribute 2 is member-editable", Attribute.bCanEdit);
									}
								}

								TestTrue("Found attribute 1", bFoundLevel);
								TestTrue("Found attribute 2", bFoundMotto);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																			  GameFuseGroups->FetchGroupAttributes(GroupData->Id, FetchCallback)));
							return true;
						}));
						return true;
					}));
					return true;
				}));
				return true;
			}));
		});

		It("modifies group attributes", [this]() {
			TSharedPtr<FGFGroup> GroupData = MakeShared<FGFGroup>();
			GroupData->Name = TEXT("Ironforge Defenders");
			GroupData->GroupType = TEXT("Clan");
			GroupData->MaxGroupSize = 50;
			GroupData->bCanAutoJoin = false;

			// Create a shared attribute to use across all operations
			TSharedPtr<FGFGroupAttribute> TerritoryAttribute = MakeShared<FGFGroupAttribute>();
			TerritoryAttribute->Key = TEXT("home_territory");
			TerritoryAttribute->Value = TEXT("Dun Morogh");

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, TerritoryAttribute]() -> bool {
				FGFGroupCallback CreateGroupCallback;
				CreateGroupCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
					AddInfo("ModifyAttributes 1 :: Create Group");
					TestTrue("Group created successfully", CreatedGroup.Id > 0);
					GroupData->Id = CreatedGroup.Id;
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																  GameFuseGroups->CreateGroup(*GroupData, CreateGroupCallback)));

				// After creating group, set home territory (member-editable)
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, TerritoryAttribute]() -> bool {
					// Set the group ID for the request
					TerritoryAttribute->CreatorId = GroupData->Id; // Used as group ID when creating

					FGFGroupAttributeCallback AddAttributeCallback;
					AddAttributeCallback.BindLambda([this, TerritoryAttribute](const TArray<FGFGroupAttribute>& Attributes) {
						AddInfo("ModifyAttributes 2 :: Add Attribute");
						TestTrue("attribute added successfully", Attributes.Num() > 0);
						if (Attributes.Num() > 0) {
							const FGFGroupAttribute& Attribute = Attributes[0];
							TestEqual("attribute has correct key", Attribute.Key, TEXT("home_territory"));
							TestEqual("attribute has correct value", Attribute.Value, TEXT("Dun Morogh"));
							TestEqual("has correct creator ID", Attribute.CreatorId, UserData1->Id); // CreatorId is the creating user's ID in response TODO:: get api changed to return both user and group ids
							TestTrue("attribute is member-editable", Attribute.bCanEdit);

							// Store the attribute ID for the update
							TerritoryAttribute->Id = Attribute.Id;
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																	  GameFuseGroups->AddAttribute(GroupData->Id, *TerritoryAttribute, false, AddAttributeCallback)));

					// After adding territory, update it
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, TerritoryAttribute]() -> bool {
						// Update the value for the next request
						TerritoryAttribute->Value = TEXT("Ironforge");

						FGFGroupActionCallback UpdateAttributeCallback;
						// TODO:: replace this once the response is consistent with the other group attribute responses
						UpdateAttributeCallback.BindLambda([this](bool bSuccess) {
							AddInfo("ModifyAttributes 3 :: Update Attribute");
							TestTrue("attribute updated successfully", bSuccess);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																		  GameFuseGroups->UpdateGroupAttribute(GroupData->Id, *TerritoryAttribute, UpdateAttributeCallback)));

						// After updating attribute, fetch the clan to verify
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
							FGFGroupAttributeCallback FetchCallback;
							FetchCallback.BindLambda([this](const TArray<FGFGroupAttribute>& Attributes) {
								AddInfo("ModifyAttributes 4 :: Verify Group Attributes");
								TestTrue("Group has attributes", Attributes.Num() > 0);
								TestEqual("Group has correct number of attributes", Attributes.Num(), 1);

								if (Attributes.Num() > 0) {
									const FGFGroupAttribute& Attribute = Attributes[0];
									TestTrue("Attribute has valid ID", Attribute.Id > 0);
									TestEqual("Creator ID matches user ID", Attribute.CreatorId, UserData1->Id);
									TestEqual("attribute has correct key", Attribute.Key, TEXT("home_territory"));
									TestEqual("attribute has updated value", Attribute.Value, TEXT("Ironforge"));
									TestTrue("attribute is member-editable", Attribute.bCanEdit);
								}
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																			  GameFuseGroups->FetchGroupAttributes(GroupData->Id, FetchCallback)));
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