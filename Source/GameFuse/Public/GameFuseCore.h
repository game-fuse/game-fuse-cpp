/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFuseUser.h"

#include "Objects/GameFuseLeaderboardItem.h"
#include "Objects/GameFuseStoreItem.h"

#include "Models/HTTPResponseManager.h"
#include "Models/StaticAPIManager.h"

#include "Kismet/KismetStringLibrary.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"

#include "GameFuseCore.generated.h"


UCLASS()
class GAMEFUSE_API UGameFuseCore : public UStaticAPIManager
{
	GENERATED_BODY()
	
public:

	//> Getters
    UFUNCTION(BlueprintPure, Category = "GameFuse")
    	static int32 GetGameId();
	
    UFUNCTION(BlueprintPure, Category = "GameFuse")
    	static FString GetGameName();

    UFUNCTION(BlueprintPure, Category = "GameFuse")
    	static FString GetGameDescription();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
		static FString GetGameToken();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
		static FString GetBaseURL();	

	UFUNCTION(BlueprintPure, Category = "GameFuse")
		static const TMap<FString, FString>& GetGameVariables();
	
	UFUNCTION(BlueprintPure, Category = "GameFuse")
		static const TArray<UGameFuseStoreItem*>& GetGameStoreItems();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
		static const TArray<UGameFuseLeaderboardItem*>& GetLeaderboard();
		
	//> GameSetup
	UFUNCTION(BlueprintCallable, Category = "GameFuse")
		static void SetUpGame(const FString& InGameId, const FString& InToken, bool bSeedStore, FGameFuseAPIResponseCallback CompletionCallback);
	
	//> Action Requests
	UFUNCTION(BlueprintCallable, Category = "GameFuse")
		static void SendPasswordResetEmail(const FString& Email, FGameFuseAPIResponseCallback CompletionCallback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse")
		static void FetchGameVariables(FGameFuseAPIResponseCallback CompletionCallback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse")
		static void FetchLeaderboardEntries(UGameFuseUser* GameFuseUser, const int Limit, bool bOnePerUser, const FString& LeaderboardName, FGameFuseAPIResponseCallback CompletionCallback);
	
    UFUNCTION(BlueprintCallable, Category = "GameFuse")
    	static void FetchStoreItems(FGameFuseAPIResponseCallback CompletionCallback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse")
		static void InternalResponseManager(bool bWasSuccessful, const FString& ResponseStr);

private:
	
    static int32 GameId;
    static FString Token;
    static FString Name;
    static FString Description;

	static TArray<UGameFuseStoreItem*> StoreItems;
	static TArray<UGameFuseLeaderboardItem*> LeaderboardEntries;
	static TMap<FString, FString> GameVariables;
	
	static void SetSetUpGameInternal(const TSharedPtr<FJsonObject>& JsonObject);
	static void SetVariablesInternal(const FString& JsonStr);
	static void SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject);
	static void SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject);
	
};