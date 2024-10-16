/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */


#include "GameFuseCore.h"

#include "GameFuseUser.h"
#include "Models/CoreAPIManager.h"
#include "Kismet/KismetStringLibrary.h"
#include "Library/GameFuseStructLibrary.h"
#include "Models/GameFuseUtilities.h"



int32 UGameFuseCore::GameId = 0;
FString UGameFuseCore::Token = "";
FString UGameFuseCore::Name = "";
FString UGameFuseCore::Description = "";

TArray<FGFStoreItem> UGameFuseCore::StoreItems;
TMap<FString, FGFLeaderboard> UGameFuseCore::Leaderboards;
TArray<FGFLeaderboardEntry> UGameFuseCore::EmptyEntries;
TMap<FString, FString> UGameFuseCore::GameVariables;


// > Region Instance Getters

int32 UGameFuseCore::GetGameId()
{
	return GameId;
}

FString UGameFuseCore::GetGameName()
{
	return Name;
}

FString UGameFuseCore::GetGameDescription()
{
	return Description;
}

FString UGameFuseCore::GetGameToken()
{
	return Token;
}

const TMap<FString, FString>& UGameFuseCore::GetGameVariables()
{
	return GameVariables;
}

const TArray<FGFStoreItem>& UGameFuseCore::GetGameStoreItems()
{
	return StoreItems;
}

const TMap<FString, FGFLeaderboard>& UGameFuseCore::GetLeaderboards()
{
	return Leaderboards;
}

const TArray<FGFLeaderboardEntry>& UGameFuseCore::GetLeaderboardEntries(const FString& LeaderboardName)
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

UGameFuseCore* UGameFuseCore::SetUpGame(const FString& InGameId, const FString& InToken)
{
	UGameFuseCore* AsyncTask = NewObject<UGameFuseCore>();
	AsyncTask->AddToRoot();

	UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseCore::InternalResponseManager);

	UCoreAPIManager::SetUpGame(InGameId, InToken);

	return AsyncTask;
}


UGameFuseCore* UGameFuseCore::SendPasswordResetEmail(const FString& Email)
{
	UGameFuseCore* AsyncTask = NewObject<UGameFuseCore>();
	AsyncTask->AddToRoot();

	if (GameId == 0)
	{
		UE_LOG(LogGameFuse, Error, TEXT("Please set up your game with SetUpGame() before sending password resets"));
		AsyncTask->CompleteTask(false, "Please set up your game with SetUpGame() before sending password resets");
		return AsyncTask;
	}

	UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseCore::InternalResponseManager);

	UCoreAPIManager::SendPasswordResetEmail(Email, GameId, Token);

	return AsyncTask;
}

UGameFuseCore* UGameFuseCore::FetchGameVariables()
{
	UGameFuseCore* AsyncTask = NewObject<UGameFuseCore>();
	AsyncTask->AddToRoot();

	UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseCore::InternalResponseManager);

	UCoreAPIManager::FetchGameVariables(GameId, Token);

	return AsyncTask;
}

UGameFuseCore* UGameFuseCore::FetchLeaderboardEntries(UGameFuseUser* GameFuseUser, const int Limit, bool bOnePerUser, const FString& LeaderboardName)
{
	UGameFuseCore* AsyncTask = NewObject<UGameFuseCore>();
	AsyncTask->AddToRoot();

	UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseCore::InternalResponseManager);

	UCoreAPIManager::FetchLeaderboardEntries(Limit, bOnePerUser, LeaderboardName, GameId, GameFuseUser->GetAuthenticationToken());

	return AsyncTask;
}

UGameFuseCore* UGameFuseCore::FetchStoreItems()
{
	UGameFuseCore* AsyncTask = NewObject<UGameFuseCore>();
	AsyncTask->AddToRoot();

	UHTTPResponseManager::CompletionCallback.BindDynamic(AsyncTask, &UGameFuseCore::InternalResponseManager);

	UCoreAPIManager::FetchStoreItems(GameId, Token);

	return AsyncTask;
}

// < End Region


void UGameFuseCore::CompleteTask(bool bSuccess, const FString& Result)
{
	if (bSuccess)
	{
		OnSuccess.Broadcast(Result);
	}
	else
	{
		OnError.Broadcast(Result);
	}
	RemoveFromRoot(); // Allow garbage collection
}


// > Region Internal Setters

void UGameFuseCore::InternalResponseManager(bool bSuccess, const FString& ResponseStr)
{
	if (!bSuccess)
	{
		this->CompleteTask(bSuccess, ResponseStr);
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
			this->CompleteTask(bSuccess, ResponseStr);
			break;
		case EGFCoreAPIResponseType::ListLeaderboardEntries:
			SetLeaderboardsInternal(JsonObject);
			this->CompleteTask(bSuccess, ResponseStr);
			break;
		case EGFCoreAPIResponseType::ListStoreItems:
			SetStoreItemsInternal(JsonObject);
			this->CompleteTask(bSuccess, ResponseStr);
			break;
		case EGFCoreAPIResponseType::ForgotPassword:
			UE_LOG(LogGameFuse, Log, TEXT("Forgot Password Email Sent!"));
			this->CompleteTask(bSuccess, ResponseStr);
			break;
		default:
			UE_LOG(LogGameFuse, Warning, TEXT("Unknown Core Response Data"));
	}
}

void UGameFuseCore::SetSetUpGameInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	GameId = JsonObject->GetIntegerField(TEXT("id"));
	JsonObject->TryGetStringField(TEXT("name"), Name);
	JsonObject->TryGetStringField(TEXT("token"), Token);
	JsonObject->TryGetStringField(TEXT("description"), Description);

	UE_LOG(LogGameFuse, Log, TEXT("SetUp Game Completed : %d : %s"), GameId, *Token);
}

void UGameFuseCore::SetVariablesInternal(const FString& JsonStr)
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

void UGameFuseCore::SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject)
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



void UGameFuseCore::SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject)
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

// < End Region