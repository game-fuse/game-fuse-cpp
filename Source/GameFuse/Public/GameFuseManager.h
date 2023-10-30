// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFuseLeaderboardEntry.h"
#include "GameFuseStoreItem.h"
#include "GameFuseUser.h"
#include "Interfaces/IHttpRequest.h"
#include "Containers/UnrealString.h"
#include "HttpModule.h"
#include "Interfaces/IHttpResponse.h"
#include "Kismet/KismetStringLibrary.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "GameFuseManager.generated.h"

/**
 * 
 */
DECLARE_DYNAMIC_DELEGATE_TwoParams(FManagerCallback, bool, bSuccess, const FString&, Response);


UCLASS()
class GAMEFUSE_API UGameFuseManager : public UObject
{
	GENERATED_BODY()
	
public:
	
	//> GameSetup
    UFUNCTION(BlueprintCallable, Category = "GameFuse")
    	static void SetUpGame(const FString& InGameId, const FString& InToken, bool bSeedStore, FManagerCallback CompletionCallback);

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
		static const TArray<UGameFuseLeaderboardEntry*>& GetLeaderboard();

	//> Action Requests
	UFUNCTION(BlueprintCallable, Category = "GameFuse")
		static void SendPasswordResetEmail(const FString& Email, FManagerCallback CompletionCallback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse")
		static void FetchGameVariables(FManagerCallback CompletionCallback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse")
		static void FetchLeaderboardEntries(UGameFuseUser* GameFuseUser, const int Limit, bool bOnePerUser, const FString& LeaderboardName, FManagerCallback CompletionCallback);
	
    UFUNCTION(BlueprintCallable, Category = "GameFuse")
    	static void FetchStoreItems(FManagerCallback CompletionCallback);


private:
	
    static int32 GameId;
    static FString Token;
    static FString Name;
    static FString Description;
	static TArray<UGameFuseStoreItem*> StoreItems;
	static TArray<UGameFuseLeaderboardEntry*> LeaderboardEntries;
	static TMap<FString, FString> GameVariables;
	
	static void SetSetUpGameInternal(const TSharedPtr<FJsonObject>& JsonObject);
	static void SetVariablesInternal(const FString& JsonStr);
	static void SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject);
	static void SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject);

	static void OnHttpResponseReceivedManager(FHttpRequestPtr Request, const FHttpResponsePtr Response, bool bWasSuccessful, FManagerCallback CompletionCallback);
};