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
	static const FGFGameData& GetGameData();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
	static int32 GetGameId();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
	static FString GetGameName();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
	static FString GetGameDescription();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
	static FString GetGameToken();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
	static const TMap<FString, FString>& GetGameVariables();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
	static const TArray<FGFStoreItem>& GetGameStoreItems();

	/** Returns a TMap of all leaderboards that have been fetched from GameFuse */
	UFUNCTION(BlueprintPure, Category = "GameFuse")
	static const TMap<FString, FGFLeaderboard>& GetLeaderboards();

	/** Returns a TArray of all leaderboard entries that have been fetched from GameFuse.
	 *  If LeaderboardEntries have not been fetched, returns an empty TArray. */
	UFUNCTION(BlueprintPure, Category = "GameFuse")
	static const TArray<FGFLeaderboardEntry>& GetLeaderboardEntries(const FString& LeaderboardName);

	// > GameSetup

	UFUNCTION(BlueprintCallable, Category = "GameFuse | Core")
	void SetUpGame(const FString& GameId, const FString& Token, FOnApiResponseReceived Callback);

	//> Action Requests

	UFUNCTION(BlueprintCallable, Category = "GameFuse | Core")
	void SendPasswordResetEmail(const FString& Email, FOnApiResponseReceived Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse | Core")
	void FetchGameVariables(FOnApiResponseReceived Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse | Core")
	void FetchLeaderboardEntries(UGameFuseUser* GameFuseUser, const int Limit, bool bOnePerUser, const FString& LeaderboardName, FOnApiResponseReceived Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse | Core")
	void FetchStoreItems(FOnApiResponseReceived Callback);

	UFUNCTION()
	void InternalResponseManager(bool bSuccess, FString ResponseStr, FString RequestID);

private:

	static FGFGameData GameData;

	static TArray<FGFStoreItem> StoreItems;
	static TMap<FString, FGFLeaderboard> Leaderboards;
	static TArray<FGFLeaderboardEntry> EmptyEntries;
	static TMap<FString, FString> GameVariables;

	static TObjectPtr<UCoreAPIHandler> RequestHandler;

	void SetUpGameInternal(const TSharedPtr<FJsonObject>& JsonObject);
	void SetVariablesInternal(const FString& JsonStr);
	void SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject);
	void SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject);

};