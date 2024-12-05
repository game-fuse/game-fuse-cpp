#pragma once

#include "CoreMinimal.h"
#include "API/TestAPIHandler.h"
#include "Library/GameFuseStructLibrary.h"
#include "Misc/AutomationTest.h"
#include "JsonObjectConverter.h"
#include "Library/GameFuseLog.h"

DEFINE_LATENT_AUTOMATION_COMMAND_TWO_PARAMETER(
FCreateGameLatentCommand,
UTestAPIHandler*, APIHandler,
FGFGameData&, GameData);

bool FCreateGameLatentCommand::Update()
{
	static FGuid RequestId;
	if (!RequestId.IsValid()) {
		FGFApiCallback Callback;
		FGFGameData* GameDataPtr = &GameData;
		Callback.AddLambda([this, GameDataPtr](const FGFAPIResponse& Response) {
			if (Response.bSuccess) {
				UE_LOG(LogTemp, Log, TEXT("Response String: %s"), *Response.ResponseStr);

				//check game data valid
				ensure(GameDataPtr);
				FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, GameDataPtr);
			}
		});
		RequestId = APIHandler->CreateGame(Callback);
		return false;
	}

	return !APIHandler->IsResponseActive(RequestId);
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(
FCreateUserLatentCommand,
UTestAPIHandler*, APIHandler,
const FGFGameData&, GameData,
FGFUserData&, UserData);

bool FCreateUserLatentCommand::Update()
{
	static FGuid RequestId;
	if (!RequestId.IsValid()) {
		FGFApiCallback Callback;
		FGFUserData* UserDataPtr = &UserData;
		Callback.AddLambda([UserDataPtr](const FGFAPIResponse& Response) {
			if (Response.bSuccess) {
				UE_LOG(LogTemp, Log, TEXT("Response String: %s"), *Response.ResponseStr);
				FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, UserDataPtr, 0, 0);
			}
		});
		RequestId = APIHandler->CreateUser(GameData.Id, TEXT("TestUser"), TEXT("test@example.com"), Callback);
		return false;
	}

	return !APIHandler->IsResponseActive(RequestId);
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(
FCreateStoreItemLatentCommand,
UTestAPIHandler*, APIHandler,
const FGFGameData&, GameData,
FGFStoreItem&, StoreItem);

bool FCreateStoreItemLatentCommand::Update()
{
	static FGuid RequestId;
	if (!RequestId.IsValid()) {
		FGFStoreItem NewItem;
		NewItem.Name = TEXT("TestItem");
		NewItem.Description = TEXT("Test Item Description");
		NewItem.Cost = 100;

		FGFApiCallback Callback;
		FGFStoreItem* StoreItemPtr = &StoreItem;
		Callback.AddLambda([StoreItemPtr](const FGFAPIResponse& Response) {
			if (Response.bSuccess) {
				UE_LOG(LogTemp, Log, TEXT("Response String: %s"), *Response.ResponseStr);
				FJsonObjectConverter::JsonObjectStringToUStruct(Response.ResponseStr, StoreItemPtr, 0, 0);
			}
		});
		RequestId = APIHandler->CreateStoreItem(GameData.Id, NewItem, Callback);
		return false;
	}

	return !APIHandler->IsResponseActive(RequestId);
}

DEFINE_LATENT_AUTOMATION_COMMAND_THREE_PARAMETER(
FCleanupGameLatentCommand,
UTestAPIHandler*, APIHandler,
const FGFGameData&, GameData,
bool&, bSuccess);

bool FCleanupGameLatentCommand::Update()
{
	static FGuid RequestId;
	if (!RequestId.IsValid()) {
		FGFApiCallback Callback;
		bool* SuccessPtr = &bSuccess;
		Callback.AddLambda([SuccessPtr](const FGFAPIResponse& Response) {
			*SuccessPtr = Response.bSuccess;
			UE_LOG(LogTemp, Log, TEXT("Cleanup Response String: %s"), *Response.ResponseStr);
		});
		RequestId = APIHandler->CleanupGame(GameData.Id, Callback);
		return false;
	}

	return !APIHandler->IsResponseActive(RequestId);
}