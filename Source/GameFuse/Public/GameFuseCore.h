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

#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"

#include "Kismet/BlueprintAsyncActionBase.h"
#include "Kismet/BlueprintFunctionLibrary.h"

#include "GameFuseCore.generated.h"



DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FGameFuseCallback, const FString&, ResponseString);

//TODO: update class methods.md docs to reflect this list
UCLASS()
class GAMEFUSE_API UGameFuseCore : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintAssignable)
		FGameFuseCallback OnSuccess;

	UPROPERTY(BlueprintAssignable)
		FGameFuseCallback OnError;
	
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
		static const TMap<FString, FString>& GetGameVariables();
	
	UFUNCTION(BlueprintPure, Category = "GameFuse")
		static const TArray<UGameFuseStoreItem*>& GetGameStoreItems();

	UFUNCTION(BlueprintPure, Category = "GameFuse")
		static const TArray<UGameFuseLeaderboardItem*>& GetLeaderboard();
	
	// > GameSetup
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "GameFuse")
		static UGameFuseCore* SetUpGame(const FString& InGameId, const FString& InToken, bool bSeedStore);

	//> Action Requests
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "GameFuse")
		static UGameFuseCore* SendPasswordResetEmail(const FString& Email);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "GameFuse")
		static UGameFuseCore* FetchGameVariables();

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "GameFuse")
		static UGameFuseCore* FetchLeaderboardEntries(UGameFuseUser* GameFuseUser, const int Limit, bool bOnePerUser, const FString& LeaderboardName);

	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true", WorldContext = "WorldContextObject"), Category = "GameFuse")
    	static UGameFuseCore* FetchStoreItems();

	UFUNCTION()
		void InternalResponseManager(bool bSuccess, const FString& ResponseStr);
	
private:
	
    static int32 GameId;
    static FString Token;
    static FString Name;
    static FString Description;

	static TArray<UGameFuseStoreItem*> StoreItems;
	static TArray<UGameFuseLeaderboardItem*> LeaderboardEntries;
	static TMap<FString, FString> GameVariables;

	void CompleteTask(bool bSuccess, const FString& Result);
	
	void SetSetUpGameInternal(const TSharedPtr<FJsonObject>& JsonObject);
	void SetVariablesInternal(const FString& JsonStr);
	void SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject);
	void SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject);
	
};