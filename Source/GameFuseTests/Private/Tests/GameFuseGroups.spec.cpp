#if WITH_AUTOMATION_TESTS

#include "Library/GameFuseLog.h"
#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Engine/GameInstance.h"
#include "Subsystems/GameFuseUser.h"
#include "Subsystems/GameFuseGroups.h"
#include "Commands/TestSuiteCommands.h"
#include "Library/GameFuseStructLibrary.h"
#include "Library/GameFuseEnumLibrary.h"
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
				const TArray<FGFGroup>& AllGroups = GameFuseGroups->GetFetchedGroups();
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
						TestEqual("Internal storage matches callback data", Groups, GameFuseGroups->GetFetchedGroups());

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
							} else if (Group.Name == "Test Group 2 for FetchAll") {
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
				FGFUserDataCallback SignInCallback;
				SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
					AddInfo("JoinGroup :: Sign In Second User");
					TestTrue("User ID should be valid", UserData.Id > 0);
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
						TestEqual("Connection has status", Connection.Status, EGFInviteRequestStatus::Accepted);

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
			GroupData->bIsInviteOnly = false;
			GroupData->bSearchable = true;

			FGFGroupCallback CreateCallback;
			CreateCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
				AddInfo("AcceptJoinRequest 1 :: Create Group");
				TestTrue("Created group has valid id", CreatedGroup.Id != 0);
				TestEqual("Created group has correct name", CreatedGroup.Name, "Test Group for Join Request Accept");
				TestFalse("Created group cannot auto join", CreatedGroup.bCanAutoJoin);
				TestFalse("Created group is not invite only", CreatedGroup.bIsInviteOnly);

				GroupData->Id = CreatedGroup.Id;
			});

			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
															  GameFuseGroups->CreateGroup(*GroupData, CreateCallback)));

			// Sign in second user to request joining
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
				FGFUserDataCallback SignInCallback;
				SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
					AddInfo("SignIn :: User Data");
					TestTrue("User ID should be valid", UserData.Id > 0);
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
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																	  GameFuseGroups->RequestToJoinGroup(GroupData->Id, RequestCallback)));

					// Sign back in as first user to accept the request
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
						FGFUserDataCallback SignInCallback;
						SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
							AddInfo("SignIn :: User Data");
							TestTrue("User ID should be valid", UserData.Id > 0);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->SignIn(UserData1->Username + "@gamefuse.com", "password", SignInCallback)));

						// Accept the join request using the stored connection data
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
							if (!TestConnectionData.IsValid()) {
								AddError("Connection data is not valid");
								return true;
							}

							if (TestConnectionData->Id == 0) {
								AddError("Cannot accept join request - connection ID is 0");
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
			GroupData->bIsInviteOnly = false;
			GroupData->bSearchable = true;

			FGFGroupCallback CreateCallback;
			CreateCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
				AddInfo("DeclineJoinRequest 1 :: Create Group");
				TestTrue("Created group has valid id", CreatedGroup.Id != 0);
				TestEqual("Created group has correct name", CreatedGroup.Name, "Test Group for Join Request Decline");
				TestFalse("Created group cannot auto join", CreatedGroup.bCanAutoJoin);
				TestFalse("Created group is not invite only", CreatedGroup.bIsInviteOnly);

				GroupData->Id = CreatedGroup.Id;
			});

			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
															  GameFuseGroups->CreateGroup(*GroupData, CreateCallback)));

			// Sign in second user to request joining
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
				FGFUserDataCallback SignInCallback;
				SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
					AddInfo("SignIn :: User Data");
					TestTrue("User ID should be valid", UserData.Id > 0);
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

				// After signing in, request to join the group
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
					FGFGroupConnectionCallback RequestCallback;
					RequestCallback.BindLambda([this](const FGFGroupConnection& Connection) {
						AddInfo("DeclineJoinRequest 3 :: Request to Join");
						if (Connection.Id == 0) {
							AddError("Join request failed - connection ID is 0");
							return;
						}
						TestTrue("Connection has valid id", Connection.Id != 0);
						TestEqual("Connection has correct user id", Connection.User.Id, UserData2->Id);
						TestEqual("Connection status is pending", Connection.Status, EGFInviteRequestStatus::Pending);

						// Store the connection data for later use
						TestConnectionData = MakeShared<FGFGroupConnection>(Connection);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																	  GameFuseGroups->RequestToJoinGroup(GroupData->Id, RequestCallback)));

					// Sign back in as first user to decline the request
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
						FGFUserDataCallback SignInCallback;
						SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
							AddInfo("SignIn :: User Data");
							TestTrue("User ID should be valid", UserData.Id > 0);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->SignIn(UserData1->Username + "@gamefuse.com", "password", SignInCallback)));

						// Decline the join request using the stored connection data
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
							if (!TestConnectionData.IsValid()) {
								AddError("Connection data is not valid");
								return true;
							}

							if (TestConnectionData->Id == 0) {
								AddError("Cannot decline join request - connection ID is 0");
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

							// Verify the group membership after declining
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
								FGFGroupCallback VerifyCallback;
								VerifyCallback.BindLambda([this, GroupData](const FGFGroup& FetchedGroup) {
									AddInfo("DeclineRequests 6 :: Verify Group Membership After Decline");
									
									// Check that second user is NOT a member
									bool bFoundMember = false;
									for (const FGFUserData& Member : FetchedGroup.Members) {
										if (Member.Id == UserData2->Id) {
											bFoundMember = true;
											break;
										}
									}
									TestFalse("Second user is not a member after decline", bFoundMember);
									
									// Verify join requests are empty or the request is no longer pending
									bool bHasPendingRequests = false;
									for (const FGFGroupConnection& Request : FetchedGroup.JoinRequests) {
										if (Request.User.Id == UserData2->Id && Request.Status == EGFInviteRequestStatus::Pending) {
											bHasPendingRequests = true;
											break;
										}
									}
									TestFalse("No pending requests for declined user", bHasPendingRequests);
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																				  GameFuseGroups->FetchGroup(GroupData->Id, VerifyCallback)));
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

		It("enforces creator-only edit permissions for attributes", [this]() {
			TSharedPtr<FGFGroup> GroupData = MakeShared<FGFGroup>();
			GroupData->Name = TEXT("Attribute Permissions Test Group");
			GroupData->GroupType = TEXT("Test");
			GroupData->MaxGroupSize = 10;
			GroupData->bCanAutoJoin = true; // Make it auto-join
			GroupData->bSearchable = true;

			// Declare shared pointers for attributes once at test scope
			TSharedPtr<FGFGroupAttribute> CreatorOnlyAttr = MakeShared<FGFGroupAttribute>();
			TSharedPtr<FGFGroupAttribute> MemberEditableAttr = MakeShared<FGFGroupAttribute>();

			// Create the group and attributes
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr, MemberEditableAttr]() -> bool {
				FGFGroupCallback CreateGroupCallback;
				CreateGroupCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
					AddInfo("AttributePermissions 1 :: Create Group");
					TestTrue("Group created successfully", CreatedGroup.Id > 0);
					GroupData->Id = CreatedGroup.Id;
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																  GameFuseGroups->CreateGroup(*GroupData, CreateGroupCallback)));

				// Create creator-only attribute
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr, MemberEditableAttr]() -> bool {
					FGFGroupAttribute CreatorOnlyAttribute;
					CreatorOnlyAttribute.Key = TEXT("secret_code");
					CreatorOnlyAttribute.Value = TEXT("1234");
					CreatorOnlyAttribute.CreatorId = GroupData->Id;

					FGFGroupAttributeCallback AddCreatorOnlyAttributeCallback;
					AddCreatorOnlyAttributeCallback.BindLambda([this, CreatorOnlyAttr](const TArray<FGFGroupAttribute>& Attributes) {
						AddInfo("AttributePermissions 2 :: Add Creator-Only Attribute");
						TestTrue("Attribute added successfully", Attributes.Num() > 0);
						if (Attributes.Num() > 0) {
							*CreatorOnlyAttr = Attributes[0];
							TestEqual("Attribute has correct key", CreatorOnlyAttr->Key, TEXT("secret_code"));
							TestEqual("Attribute has correct value", CreatorOnlyAttr->Value, TEXT("1234"));
							TestEqual("Attribute has correct creator ID", CreatorOnlyAttr->CreatorId, UserData1->Id);
							TestTrue("Attribute creator can edit", CreatorOnlyAttr->bCanEdit);
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																	  GameFuseGroups->AddAttribute(GroupData->Id, CreatorOnlyAttribute, false, AddCreatorOnlyAttributeCallback)));
					// Create member-editable attribute
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr, MemberEditableAttr]() -> bool {
						FGFGroupAttribute MemberEditableAttribute;
						MemberEditableAttribute.Key = TEXT("public_data");
						MemberEditableAttribute.Value = TEXT("original_value");
						MemberEditableAttribute.CreatorId = GroupData->Id;

						FGFGroupAttributeCallback AddMemberAttributeCallback;
						AddMemberAttributeCallback.BindLambda([this, MemberEditableAttr](const TArray<FGFGroupAttribute>& Attributes) {
							AddInfo("AttributePermissions 3 :: Add Member-Editable Attribute");
							TestTrue("Attribute added successfully", Attributes.Num() > 0);
							if (Attributes.Num() > 0) {
								*MemberEditableAttr = Attributes[0];
								TestEqual("Attribute has correct key", MemberEditableAttr->Key, TEXT("public_data"));
								TestEqual("Attribute has correct value", MemberEditableAttr->Value, TEXT("original_value"));
								TestEqual("Attribute has correct creator ID", MemberEditableAttr->CreatorId, UserData1->Id);
								TestTrue("Attribute creator can edit", MemberEditableAttr->bCanEdit);
							}
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																		  GameFuseGroups->AddAttribute(GroupData->Id, MemberEditableAttribute, true, AddMemberAttributeCallback)));
						// Sign in as second user to test attribute permissions
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr, MemberEditableAttr]() -> bool {
							FGFUserDataCallback SignInCallback;
							SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
								AddInfo("AttributePermissions 4 :: Sign In Second User");
								TestTrue("Second user sign in succeeded", bSuccess);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

							// Join the group
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr, MemberEditableAttr]() -> bool {
								// Store the connection data for later use
								TSharedPtr<FGFGroupConnection> ConnectionData = MakeShared<FGFGroupConnection>();

								FGFGroupConnectionCallback JoinCallback;
								JoinCallback.BindLambda([this, ConnectionData](const FGFGroupConnection& Connection) {
									AddInfo("AttributePermissions 5 :: Join Group as Second User");
									TestTrue("Connection has valid id", Connection.Id != 0);
									TestEqual("Connection has correct user id", Connection.User.Id, UserData2->Id);
									TestEqual("Connection status is accepted", Connection.Status, EGFInviteRequestStatus::Accepted);

									// Store the connection data for later use
									*ConnectionData = Connection;
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																				  GameFuseGroups->RequestToJoinGroup(GroupData->Id, JoinCallback)));

								// Switch back to user 1 to accept the join request
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr, MemberEditableAttr, ConnectionData]() -> bool {
									FGFUserDataCallback SignInCallback;
									SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
										AddInfo("AttributePermissions 6 :: Switch Back to Creator");
										TestTrue("Creator sign in succeeded", bSuccess);
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																					  GameFuseUser->SignIn(UserData1->Username + "@gamefuse.com", "password", SignInCallback)));

									// Accept the join request with the stored connection data
									ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr, MemberEditableAttr, ConnectionData]() -> bool {
										if (ConnectionData->Id == 0) {
											AddError("Connection data is not valid");
											return true;
										}

										UE_LOG(LogGameFuse, Log, TEXT("Accepting connection - ID: %d, User ID: %d"), ConnectionData->Id, ConnectionData->User.Id);

										FGFGroupActionCallback AcceptCallback;
										AcceptCallback.BindLambda([this](bool bSuccess) {
											AddInfo("AttributePermissions 7 :: Accept Join Request");
											TestTrue("Accept join request succeeded", bSuccess);
										});

										ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																						  GameFuseGroups->RespondToGroupJoinRequest(ConnectionData->Id, ConnectionData->User.Id, EGFInviteRequestStatus::Accepted, AcceptCallback)));

										// Now switch back to user 2 to test editing attributes
										ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr, MemberEditableAttr]() -> bool {
											FGFUserDataCallback SignInCallback;
											SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
												AddInfo("AttributePermissions 8 :: Switch Back to Second User");
												TestTrue("Second user sign in succeeded", bSuccess);
											});

											ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																						  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

											// Fetch attributes as second user
											ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr, MemberEditableAttr]() -> bool {
												FGFGroupAttributeCallback FetchCallback;
												FetchCallback.BindLambda([this, CreatorOnlyAttr, MemberEditableAttr](const TArray<FGFGroupAttribute>& Attributes) {
													AddInfo("AttributePermissions 9 :: Fetch Attributes as Second User");
													TestEqual("Both attributes fetched successfully", Attributes.Num(), 2);

													for (const FGFGroupAttribute& Attribute : Attributes) {
														if (Attribute.Key == TEXT("secret_code")) {
															*CreatorOnlyAttr = Attribute;
															TestEqual("Secret code has correct value", Attribute.Value, TEXT("1234"));
															TestFalse("Second user cannot edit creator-only attribute", Attribute.bCanEdit);
														} else if (Attribute.Key == TEXT("public_data")) {
															*MemberEditableAttr = Attribute;
															TestEqual("Public data has correct value", Attribute.Value, TEXT("original_value"));
															TestTrue("Second user can edit member-editable attribute", Attribute.bCanEdit);
														}
													}
												});

												ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																								  GameFuseGroups->FetchGroupAttributes(GroupData->Id, FetchCallback)));

												// Try to update creator-only attribute (should fail)
												ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr, MemberEditableAttr]() -> bool {
													CreatorOnlyAttr->Value = TEXT("5678");

													FGFGroupActionCallback UpdateCreatorOnlyCallback;
													UpdateCreatorOnlyCallback.BindLambda([this](bool bSuccess) {
														AddInfo("AttributePermissions 10 :: Try Update Creator-Only as Second User");
														TestFalse("Update should fail for non-creator", bSuccess);
													});

													ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																									  GameFuseGroups->UpdateGroupAttribute(GroupData->Id, *CreatorOnlyAttr, UpdateCreatorOnlyCallback)));

													// Try to update member-editable attribute (should succeed)
													ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr, MemberEditableAttr]() -> bool {
														MemberEditableAttr->Value = TEXT("updated_by_member");

														FGFGroupActionCallback UpdateMemberEditableCallback;
														UpdateMemberEditableCallback.BindLambda([this](bool bSuccess) {
															AddInfo("AttributePermissions 11 :: Try Update Member-Editable as Second User");
															TestTrue("Update should succeed for member-editable attribute", bSuccess);
														});

														ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																										  GameFuseGroups->UpdateGroupAttribute(GroupData->Id, *MemberEditableAttr, UpdateMemberEditableCallback)));

														// Switch back to creator to verify changes
														ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr, MemberEditableAttr]() -> bool {
															FGFUserDataCallback SignInCallback;
															SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
																AddInfo("AttributePermissions 12 :: Sign Back In as Creator");
																TestTrue("Creator sign in succeeded", bSuccess);
															});

															ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																											  GameFuseUser->SignIn(UserData1->Username + "@gamefuse.com", "password", SignInCallback)));

															// Verify attribute states
															ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr, MemberEditableAttr]() -> bool {
																FGFGroupAttributeCallback FetchCallback;
																FetchCallback.BindLambda([this, CreatorOnlyAttr, MemberEditableAttr](const TArray<FGFGroupAttribute>& Attributes) {
																	AddInfo("AttributePermissions 13 :: Verify Attributes as Creator");
																	TestEqual("Both attributes still exist", Attributes.Num(), 2);

																	for (const FGFGroupAttribute& Attribute : Attributes) {
																		if (Attribute.Key == TEXT("secret_code")) {
																			*CreatorOnlyAttr = Attribute;
																			TestEqual("Creator-only attribute still has original value", Attribute.Value, TEXT("1234"));
																			TestTrue("Creator can edit attribute", Attribute.bCanEdit);
																		} else if (Attribute.Key == TEXT("public_data")) {
																			*MemberEditableAttr = Attribute;
																			TestEqual("Member-editable attribute has updated value", Attribute.Value, TEXT("updated_by_member"));
																			TestTrue("Creator can edit attribute", Attribute.bCanEdit);
																		}
																	}
																});

																ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																												  GameFuseGroups->FetchGroupAttributes(GroupData->Id, FetchCallback)));

																// Update creator-only attribute as creator
																ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, CreatorOnlyAttr]() -> bool {
																	CreatorOnlyAttr->Value = TEXT("9999");

																	FGFGroupActionCallback UpdateCallback;
																	UpdateCallback.BindLambda([this](bool bSuccess) {
																		AddInfo("AttributePermissions 14 :: Update Creator-Only as Creator");
																		TestTrue("Update should succeed for creator", bSuccess);
																	});

																	ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																													  GameFuseGroups->UpdateGroupAttribute(GroupData->Id, *CreatorOnlyAttr, UpdateCallback)));

																	// Final verification
																	ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
																		FGFGroupAttributeCallback VerifyCallback;
																		VerifyCallback.BindLambda([this](const TArray<FGFGroupAttribute>& FinalAttributes) {
																			AddInfo("AttributePermissions 15 :: Final Verification");
																			TestEqual("Both attributes still exist", FinalAttributes.Num(), 2);

																			for (const FGFGroupAttribute& Attribute : FinalAttributes) {
																				if (Attribute.Key == TEXT("secret_code")) {
																					TestEqual("Creator-only attribute has updated value", Attribute.Value, TEXT("9999"));
																					TestTrue("Creator can still edit attribute", Attribute.bCanEdit);
																				} else if (Attribute.Key == TEXT("public_data")) {
																					TestEqual("Member-editable attribute still has member-updated value", Attribute.Value, TEXT("updated_by_member"));
																					TestTrue("Creator can still edit attribute", Attribute.bCanEdit);
																				}
																			}
																		});

																		ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																														  GameFuseGroups->FetchGroupAttributes(GroupData->Id, VerifyCallback)));
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
		});
	});

	Describe("Group Join Requests and Invites", [this]() {
		It("manages join requests for groups", [this]() {
			// Create a test group that allows join requests
			TSharedPtr<FGFGroup> GroupData = MakeShared<FGFGroup>();
			GroupData->Name = TEXT("Join Requests Test Group");
			GroupData->GroupType = TEXT("Test");
			GroupData->MaxGroupSize = 10;
			GroupData->bCanAutoJoin = false; // Requires approval
			GroupData->bIsInviteOnly = false; // Allow join requests
			GroupData->bSearchable = true;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
				FGFGroupCallback CreateGroupCallback;
				CreateGroupCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
					AddInfo("JoinRequests 1 :: Create Group");
					TestTrue("Group created successfully", CreatedGroup.Id > 0);
					TestFalse("Group cannot auto join", CreatedGroup.bCanAutoJoin);
					TestFalse("Group is not invite only", CreatedGroup.bIsInviteOnly);
					GroupData->Id = CreatedGroup.Id;
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																  GameFuseGroups->CreateGroup(*GroupData, CreateGroupCallback)));

				// Sign in second user to request joining
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
					FGFUserDataCallback SignInCallback;
					SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
						AddInfo("JoinRequests 2 :: Sign In Second User");
						TestTrue("Second user sign in succeeded", bSuccess);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

					// Request to join the group
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
						FGFGroupConnectionCallback RequestCallback;
						RequestCallback.BindLambda([this](const FGFGroupConnection& Connection) {
							AddInfo("JoinRequests 3 :: Request to Join");
							if (Connection.Id == 0) {
								AddError("Join request failed - connection ID is 0");
								return;
							}
							TestTrue("Connection has valid id", Connection.Id != 0);
							TestEqual("Connection has correct user id", Connection.User.Id, UserData2->Id);
							TestEqual("Connection status is pending", Connection.Status, EGFInviteRequestStatus::Pending);

							// Store the connection data for later use
							TestConnectionData = MakeShared<FGFGroupConnection>(Connection);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																		  GameFuseGroups->RequestToJoinGroup(GroupData->Id, RequestCallback)));

						// Switch back to first user to check join requests
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
							FGFUserDataCallback SignInCallback;
							SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
								AddInfo("JoinRequests 4 :: Switch Back to Creator");
								TestTrue("Creator sign in succeeded", bSuccess);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->SignIn(UserData1->Username + "@gamefuse.com", "password", SignInCallback)));

							// Fetch the group to check join requests from server data
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
								FGFGroupCallback FetchGroupCallback;
								FetchGroupCallback.BindLambda([this, GroupData](const FGFGroup& FetchedGroup) {
									AddInfo("JoinRequests 5 :: Fetch Group with Join Requests");
									TestTrue("Group fetched successfully", FetchedGroup.Id == GroupData->Id);
									TestTrue("Group has join requests", FetchedGroup.JoinRequests.Num() > 0);
									
									// Verify the join request details from server data
									bool bFoundRequest = false;
									for (const FGFGroupConnection& Request : FetchedGroup.JoinRequests) {
										if (Request.User.Id == UserData2->Id) {
											bFoundRequest = true;
											TestEqual("Request status is pending", Request.Status, EGFInviteRequestStatus::Pending);
											TestEqual("Request user ID matches", Request.User.Id, UserData2->Id);
											TestEqual("Request username matches", Request.User.Username, UserData2->Username);
											break;
										}
									}
									TestTrue("Found the join request from second user", bFoundRequest);
									
									// Verify no invites exist for this non-invite-only group
									TestEqual("Group has no invites", FetchedGroup.Invites.Num(), 0);
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																				  GameFuseGroups->FetchGroup(GroupData->Id, FetchGroupCallback)));

								// Accept the join request
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
									if (!TestConnectionData.IsValid()) {
										AddError("Connection data is not valid");
										return true;
									}

									FGFGroupActionCallback AcceptCallback;
									AcceptCallback.BindLambda([this](bool bSuccess) {
										AddInfo("JoinRequests 6 :: Accept Join Request");
										TestTrue("Accept join request succeeded", bSuccess);
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																					  GameFuseGroups->RespondToGroupJoinRequest(TestConnectionData->Id, TestConnectionData->User.Id, EGFInviteRequestStatus::Accepted, AcceptCallback)));

									// Verify the group membership after accepting
									ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
										FGFGroupCallback VerifyCallback;
										VerifyCallback.BindLambda([this, GroupData](const FGFGroup& FetchedGroup) {
											AddInfo("JoinRequests 7 :: Verify Group Membership");
											TestTrue("Group has members", FetchedGroup.Members.Num() > 0);
											
											// Check if second user is now a member
											bool bFoundMember = false;
											for (const FGFUserData& Member : FetchedGroup.Members) {
												if (Member.Id == UserData2->Id) {
													bFoundMember = true;
													TestEqual("Member username matches", Member.Username, UserData2->Username);
													break;
												}
											}
											TestTrue("Second user is now a member", bFoundMember);
											
											// Verify join requests are empty or the request is no longer pending
											bool bHasPendingRequests = false;
											for (const FGFGroupConnection& Request : FetchedGroup.JoinRequests) {
												if (Request.User.Id == UserData2->Id && Request.Status == EGFInviteRequestStatus::Pending) {
													bHasPendingRequests = true;
													break;
												}
											}
											TestFalse("No pending requests for accepted user", bHasPendingRequests);
										});

										ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																						  GameFuseGroups->FetchGroup(GroupData->Id, VerifyCallback)));
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

		It("manages group invites", [this]() {
			// Create a test group that is invite-only
			TSharedPtr<FGFGroup> GroupData = MakeShared<FGFGroup>();
			GroupData->Name = TEXT("Group Invites Test Group");
			GroupData->GroupType = TEXT("Test");
			GroupData->MaxGroupSize = 10;
			GroupData->bCanAutoJoin = false;
			GroupData->bIsInviteOnly = true; // Make it invite-only
			GroupData->bSearchable = true;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
				FGFGroupCallback CreateGroupCallback;
				CreateGroupCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
					AddInfo("GroupInvites 1 :: Create Invite-Only Group");
					TestTrue("Group created successfully", CreatedGroup.Id > 0);
					TestTrue("Group is invite only", CreatedGroup.bIsInviteOnly);
					GroupData->Id = CreatedGroup.Id;
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																  GameFuseGroups->CreateGroup(*GroupData, CreateGroupCallback)));

				// Fetch the group to verify initial state (no invites, no join requests)
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
					FGFGroupCallback FetchGroupCallback;
					FetchGroupCallback.BindLambda([this, GroupData](const FGFGroup& FetchedGroup) {
						AddInfo("GroupInvites 2 :: Verify Initial Group State");
						TestTrue("Group fetched successfully", FetchedGroup.Id == GroupData->Id);
						TestTrue("Group is invite only", FetchedGroup.bIsInviteOnly);
						
						// Initially, the group should have no invites or join requests
						TestEqual("Group has no invites initially", FetchedGroup.Invites.Num(), 0);
						TestEqual("Group has no join requests initially", FetchedGroup.JoinRequests.Num(), 0);
						
						// Verify the group only has the creator as a member
						TestEqual("Group has only creator as member", FetchedGroup.Members.Num(), 1);
						if (FetchedGroup.Members.Num() > 0) {
							TestEqual("Creator is the only member", FetchedGroup.Members[0].Id, UserData1->Id);
						}
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																	  GameFuseGroups->FetchGroup(GroupData->Id, FetchGroupCallback)));

					// Create second user and invite them to the group
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
						FGFUserDataCallback SignInCallback;
						SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
							AddInfo("GroupInvites 3 :: Sign In Second User");
							TestTrue("Second user sign in succeeded", bSuccess);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																		  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

						// Switch back to first user (admin) to invite the second user
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
							FGFUserDataCallback SignInCallback;
							SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
								AddInfo("GroupInvites 4 :: Switch Back to Admin");
								TestTrue("Admin sign in succeeded", bSuccess);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->SignIn(UserData1->Username + "@gamefuse.com", "password", SignInCallback)));

							// Admin invites the second user to the group
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
								FGFGroupConnectionCallback InviteCallback;
								InviteCallback.BindLambda([this](const FGFGroupConnection& Connection) {
									AddInfo("GroupInvites 5 :: Admin Invites Second User");
									if (Connection.Id == 0) {
										AddError("Invite failed - connection ID is 0");
										return;
									}
									TestTrue("Invite created successfully", Connection.Id != 0);
									TestEqual("Invite has correct user id", Connection.User.Id, UserData2->Id);
									TestEqual("Invite status is pending", Connection.Status, EGFInviteRequestStatus::Pending);

									// Store the connection data for later use
									TestConnectionData = MakeShared<FGFGroupConnection>(Connection);
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																				  GameFuseGroups->InviteGroupMember(GroupData->Id, UserData2->Id, InviteCallback)));

								// Fetch the group to verify the invite was created
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
									FGFGroupCallback FetchGroupCallback;
									FetchGroupCallback.BindLambda([this, GroupData](const FGFGroup& FetchedGroup) {
										AddInfo("GroupInvites 6 :: Verify Group Has Invite");
										TestTrue("Group fetched successfully", FetchedGroup.Id == GroupData->Id);
										TestTrue("Group is invite only", FetchedGroup.bIsInviteOnly);
										
										// The group should now have an invite
										TestTrue("Group has invites", FetchedGroup.Invites.Num() > 0);
										
										// Verify the invite details
										bool bFoundInvite = false;
										for (const FGFGroupConnection& Invite : FetchedGroup.Invites) {
											if (Invite.User.Id == UserData2->Id) {
												bFoundInvite = true;
												TestEqual("Invite status is pending", Invite.Status, EGFInviteRequestStatus::Pending);
												TestEqual("Invite user ID matches", Invite.User.Id, UserData2->Id);
												TestEqual("Invite username matches", Invite.User.Username, UserData2->Username);
												break;
											}
										}
										TestTrue("Found the invite for second user", bFoundInvite);
										
										// Verify no join requests exist for this invite-only group
										TestEqual("Group has no join requests", FetchedGroup.JoinRequests.Num(), 0);
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																					  GameFuseGroups->FetchGroup(GroupData->Id, FetchGroupCallback)));

									// Switch to second user to accept the invite
									ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
										FGFUserDataCallback SignInCallback;
										SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
											AddInfo("GroupInvites 7 :: Switch to Second User");
											TestTrue("Second user sign in succeeded", bSuccess);
										});

										ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																						  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

										// Second user accepts the invite
										ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
											if (!TestConnectionData.IsValid()) {
												AddError("Connection data is not valid");
												return true;
											}

											if (TestConnectionData->Id == 0) {
												AddError("Cannot accept invite - connection ID is 0");
												return true;
											}

											FGFGroupActionCallback AcceptCallback;
											AcceptCallback.BindLambda([this](bool bSuccess) {
												AddInfo("GroupInvites 8 :: Second User Accepts Invite");
												TestTrue("Accept invite succeeded", bSuccess);
											});

											ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																							  GameFuseGroups->RespondToGroupJoinRequest(TestConnectionData->Id, TestConnectionData->User.Id, EGFInviteRequestStatus::Accepted, AcceptCallback)));

											// Verify the group membership after accepting
											ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
												FGFGroupCallback VerifyCallback;
												VerifyCallback.BindLambda([this, GroupData](const FGFGroup& FetchedGroup) {
													AddInfo("GroupInvites 9 :: Verify Group Membership After Accept");
													TestTrue("Group has members", FetchedGroup.Members.Num() > 0);
													
													// Check if second user is now a member
													bool bFoundMember = false;
													for (const FGFUserData& Member : FetchedGroup.Members) {
														if (Member.Id == UserData2->Id) {
															bFoundMember = true;
															TestEqual("Member username matches", Member.Username, UserData2->Username);
															break;
														}
													}
													TestTrue("Second user is now a member", bFoundMember);
													
													// Verify invites are empty or the invite is no longer pending
													bool bHasPendingInvites = false;
													for (const FGFGroupConnection& Invite : FetchedGroup.Invites) {
														if (Invite.User.Id == UserData2->Id && Invite.Status == EGFInviteRequestStatus::Pending) {
															bHasPendingInvites = true;
															break;
														}
													}
													TestFalse("No pending invites for accepted user", bHasPendingInvites);
												});

												ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																								  GameFuseGroups->FetchGroup(GroupData->Id, VerifyCallback)));
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

		It("declines join requests and invites", [this]() {
			// Create a test group
			TSharedPtr<FGFGroup> GroupData = MakeShared<FGFGroup>();
			GroupData->Name = TEXT("Decline Requests Test Group");
			GroupData->GroupType = TEXT("Test");
			GroupData->MaxGroupSize = 10;
			GroupData->bCanAutoJoin = false;
			GroupData->bIsInviteOnly = false;
			GroupData->bSearchable = true;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
				FGFGroupCallback CreateGroupCallback;
				CreateGroupCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
					AddInfo("DeclineRequests 1 :: Create Group");
					TestTrue("Group created successfully", CreatedGroup.Id > 0);
					GroupData->Id = CreatedGroup.Id;
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																  GameFuseGroups->CreateGroup(*GroupData, CreateGroupCallback)));

				// Sign in second user to request joining
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
					FGFUserDataCallback SignInCallback;
					SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
						AddInfo("DeclineRequests 2 :: Sign In Second User");
						TestTrue("Second user sign in succeeded", bSuccess);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

					// Request to join the group
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
						FGFGroupConnectionCallback RequestCallback;
						RequestCallback.BindLambda([this](const FGFGroupConnection& Connection) {
							AddInfo("DeclineRequests 3 :: Request to Join");
							TestTrue("Connection has valid id", Connection.Id != 0);
							TestEqual("Connection has correct user id", Connection.User.Id, UserData2->Id);
							TestEqual("Connection status is pending", Connection.Status, EGFInviteRequestStatus::Pending);

							// Store the connection data for later use
							TestConnectionData = MakeShared<FGFGroupConnection>(Connection);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																		  GameFuseGroups->RequestToJoinGroup(GroupData->Id, RequestCallback)));

						// Switch back to first user to decline the request
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
							FGFUserDataCallback SignInCallback;
							SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
								AddInfo("DeclineRequests 4 :: Switch Back to Creator");
								TestTrue("Creator sign in succeeded", bSuccess);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->SignIn(UserData1->Username + "@gamefuse.com", "password", SignInCallback)));

							// Decline the join request
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
								if (!TestConnectionData.IsValid()) {
									AddError("Connection data is not valid");
									return true;
								}

								FGFGroupActionCallback DeclineCallback;
								DeclineCallback.BindLambda([this](bool bSuccess) {
									AddInfo("DeclineRequests 5 :: Decline Join Request");
									TestTrue("Decline join request succeeded", bSuccess);
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																				  GameFuseGroups->RespondToGroupJoinRequest(TestConnectionData->Id, TestConnectionData->User.Id, EGFInviteRequestStatus::Declined, DeclineCallback)));

								// Verify the group membership after declining
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
									FGFGroupCallback VerifyCallback;
									VerifyCallback.BindLambda([this, GroupData](const FGFGroup& FetchedGroup) {
										AddInfo("DeclineRequests 6 :: Verify Group Membership After Decline");
										
										// Check that second user is NOT a member
										bool bFoundMember = false;
										for (const FGFUserData& Member : FetchedGroup.Members) {
											if (Member.Id == UserData2->Id) {
												bFoundMember = true;
												break;
											}
										}
										TestFalse("Second user is not a member after decline", bFoundMember);
										
										// Verify join requests are empty or the request is no longer pending
										bool bHasPendingRequests = false;
										for (const FGFGroupConnection& Request : FetchedGroup.JoinRequests) {
											if (Request.User.Id == UserData2->Id && Request.Status == EGFInviteRequestStatus::Pending) {
												bHasPendingRequests = true;
												break;
											}
										}
										TestFalse("No pending requests for declined user", bHasPendingRequests);
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																					  GameFuseGroups->FetchGroup(GroupData->Id, VerifyCallback)));
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

		It("handles multiple join requests and invites", [this]() {
			// Create a test group that allows join requests (not invite-only)
			TSharedPtr<FGFGroup> GroupData = MakeShared<FGFGroup>();
			GroupData->Name = TEXT("Multiple Requests Test Group");
			GroupData->GroupType = TEXT("Test");
			GroupData->MaxGroupSize = 10;
			GroupData->bCanAutoJoin = false;
			GroupData->bIsInviteOnly = false; // Allow join requests
			GroupData->bSearchable = true;

			// Create a third user for testing multiple requests
			TSharedPtr<FGFUserData> UserData3 = MakeShared<FGFUserData>();
			UserData3->Username = "testuser3_" + FString::FromInt(FMath::RandRange(1000, 9999));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, UserData3]() -> bool {
				FGFGroupCallback CreateGroupCallback;
				CreateGroupCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
					AddInfo("MultipleRequests 1 :: Create Group");
					TestTrue("Group created successfully", CreatedGroup.Id > 0);
					GroupData->Id = CreatedGroup.Id;
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																  GameFuseGroups->CreateGroup(*GroupData, CreateGroupCallback)));

				// Create third user
				ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, UserData3, this, FGuid()));

				// Sign in second user to request joining
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, UserData3]() -> bool {
					FGFUserDataCallback SignInCallback;
					SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
						AddInfo("MultipleRequests 2 :: Sign In Second User");
						TestTrue("Second user sign in succeeded", bSuccess);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

					// Request to join the group
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, UserData3]() -> bool {
						FGFGroupConnectionCallback RequestCallback;
						RequestCallback.BindLambda([this](const FGFGroupConnection& Connection) {
							AddInfo("MultipleRequests 3 :: Second User Request to Join");
							if (Connection.Id == 0) {
								AddError("Second user join request failed - connection ID is 0");
								return;
							}
							TestTrue("Connection has valid id", Connection.Id != 0);
							TestEqual("Connection has correct user id", Connection.User.Id, UserData2->Id);
							TestEqual("Connection status is pending", Connection.Status, EGFInviteRequestStatus::Pending);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																		  GameFuseGroups->RequestToJoinGroup(GroupData->Id, RequestCallback)));

						// Sign in third user to request joining
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, UserData3]() -> bool {
							FGFUserDataCallback SignInCallback;
							SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
								AddInfo("MultipleRequests 4 :: Sign In Third User");
								TestTrue("Third user sign in succeeded", bSuccess);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->SignIn(UserData3->Username + "@gamefuse.com", "password", SignInCallback)));

							// Request to join the group
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, UserData3]() -> bool {
								FGFGroupConnectionCallback RequestCallback;
								RequestCallback.BindLambda([this, UserData3](const FGFGroupConnection& Connection) {
									AddInfo("MultipleRequests 5 :: Third User Request to Join");
									if (Connection.Id == 0) {
										AddError("Third user join request failed - connection ID is 0");
										return;
									}
									TestTrue("Connection has valid id", Connection.Id != 0);
									TestEqual("Connection has correct user id", Connection.User.Id, UserData3->Id);
									TestEqual("Connection status is pending", Connection.Status, EGFInviteRequestStatus::Pending);
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																				GameFuseGroups->RequestToJoinGroup(GroupData->Id, RequestCallback)));

								// Switch back to first user to check multiple requests
								ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, UserData3]() -> bool {
									FGFUserDataCallback SignInCallback;
									SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
										AddInfo("MultipleRequests 6 :: Switch Back to Creator");
										TestTrue("Creator sign in succeeded", bSuccess);
									});

									ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																					  GameFuseUser->SignIn(UserData1->Username + "@gamefuse.com", "password", SignInCallback)));

									// Fetch the group to check multiple join requests
									ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, UserData3]() -> bool {
										FGFGroupCallback FetchGroupCallback;
										FetchGroupCallback.BindLambda([this, GroupData, UserData3](const FGFGroup& FetchedGroup) {
											AddInfo("MultipleRequests 7 :: Fetch Group with Multiple Join Requests");
											TestTrue("Group fetched successfully", FetchedGroup.Id == GroupData->Id);
											TestTrue("Group has multiple join requests", FetchedGroup.JoinRequests.Num() >= 2);
											
											// Verify both users have pending join requests
											bool bFoundUser2Request = false;
											bool bFoundUser3Request = false;
											
											for (const FGFGroupConnection& Request : FetchedGroup.JoinRequests) {
												if (Request.User.Id == UserData2->Id) {
													bFoundUser2Request = true;
													TestEqual("User2 request status is pending", Request.Status, EGFInviteRequestStatus::Pending);
												} else if (Request.User.Id == UserData3->Id) {
													bFoundUser3Request = true;
													TestEqual("User3 request status is pending", Request.Status, EGFInviteRequestStatus::Pending);
												}
											}
											
											TestTrue("Found join request for user 2", bFoundUser2Request);
											TestTrue("Found join request for user 3", bFoundUser3Request);
											
											// Verify no invites exist for this non-invite-only group
											TestEqual("Group has no invites", FetchedGroup.Invites.Num(), 0);
										});

										ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																						  GameFuseGroups->FetchGroup(GroupData->Id, FetchGroupCallback)));
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

		It("handles multiple invites for invite-only groups", [this]() {
			// Create a test group that is invite-only
			TSharedPtr<FGFGroup> GroupData = MakeShared<FGFGroup>();
			GroupData->Name = TEXT("Multiple Invites Test Group");
			GroupData->GroupType = TEXT("Test");
			GroupData->MaxGroupSize = 10;
			GroupData->bCanAutoJoin = false;
			GroupData->bIsInviteOnly = true; // Make it invite-only
			GroupData->bSearchable = true;

			// Create a third user for testing multiple invites
			TSharedPtr<FGFUserData> UserData3 = MakeShared<FGFUserData>();
			UserData3->Username = "testuser3_" + FString::FromInt(FMath::RandRange(1000, 9999));

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, UserData3]() -> bool {
				FGFGroupCallback CreateGroupCallback;
				CreateGroupCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
					AddInfo("MultipleInvites 1 :: Create Invite-Only Group");
					TestTrue("Group created successfully", CreatedGroup.Id > 0);
					TestTrue("Group is invite only", CreatedGroup.bIsInviteOnly);
					GroupData->Id = CreatedGroup.Id;
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																  GameFuseGroups->CreateGroup(*GroupData, CreateGroupCallback)));

				// Create third user
				ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, UserData3, this, FGuid()));

				// Admin invites second user
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, UserData3]() -> bool {
					FGFGroupConnectionCallback InviteCallback1;
					InviteCallback1.BindLambda([this](const FGFGroupConnection& Connection) {
						AddInfo("MultipleInvites 2 :: Admin Invites Second User");
						if (Connection.Id == 0) {
							AddError("First invite failed - connection ID is 0");
							return;
						}
						TestTrue("Invite 1 created successfully", Connection.Id != 0);
						TestEqual("Invite 1 has correct user id", Connection.User.Id, UserData2->Id);
						TestEqual("Invite 1 status is pending", Connection.Status, EGFInviteRequestStatus::Pending);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																	  GameFuseGroups->InviteGroupMember(GroupData->Id, UserData2->Id, InviteCallback1)));

					// Admin invites third user
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, UserData3]() -> bool {
						FGFGroupConnectionCallback InviteCallback2;
						InviteCallback2.BindLambda([this, UserData3](const FGFGroupConnection& Connection) {
							AddInfo("MultipleInvites 3 :: Admin Invites Third User");
							if (Connection.Id == 0) {
								AddError("Second invite failed - connection ID is 0");
								return;
							}
							TestTrue("Invite 2 created successfully", Connection.Id != 0);
							TestEqual("Invite 2 has correct user id", Connection.User.Id, UserData3->Id);
							TestEqual("Invite 2 status is pending", Connection.Status, EGFInviteRequestStatus::Pending);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																		  GameFuseGroups->InviteGroupMember(GroupData->Id, UserData3->Id, InviteCallback2)));

						// Fetch the group to check multiple invites
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData, UserData3]() -> bool {
							FGFGroupCallback FetchGroupCallback;
							FetchGroupCallback.BindLambda([this, GroupData, UserData3](const FGFGroup& FetchedGroup) {
								AddInfo("MultipleInvites 4 :: Fetch Group with Multiple Invites");
								TestTrue("Group fetched successfully", FetchedGroup.Id == GroupData->Id);
								TestTrue("Group has multiple invites", FetchedGroup.Invites.Num() >= 2);
								
								// Verify both users have pending invites
								bool bFoundUser2Invite = false;
								bool bFoundUser3Invite = false;
								
								for (const FGFGroupConnection& Invite : FetchedGroup.Invites) {
									if (Invite.User.Id == UserData2->Id) {
										bFoundUser2Invite = true;
										TestEqual("User2 invite status is pending", Invite.Status, EGFInviteRequestStatus::Pending);
									} else if (Invite.User.Id == UserData3->Id) {
										bFoundUser3Invite = true;
										TestEqual("User3 invite status is pending", Invite.Status, EGFInviteRequestStatus::Pending);
									}
								}
								
								TestTrue("Found invite for user 2", bFoundUser2Invite);
								TestTrue("Found invite for user 3", bFoundUser3Invite);
								
								// Verify no join requests exist for this invite-only group
								TestEqual("Group has no join requests", FetchedGroup.JoinRequests.Num(), 0);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																			  GameFuseGroups->FetchGroup(GroupData->Id, FetchGroupCallback)));
							return true;
						}));
						return true;
					}));
					return true;
				}));
				return true;
			}));
		});

		It("rejects join requests to invite-only groups", [this]() {
			// Create a test group that is invite-only
			TSharedPtr<FGFGroup> GroupData = MakeShared<FGFGroup>();
			GroupData->Name = TEXT("Invite-Only Reject Test Group");
			GroupData->GroupType = TEXT("Test");
			GroupData->MaxGroupSize = 10;
			GroupData->bCanAutoJoin = false;
			GroupData->bIsInviteOnly = true; // Make it invite-only
			GroupData->bSearchable = true;

			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
				FGFGroupCallback CreateGroupCallback;
				CreateGroupCallback.BindLambda([this, GroupData](const FGFGroup& CreatedGroup) {
					AddInfo("RejectJoinRequest 1 :: Create Invite-Only Group");
					TestTrue("Group created successfully", CreatedGroup.Id > 0);
					TestTrue("Group is invite only", CreatedGroup.bIsInviteOnly);
					GroupData->Id = CreatedGroup.Id;
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																  GameFuseGroups->CreateGroup(*GroupData, CreateGroupCallback)));

				// Sign in second user to try to request joining (this should fail)
				ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
					FGFUserDataCallback SignInCallback;
					SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
						AddInfo("RejectJoinRequest 2 :: Sign In Second User");
						TestTrue("Second user sign in succeeded", bSuccess);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																	  GameFuseUser->SignIn(UserData2->Username + "@gamefuse.com", "password", SignInCallback)));

					// Try to request to join the invite-only group (this should fail)
					ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
						FGFGroupConnectionCallback RequestCallback;
						RequestCallback.BindLambda([this](const FGFGroupConnection& Connection) {
							AddInfo("RejectJoinRequest 3 :: Request to Join Invite-Only Group (Should Fail)");
							// This should fail for invite-only groups, so we expect an empty connection
							if (Connection.Id != 0) {
								AddError("Join request to invite-only group should have failed but got valid connection ID");
								return;
							}
							TestTrue("Connection should be invalid for invite-only group", Connection.Id == 0);
							TestTrue("Connection should be empty for failed request", Connection.User.Id == 0);
						});

						ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																		  GameFuseGroups->RequestToJoinGroup(GroupData->Id, RequestCallback)));

						// Switch back to first user to verify group state after failed request
						ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
							FGFUserDataCallback SignInCallback;
							SignInCallback.BindLambda([this](bool bSuccess, const FGFUserData& UserData) {
								AddInfo("RejectJoinRequest 4 :: Switch Back to Creator");
								TestTrue("Creator sign in succeeded", bSuccess);
							});

							ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(),
																			  GameFuseUser->SignIn(UserData1->Username + "@gamefuse.com", "password", SignInCallback)));

							// Fetch the group to verify it still has no invites or join requests
							ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this, GroupData]() -> bool {
								FGFGroupCallback FetchGroupCallback;
								FetchGroupCallback.BindLambda([this, GroupData](const FGFGroup& FetchedGroup) {
									AddInfo("RejectJoinRequest 5 :: Verify Group State After Failed Request");
									TestTrue("Group fetched successfully", FetchedGroup.Id == GroupData->Id);
									TestTrue("Group is invite only", FetchedGroup.bIsInviteOnly);
									
									// Failed requests should not create any invites or join requests
									TestEqual("Group has no invites after failed request", FetchedGroup.Invites.Num(), 0);
									TestEqual("Group has no join requests after failed request", FetchedGroup.JoinRequests.Num(), 0);
									
									// Verify the group still only has the creator as a member
									TestEqual("Group still has only creator as member", FetchedGroup.Members.Num(), 1);
									if (FetchedGroup.Members.Num() > 0) {
										TestEqual("Creator is still the only member", FetchedGroup.Members[0].Id, UserData1->Id);
									}
								});

								ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
																				  GameFuseGroups->FetchGroup(GroupData->Id, FetchGroupCallback)));
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