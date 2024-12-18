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
			TSharedPtr<FGFUserData> TestUserData = MakeShared<FGFUserData>();
			FString RandomGuid = FGuid::NewGuid().ToString();
			TestUserData->Username = FString::Printf(TEXT("user_%s"), *RandomGuid.Left(8));

			// FGFApiCallback OnGameCreated;
			// OnGameCreated.AddLambda([this](const FGFAPIResponse& Response) {
			// 	TestTrue("Create game request succeeded", Response.bSuccess);
			// 	if (!Response.bSuccess) {
			// 		AddError(FString::Printf(TEXT("Create Game Request failed. Response: %s"), *Response.ResponseStr));
			// 		return;
			// 	}
			//
			// 	bool parseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, GameData.Get());
			// 	TestTrue("got game data from response", parseSuccess);
			// });
			//
			// ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(TestAPIHandler, GameData, OnGameCreated, this, FGuid()));

			FGFApiCallback OnUserCreated;
			OnUserCreated.AddLambda([this, TestUserData](const FGFAPIResponse& Response) {
				TestTrue("Create user request succeeded", Response.bSuccess);
				if (!Response.bSuccess) {
					AddError(FString::Printf(TEXT("Create User Request failed. Response: %s"), *Response.ResponseStr));
					return;
				}

				bool bParseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, TestUserData.Get());
				TestTrue("Parse user data response", bParseSuccess);
				
				TestTrue("User ID should be valid", TestUserData->Id != 0);
				UE_LOG(LogGameFuse, Log, TEXT("TestUserData updated - ID: %d, Username: %s"), TestUserData->Id, *TestUserData->Username);

				FGFApiCallback SignInCallback;
				SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Sign in Response: %s"), *Response.ResponseStr);
					TestTrue("Sign in request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Sign in failed: %s"), *Response.ResponseStr));
					}
				});

				FGuid SignInRequestId = GameFuseUser->SignIn(TestUserData->Username + TEXT("@gamefuse.com"), TEXT("password"), SignInCallback);
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), SignInRequestId));
			});

			ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, TestUserData, OnUserCreated, this));

			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
				if (!GameFuseUser) {
					AddError("GameFuseUser is null");
					return true;
				}

				return GameFuseUser->IsSignedIn();
			}));
		});

		It("Should handle credits operations", [this]() {
			TSharedPtr<FGFUserData> TestUserData = MakeShared<FGFUserData>();
			FString RandomGuid = FGuid::NewGuid().ToString();
			TestUserData->Username = FString::Printf(TEXT("user_%s"), *RandomGuid.Left(8));

			FGFApiCallback OnGameCreated;
			OnGameCreated.AddLambda([this](const FGFAPIResponse& Response) {
				TestTrue("Create game request succeeded", Response.bSuccess);
				if (!Response.bSuccess) {
					AddError(FString::Printf(TEXT("Create Game Request failed. Response: %s"), *Response.ResponseStr));
					return;
				}

				bool parseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, GameData.Get());
				TestTrue("got game data from response", parseSuccess);
			});

			ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(TestAPIHandler, GameData, OnGameCreated, this, FGuid()));

			FGFApiCallback OnUserCreated;
			OnUserCreated.AddLambda([this, TestUserData](const FGFAPIResponse& Response) {
				TestTrue("Create user request succeeded", Response.bSuccess);
				if (!Response.bSuccess) {
					AddError(FString::Printf(TEXT("Create User Request failed. Response: %s"), *Response.ResponseStr));
					return;
				}

				bool bParseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, TestUserData.Get());
				TestTrue("Parse user data response", bParseSuccess);
				
				TestTrue("User ID should be valid", TestUserData->Id != 0);
				UE_LOG(LogGameFuse, Log, TEXT("TestUserData updated - ID: %d, Username: %s"), TestUserData->Id, *TestUserData->Username);

				FGFApiCallback SignInCallback;
				SignInCallback.AddLambda([this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Sign in Response: %s"), *Response.ResponseStr);
					TestTrue("Sign in request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Sign in failed: %s"), *Response.ResponseStr));
					}
				});

				FGuid SignInRequestId = GameFuseUser->SignIn(TestUserData->Username + TEXT("@gamefuse.com"), TEXT("password"), SignInCallback);
				ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), SignInRequestId));
			});

			ADD_LATENT_AUTOMATION_COMMAND(FCreateUser(TestAPIHandler, GameData, TestUserData, OnUserCreated, this));

			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
				return GameFuseUser->IsSignedIn();
			}));

			FGuid AddCreditsRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, &AddCreditsRequestId]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
					return false;
				}

				FGFApiCallback AddCreditsCallback;
				AddCreditsCallback.AddLambda([this](const FGFAPIResponse& Response) {
					TestTrue("Add credits request succeeded", Response.bSuccess);
					if (!Response.bSuccess) {
						AddError(FString::Printf(TEXT("Add credits failed: %s"), *Response.ResponseStr));
					}
				});

				AddCreditsRequestId = GameFuseUser->AddCredits(100, AddCreditsCallback);
				return true;
			}));
			ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseUser->GetRequestHandler(), AddCreditsRequestId));

			FGuid SetCreditsRequestId;
			ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, &SetCreditsRequestId]() -> bool {
				if (!GameFuseUser->IsSignedIn()) {
					return false;
				}

				FGFApiCallback SetCreditsCallback;
				SetCreditsCallback.AddLambda([this](const FGFAPIResponse& Response) {
					TestTrue("Set credits request succeeded", Response.bSuccess);
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