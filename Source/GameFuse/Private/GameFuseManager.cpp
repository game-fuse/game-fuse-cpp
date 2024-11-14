/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */


#include "GameFuseManager.h"

#include "GameFuseCore.h"
#include "GameFuseUser.h"
#include "Models/CoreAPIManager.h"
#include "Kismet/KismetStringLibrary.h"
#include "Library/GameFuseStructLibrary.h"
#include "Models/GameFuseUtilities.h"
#include "Objects/GameFuseAsyncAction.h"


TObjectPtr<UCoreAPIHandler> UGameFuseManager::RequestHandler;

FGFGameData UGameFuseManager::GameData;

TArray<FGFStoreItem> UGameFuseManager::StoreItems;
TMap<FString, FGFLeaderboard> UGameFuseManager::Leaderboards;
TArray<FGFLeaderboardEntry> UGameFuseManager::EmptyEntries;
TMap<FString, FString> UGameFuseManager::GameVariables;



void UGameFuseManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RequestHandler = NewObject<UCoreAPIHandler>();
}

void UGameFuseManager::Deinitialize()
{
	//do some sort of specific cleanup of request handler?
	RequestHandler = nullptr;
	Super::Deinitialize();
}

// > Region Instance Getters
const FGFGameData& UGameFuseManager::GetGameData()
{
	return GameData;
}

int32 UGameFuseManager::GetGameId()
{
	return GameData.Id;
}

FString UGameFuseManager::GetGameName()
{
	return GameData.Name;
}

FString UGameFuseManager::GetGameDescription()
{
	return GameData.Description;
}

FString UGameFuseManager::GetGameToken()
{
	return GameData.Token;
}

const TMap<FString, FString>& UGameFuseManager::GetGameVariables()
{
	return GameVariables;
}

const TArray<FGFStoreItem>& UGameFuseManager::GetGameStoreItems()
{
	return StoreItems;
}

const TMap<FString, FGFLeaderboard>& UGameFuseManager::GetLeaderboards()
{
	return Leaderboards;
}

const TArray<FGFLeaderboardEntry>& UGameFuseManager::GetLeaderboardEntries(const FString& LeaderboardName)
{
	if (!Leaderboards.Contains(LeaderboardName))
	{
		UE_LOG(LogGameFuse, Error, TEXT("Leaderboard %s has not been fetched"), *LeaderboardName);
		return EmptyEntries;
	}
	return Leaderboards[LeaderboardName].Entries;
}

// < End Region
// > Region Game Fuse Asynchronous Functions

void UGameFuseManager::SetUpGame(const FString& GameId, const FString& Token, FOnApiResponseReceived Callback)
{
	RequestHandler->SetUpGame(GameId, Token, Callback);
}


/*
UGameFuseAsyncAction* UGameFuseManager::SendPasswordResetEmail(const FString& Email)
{
	UGameFuseAsyncAction* AsyncAction = NewObject<UGameFuseAsyncAction>();

	if (GameData.Id == 0)
	{
		UE_LOG(LogGameFuse, Error, TEXT("Please set up your game with SetUpGame() before sending password resets"));
		// AsyncTask->CompleteTask(false, "Please set up your game with SetUpGame() before sending password resets");
		return AsyncAction;
	}

	// UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseManager::InternalResponseManager);
	//
	// UCoreAPIManager::SendPasswordResetEmail(Email, GameData.Id, GameData.Token);

	return AsyncAction;
}

UGameFuseAsyncAction* UGameFuseManager::FetchGameVariables()
{
	UGameFuseAsyncAction* AsyncAction = NewObject<UGameFuseAsyncAction>();

	// UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseManager::InternalResponseManager);
	//
	// UCoreAPIManager::FetchGameVariables(GameData.Id, GameData.Token);

	return AsyncAction;
}

UGameFuseAsyncAction* UGameFuseManager::FetchLeaderboardEntries(UGameFuseUser* GameFuseUser, const int Limit, bool bOnePerUser, const FString& LeaderboardName)
{
	UGameFuseAsyncAction* AsyncAction = NewObject<UGameFuseAsyncAction>();

	// UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseManager::InternalResponseManager);
	//
	// UCoreAPIManager::FetchLeaderboardEntries(Limit, bOnePerUser, LeaderboardName, GameData.Id, GameFuseUser->GetAuthenticationToken());

	return AsyncAction;
}

UGameFuseAsyncAction* UGameFuseManager::FetchStoreItems()
{
	UGameFuseAsyncAction* AsyncAction = NewObject<UGameFuseAsyncAction>();

	// UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseManager::InternalResponseManager);
	//
	// UCoreAPIManager::FetchStoreItems(GameData.Id, GameData.Token);

	return AsyncAction;
}

//< End Region/
*/

