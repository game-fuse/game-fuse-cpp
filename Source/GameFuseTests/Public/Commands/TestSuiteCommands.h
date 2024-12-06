#pragma once

#include "CoreMinimal.h"
#include "API/TestAPIHandler.h"
#include "Library/GameFuseStructLibrary.h"
#include "Misc/AutomationTest.h"
#include "JsonObjectConverter.h"
#include "Library/GameFuseLog.h"

DEFINE_LATENT_AUTOMATION_COMMAND_FOUR_PARAMETER(
FCreateGame,
UTestAPIHandler*, APIHandler,
TSharedPtr<FGFGameData>, GameData,
FAutomationTestBase*, Test,
FGuid, RequestId);

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

DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(
FCreateUser,
UTestAPIHandler*, APIHandler,
TSharedPtr<FGFGameData>, GameData,
FGFUserData&, UserData,
FAutomationTestBase*, Test,
FGuid, RequestId);

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

DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(
FCreateStoreItem,
UTestAPIHandler*, APIHandler,
const FGFGameData&, GameData,
FGFStoreItem&, StoreItem,
FAutomationTestBase*, Test,
FGuid, RequestId);

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

DEFINE_LATENT_AUTOMATION_COMMAND_FIVE_PARAMETER(
FCleanupGame,
UTestAPIHandler*, APIHandler,
FGFGameData&, GameData,
bool&, bSuccess,
FAutomationTestBase*, Test,
FGuid, RequestId);

bool FCleanupGame::Update()
{
	if (RequestId.IsValid()) {
		return !APIHandler->IsRequestActive(RequestId);
	}


	FGFApiCallback Callback;
	Callback.AddLambda([this](const FGFAPIResponse& Response) {
		Test->AddInfo(FString::Printf(TEXT("FCleanupGame::Update - Callback invoked, Success: %d"), Response.bSuccess));
		Test->AddErrorIfFalse(Response.bSuccess, FString::Printf(TEXT("Request failed. Response: %s"), *Response.ResponseStr));

		if (Response.bSuccess) {
			bSuccess = Response.bSuccess;
			GameData = FGFGameData();
		}

		Test->TestTrue("Game cleanup should succeed", bSuccess);
		Test->TestTrue("Game ID should be reset", GameData.Id == 0);
		Test->AddErrorIfFalse(bSuccess, TEXT("Game cleanup failed"));
	});

	RequestId = APIHandler->CleanupGame(GameData.Id, Callback);
	return false;
}