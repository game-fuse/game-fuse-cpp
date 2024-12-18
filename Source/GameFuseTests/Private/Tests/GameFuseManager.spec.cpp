#include "Library/GameFuseLog.h"
#if WITH_AUTOMATION_TESTS
#include "Misc/AutomationTest.h"
#include "Subsystems/GameFuseManager.h"
#include "Commands/TestSuiteCommands.h"

BEGIN_DEFINE_SPEC(GameFuseManagerSpec, "GameFuseTests.GameFuseManager",
                  EAutomationTestFlags::EditorContext | EAutomationTestFlags::EngineFilter)
	UGameFuseManager *GameFuseManager;
	UGameInstance *GameInstance;
	UTestAPIHandler *TestAPIHandler;
	TSharedPtr<FGFGameData> GameData;
END_DEFINE_SPEC(GameFuseManagerSpec);

void GameFuseManagerSpec::Define()
{
	GameInstance = NewObject<UGameInstance>();
	GameInstance->Init();
	GameFuseManager = GameInstance->GetSubsystem<UGameFuseManager>();
	GameData = MakeShared<FGFGameData>();
	TestAPIHandler = NewObject<UTestAPIHandler>();

	It("Has valid classes", [this]() {
		TestTrueExpr(GameFuseManager != nullptr);
		TestTrueExpr(TestAPIHandler != nullptr);
	});

	It("Sets up GameFuse", [this]() {
		// Create game with callback
		FGFApiCallback OnGameCreated;
		OnGameCreated.AddLambda([this](const FGFAPIResponse& Response) {
			TestTrue("Create game request succeeded", Response.bSuccess);
			if (!Response.bSuccess) {
				AddError(FString::Printf(TEXT("Create Game Request failed. Response: %s"), *Response.ResponseStr));
				return;
			}

			bool parseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, GameData.Get());
			UE_LOG(LogGameFuse, Log, TEXT("Parsing CreateGame response. Success: %d, GameData: ID=%d, Token=%s"),
				   parseSuccess, GameData->Id, *GameData->Token);

			TestTrue("got game data from response", parseSuccess);
			TestTrue("Game ID should be valid", GameData->Id != 0);
			AddErrorIfFalse(GameData->Id != 0, TEXT("Game was not initialized"));
			AddErrorIfFalse(GameData->Token.Len() > 0, TEXT("Game Authentication Token was not initialized"));
		});

		ADD_LATENT_AUTOMATION_COMMAND(FCreateGame(TestAPIHandler, GameData, OnGameCreated, this, FGuid()));

		FGuid SetupRequestId;
		ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this, &SetupRequestId]() -> bool {
			FGFApiCallback SetUpCallback;
			SetUpCallback.AddLambda(
				[this](const FGFAPIResponse& Response) {
					UE_LOG(LogGameFuse, Log, TEXT("Setup Game Responded: %s"), *Response.ResponseStr);
					TestTrue("setup game should be successful", Response.bSuccess);
				});

			// Set up the game and capture its request ID
			SetupRequestId = GameFuseManager->SetUpGame(GameData->Id, GameData->Token, SetUpCallback);
			return true;
		}));

		// Wait for setup to complete
		ADD_LATENT_AUTOMATION_COMMAND(FWaitForFGFResponse(GameFuseManager->GetRequestHandler(), SetupRequestId));

		// Verify final state
		ADD_LATENT_AUTOMATION_COMMAND(FDelayedFunctionLatentCommand([this]() -> bool {
			TestTrue("GameFuseManager should be set up", GameFuseManager->SetupCheck());
			TestTrue("has correct GameData", GameFuseManager->GetGameData() == *GameData);
			return true;
		}));
	});
}

#endif