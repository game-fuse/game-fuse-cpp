/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */


#include "Subsystems/GameFuseManager.h"

#include "Subsystems/GameFuseUser.h"
#include "Library/GameFuseLog.h"
#include "Library/GameFuseUtilities.h"


#pragma region Subsystem Overloads

void UGameFuseManager::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RequestHandler = NewObject<UCoreAPIHandler>();
}

void UGameFuseManager::Deinitialize()
{
	// do some sort of specific cleanup of request handler?
	RequestHandler = nullptr;
	Super::Deinitialize();
}

#pragma endregion

#pragma region Instance Getters

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
	if (!Leaderboards.Contains(LeaderboardName)) {
		UE_LOG(LogGameFuse, Error, TEXT("Leaderboard %s has not been fetched"), *LeaderboardName);
		return EmptyEntries;
	}
	return Leaderboards[LeaderboardName].Entries;
}

#pragma endregion

#pragma region Blueprint Delegate Wrappers

void UGameFuseManager::StoreBlueprintCallback(const FGuid& RequestId, const FBP_GFApiCallback& Callback)
{
	if (Callback.IsBound()) {
		BlueprintCallbacks.Add(RequestId, Callback);
	}
}

void UGameFuseManager::ExecuteBlueprintCallback(const FGFAPIResponse& Response)
{
	if (BlueprintCallbacks.Contains(Response.RequestId)) {
		BlueprintCallbacks[Response.RequestId].ExecuteIfBound(Response);
		BlueprintCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseManager::BP_SetUpGame(const FString& GameId, const FString& Token, const FBP_GFApiCallback& Callback = FBP_GFApiCallback())
{
	FGFApiCallback InternalCallback;

	FGuid RequestId = SetUpGame(FCString::Atoi(*GameId), Token, InternalCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseManager::BP_SendPasswordResetEmail(const FString& Email, const FBP_GFApiCallback& Callback = FBP_GFApiCallback())
{
	FGFApiCallback InternalCallback;

	FGuid RequestId = SendPasswordResetEmail(Email, InternalCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseManager::BP_FetchGameVariables(const FBP_GFApiCallback& Callback = FBP_GFApiCallback())
{
	FGFApiCallback InternalCallback;

	FGuid RequestId = FetchGameVariables(InternalCallback);
	StoreBlueprintCallback(RequestId, Callback);
}


void UGameFuseManager::BP_FetchStoreItems(const FBP_GFApiCallback& Callback = FBP_GFApiCallback())
{
	FGFApiCallback InternalCallback;

	FGuid RequestId = FetchStoreItems(InternalCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseManager::BP_FetchLeaderboardEntries(const int Limit = 20, bool bOnePerUser = false, const FString& LeaderboardName = "", const FBP_GFApiCallback& Callback = FBP_GFApiCallback())
{
	FGFApiCallback InternalCallback;

	FGuid RequestId = FetchLeaderboardEntries(Limit, bOnePerUser, LeaderboardName, InternalCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

#pragma endregion

#pragma region CPP Implementations

FGuid UGameFuseManager::SetUpGame(int GameId, const FString& Token, FGFApiCallback Callback)
{
	if (GameId <= 0) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid Game ID: %d. Game ID must be greater than 0"), GameId);
		FGFAPIResponse ErrorResponse;
		ErrorResponse.bSuccess = false;
		ErrorResponse.ResponseStr = TEXT("Invalid Game ID. Game ID must be greater than 0");
		Callback.Broadcast(ErrorResponse);
		return FGuid();
	}

	if (Token.IsEmpty()) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid Token: Token cannot be empty"));
		FGFAPIResponse ErrorResponse;
		ErrorResponse.bSuccess = false;
		ErrorResponse.ResponseStr = TEXT("Invalid Token. Token cannot be empty");
		Callback.Broadcast(ErrorResponse);
		return FGuid();
	}

	Callback.AddUObject(this, &UGameFuseManager::HandleSetUpGameResponse);
	return RequestHandler->SetUpGame(GameId, Token, Callback);
}

FGuid UGameFuseManager::SendPasswordResetEmail(const FString& Email, FGFApiCallback Callback)
{
	if (!SetupCheck()) {
		return FGuid();
	}

	Callback.AddUObject(this, &UGameFuseManager::HandleForgotPasswordResponse);
	return RequestHandler->SendPasswordResetEmail(Email, GameData.Id, GameData.Token, Callback);
}


FGuid UGameFuseManager::FetchGameVariables(FGFApiCallback Callback)
{
	if (!SetupCheck()) {
		return FGuid();
	}

	Callback.AddUObject(this, &UGameFuseManager::HandleGameVariablesResponse);
	return RequestHandler->FetchGameVariables(GameData.Id, GameData.Token, Callback);
}

FGuid UGameFuseManager::FetchLeaderboardEntries(const int Limit, bool bOnePerUser, const FString& LeaderboardName, FGFApiCallback Callback)
{
	if (!SetupCheck()) {
		return FGuid();
	}
	const FGFUserData& UserData = GetGameInstance()->GetSubsystem<UGameFuseUser>()->GetUserData();

	Callback.AddUObject(this, &UGameFuseManager::HandleLeaderboardEntriesResponse);
	return RequestHandler->FetchLeaderboardEntries(Limit, bOnePerUser, LeaderboardName, GameData.Id, UserData.AuthenticationToken, Callback);
}

FGuid UGameFuseManager::FetchStoreItems(FGFApiCallback Callback)
{
	if (!SetupCheck()) {
		return FGuid();
	}

	Callback.AddUObject(this, &UGameFuseManager::HandleStoreItemsResponse);
	return RequestHandler->FetchStoreItems(GameData.Id, GameData.Token, Callback);
}

#pragma endregion

#pragma region Utility Methods

bool UGameFuseManager::IsSetUp()
{
	return GameData.Id != 0 && !GameData.Token.IsEmpty();
}


/**
 * Checks if GameFuse has been set up.
 * @return True if GameFuse has been set up, false otherwise.
 */
bool UGameFuseManager::SetupCheck()
{
	if (!IsSetUp()) {
		UE_LOG(LogGameFuse, Error, TEXT("GameFuse has not been set up. Please call BPSetUpGame() before using GameFuse."));
		return false;
	}
	return true;
}

void UGameFuseManager::ClearGameData()
{
	GameData = FGFGameData();
}

#pragma endregion

#pragma region Response Handlers

void UGameFuseManager::HandleSetUpGameResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Warning, TEXT("SetUpGame Request Failed. ID : %s"), *Response.RequestId.ToString());
		// Execute the blueprint callback even on failure
		ExecuteBlueprintCallback(Response);
		return;
	}
	
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.ResponseStr);
	TSharedPtr<FJsonObject> JsonObject;

	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed To Parse JSON Response"));
		// Execute the blueprint callback even on parsing failure
		ExecuteBlueprintCallback(Response);
		return;
	}

	// Handle game data
	const bool bSuccess = GameFuseUtilities::ConvertJsonToGameData(GameData, JsonObject);
	if (!bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed To Parse Game Data"));
	}
	UE_LOG(LogGameFuse, Log, TEXT("SetUp Game Completed : %d : %s"), GameData.Id, *GameData.Token);
	
	// Handle game variables using the utility function
	GameFuseUtilities::ConvertJsonToGameVariables(GameVariables, JsonObject);
	
	// Execute the blueprint callback after all data is processed
	ExecuteBlueprintCallback(Response);
}

void UGameFuseManager::HandleLeaderboardEntriesResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Warning, TEXT("FetchLeaderboardEntries Request Failed. ID : %s"), *Response.RequestId.ToString());
		// Execute the blueprint callback even on failure
		ExecuteBlueprintCallback(Response);
		return;
	}
	
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.ResponseStr);
	TSharedPtr<FJsonObject> JsonObject;

	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed To Parse JSON Response"));
		// Execute the blueprint callback even on parsing failure
		ExecuteBlueprintCallback(Response);
		return;
	}

	if (!JsonObject->HasField(TEXT("leaderboard_entries"))) {
		UE_LOG(LogGameFuse, Error, TEXT("Fetching Leaderboard Failed to parse JSON"));
		// Execute the blueprint callback even on missing field
		ExecuteBlueprintCallback(Response);
		return;
	}

	const TArray<TSharedPtr<FJsonValue>>& AttributeArray = JsonObject->GetArrayField(TEXT("leaderboard_entries"));
	if (AttributeArray.Num() == 0) {
		UE_LOG(LogGameFuse, Log, TEXT("Leaderboard Entries Empty"));
		// Execute the blueprint callback even on empty array
		ExecuteBlueprintCallback(Response);
		return;
	}

	// grab leaderboard_name from the first entry
	const FString LeaderboardKey = AttributeArray[0]->AsObject()->GetStringField(TEXT("leaderboard_name"));

	if (!Leaderboards.Contains(LeaderboardKey)) {
		Leaderboards.Add(LeaderboardKey, FGFLeaderboard(LeaderboardKey));
	} else {
		Leaderboards[LeaderboardKey].Entries.Empty();
	}

	TArray<FGFLeaderboardEntry>& CurrLeaderboardEntries = Leaderboards[LeaderboardKey].Entries;
	CurrLeaderboardEntries.Reserve(AttributeArray.Num());

	for (const TSharedPtr<FJsonValue>& AttributeValue : AttributeArray) {
		const size_t newIndex = CurrLeaderboardEntries.AddDefaulted();
		const bool bSuccess = GameFuseUtilities::ConvertJsonToLeaderboardEntry(CurrLeaderboardEntries[newIndex], AttributeValue);
		if (!bSuccess) {
			CurrLeaderboardEntries.RemoveAt(newIndex);
		}
	}
	UE_LOG(LogGameFuse, Log, TEXT("Fetched Leaderboards amount of : %d"), CurrLeaderboardEntries.Num());
	
	// Execute the blueprint callback after all data is processed
	ExecuteBlueprintCallback(Response);
}

