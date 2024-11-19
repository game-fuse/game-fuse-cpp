/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFuseCore.h"
#include "GameFuseUser.h"

#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"

#include "Kismet/BlueprintFunctionLibrary.h"
#include "Library/GameFuseStructLibrary.h"
#include "Models/CoreAPIHandler.h"
#include "Objects/GameFuseAsyncAction.h"

#include "GameFuseManager.generated.h"


//TODO: update class methods.md docs to reflect this list
UCLASS()
class GAMEFUSE_API UGameFuseManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	//> Subsystem Initialization and Deinitialization

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	//> Getters
	UFUNCTION(BlueprintPure, Category = "GameFuse")
	const FGFGameData& GetGameData();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
	int32 GetGameId();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
	FString GetGameName();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
	FString GetGameDescription();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
	FString GetGameToken();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
	const TMap<FString, FString>& GetGameVariables();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
	const TArray<FGFStoreItem>& GetGameStoreItems();

	/** Returns a TMap of all leaderboards that have been fetched from GameFuse */
	UFUNCTION(BlueprintPure, Category = "GameFuse")
	const TMap<FString, FGFLeaderboard>& GetLeaderboards();

	/** Returns a TArray of all leaderboard entries that have been fetched from GameFuse.
	 *  If LeaderboardEntries have not been fetched, returns an empty TArray. */
	UFUNCTION(BlueprintPure, Category = "GameFuse | Manager")
	const TArray<FGFLeaderboardEntry>& GetLeaderboardEntries(const FString& LeaderboardName);

	UFUNCTION(BlueprintPure, Category = "GameFuse | Manager")
	bool IsSetUp();

	UFUNCTION(NotBlueprintable, Category = "GameFuse | Manager")
	bool SetupCheck();


	/*
	 * Registers the GameFuseManager with the GameFuse API.
	 * GameId The GameFuse ID of the game.
	 * Token The GameFuse API Token of the game.
	 */
	UFUNCTION(BlueprintCallable, Category = "GameFuse | Manager")
	void SetUpGame(const FString& GameId, const FString& Token, const FBP_ApiCallback& Callback);

	//> Action Requests

	UFUNCTION(BlueprintCallable, Category = "GameFuse | Manager")
	void SendPasswordResetEmail(const FString& Email, const FBP_ApiCallback& Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse | Manager")
	void FetchGameVariables(const FBP_ApiCallback& Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse | Manager")
	void FetchLeaderboardEntries(UGameFuseUser* GameFuseUser, const int Limit, bool bOnePerUser, const FString& LeaderboardName, const FBP_ApiCallback& Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse | Manager")
	void FetchStoreItems(const FBP_ApiCallback& Callback);

	UFUNCTION()
	void InternalResponseManager(FGFAPIResponse ResponseData);

private:

	FGFGameData GameData;

	TArray<FGFStoreItem> StoreItems;
	TMap<FString, FGFLeaderboard> Leaderboards;
	TArray<FGFLeaderboardEntry> EmptyEntries;
	TMap<FString, FString> GameVariables;

	TObjectPtr<UCoreAPIHandler> RequestHandler;

	void SetUpGameInternal(const TSharedPtr<FJsonObject>& JsonObject);
	void SetVariablesInternal(const FString& JsonStr);
	void SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject);
	void SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject);

};