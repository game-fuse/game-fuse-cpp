#include "Library/GameFuseStructLibrary.h"
#include "Models/APIResponseManager.h"
#include "TestSuiteAPIManager.generated.h"

using FDefaultCallback = TFunction<void(FHttpRequestPtr, FHttpResponsePtr, bool)>;

UCLASS(meta = (Hidden, HideDropDown))
class GAMEFUSETESTS_API UTestSuiteAPIManager : public UHTTPResponseManager
{
	GENERATED_BODY()

public:

	UTestSuiteAPIManager();
	static void LogRequestInfo(TSharedRef<IHttpRequest> HttpRequest);
	static void LogRequestInfo(const FHttpRequestPtr& HttpRequest);
	void CreateGame(FDefaultCallback Callback);
	void OnStatusCodeReceived(TSharedPtr<IHttpRequest> HttpRequest, int I);

	void CreateUser(int32 GameId, const FString& Username, const FString& Email, FDefaultCallback Callback);
	void CreateStoreItem(int32 GameId, const FString& Name, const FString& Description, const FString& Category, int32 cost, FDefaultCallback Callback);
	void CreateStoreItem(int32 GameId, const FGFStoreItem& StoreItem, FDefaultCallback Callback);
	void CleanUpTestData(int32 GameId, FDefaultCallback Callback);

protected:

	//override base url
	inline static const FString BaseURL = "https://gamefuse.co/api/v3/test_suite";

};