// > Region Internal Setters
void UGameFuseManager::InternalResponseManager(bool bSuccess, const FString& ResponseStr)
{
	if (!bSuccess)
	{
		// this->CompleteTask(bSuccess, ResponseStr);
		return;
	}

	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseStr);
	TSharedPtr<FJsonObject> JsonObject;

	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UE_LOG(LogGameFuse, Error, TEXT("Failed To Parse JSON Response"));
		return;
	}

	switch (GameFuseUtilities::DetermineCoreAPIResponseType(JsonObject))
	{
		case EGFCoreAPIResponseType::SetUpGame:
			SetSetUpGameInternal(JsonObject);
			SetVariablesInternal(ResponseStr);
		// this->CompleteTask(bSuccess, ResponseStr);
			break;
		case EGFCoreAPIResponseType::ListLeaderboardEntries:
			SetLeaderboardsInternal(JsonObject);
		// this->CompleteTask(bSuccess, ResponseStr);
			break;
		case EGFCoreAPIResponseType::ListStoreItems:
			SetStoreItemsInternal(JsonObject);
		// this->CompleteTask(bSuccess, ResponseStr);
			break;
		case EGFCoreAPIResponseType::ForgotPassword:
			UE_LOG(LogGameFuse, Log, TEXT("Forgot Password Email Sent!"));
		// this->CompleteTask(bSuccess, ResponseStr);
			break;
		default:
			UE_LOG(LogGameFuse, Warning, TEXT("Unknown Core Response Data"));
	}
}

void UGameFuseManager::SetSetUpGameInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	bool bSuccess = GameFuseUtilities::ConvertJsonToGameData(GameData, JsonObject);
	if (!bSuccess)
	{
		UE_LOG(LogGameFuse, Error, TEXT("Failed To Parse Game Data"));
	}
	UE_LOG(LogGameFuse, Log, TEXT("SetUp Game Completed : %d : %s"), GameData.Id, *GameData.Token);
}

void UGameFuseManager::SetVariablesInternal(const FString& JsonStr)
{
	GameVariables.Empty();

	const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonStr);

	if (TSharedPtr<FJsonObject> JsonObject; FJsonSerializer::Deserialize(JsonReader, JsonObject))
	{
		if (const TArray<TSharedPtr<FJsonValue>>* GameVariablesArray = nullptr; JsonObject->TryGetArrayField(TEXT("game_variables"), GameVariablesArray))
		{
			for (const TSharedPtr<FJsonValue>& JsonValue : *GameVariablesArray)
			{
				const TSharedPtr<FJsonObject> VariableObject = JsonValue->AsObject();

				FString Key = "";
				FString Value = "";

				if (VariableObject->TryGetStringField(TEXT("key"), Key) && VariableObject->TryGetStringField(TEXT("value"), Value))
				{
					GameVariables.Add(Key, Value);
				}
			}
			UE_LOG(LogGameFuse, Log, TEXT("Fetched Variables amount of : %d"), GameVariables.Num());
		}
	}
	else
	{
		// Handle JSON parsing error
		UE_LOG(LogGameFuse, Error, TEXT("Fetching Game Variables Failed to parse JSON"));
	}
}

void UGameFuseManager::SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject)
{

	if (!JsonObject->HasField(TEXT("leaderboard_entries")))
	{
		UE_LOG(LogGameFuse, Error, TEXT("Fetching Leaderboard Failed to parse JSON"));
		return;
	}

	const TArray<TSharedPtr<FJsonValue>>& AttributeArray = JsonObject->GetArrayField(TEXT("leaderboard_entries"));
	if (AttributeArray.Num() == 0)
	{
		return;
	}

	// grab leaderboard_name from the first entry
	const FString LeaderboardKey = AttributeArray[0]->AsObject()->GetStringField(TEXT("leaderboard_name"));

	// Entries.Reserve(AttributeArray.Num());

	if (!Leaderboards.Contains(LeaderboardKey))
	{
		Leaderboards.Add(LeaderboardKey, FGFLeaderboard(LeaderboardKey));
	}
	else
	{
		Leaderboards[LeaderboardKey].Entries.Empty();
	}

	TArray<FGFLeaderboardEntry>& CurrLeaderboardEntries = Leaderboards[LeaderboardKey].Entries;
	CurrLeaderboardEntries.Reserve(AttributeArray.Num());


	for (const TSharedPtr<FJsonValue>& AttributeValue : AttributeArray)
	{
		const size_t newIndex = CurrLeaderboardEntries.AddDefaulted();
		const bool bSuccess = GameFuseUtilities::ConvertJsonToLeaderboardItem(CurrLeaderboardEntries[newIndex], AttributeValue);
		if (!bSuccess)
		{
			CurrLeaderboardEntries.RemoveAt(newIndex);
		}

	}
	UE_LOG(LogGameFuse, Log, TEXT("Fetched Leaderboards amount of : %d"), CurrLeaderboardEntries.Num());

}



void UGameFuseManager::SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	StoreItems.Empty();

	if (const TArray<TSharedPtr<FJsonValue>>* AttributeArray; JsonObject->TryGetArrayField(TEXT("store_items"), AttributeArray))
	{
		StoreItems.Reserve(AttributeArray->Num());
		for (const TSharedPtr<FJsonValue>& AttributeValue : *AttributeArray)
		{
			//create store items in place
			const size_t newIndex = StoreItems.AddDefaulted();

			bool bSuccess = GameFuseUtilities::ConvertJsonToStoreItem(StoreItems[newIndex], AttributeValue);
			if (!bSuccess)
			{
				StoreItems.RemoveAt(newIndex);
			}
		}
		UE_LOG(LogGameFuse, Log, TEXT("Fetched Store Items amount of : %d"), StoreItems.Num());
	}
	else
	{
		UE_LOG(LogGameFuse, Error, TEXT("Fetching Store Items Failed to parse JSON"));
	}
}