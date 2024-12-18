#pragma once

#include "CoreMinimal.h"
#include "API/TestAPIHandler.h"
#include "Library/GameFuseStructLibrary.h"
#include "Misc/AutomationTest.h"
#include "JsonObjectConverter.h"

DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(
FCreateGame,
UTestAPIHandler*, APIHandler,
TSharedPtr<FGFGameData>, GameData,
FAutomationTestBase*, Test,
FGuid, RequestId);

DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(
FCreateUser,
UTestAPIHandler*, APIHandler,
TSharedPtr<FGFGameData>, GameData,
TSharedPtr<FGFUserData>, UserData,
FAutomationTestBase*, Test,
FGuid, RequestId);

DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(
FCreateStoreItem,
UTestAPIHandler*, APIHandler,
TSharedPtr<FGFGameData>, GameData,
TSharedPtr<FGFStoreItem>, StoreItem,
FAutomationTestBase*, Test,
FGuid, RequestId);

DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(
FCleanupGame,
UTestAPIHandler*, APIHandler,
TSharedPtr<FGFGameData>, GameData,
bool&, bCleanupSuccess,
FAutomationTestBase*, Test,
FGuid, RequestId);

DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(
FWaitForFGFResponse,
TObjectPtr<UAPIRequestHandler>, APIHandler,
FGuid, RequestId);

/**
 * FSetupGame
 * Sets up the GameFuseManager with the APIHandler, creating a test suite game
 */
DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(
FSetupGame,
UTestAPIHandler*, APIHandler,
TSharedPtr<FGFGameData>, GameData,
TObjectPtr<UGameFuseManager>, GameFuseManager,
FAutomationTestBase*, Test,
FGuid, RequestId);

/**
 * FSetupUser
 * Creates a test user and signs them in using the GameFuseUser subsystem
 */
DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(
FSetupUser,
UTestAPIHandler*, APIHandler,
TSharedPtr<FGFGameData>, GameData,
TSharedPtr<FGFUserData>, UserData,
TObjectPtr<UGameFuseUser>, GameFuseUser,
FAutomationTestBase*, Test);