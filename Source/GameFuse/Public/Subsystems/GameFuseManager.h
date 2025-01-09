/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Engine/GameInstance.h"

#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Kismet/BlueprintFunctionLibrary.h"


#include "Library/GameFuseStructLibrary.h"
#include "API/CoreAPIHandler.h"

#include "GameFuseManager.generated.h"


//TODO: update class methods.md docs to reflect this list
UCLASS()
class GAMEFUSE_API UGameFuseManager : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;


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

	/**
	 * CPP only usage
	 * @return A reference to the RequestHandler
	 */
	TObjectPtr<UAPIRequestHandler> GetRequestHandler()
	{
		return RequestHandler;
	}

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


	UFUNCTION(NotBlueprintable, Category = "GameFuse | Manager")
	void ClearGameData();


	/**
	 * DO NOT USE FROM C++
	 * @brief Registers the GameFuseManager with the GameFuse API.
	 * @param GameId The GameFuse ID of the game.
	 * @param Token The GameFuse API Token of the game.
	 * @param Callback The blueprint delegate to be called when the request is complete. Only bound to the node's delegate pin.
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Set Up Game", Category = "GameFuse | Manager")
	void BP_SetUpGame(const FString& GameId, const FString& Token, const FBP_GFApiCallback& Callback);

	/**
	 * @brief CPP implementation. Registers the GameFuseManager with the GameFuse API.
	 * @param GameId The GameFuse ID of the game.
	 * @param Token The GameFuse API Token of the game.
	 * @param Callback The cpp multicast delegate to be called when the request is complete. Can be bound many times.
	 */
	FGuid SetUpGame(const int GameId, const FString& Token, FGFApiCallback Callback);

	/**
	 * DO NOT USE FROM C++
	 * Sends a password reset email to the specified email address.
	 * @param Email Address to send the password reset email to.
	 * @param Callback Blueprint Dynamic Delegate
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Send Password Reset Email", Category = "GameFuse | Manager")
	void BP_SendPasswordResetEmail(const FString& Email, const FBP_GFApiCallback& Callback);

	/**
	 * Sends a password reset email to the specified email address.
	 * @param Email Address to send the password reset email to.
	 * @param Callback Cpp Multicast Delegate
	 */
	FGuid SendPasswordResetEmail(const FString& Email, FGFApiCallback Callback);

	/**
	 * DO NOT USE FROM C++
	 * Get GameVariables set in GameFuse Dashboard
	 * @param Callback Blueprint Dynamic Delegate
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Fetch Game Variables", Category = "GameFuse | Manager")
	void BP_FetchGameVariables(const FBP_GFApiCallback& Callback);

	/**
	 * Get GameVariables set in GameFuse Dashboard
	 * @param Callback CPP Multicast Delegate
	 */
	FGuid FetchGameVariables(FGFApiCallback Callback);

	/**
	 * DO NOT USE FROM C++
	 * Fetches Leaderboard entries
	 * @param GameFuseUser
	 * @param Limit The number of entries to fetch.
	 * @param bOnePerUser Whether to fetch one entry per user or not.
	 * @param LeaderboardName The name of the leaderboard to fetch entries from.
	 * @param Callback Blueprint Dynamic Delegate
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Fetch Leaderboard Entries", Category = "GameFuse | Manager")
	void BP_FetchLeaderboardEntries(const int Limit, bool bOnePerUser, const FString& LeaderboardName, const FBP_GFApiCallback& Callback);

	/**
	 * Fetches Leaderboard entries
	 * @param GameFuseUser
	 * @param Limit The number of entries to fetch.
	 * @param bOnePerUser Whether to fetch one entry per user or not.
	 * @param LeaderboardName The name of the leaderboard to fetch entries from.
	 * @param Callback Blueprint Dynamic Delegate
	 */
	FGuid FetchLeaderboardEntries(const int Limit, bool bOnePerUser, const FString& LeaderboardName, FGFApiCallback Callback);

	/**
	 * DO NOT USE FROM C++
	 * Get Store items from GameFuse Dashboard
	 * @param Callback Blueprint Dynamic Delegate
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Fetch Store Items", Category = "GameFuse | Manager")
	void BP_FetchStoreItems(const FBP_GFApiCallback& Callback);

	/**
	 * Get Store items from GameFuse Dashboard
	 * @param Callback CPP Multicast Delegate
	 */
	FGuid FetchStoreItems(FGFApiCallback Callback);

private:

	FGFGameData GameData;

	TArray<FGFStoreItem> StoreItems;
	TMap<FString, FGFLeaderboard> Leaderboards;
	TArray<FGFLeaderboardEntry> EmptyEntries;
	TMap<FString, FString> GameVariables;

	UPROPERTY()
	TObjectPtr<UCoreAPIHandler> RequestHandler;


	/**
	 * Central response handling, determines internal setter from ResponseData
	 * @param ResponseData
	 */
	void InternalResponseManager(FGFAPIResponse ResponseData);
	void SetUpGameInternal(const TSharedPtr<FJsonObject>& JsonObject);
	void SetVariablesInternal(const FString& JsonStr);
	void SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject);
	void SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject);

	/**
	 * @brief Binds BP_APICallback to InternalCallback to use as multicast delegate in CPP
	 */
	void WrapBlueprintCallback(const FBP_GFApiCallback& Callback, FGFApiCallback& InternalCallback);

};