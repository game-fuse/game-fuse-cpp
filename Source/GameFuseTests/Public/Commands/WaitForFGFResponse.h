#pragma once

#include "CoreMinimal.h"
#include "Library/GameFuseStructLibrary.h"
#include "Misc/AutomationTest.h"
#include "API/APIRequestHandler.h"

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(FWaitForFGFResponse, UAPIRequestHandler*, APIHandler, FGuid, RequestId, FGFAPIResponse&, Response);

bool FWaitForFGFResponse::Update()
{
    return !RequestId.IsValid() || !APIHandler->IsRequestActive(RequestId);
}
