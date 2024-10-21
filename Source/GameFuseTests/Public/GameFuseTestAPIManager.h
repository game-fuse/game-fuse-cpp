#pragma once

#include "CoreMinimal.h"
#include "Library/GameFuseStructLibrary.h"
#include "Models/APIResponseManager.h"


#include "GameFuseTestAPIManager.generated.h"

UCLASS(meta = (Hidden, HideDropDown))
class GAMEFUSETESTS_API UGameFuseTestAPIManager : public UHTTPResponseManager
{
	GENERATED_BODY()
public:
	UGameFuseTestAPIManager();
	static void CreateGame();
	static void OnStatusCodeReceived(TSharedPtr<IHttpRequest> HttpRequest, int I);

	static void CreateUser(int32 GameId, const FGFUserData&);
	static void CreateStoreItem(int32 GameId, const FGFStoreItem&);
	static void CleanUpTestData(int32 GameId);

protected:
	//override base url
	inline static const FString BaseURL = "https://gamefuse.co/api/v3/test_suite";

};