void UGameFuseManager::HandleStoreItemsResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Warning, TEXT("FetchStoreItems Request Failed. ID : %s"), *Response.RequestId.ToString());
		// Execute the blueprint callback even on failure
		ExecuteBlueprintCallback(Response);
		return;
	}
	
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.ResponseStr);
	TSharedPtr<FJsonObject> JsonObject;

	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed To Parse JSON Response"));
		// Execute the blueprint callback even on parsing failure
		ExecuteBlueprintCallback(Response);
		return;
	}

	StoreItems.Empty();

	if (const TArray<TSharedPtr<FJsonValue>>* AttributeArray; JsonObject->TryGetArrayField(TEXT("store_items"), AttributeArray)) {
		StoreItems.Reserve(AttributeArray->Num());
		for (const TSharedPtr<FJsonValue>& AttributeValue : *AttributeArray) {
			// create store items in place
			const size_t newIndex = StoreItems.AddDefaulted();

			bool bSuccess = GameFuseUtilities::ConvertJsonToStoreItem(StoreItems[newIndex], AttributeValue);
			if (!bSuccess) {
				StoreItems.RemoveAt(newIndex);
			}
		}
		UE_LOG(LogGameFuse, Log, TEXT("Fetched Store Items amount of : %d"), StoreItems.Num());
	} else {
		UE_LOG(LogGameFuse, Error, TEXT("Fetching Store Items Failed to parse JSON"));
	}
	
	// Execute the blueprint callback after all data is processed
	ExecuteBlueprintCallback(Response);
}

void UGameFuseManager::HandleGameVariablesResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Warning, TEXT("FetchGameVariables Request Failed. ID : %s"), *Response.RequestId.ToString());
		// Execute the blueprint callback even on failure
		ExecuteBlueprintCallback(Response);
		return;
	}
	
	// Use the utility function to parse game variables
	GameFuseUtilities::ConvertJsonToGameVariables(GameVariables, Response.ResponseStr);
	
	// Execute the blueprint callback after all data is processed
	ExecuteBlueprintCallback(Response);
}

void UGameFuseManager::HandleForgotPasswordResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Warning, TEXT("SendPasswordResetEmail Request Failed. ID : %s"), *Response.RequestId.ToString());
		// Execute the blueprint callback even on failure
		ExecuteBlueprintCallback(Response);
		return;
	}
	
	UE_LOG(LogGameFuse, Log, TEXT("Forgot Password Email Sent!"));
	
	// Execute the blueprint callback after all data is processed
	ExecuteBlueprintCallback(Response);
}

#pragma endregion