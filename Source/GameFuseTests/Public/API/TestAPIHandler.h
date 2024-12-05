#pragma once

#include "CoreMinimal.h"
#include "API/APIRequestHandler.h"
#include "TestAPIHandler.generated.h"

UCLASS()
class GAMEFUSETESTS_API UTestAPIHandler : public UAPIRequestHandler
{
    GENERATED_BODY()

public:
    UTestAPIHandler();

    // C++ API methods
    FGuid CreateGame(const FGFApiCallback& Callback);
    FGuid CreateUser(int32 GameId, const FString& Username, const FString& Email, const FGFApiCallback& Callback);
    FGuid CreateStoreItem(int32 GameId, const FGFStoreItem& Item, const FGFApiCallback& Callback);
    FGuid CleanupGame(int32 GameId, const FGFApiCallback& Callback);

private:
    TSet<FGuid> ActiveRequests;
};