#include "Commands/TestSuiteCommands.h"

#include "Library/GameFuseLog.h"

bool FCreateGame::Update()
{

	if (RequestId.IsValid()) {
		UE_LOG(LogGameFuse, Log, TEXT("Request %s is still active: %i"), *RequestId.ToString(), APIHandler->IsRequestActive(RequestId));
		return !APIHandler->IsRequestActive(RequestId);
	}
	UE_LOG(LogGameFuse, Log, TEXT("Creating Game"));

	FGFApiCallback Callback;
	Callback.AddLambda([this](const FGFAPIResponse& Response) {
		Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Create Game Request failed. Response: %s"), *Response.ResponseStr));

		bool parseSuccess = FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, GameData.Get());
		UE_LOG(LogGameFuse, Log, TEXT("Parsing CreateGame response. Success: %d, GameData: ID=%d, Token=%s"),
		       parseSuccess, GameData->Id, *GameData->Token);

		Test->TestTrue("got game data from response", parseSuccess);
		Test->TestTrue("Game ID should be valid", GameData->Id != 0);
		Test->AddErrorIfFalse(GameData->Id != 0, TEXT("Game was not initialized"));
		Test->AddErrorIfFalse(GameData->Token.Len() > 0, TEXT("Game Authentication Token was not initialized"));
		Test->AddWarning("We get here right");
	});

	RequestId = APIHandler->CreateGame(Callback);
	return false;
}




bool FCreateUser::Update()
{

	if (!APIHandler || !GameData) {
		Test->AddError(TEXT("APIHandler or GameData is null in FCreateUser::Update"));
		return true; // End the command
	}
	if (RequestId.IsValid()) {
		return !APIHandler->IsRequestActive(RequestId);
	}


	// Generate random username using GUID
	FString RandomGuid = FGuid::NewGuid().ToString();
	FString Username = FString::Printf(TEXT("user_%s"), *RandomGuid.Left(8));
	FString Email = FString::Printf(TEXT("%s@gamefuse.com"), *Username);

	// Store the username for later use
	UserData->Username = Username;

	FGFApiCallback Callback;
	Callback.AddLambda([this](const FGFAPIResponse& Response) {
		Test->AddErrorIfFalse(Response.bSuccess || !UserData.IsValid(), FString::Printf(TEXT("Create User Request failed. Response: %s"), *Response.ResponseStr));

		FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, UserData.Get());

		Test->TestTrue("User ID should be valid", UserData->Id != 0);
		Test->AddErrorIfFalse(UserData->Id != 0, TEXT("User was not initialized"));
	});

	if (GameData->Id != 0) {
		RequestId = APIHandler->CreateUser(GameData->Id, Username, Email, Callback);
	} else {
		Test->AddError(TEXT("GameData ID is 0 in FCreateUser::Update"));
		return true; // End the command
	}

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
		Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Create Store ItemRequest failed. Response: %s"), *Response.ResponseStr));

		FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, StoreItem.Get());

		Test->TestTrue("Store Item ID should be valid", StoreItem->Id != 0);
		Test->AddErrorIfFalse(StoreItem->Id != 0, TEXT("Store Item was not initialized"));
	});

	RequestId = APIHandler->CreateStoreItem(GameData->Id, NewItem, Callback);
	return false;
}



bool FCleanupGame::Update()
{
	if (RequestId.IsValid()) {
		return !APIHandler->IsRequestActive(RequestId);
	}

	FGFApiCallback Callback;
	Callback.AddLambda([this](const FGFAPIResponse& Response) {
		Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Clean up request failed. Response: %s"), *Response.ResponseStr));

		bCleanupSuccess = Response.bSuccess;
	});

	RequestId = APIHandler->CleanupGame(GameData->Id, Callback);
	return false;
}

bool FWaitForFGFResponse::Update()
{
	if (!RequestId.IsValid()) {
		return true;
	}

	UE_LOG(LogGameFuse, Log, TEXT("Waiting for request %s to complete. Is Active: %s"), 
		*RequestId.ToString(), 
		APIHandler->IsRequestActive(RequestId) ? TEXT("True") : TEXT("False"));

	return !APIHandler->IsRequestActive(RequestId);
}