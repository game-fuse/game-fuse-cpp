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
	GameFuseGroups = GameInstance->GetSubsystem<UGameFuseGroups>();
	GameFuseUser = GameInstance->GetSubsystem<UGameFuseUser>();
	TestAPIHandler = NewObject<UTestAPIHandler>();

	// Init testing data
	GameData = MakeShared<FGFGameData>();
	UserData1 = MakeShared<FGFUserData>();
	UserData2 = MakeShared<FGFUserData>();

	Describe("GameFuseGroups Basic Operations", [this]() {
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
			ADD_LATENT_AUTOMATION_COMMAND(FSetupUser(TestAPIHandler, GameData, UserData1, GameFuseUser, this));

			// Wait for user to be fully signed in
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
					UE_LOG(LogGameFuse, Warning, TEXT("Waiting for user signin..."));
					return false; // Keep waiting
				}
				UE_LOG(LogGameFuse, Log, TEXT("User signed in successfully"));
				return true;
			}));

			// Create second user for testing
			ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, UserData2, this, FGuid()));
		});

		It("creates a group", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				FGFGroup Group;
				Group.Name = "Test Group";
				Group.GroupType = "Test";
				Group.MaxGroupSize = 10;
				Group.bCanAutoJoin = true;
				Group.bIsInviteOnly = false;
				Group.bSearchable = true;

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
					GameFuseGroups->CreateGroup(Group, TypedCallback)));
				return true;
			}));
		});

		It("gets all groups", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// First create a test group
				FGFGroup Group;
				Group.Name = "Test Group for GetAll";
				Group.GroupType = "Test";
				Group.MaxGroupSize = 10;
				Group.bCanAutoJoin = true;
				Group.bSearchable = true;

				FGFGroupCallback CreateCallback;
				CreateCallback.BindLambda([this](const FGFGroup& CreatedGroup) {
					AddInfo("GetAllGroups :: Create Initial Group");
					TestTrue("Created group has valid id", CreatedGroup.Id != 0);
					TestEqual("Created group has correct name", CreatedGroup.Name, "Test Group for GetAll");

					// After creating group, fetch all groups to verify
					FGFGroupListCallback FetchCallback;
					FetchCallback.BindLambda([this, CreatedGroup](const TArray<FGFGroup>& Groups) {
						AddInfo("GetAllGroups :: Verify Groups List");
						TestTrue("Has at least one group", Groups.Num() > 0);
						TestEqual("Internal storage matches callback data", Groups, GameFuseGroups->GetAllGroups());

						// Find our created group in the list
						bool bFoundGroup = false;
						for (const FGFGroup& Group : Groups) {
							TestTrue("Each group has valid id", Group.Id != 0);
							TestFalse("Each group has name", Group.Name.IsEmpty());
							TestFalse("Each group has type", Group.GroupType.IsEmpty());

							if (Group.Id == CreatedGroup.Id) {
								bFoundGroup = true;
								TestEqual("Found group matches created group", Group, CreatedGroup);
							}
						}
						TestTrue("Created group was found in list", bFoundGroup);
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
						GameFuseGroups->GetAllGroups(FetchCallback)));
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
					GameFuseGroups->CreateGroup(Group, CreateCallback)));
				return true;
			}));
		});

		It("requests to join a group", [this]() {
			ADD_LATENT_AUTOMATION_COMMAND(FFunctionLatentCommand([this]() -> bool {
				// First create a test group
				FGFGroup Group;
				Group.Name = "Test Group for Joining";
				Group.GroupType = "Test";
				Group.MaxGroupSize = 10;
				Group.bCanAutoJoin = true;
				Group.bSearchable = true;

				FGFGroupCallback CreateCallback;
				CreateCallback.BindLambda([this](const FGFGroup& CreatedGroup) {
					AddInfo("JoinGroup :: Create Group");
					TestTrue("Created group has valid id", CreatedGroup.Id != 0);
					TestEqual("Created group has correct name", CreatedGroup.Name, "Test Group for Joining");
					TestTrue("Created group can auto join", CreatedGroup.bCanAutoJoin);

					// After creating group, attempt to join it
					FGFGroupConnectionCallback JoinCallback;
					JoinCallback.BindLambda([this, CreatedGroup](const FGFGroupConnection& Connection) {
						AddInfo("JoinGroup :: Request to Join");
						TestTrue("Connection has valid id", Connection.Id != 0);
						TestEqual("Connection has correct group id", Connection.GroupId, CreatedGroup.Id);
						TestEqual("Connection has correct user id", Connection.UserId, UserData1->Id);
						TestFalse("Connection has status", Connection.Status.IsEmpty());

						// Verify the connection was successful
						TestTrue("Connection status indicates success", Connection.Status == "pending" || Connection.Status == "accepted");
					});

					ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
						GameFuseGroups->RequestToJoinGroup(CreatedGroup.Id, JoinCallback)));
				});

				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseGroups->GetRequestHandler(),
					GameFuseGroups->CreateGroup(Group, CreateCallback)));
				return true;
			}));
		});
	});
}

#endif