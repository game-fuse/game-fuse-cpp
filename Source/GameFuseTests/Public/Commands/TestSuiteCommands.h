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
FGFUserData&, UserData,
FAutomationTestBase*, Test,
FGuid, RequestId);

DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(
FCreateStoreItem,
UTestAPIHandler*, APIHandler,
const FGFGameData&, GameData,
FGFStoreItem&, StoreItem,
FAutomationTestBase*, Test,
FGuid, RequestId);

DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(
FCleanupGame,
UTestAPIHandler*, APIHandler,
FGFGameData&, GameData,
bool&, bCleanupSuccess,
FAutomationTestBase*, Test,
FGuid, RequestId);