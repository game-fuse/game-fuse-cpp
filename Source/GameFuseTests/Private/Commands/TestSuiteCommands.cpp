#include "Commands/TestSuiteCommands.h"

bool FCreateGame::Update()
{

	if (RequestId.IsValid()) {
		return !APIHandler->IsRequestActive(RequestId);
	}


	FGFApiCallback Callback;
	Callback.AddLambda([this](const FGFAPIResponse& Response) {
		Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Request failed. Response: %s"), *Response.ResponseStr));

		FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, GameData.Get());

		Test->TestTrue("Game ID should be valid", GameData->Id != 0);
		Test->AddErrorIfFalse(GameData->Id != 0, TEXT("Game was not initialized"));
	});

	RequestId = APIHandler->CreateGame(Callback);
	return false;
}




bool FCreateUser::Update()
{

	if (RequestId.IsValid()) {
		return !APIHandler->IsRequestActive(RequestId);
	}


	FGFApiCallback Callback;
	Callback.AddLambda([this](const FGFAPIResponse& Response) {
		Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Request failed. Response: %s"), *Response.ResponseStr));

		FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, &UserData);

		Test->TestTrue("User ID should be valid", UserData.Id != 0);
		Test->AddErrorIfFalse(UserData.Id != 0, TEXT("User was not initialized"));
	});

	RequestId = APIHandler->CreateUser(GameData->Id, TEXT("TestUser"), TEXT("test@example.com"), Callback);
	return false;
}

bool FCreateStoreItem::Update()
{

	if (RequestId.IsValid()) {
		return !APIHandler->IsRequestActive(RequestId);
	}

	FGFStoreItem NewItem;
	NewItem.Name = TEXT("TestItem");
	NewItem.Description = TEXT("Test Item Description");
	NewItem.Cost = 100;

	FGFApiCallback Callback;
	Callback.AddLambda([this](const FGFAPIResponse& Response) {
		Test->AddInfo(FString::Printf(TEXT("FCreateStoreItem::Update - Callback invoked, Success: %d"), Response.bSuccess));
		Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Request failed. Response: %s"), *Response.ResponseStr));

		FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, &StoreItem);

		Test->TestTrue("Store Item ID should be valid", StoreItem.Id != 0);
		Test->AddErrorIfFalse(StoreItem.Id != 0, TEXT("Store Item was not initialized"));
	});

	RequestId = APIHandler->CreateStoreItem(GameData.Id, NewItem, Callback);
	return false;
}



bool FCleanupGame::Update()
{
	if (RequestId.IsValid()) {
		return !APIHandler->IsRequestActive(RequestId);
	}

	FGFApiCallback Callback;
	Callback.AddLambda([this](const FGFAPIResponse& Response) {
		Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Request failed. Response: %s"), *Response.ResponseStr));

		bCleanupSuccess = Response.bSuccess;
	});

	RequestId = APIHandler->CleanupGame(GameData.Id, Callback);
	return false;
}