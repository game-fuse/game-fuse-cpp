#include "Library/GameFuseLog.h"
#if WITH_AUTOMATION_TESTS

#include "CoreMinimal.h"
#include "Misc/AutomationTest.h"
#include "Tests/AutomationCommon.h"
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

	It("gets all groups", [this]() {
		// First create a test group
		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
			FGFGroup GroupData;
			GroupData.Name = "Test Group for GetAll";
			GroupData.GroupType = "Test";
			GroupData.MaxGroupSize = 10;
			GroupData.bCanAutoJoin = true;
			GroupData.bSearchable = true;

			FGFGroupCallback CreateCallback;
			CreateCallback.BindLambda([this](const FGFGroup& CreatedGroup) {
				AddInfo("GetAllGroups 1 :: Create Initial Group");
				TestTrue("Created group has valid id", CreatedGroup.Id != 0);
				TestEqual("Created group has correct name", CreatedGroup.Name, "Test Group for GetAll");
			});

			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
															  GameFuseGroups->CreateGroup(GroupData, CreateCallback)));
			return true;
		}));

		// After creating group, fetch all groups to verify
		ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
			FGFGroupListCallback FetchCallback;
			FetchCallback.BindLambda([this](const TArray<FGFGroup>& Groups) {
				AddInfo("GetAllGroups 2 :: Verify Groups List");
				TestTrue("Has at least one group", Groups.Num() > 0);
				TestEqual("Internal storage matches callback data", Groups, GameFuseGroups->GetAllGroups());

				// Find our created group in the list
				bool bFoundGroup = false;
				for (const FGFGroup& Group : Groups) {
					TestTrue("Each group has valid id", Group.Id != 0);
					TestFalse("Each group has name", Group.Name.IsEmpty());
					TestFalse("Each group has type", Group.GroupType.IsEmpty());

					if (Group.Name == "Test Group for GetAll") {
						bFoundGroup = true;
						TestEqual("Found group has correct name", Group.Name, "Test Group for GetAll");
						TestEqual("Found group has correct type", Group.GroupType, "Test");
						TestEqual("Found group has correct max size", Group.MaxGroupSize, 10);
						TestTrue("Found group can auto join", Group.bCanAutoJoin);
						TestTrue("Found group is searchable", Group.bSearchable);
					}
				}
				TestTrue("Created group was found in list", bFoundGroup);
			});

			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
															  GameFuseGroups->GetAllGroups(FetchCallback)));
			return true;
		}));
	});

	It("requests to join a group", [this]() {
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
						TestFalse("Connection has status", Connection.Status.IsEmpty());

						// Verify the connection was successful
						TestTrue("Connection status indicates success", Connection.Status == "pending" || Connection.Status == "accepted");
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
}

#endif