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

// Single-cast delegates for user callbacks
DECLARE_DELEGATE_TwoParams(FGFUserDataCallback, bool, const FGFUserData&);
DECLARE_DELEGATE_TwoParams(FGFStoreItemsCallback, bool, const TArray<FGFStoreItem>&);
DECLARE_DELEGATE_TwoParams(FGFLeaderboardEntriesCallback, bool, const TArray<FGFLeaderboardEntry>&);
DECLARE_DELEGATE_TwoParams(FGFAttributesCallback, bool, const FGFAttributeList&);
DECLARE_DELEGATE_OneParam(FGFUserActionCallback, bool);

UCLASS()
class GAMEFUSE_API UGameFuseUser : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	//> Subsystem Initialization
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	//> Core User Data & Authentication
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	const FGFUserData& GetUserData() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	FString GetUsername() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	int32 GetNumberOfLogins() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	FString GetLastLogin() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	bool IsSignedIn() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	FString GetAuthenticationToken() const;

	// C++ callable functions with typed callbacks
	FGuid SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FGFUserDataCallback TypedCallback);
	FGuid SignUp(const FGFGameData& GameData, const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FGFUserDataCallback TypedCallback);
	FGuid SignIn(const FString& Email, const FString& Password, FGFUserDataCallback TypedCallback);
	FGuid SignIn(const FGFGameData& GameData, const FString& Email, const FString& Password, FGFUserDataCallback TypedCallback);

	UFUNCTION(BlueprintCallable, DisplayName = "Log Out", Category = "GameFuse|User")
	void LogOut(const FString& SaveSlotName = TEXT("GameFuseSaveSlot"));

	//> Score & Credits
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	int32 GetScore() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	int32 GetCredits() const;

	FGuid AddScore(const int32 AddScore, FGFUserDataCallback TypedCallback);
	FGuid SetScore(const int32 SetScore, FGFUserDataCallback TypedCallback);
	FGuid AddCredits(const int32 AddCredits, FGFUserDataCallback TypedCallback);
	FGuid SetCredits(const int32 SetCredits, FGFUserDataCallback TypedCallback);

	//> Store Items
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	const TArray<FGFStoreItem>& GetPurchasedStoreItems() const;

	FGuid PurchaseStoreItem(const int32 StoreItemId, FGFStoreItemsCallback TypedCallback);
	FGuid RemoveStoreItem(const int32 StoreItemId, FGFStoreItemsCallback TypedCallback);
	FGuid FetchPurchasedStoreItems(FGFStoreItemsCallback TypedCallback);

	//> Attributes
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	const TMap<FString, FString>& GetAttributes() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	TArray<FString> GetAttributesKeys() const;

	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	const TMap<FString, FString>& GetDirtyAttributes() const;

	UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
	FString GetAttributeValue(const FString Key) const;

	FGuid FetchAttributes(FGFAttributesCallback TypedCallback);
	FGuid SyncLocalAttributes(FGFAttributesCallback TypedCallback);
	FGuid SetAttribute(const FString& Key, const FString& Value, FGFAttributesCallback TypedCallback);
	FGuid SetAttributes(const TMap<FString, FString>& NewAttributes, FGFAttributesCallback TypedCallback);
	void SetAttributeLocal(const FString& SetKey, const FString& SetValue);
	FGuid RemoveAttribute(const FString& SetKey, FGFAttributesCallback TypedCallback);

	//> Leaderboards
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	const TArray<FGFLeaderboardEntry>& GetLeaderboardEntries() const;

	FGuid AddLeaderboardEntry(const FString& LeaderboardName, const int32 Score, const TMap<FString, FString>& Metadata, FGFInternalSuccessCallback TypedCallback);
	FGuid AddLeaderboardEntry(const FString& LeaderboardName, const int32 Score, FGFInternalSuccessCallback TypedCallback);
	FGuid ClearLeaderboardEntry(const FString& LeaderboardName, FGFInternalSuccessCallback TypedCallback);
	FGuid FetchMyLeaderboardEntries(const int32 Limit, bool bOnePerUser, FGFLeaderboardEntriesCallback TypedCallback);

	//> Blueprint Wrapper Functions
	UFUNCTION(BlueprintCallable, DisplayName = "Sign Up", Category = "GameFuse|User")
	void BP_SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Sign In", Category = "GameFuse|User")
	void BP_SignIn(const FString& Email, const FString& Password, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Add Score", Category = "GameFuse|User")
	void BP_AddScore(const int32 Score, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Set Score", Category = "GameFuse|User")
	void BP_SetScore(const int32 Score, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Add Credits", Category = "GameFuse|User")
	void BP_AddCredits(const int32 Credits, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Set Credits", Category = "GameFuse|User")
	void BP_SetCredits(const int32 Credits, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Set Attribute", Category = "GameFuse|User")
	void BP_SetAttribute(const FString& Key, const FString& Value, FGFSuccessCallback Callback);

	void BP_GetStoreItems(FGFSuccessCallback Callback);
	UFUNCTION(BlueprintCallable, DisplayName = "Set Attributes", Category = "GameFuse|User")
	void BP_SetAttributes(const TMap<FString, FString>& NewAttributes, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Set Attribute Local", Category = "GameFuse|User")
	void BP_SetAttributeLocal(const FString& Key, const FString& Value);

	UFUNCTION(BlueprintCallable, DisplayName = "Remove Attribute", Category = "GameFuse|User")
	void BP_RemoveAttribute(const FString& Key, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Attributes", Category = "GameFuse|User")
	void BP_FetchAttributes(FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Sync Local Attributes", Category = "GameFuse|User")
	void BP_SyncLocalAttributes(FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Add Leaderboard Entry", Category = "GameFuse|User")
	void BP_AddLeaderboardEntry(const FString& LeaderboardName, const int32 Score, const TMap<FString, FString>& Metadata, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Clear Leaderboard Entry", Category = "GameFuse|User")
	void BP_ClearLeaderboardEntry(const FString& LeaderboardName, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Fetch My Leaderboard Entries", Category = "GameFuse|User")
	void BP_FetchMyLeaderboardEntries(const int32 Limit, bool bOnePerUser, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Purchase Store Item", Category = "GameFuse|User")
	void BP_PurchaseStoreItem(const int32 StoreItemId, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Remove Store Item", Category = "GameFuse|User")
	void BP_RemoveStoreItem(const int32 StoreItemId, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Purchased Store Items", Category = "GameFuse|User")
	void BP_FetchPurchasedStoreItems(FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, DisplayName = "Get Attributes", Category = "GameFuse|User")
	void BP_GetAttributes(FGFSuccessCallback Callback);

	//> Internal
	TObjectPtr<UUserAPIHandler> GetRequestHandler() const
	{
		return RequestHandler;
	}

protected:

	//> Response Handlers
	bool HandleUserDataResponse(FGFAPIResponse Response);
	void HandleStoreItemsResponse(FGFAPIResponse Response);
	void HandleLeaderboardEntriesResponse(FGFAPIResponse Response);
	void HandleAttributesResponse(FGFAPIResponse Response);
	void HandleUserActionResponse(FGFAPIResponse Response);
	void HandleUserLogin(FGFAPIResponse Response);

private:

	FGFUserData UserData;
	TMap<FString, FString> Attributes;
	TMap<FString, FString> LocalAttributes;
	TArray<FGFStoreItem> PurchasedStoreItems;
	TArray<FGFLeaderboardEntry> LeaderboardEntries;

	UPROPERTY()
	TObjectPtr<UGameFuseManager> GameFuseManager;
	UPROPERTY()
	TObjectPtr<UUserAPIHandler> RequestHandler;

	//> Callback storage
	TMap<FGuid, FGFUserDataCallback> UserDataCallbacks;
	TMap<FGuid, FGFStoreItemsCallback> StoreItemsCallbacks;
	TMap<FGuid, FGFLeaderboardEntriesCallback> LeaderboardEntriesCallbacks;
	TMap<FGuid, FGFAttributesCallback> AttributesCallbacks;
	TMap<FGuid, FGFInternalSuccessCallback> SimpleSuccessCallbacks;
	TMap<FGuid, FGFUserDataCallback> LoginCallbacks;
};