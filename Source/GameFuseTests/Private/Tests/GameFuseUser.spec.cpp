#if WITH_AUTOMATION_TESTS
#include "Library/GameFuseLog.h"
#include "Misc/AutomationTest.h"
#include "Subsystems/GameFuseManager.h"
#include "Subsystems/GameFuseUser.h"
#include "Commands/TestSuiteCommands.h"

BEGIN_DEFINE_SPEC(GameFuseUserSpec, "GameFuseTests.GameFuseUser",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UGameFuseManager *GameFuseManager;
	UGameFuseUser *GameFuseUser;
	UGameInstance *GameInstance;
	UTestAPIHandler *TestAPIHandler;
	TSharedPtr<FGFGameData> GameData;
	TSharedPtr<FGFUserData> UserData;
	bool bCleanupSuccess;
END_DEFINE_SPEC(GameFuseUserSpec);

void GameFuseUserSpec::Define()
{
	// Setup
	GameInstance = NewObject<UGameInstance>();
	GameInstance->Init();

	// Get subsystems/ test api handler
	GameFuseManager = GameInstance->GetSubsystem<UGameFuseManager>();
	GameFuseUser = GameInstance->GetSubsystem<UGameFuseUser>();
	TestAPIHandler = NewObject<UTestAPIHandler>();

	//init testing data
	GameData = MakeShared<FGFGameData>();
	UserData = MakeShared<FGFUserData>();
	bCleanupSuccess = false;

	Describe("GameFuseUser Authentication", [this]() {
		BeforeEach([this]() {
            // Setup GameFuse before each test
            if (GameFuseManager->IsSetUp())
            {
                AddWarning("Already have a game setup");
                return;
            }

            // Clear any saved user data
            if (GameFuseUser)
            {
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
                    return false;  // Keep waiting
                }
                UE_LOG(LogGameFuse, Log, TEXT("GameFuseManager setup complete"));
                return true;
            }));
        });

		AfterEach([this]() {
			// Cleanup GameFuse after each test
			ADD_LATENT_AUTOMATION_COMMAND(FCleanupGame(TestAPIHandler, GameData, bCleanupSuccess, this, FGuid()));

			GameData = MakeShared<FGFGameData>();
			UserData = MakeShared<FGFUserData>();
		});

		It("Should sign in user successfully", [this]() {
			// Create user and wait for response
			FGuid CreateUserRequestId = FGuid();
			ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, UserData, this, CreateUserRequestId));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(TestAPIHandler, CreateUserRequestId));

			// Wait for UserData to be populated
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
				if (!UserData.IsValid() || UserData->Id == 0 || UserData->Username.IsEmpty()) {
					UE_LOG(LogGameFuse, Warning, TEXT("Waiting for UserData to be populated..."));
					return false;
				}

				return true;
			}));

			// Log UserData before sign-in
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
				UE_LOG(LogGameFuse, Log, TEXT("UserData before sign-in: ID=%i, Username=%s, Email=%s@gamefuse.com"), UserData->Id, *UserData->Username, *UserData->Username);
				return true;
			}));

			// Sign in user and wait for response
			FGuid SignInRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, &SignInRequestId]() -> bool {
				if (!GameFuseManager || !GameFuseManager->IsSetUp()) {
					AddError("GameFuseManager is not set up");
					return false;
				}

				FGFApiCallback SignInCallback;
				SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Sign in Response: %s"), *Response.ResponseStr);
					AddErrorIfFalse(Response.bSuccess, "Failed to sign in user: Response: " + Response.ResponseStr);
				});

				SignInRequestId = GameFuseUser->SignIn(UserData->Username, TEXT("password"), SignInCallback);
				return true;
			}));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), SignInRequestId));

			// Verify sign in results
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
				if (!GameFuseUser) {
					AddError("GameFuseUser is null");
					return true;
				}

				TestTrue("logs in the User", GameFuseUser->IsSignedIn());

				const FGFUserData& CurrentUserData = GameFuseUser->GetUserData();
				TestTrue("User IDs match", CurrentUserData.Id == UserData->Id);
				TestTrue("Usernames match", CurrentUserData.Username == UserData->Username);
				TestFalse("Auth token should be updated after sign in", CurrentUserData.AuthenticationToken.IsEmpty());

				return true;
			}));
		});

		It("Should handle credits operations", [this]() {
			// Create and sign in user first
			ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, UserData, this, FGuid()));

			// Wait until user is created before signing in
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
				return UserData.IsValid() && UserData->Id != 0;
			}));

			FGuid SignInRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, &SignInRequestId]() -> bool {
				if (!GameFuseManager->IsSetUp()) {
					AddError("GameFuseManager is not set up");
					return true; // End the command if not set up
				}

				FGFApiCallback SignInCallback;
				SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Sign in Response: %s"), *Response.ResponseStr);
					TestTrue("Sign in should be successful", Response.bSuccess);
					TestTrue("User should be signed in", GameFuseUser->IsSignedIn());
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Sign in failed: %s"), *Response.ResponseStr));
					}
				});

				SignInRequestId = GameFuseUser->SignIn(UserData->Username + "@gamefuse.com", "password", SignInCallback);
				return true;
			}));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), SignInRequestId));

			// Wait until user is signed in before proceeding
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
				return GameFuseUser->IsSignedIn();
			}));

			// Test adding credits
			FGuid AddCreditsRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, &AddCreditsRequestId]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
					AddError("User must be signed in to add credits");
					return true;
				}

				FGFApiCallback AddCreditsCallback;
				AddCreditsCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Add Credits Response: %s"), *Response.ResponseStr);
					TestTrue("Adding credits should be successful", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Add credits failed: %s"), *Response.ResponseStr));
					}
				});

				AddCreditsRequestId = GameFuseUser->AddCredits(100, AddCreditsCallback);
				return true;
			}));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), AddCreditsRequestId));

			// Test setting credits
			FGuid SetCreditsRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, &SetCreditsRequestId]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
					AddError("User must be signed in to set credits");
					return true;
				}

				FGFApiCallback SetCreditsCallback;
				SetCreditsCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Set Credits Response: %s"), *Response.ResponseStr);
					TestTrue("Setting credits should be successful", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Set credits failed: %s"), *Response.ResponseStr));
					}
				});

				SetCreditsRequestId = GameFuseUser->SetCredits(200, SetCreditsCallback);
				return true;
			}));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), SetCreditsRequestId));
		});
	});
}

#endif