/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFuseManager.h"
#include "API/UserAPIHandler.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Dom/JsonObject.h"
#include "Library/GameFuseStructLibrary.h"

#include "GameFuseUser.generated.h"


//TODO: update class methods.md docs to reflect this list
UCLASS()
class GAMEFUSE_API UGameFuseUser : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	//> Subsystem Initialization and Deinitialization


	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	//> Getters

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	const FGFUserData& GetUserData() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	FString GetUsername() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	int32 GetNumberOfLogins() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	FString GetLastLogin() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	int32 GetScore() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	int32 GetCredits() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	TMap<FString, FString>& GetAttributes();

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	TArray<FString> GetAttributesKeys() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	TMap<FString, FString>& GetDirtyAttributes();

	UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
	FString GetAttributeValue(const FString Key) const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	TArray<FGFStoreItem>& GetPurchasedStoreItems();

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	const TArray<FGFLeaderboardEntry>& GetLeaderboardEntries();

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	bool IsSignedIn() const;

	FString GetAuthenticationToken() const;
	void WrapBlueprintCallback(const FBP_GFApiCallback& Callback, FGFApiCallback& InternalCallback);

	//> Sign

	UFUNCTION(BlueprintCallable, DisplayName="Sign Up", Category = "GameFuse|User")
	void BP_SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FBP_GFApiCallback Callback);

	UFUNCTION()
	void SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Sign In", Category = "GameFuse|User")
	void BP_SignIn(const FString& Email, const FString& Password, FBP_GFApiCallback Callback);

	UFUNCTION()
	void SignIn(const FString& Email, const FString& Password, FGFApiCallback Callback);

	/**
	 * Log out the current user.
	 *
	 * This will clear the user's authentication token and reset the user data.
	 *
	 */
	UFUNCTION(BlueprintCallable, DisplayName="Log Out", Category = "GameFuse|User")
	void LogOut();
	//> Action Requests

	UFUNCTION(BlueprintCallable, DisplayName="Add Credits", Category = "GameFuse|User")
	void BP_AddCredits(const int AddCredits, FBP_GFApiCallback Callback);

	UFUNCTION()
	void AddCredits(const int AddCredits, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Set Credits", Category = "GameFuse|User")
	void BP_SetCredits(const int SetCredits, FBP_GFApiCallback Callback);

	UFUNCTION()
	void SetCredits(const int SetCredits, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Add Score", Category = "GameFuse|User")
	void BP_AddScore(const int AddScore, FBP_GFApiCallback Callback);

	UFUNCTION()
	void AddScore(const int AddScore, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Set Score", Category = "GameFuse|User")
	void BP_SetScore(const int SetScore, FBP_GFApiCallback Callback);

	UFUNCTION()
	void SetScore(const int SetScore, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Set Attribute", Category = "GameFuse|User")
	void BP_SetAttribute(const FString& Key, const FString& Value, FBP_GFApiCallback Callback);

	UFUNCTION()
	void SetAttribute(const FString& SetKey, const FString& SetValue, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Set Attribute Local", Category = "GameFuse|User")
	void BP_SetAttributeLocal(const FString& Key, const FString& Value, FBP_GFApiCallback Callback);

	UFUNCTION()
	void SetAttributeLocal(const FString& SetKey, const FString& SetValue, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Remove Attribute", Category = "GameFuse|User")
	void BP_RemoveAttribute(const FString& Key, FBP_GFApiCallback Callback);

	UFUNCTION()
	void RemoveAttribute(const FString& SetKey, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Purchase Store Item With Id", Category = "GameFuse|User")
	void BP_PurchaseStoreItemWithId(const int StoreItemId, FBP_GFApiCallback Callback);

	UFUNCTION()
	void PurchaseStoreItemWithId(const int StoreItemId, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Purchase Store Item", Category = "GameFuse|User")
	void BP_PurchaseStoreItem(const FGFStoreItem& StoreItem, FBP_GFApiCallback Callback);

	UFUNCTION()
	void PurchaseStoreItem(const FGFStoreItem& StoreItem, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Remove Store Item With Id", Category = "GameFuse|User")
	void BP_RemoveStoreItemWithId(const int StoreItemId, FBP_GFApiCallback Callback);

	UFUNCTION()
	void RemoveStoreItemWithId(const int StoreItemId, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Remove Store Item", Category = "GameFuse|User")
	void BP_RemoveStoreItem(const FGFStoreItem& StoreItem, FBP_GFApiCallback Callback);

	UFUNCTION()
	void RemoveStoreItem(const FGFStoreItem& StoreItem, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Add Leaderboard Entry", Category = "GameFuse|User")
	void BP_AddLeaderboardEntry(const FString& LeaderboardName, const int Score, FBP_GFApiCallback Callback);

	UFUNCTION()
	void AddLeaderboardEntry(const FString& LeaderboardName, const int OurScore, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Add Leaderboard Entry With Attributes", Category = "GameFuse|User")
	void BP_AddLeaderboardEntryWithAttributes(const FString& LeaderboardName, const int Score, TMap<FString, FString> ExtraAttributes, FBP_GFApiCallback Callback);

	UFUNCTION()
	void AddLeaderboardEntryWithAttributes(const FString& LeaderboardName, const int OurScore, TMap<FString, FString> ExtraAttributes, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Clear Leaderboard Entry", Category = "GameFuse|User")
	void BP_ClearLeaderboardEntry(const FString& LeaderboardName, FBP_GFApiCallback Callback);

	UFUNCTION()
	void ClearLeaderboardEntry(const FString& LeaderboardName, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Fetch My Leaderboard Entries", Category = "GameFuse|User")
	void BP_FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, FBP_GFApiCallback Callback);

	/** Fetches entries for all leaderboards User has posted entries in. */

	UFUNCTION()
	void FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Fetch Attributes", Category = "GameFuse|User")
	void BP_FetchAttributes(bool bChainedFromLogin, FBP_GFApiCallback Callback);

	UFUNCTION()
	void FetchAttributes(bool bChainedFromLogin, FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Sync Local Attributes", Category = "GameFuse|User")
	void BP_SyncLocalAttributes(FBP_GFApiCallback Callback);

	UFUNCTION()
	void SyncLocalAttributes(FGFApiCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName="Fetch Purchased Store Items", Category = "GameFuse|User")
	void BP_FetchPurchasedStoreItems(bool bChainedFromLogin, FBP_GFApiCallback Callback);

	UFUNCTION()
	void FetchPurchasedStoreItems(bool bChainedFromLogin, FGFApiCallback Callback);

	UFUNCTION()
	void InternalResponseManager(FGFAPIResponse ResponseData);

private:

	FGFUserData UserData;

	TMap<FString, FString> Attributes;
	TMap<FString, FString> DirtyAttributes;
	TArray<FGFStoreItem> PurchasedStoreItems;
	TArray<FGFLeaderboardEntry> LeaderboardEntries;

	UPROPERTY()
	TObjectPtr<UGameFuseManager> GameFuseManager;
	UPROPERTY()
	TObjectPtr<UUserAPIHandler> RequestHandler;

	//> Setters

	void SetLoginInternal(const TSharedPtr<FJsonObject>& JsonObject);
	void SetCreditsInternal(const TSharedPtr<FJsonObject>& JsonObject);
	void SetScoresInternal(const TSharedPtr<FJsonObject>& JsonObject);
	void SetAttributesInternal(const TSharedPtr<FJsonObject>& JsonObject);
	void SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject);
	void SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject);

};