#pragma once

#include "API/APIRequestHandler.h"
#include "Library/GameFuseStructLibrary.h"
#include "TestAPIHandler.generated.h"

UCLASS(meta = (Hidden, HideDropDown))
class GAMEFUSETESTS_API UTestAPIHandler : public UAPIRequestHandler
{
	GENERATED_BODY()

public:

	UTestAPIHandler();
	void CreateGame(const FGFApiCallback& Callback);

	void CreateUser(int32 GameId, const FString& Username, const FString& Email, const FGFApiCallback& Callback);
	void CreateStoreItem(int32 GameId, const FString& Name, const FString& Description, const FString& Category, int32 Cost, const FGFApiCallback& Callback);
	void CreateStoreItem(int32 GameId, const FGFStoreItem& StoreItem, const FGFApiCallback& Callback);
	void CleanUpTestData(int32 GameId, const FGFApiCallback& Callback);

protected:

	//override base url
	inline static const FString BaseURL = "https://gamefuse.co/api/v3/test_suite";

};