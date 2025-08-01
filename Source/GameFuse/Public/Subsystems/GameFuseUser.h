/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#pragma once

#include "API/UserAPIHandler.h"
#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "GameFuseManager.h"
#include "Library/GameFuseStructLibrary.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "GameFuseUser.generated.h"

// Single-cast delegates for user callbacks
DECLARE_DELEGATE_TwoParams(FGFUserDataCallback, bool, const FGFUserData&);
DECLARE_DELEGATE_TwoParams(FGFStoreItemsCallback, bool, const TArray<FGFStoreItem>&);
DECLARE_DELEGATE_TwoParams(FGFLeaderboardEntriesCallback, bool, const TArray<FGFLeaderboardEntry>&);
DECLARE_DELEGATE_TwoParams(FGFAttributesCallback, bool, const FGFAttributeList&);

/**
 * GameFuse User Subsystem for managing user authentication, data, and interactions.
 * 
 * This subsystem provides comprehensive functionality for user management including:
 * - User authentication (sign up, sign in, log out)
 * - User data management (scores, credits, attributes)
 * - Store item management (purchase, remove, fetch)
 * - Leaderboard functionality (add entries, fetch rankings)
 * - Attribute system for custom user data
 *
 * The subsystem can be accessed from any UObject using GetWorld()->GetSubsystem<UGameFuseUser>()
 */
UCLASS()
class GAMEFUSE_API UGameFuseUser : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

#pragma region Subsystem Initialization
	/**
	 * Initializes the GameFuse User subsystem.
	 * 
	 * Called automatically by Unreal Engine when the subsystem is created.
	 * Sets up the API handler and initializes internal data structures.
	 * 
	 * @param Collection The subsystem collection being initialized
	 */
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	/**
	 * Deinitializes the GameFuse User subsystem.
	 * 
	 * Called automatically by Unreal Engine when the subsystem is being destroyed.
	 * Cleans up resources and clears stored data.
	 */
	virtual void Deinitialize() override;

#pragma endregion

#pragma region Members
private:

	/**
	 * Current user data - represents the authenticated user's information.
	 * This data is set during sign in and remains unchanged when fetching other users' data.
	 */
	FGFUserData CurrentUserData;

	/**
	 * Last fetched user data - represents the most recently fetched user information.
	 * This can be either the current user's data or another user's data from FetchUser().
	 * Used for general user data operations and is updated with each fetch operation.
	 */
	FGFUserData LastFetchedUserData;

	/**
	 * Attributes from the last fetch attributes API call.
	 * Contains key-value pairs of custom data from the most recent attributes fetch operation.
	 * Updated when fetching attributes for any user (current or other).
	 */
	TMap<FString, FString> Attributes;

	/**
	 * Locally modified attributes that haven't been synced to the server.
	 * These are temporary changes made locally that will be sent to the server
	 * when SyncLocalAttributes() is called.
	 */
	TMap<FString, FString> LocalAttributes;

	/**
	 * Store items from the last fetch store items API call.
	 * Contains all store items from the most recent store items fetch operation.
	 * Updated when fetching store items for any user (current or other).
	 */
	TArray<FGFStoreItem> PurchasedStoreItems;

	/**
	 * Leaderboard entries from the last fetch leaderboard entries API call.
	 * Contains all leaderboard entries from the most recent leaderboard entries fetch operation.
	 * Updated when fetching leaderboard entries for any user (current or other).
	 */
	TArray<FGFLeaderboardEntry> LeaderboardEntries;

	UPROPERTY()
	TObjectPtr<UGameFuseManager> GameFuseManager;
	UPROPERTY()
	TObjectPtr<UUserAPIHandler> RequestHandler;

#pragma endregion
public:

#pragma region Core User Data & Authentication


	/**
	 * Gets the current user data.
	 * 
	 * Returns the complete user data structure for the authenticated user.
	 * This data is set during sign in and remains unchanged when fetching other users' data.
	 * Contains ID, username, email, scores, credits, and other metadata for the current user.
	 * 
	 * @return Reference to the current user data structure
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	const FGFUserData& GetCurrentUserData() const;

	/**
	 * Gets the last fetched user's data.
	 * 
	 * Fetching any user will update this data.
	 * Contains ID, username, email, scores, credits, and other metadata for the user.
	 * 
	 * @return Reference to the current user data structure
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	const FGFUserData& GetLastFetchedUserData() const;

	/**
	 * Gets the current user's username.
	 * 
	 * Returns the username of the currently authenticated user.
	 * This data comes from CurrentUser and is not affected by FetchUser() operations.
	 * Returns empty string if no user is signed in.
	 * 
	 * @return The username as a string
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	FString GetUsername() const;

	/**
	 * Gets the number of times the current user has logged in.
	 * 
	 * Returns the total login count for the currently authenticated user.
	 * This data comes from CurrentUser and is not affected by FetchUser() operations.
	 * Returns 0 if no user is signed in.
	 * 
	 * @return The number of logins as an integer
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	int32 GetNumberOfLogins() const;

	/**
	 * Gets the timestamp of the current user's last login.
	 * 
	 * Returns the date/time string of when the current user last logged in.
	 * This data comes from CurrentUser and is not affected by FetchUser() operations.
	 * Returns empty string if no user is signed in.
	 * 
	 * @return The last login timestamp as a string
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	FString GetLastLogin() const;

	/**
	 * Checks if a user is currently signed in.
	 * 
	 * Returns true if a user is authenticated and signed in,
	 * false otherwise.
	 * 
	 * @return True if user is signed in, false otherwise
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	bool IsSignedIn() const;

	/**
	 * Gets the current authentication token.
	 * 
	 * Returns the JWT token used for API authentication.
	 * Returns empty string if no user is signed in.
	 * 
	 * @return The authentication token as a string
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	FString GetAuthenticationToken() const;

	/**
	 * Signs up a new user with the provided credentials.
	 * 
	 * Creates a new user account with the specified email, password, and username.
	 * The callback will be triggered when the signup process completes.
	 * 
	 * @param Email The user's email address
	 * @param Password The user's password
	 * @param PasswordConfirmation Password confirmation (must match Password)
	 * @param Username The desired username
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FGFUserDataCallback TypedCallback);
	
	/**
	 * Signs up a new user with game data and credentials.
	 * 
	 * Creates a new user account with the specified email, password, username, and game data.
	 * The callback will be triggered when the signup process completes.
	 * 
	 * @param GameData Additional game-specific data to associate with the user
	 * @param Email The user's email address
	 * @param Password The user's password
	 * @param PasswordConfirmation Password confirmation (must match Password)
	 * @param Username The desired username
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid SignUp(const FGFGameData& GameData, const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FGFUserDataCallback TypedCallback);
	
	/**
	 * Signs in an existing user with email and password.
	 * 
	 * Authenticates a user with the provided credentials and loads their data.
	 * The callback will be triggered when the signin process completes.
	 * 
	 * @param Email The user's email address
	 * @param Password The user's password
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid SignIn(const FString& Email, const FString& Password, FGFUserDataCallback TypedCallback);
	
	/**
	 * Signs in an existing user with game data, email and password.
	 * 
	 * Authenticates a user with the provided credentials and loads their data,
	 * including additional game-specific information.
	 * The callback will be triggered when the signin process completes.
	 * 
	 * @param GameData Additional game-specific data to associate with the session
	 * @param Email The user's email address
	 * @param Password The user's password
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid SignIn(const FGFGameData& GameData, const FString& Email, const FString& Password, FGFUserDataCallback TypedCallback);

	/**
	 * Fetches user data for a specific user ID.
	 * 
	 * Retrieves the complete user data for the specified user ID.
	 * This can be used to get information about other users.
	 * 
	 * @param UserId The ID of the user to fetch
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid FetchUser(const int32 UserId, FGFUserDataCallback TypedCallback);

	/**
	 * Logs out the current user and clears local data.
	 * 
	 * Signs out the current user, clears authentication tokens,
	 * and optionally saves the current state to a save slot.
	 * 
	 * @param SaveSlotName Optional save slot name for persisting data (default: "GameFuseSaveSlot")
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Log Out", Category = "GameFuse|User")
	void LogOut(const FString& SaveSlotName = TEXT("GameFuseSaveSlot"));

#pragma endregion
#pragma region Score & Credits

	/**
	 * Gets the current user's score.
	 * 
	 * Returns the current score value for the authenticated user.
	 * This data comes from CurrentUser and is not affected by FetchUser() operations.
	 * Returns 0 if no user is signed in.
	 * 
	 * @return The current score as an integer
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	int32 GetScore() const;

	/**
	 * Gets the current user's credits.
	 * 
	 * Returns the current credits value for the authenticated user.
	 * This data comes from CurrentUser and is not affected by FetchUser() operations.
	 * Returns 0 if no user is signed in.
	 * 
	 * @return The current credits as an integer
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	int32 GetCredits() const;

	/**
	 * Adds to the current user's score.
	 * 
	 * Increases the user's score by the specified amount.
	 * The callback will be triggered when the operation completes.
	 * 
	 * @param AddScore The amount to add to the current score
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid AddScore(const int32 AddScore, FGFUserDataCallback TypedCallback);
	
	/**
	 * Sets the current user's score to a specific value.
	 * 
	 * Replaces the user's current score with the specified value.
	 * The callback will be triggered when the operation completes.
	 * 
	 * @param SetScore The new score value to set
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid SetScore(const int32 SetScore, FGFUserDataCallback TypedCallback);
	
	/**
	 * Adds to the current user's credits.
	 * 
	 * Increases the user's credits by the specified amount.
	 * The callback will be triggered when the operation completes.
	 * 
	 * @param AddCredits The amount to add to the current credits
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid AddCredits(const int32 AddCredits, FGFUserDataCallback TypedCallback);
	
	/**
	 * Sets the current user's credits to a specific value.
	 * 
	 * Replaces the user's current credits with the specified value.
	 * The callback will be triggered when the operation completes.
	 * 
	 * @param SetCredits The new credits value to set
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid SetCredits(const int32 SetCredits, FGFUserDataCallback TypedCallback);

#pragma endregion
#pragma region Store Items

	/**
	 * Gets the list of store items from the last fetch store items API call.
	 * 
	 * Returns an array of all store items from the most recent store items fetch operation.
	 * This data comes from the last fetch store items API call (could be current user or another user).
	 * Returns empty array if no store items have been fetched.
	 * 
	 * @return Array of purchased store items
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	const TArray<FGFStoreItem>& GetPurchasedStoreItems() const;

	/**
	 * Purchases a store item for the current user.
	 * 
	 * Attempts to purchase the specified store item using the user's credits.
	 * The callback will be triggered when the purchase completes.
	 * 
	 * @param StoreItemId The ID of the store item to purchase
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid PurchaseStoreItem(const int32 StoreItemId, FGFStoreItemsCallback TypedCallback);
	
	/**
	 * Removes a store item from the current user's inventory.
	 * 
	 * Removes the specified store item from the user's purchased items.
	 * The callback will be triggered when the removal completes.
	 * 
	 * @param StoreItemId The ID of the store item to remove
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid RemoveStoreItem(const int32 StoreItemId, FGFStoreItemsCallback TypedCallback);
	
	/**
	 * Fetches all store items purchased by the current user.
	 * 
	 * Retrieves the complete list of store items that the current user has purchased.
	 * The callback will be triggered when the fetch completes.
	 * 
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid FetchMyPurchasedStoreItems(FGFStoreItemsCallback TypedCallback);
	
	/**
	 * Fetches all store items purchased by a specific user.
	 * 
	 * Retrieves the complete list of store items that the specified user has purchased.
	 * The callback will be triggered when the fetch completes.
	 * 
	 * @param UserId The ID of the user whose purchases to fetch
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid FetchUserPurchasedStoreItems(const int32 UserId, FGFStoreItemsCallback TypedCallback);

#pragma endregion
#pragma region Attributes

	/**
	 * Gets map of attributes from the GameFuse server
	 *
	 * This data comes from the last fetch attributes operation (could be current user or another user).
	 * Returns empty map if no user data has been fetched.
	 * 
	 * @return Map of attribute keys to values
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	const TMap<FString, FString>& GetAttributes() const;

	/**
	 * Gets all attribute keys from the last fetch attributes API call.
	 * 
	 * Returns an array of all attribute keys from the most recent attributes fetch operation.
	 * This data comes from the last fetch attributes API call (could be current user or another user).
	 * Returns empty array if no attributes have been fetched.
	 * 
	 * @return Array of attribute keys
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	TArray<FString> GetAttributesKeys() const;

	/**
	 * Gets all locally modified attributes that haven't been synced.
	 * 
	 * Returns a map of attributes that have been modified locally but not yet
	 * synchronized with the server. These are temporary changes for the current user.
	 * 
	 * @return Map of dirty attribute keys to values
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	const TMap<FString, FString>& GetDirtyAttributes() const;

	/**
	 * Gets the value of a specific attribute from the last fetch attributes API call.
	 * 
	 * Returns the value associated with the specified attribute key from the most recent attributes fetch operation.
	 * This data comes from the last fetch attributes API call (could be current user or another user).
	 * Returns empty string if the attribute doesn't exist.
	 * 
	 * @param Key The attribute key to look up
	 * @return The attribute value as a string
	 */
	UFUNCTION(BlueprintCallable, Category = "GameFuse|User")
	FString GetAttributeValue(const FString Key) const;

	/**
	 * Fetches all attributes for the current user from the server.
	 * 
	 * Retrieves the complete list of attributes for the current user from the server.
	 * The callback will be triggered when the fetch completes.
	 * 
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid FetchMyAttributes(FGFAttributesCallback TypedCallback);

	/**
	 * Fetches all attributes for a specific user from the server.
	 * 
	 * Retrieves the complete list of attributes for the specified user from the server.
	 * The callback will be triggered when the fetch completes.
	 * 
	 * @param UserId The ID of the user whose attributes to fetch
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid FetchUserAttributes(const int32 UserId, FGFAttributesCallback TypedCallback);
	
	/**
	 * Synchronizes locally modified attributes with the server.
	 * 
	 * Sends all locally modified attributes to the server to update the user's data.
	 * The callback will be triggered when the sync completes.
	 * 
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid SyncLocalAttributes(FGFAttributesCallback TypedCallback);
	
	/**
	 * Sets a single attribute for the current user.
	 * 
	 * Sets or updates the value of a specific attribute key for the current user.
	 * The callback will be triggered when the operation completes.
	 * 
	 * @param Key The attribute key to set
	 * @param Value The value to assign to the attribute
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid SetAttribute(const FString& Key, const FString& Value, FGFAttributesCallback TypedCallback);
	
	/**
	 * Sets multiple attributes for the current user.
	 * 
	 * Sets or updates multiple attribute key-value pairs for the current user.
	 * The callback will be triggered when the operation completes.
	 * 
	 * @param NewAttributes Map of attribute keys to values to set
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid SetAttributes(const TMap<FString, FString>& NewAttributes, FGFAttributesCallback TypedCallback);
	
	/**
	 * Sets an attribute locally without syncing to server.
	 * 
	 * Sets or updates the value of a specific attribute key locally.
	 * The change will be stored locally and can be synced later using SyncLocalAttributes.
	 * 
	 * @param SetKey The attribute key to set
	 * @param SetValue The value to assign to the attribute
	 */
	void SetAttributeLocal(const FString& SetKey, const FString& SetValue);
	
	/**
	 * Removes a single attribute for the current user.
	 * 
	 * Deletes the specified attribute key and its value for the current user.
	 * The callback will be triggered when the operation completes.
	 * 
	 * @param SetKey The attribute key to remove
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid RemoveAttribute(const FString& SetKey, FGFAttributesCallback TypedCallback);
	
	/**
	 * Removes multiple attributes for the current user.
	 * 
	 * Deletes multiple attribute keys and their values for the current user.
	 * The callback will be triggered when the operation completes.
	 * 
	 * @param AttributeKeys Array of attribute keys to remove
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid RemoveAttributes(const TArray<FString>& AttributeKeys, FGFAttributesCallback TypedCallback);

#pragma endregion
#pragma region Leaderboards

	/**
	 * Gets the leaderboard entries from the last fetch leaderboard entries API call.
	 * 
	 * Returns an array of all leaderboard entries from the most recent leaderboard entries fetch operation.
	 * This data comes from the last fetch leaderboard entries API call (could be current user or another user).
	 * Returns empty array if no leaderboard entries have been fetched.
	 * 
	 * @return Array of leaderboard entries
	 */
	UFUNCTION(BlueprintPure, Category = "GameFuse|User")
	const TArray<FGFLeaderboardEntry>& GetLeaderboardEntries() const;

	/**
	 * Adds a leaderboard entry with metadata for the current user.
	 * 
	 * Creates a new leaderboard entry with the specified score and metadata.
	 * The callback will be triggered when the operation completes.
	 * 
	 * @param LeaderboardName The name of the leaderboard to add the entry to
	 * @param Score The score value for the entry
	 * @param Metadata Additional metadata to associate with the entry
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid AddLeaderboardEntry(const FString& LeaderboardName, const int32 Score, const TMap<FString, FString>& Metadata, FGFInternalSuccessCallback TypedCallback);
	
	/**
	 * Adds a leaderboard entry for the current user.
	 * 
	 * Creates a new leaderboard entry with the specified score.
	 * The callback will be triggered when the operation completes.
	 * 
	 * @param LeaderboardName The name of the leaderboard to add the entry to
	 * @param Score The score value for the entry
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid AddLeaderboardEntry(const FString& LeaderboardName, const int32 Score, FGFInternalSuccessCallback TypedCallback);
	
	/**
	 * Clears a leaderboard entry for the current user.
	 * 
	 * Removes the current user's entry from the specified leaderboard.
	 * The callback will be triggered when the operation completes.
	 * 
	 * @param LeaderboardName The name of the leaderboard to clear the entry from
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid ClearLeaderboardEntry(const FString& LeaderboardName, FGFInternalSuccessCallback TypedCallback);
	
	/**
	 * Fetches leaderboard entries for the current user.
	 * 
	 * Retrieves leaderboard entries for the current user with optional filtering.
	 * The callback will be triggered when the fetch completes.
	 * 
	 * @param Limit Maximum number of entries to retrieve
	 * @param bOnePerUser If true, only one entry per user will be returned
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid FetchMyLeaderboardEntries(const int32 Limit, bool bOnePerUser, FGFLeaderboardEntriesCallback TypedCallback);
	
	/**
	 * Fetches leaderboard entries for a specific user.
	 * 
	 * Retrieves leaderboard entries for the specified user with optional filtering.
	 * The callback will be triggered when the fetch completes.
	 * 
	 * @param UserId The ID of the user whose entries to fetch
	 * @param Limit Maximum number of entries to retrieve
	 * @param bOnePerUser If true, only one entry per user will be returned
	 * @param TypedCallback Callback function to handle the response
	 * @return Unique identifier for tracking this request
	 */
	FGuid FetchUserLeaderboardEntries(const int32 UserId, const int32 Limit, bool bOnePerUser, FGFLeaderboardEntriesCallback TypedCallback);
#pragma endregion
#pragma region Blueprint Wrapper Functions
	/**
	 * Blueprint wrapper for user sign up.
	 * 
	 * Creates a new user account with the specified credentials.
	 * Use this function in Blueprint graphs for user registration.
	 * 
	 * @param Email The user's email address
	 * @param Password The user's password
	 * @param PasswordConfirmation Password confirmation (must match Password)
	 * @param Username The desired username
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Sign Up", Category = "GameFuse|User")
	void BP_SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for user sign in.
	 * 
	 * Authenticates an existing user with email and password.
	 * Use this function in Blueprint graphs for user login.
	 * 
	 * @param Email The user's email address
	 * @param Password The user's password
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Sign In", Category = "GameFuse|User")
	void BP_SignIn(const FString& Email, const FString& Password, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for adding score.
	 * 
	 * Increases the current user's score by the specified amount.
	 * Use this function in Blueprint graphs for score management.
	 * 
	 * @param Score The amount to add to the current score
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Add Score", Category = "GameFuse|User")
	void BP_AddScore(const int32 Score, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for setting score.
	 * 
	 * Sets the current user's score to the specified value.
	 * Use this function in Blueprint graphs for score management.
	 * 
	 * @param Score The new score value to set
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Set Score", Category = "GameFuse|User")
	void BP_SetScore(const int32 Score, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for adding credits.
	 * 
	 * Increases the current user's credits by the specified amount.
	 * Use this function in Blueprint graphs for credit management.
	 * 
	 * @param Credits The amount to add to the current credits
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Add Credits", Category = "GameFuse|User")
	void BP_AddCredits(const int32 Credits, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for setting credits.
	 * 
	 * Sets the current user's credits to the specified value.
	 * Use this function in Blueprint graphs for credit management.
	 * 
	 * @param Credits The new credits value to set
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Set Credits", Category = "GameFuse|User")
	void BP_SetCredits(const int32 Credits, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for setting a single attribute.
	 * 
	 * Sets or updates the value of a specific attribute key for the current user.
	 * Use this function in Blueprint graphs for attribute management.
	 * 
	 * @param Key The attribute key to set
	 * @param Value The value to assign to the attribute
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Set Attribute", Category = "GameFuse|User")
	void BP_SetAttribute(const FString& Key, const FString& Value, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for setting multiple attributes.
	 * 
	 * Sets or updates multiple attribute key-value pairs for the current user.
	 * Use this function in Blueprint graphs for attribute management.
	 * 
	 * @param NewAttributes Map of attribute keys to values to set
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Set Attributes", Category = "GameFuse|User")
	void BP_SetAttributes(const TMap<FString, FString>& NewAttributes, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for setting an attribute locally.
	 * 
	 * Sets or updates the value of a specific attribute key locally without syncing to server.
	 * Use this function in Blueprint graphs for local attribute management.
	 * 
	 * @param Key The attribute key to set
	 * @param Value The value to assign to the attribute
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Set Attribute Local", Category = "GameFuse|User")
	void BP_SetAttributeLocal(const FString& Key, const FString& Value);

	/**
	 * Blueprint wrapper for removing a single attribute.
	 * 
	 * Deletes the specified attribute key and its value for the current user.
	 * Use this function in Blueprint graphs for attribute management.
	 * 
	 * @param Key The attribute key to remove
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Remove Attribute", Category = "GameFuse|User")
	void BP_RemoveAttribute(const FString& Key, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for removing multiple attributes.
	 * 
	 * Deletes multiple attribute keys and their values for the current user.
	 * Use this function in Blueprint graphs for attribute management.
	 * 
	 * @param AttributeKeys Array of attribute keys to remove
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Remove Attributes", Category = "GameFuse|User")
	void BP_RemoveAttributes(const TArray<FString>& AttributeKeys, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for fetching current user's attributes.
	 * 
	 * Retrieves the complete list of attributes for the current user from the server.
	 * Use this function in Blueprint graphs for attribute management.
	 * 
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch My Attributes", Category = "GameFuse|User")
	void BP_FetchMyAttributes(FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for fetching a specific user's attributes.
	 * 
	 * Retrieves the complete list of attributes for the specified user from the server.
	 * Use this function in Blueprint graphs for attribute management.
	 * 
	 * @param UserId The ID of the user whose attributes to fetch
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch User Attributes", Category = "GameFuse|User")
	void BP_FetchUserAttributes(const int32 UserId, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for syncing local attributes.
	 * 
	 * Sends all locally modified attributes to the server to update the user's data.
	 * Use this function in Blueprint graphs for attribute synchronization.
	 * 
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Sync Local Attributes", Category = "GameFuse|User")
	void BP_SyncLocalAttributes(FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for adding a leaderboard entry.
	 * 
	 * Creates a new leaderboard entry with the specified score for the current user.
	 * Use this function in Blueprint graphs for leaderboard management.
	 * 
	 * @param LeaderboardName The name of the leaderboard to add the entry to
	 * @param Score The score value for the entry
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Add Leaderboard Entry", Category = "GameFuse|User")
	void BP_AddLeaderboardEntry(const FString& LeaderboardName, const int32 Score, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for adding a leaderboard entry with metadata.
	 * 
	 * Creates a new leaderboard entry with the specified score and metadata for the current user.
	 * Use this function in Blueprint graphs for leaderboard management.
	 * 
	 * @param LeaderboardName The name of the leaderboard to add the entry to
	 * @param Score The score value for the entry
	 * @param Metadata Additional metadata to associate with the entry
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Add Leaderboard Entry With Attributes", Category = "GameFuse|User")
	void BP_AddLeaderboardEntryWithAttributes(const FString& LeaderboardName, const int32 Score, const TMap<FString, FString>& Metadata, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for clearing a leaderboard entry.
	 * 
	 * Removes the current user's entry from the specified leaderboard.
	 * Use this function in Blueprint graphs for leaderboard management.
	 * 
	 * @param LeaderboardName The name of the leaderboard to clear the entry from
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Clear Leaderboard Entry", Category = "GameFuse|User")
	void BP_ClearLeaderboardEntry(const FString& LeaderboardName, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for fetching current user's leaderboard entries.
	 * 
	 * Retrieves leaderboard entries for the current user with optional filtering.
	 * Use this function in Blueprint graphs for leaderboard management.
	 * 
	 * @param Limit Maximum number of entries to retrieve (max 100)
	 * @param bOnePerUser If true, only one entry per user will be returned
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch My Leaderboard Entries", Category = "GameFuse|User", meta = (Limit = 100))
	void BP_FetchMyLeaderboardEntries(const int32 Limit, bool bOnePerUser, FBP_GFApiCallback Callback);
	
	/**
	 * Blueprint wrapper for fetching a specific user's leaderboard entries.
	 * 
	 * Retrieves leaderboard entries for the specified user with optional filtering.
	 * Use this function in Blueprint graphs for leaderboard management.
	 * 
	 * @param UserId The ID of the user whose entries to fetch
	 * @param Limit Maximum number of entries to retrieve (max 100)
	 * @param bOnePerUser If true, only one entry per user will be returned
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch User Leaderboard Entries", Category = "GameFuse|User", meta = (Limit = 100))
	void BP_FetchUserLeaderboardEntries(const int32 UserId, const int32 Limit, bool bOnePerUser, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for purchasing a store item.
	 * 
	 * Attempts to purchase the specified store item using the user's credits.
	 * Use this function in Blueprint graphs for store management.
	 * 
	 * @param StoreItemId The ID of the store item to purchase
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Purchase Store Item", Category = "GameFuse|User")
	void BP_PurchaseStoreItem(const int32 StoreItemId, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for removing a store item.
	 * 
	 * Removes the specified store item from the user's purchased items.
	 * Use this function in Blueprint graphs for store management.
	 * 
	 * @param StoreItemId The ID of the store item to remove
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Remove Store Item", Category = "GameFuse|User")
	void BP_RemoveStoreItem(const int32 StoreItemId, FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for fetching current user's purchased store items.
	 * 
	 * Retrieves the complete list of store items that the current user has purchased.
	 * Use this function in Blueprint graphs for store management.
	 * 
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch My Purchased Store Items", Category = "GameFuse|User")
	void BP_FetchMyPurchasedStoreItems(FBP_GFApiCallback Callback);

	/**
	 * Blueprint wrapper for fetching a specific user's purchased store items.
	 * 
	 * Retrieves the complete list of store items that the specified user has purchased.
	 * Use this function in Blueprint graphs for store management.
	 * 
	 * @param UserId The ID of the user whose purchases to fetch
	 * @param Callback Blueprint callback to handle the response
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch User Purchased Store Items", Category = "GameFuse|User")
	void BP_FetchUserPurchasedStoreItems(const int32 UserId, FBP_GFApiCallback Callback);

#pragma endregion
#pragma region Internal
	/**
	 * Gets the internal API request handler.
	 * 
	 * Returns the UserAPIHandler instance used for making API requests.
	 * This is primarily used internally by the subsystem.
	 * 
	 * @return Pointer to the UserAPIHandler instance
	 */
	TObjectPtr<UUserAPIHandler> GetRequestHandler() const
	{
		return RequestHandler;
	}

protected:

#pragma endregion
#pragma region Response Handlers
	/**
	 * Handles user data response from API calls.
	 * 
	 * Processes the response from user-related API calls and updates internal data.
	 * Called internally by the subsystem.
	 * 
	 * @param Response The API response to process
	 * @param bUpdateCurrentUser If true, updates CurrentUserData (for sign in/up operations)
	 *                           If false, updates LastFetchedUserData (for fetch operations)
	 * @return True if the response was processed successfully
	 */
	bool HandleUserDataResponse(FGFAPIResponse Response, bool bUpdateCurrentUser = false);
	
	/**
	 * Handles store items response from API calls.
	 * 
	 * Processes the response from store-related API calls and updates internal data.
	 * Called internally by the subsystem.
	 * 
	 * @param Response The API response to process
	 */
	void HandleStoreItemsResponse(FGFAPIResponse Response);
	
	/**
	 * Handles leaderboard entries response from API calls.
	 * 
	 * Processes the response from leaderboard-related API calls and updates internal data.
	 * Called internally by the subsystem.
	 * 
	 * @param Response The API response to process
	 */
	void HandleLeaderboardEntriesResponse(FGFAPIResponse Response);
	
	/**
	 * Handles attributes response from API calls.
	 * 
	 * Processes the response from attribute-related API calls and updates internal data.
	 * Called internally by the subsystem.
	 * 
	 * @param Response The API response to process
	 */
	void HandleAttributesResponse(FGFAPIResponse Response);
	
	/**
	 * Handles general user action response from API calls.
	 * 
	 * Processes the response from general user action API calls.
	 * Called internally by the subsystem.
	 * 
	 * @param Response The API response to process
	 */
	void HandleUserActionResponse(FGFAPIResponse Response);
	
	/**
	 * Executes blueprint callbacks with API response data.
	 * 
	 * Converts API response data to blueprint-compatible format and executes
	 * the appropriate blueprint callback. Called internally by the subsystem.
	 * 
	 * @param Response The API response to convert and send to blueprints
	 */
	void ExecuteBlueprintCallback(const FGFAPIResponse& Response);

#pragma endregion
#pragma region Callback storage
	TMap<FGuid, FGFUserDataCallback> UserDataCallbacks;
	TMap<FGuid, FGFStoreItemsCallback> StoreItemsCallbacks;
	TMap<FGuid, FGFLeaderboardEntriesCallback> LeaderboardEntriesCallbacks;
	TMap<FGuid, FGFAttributesCallback> AttributesCallbacks;
	TMap<FGuid, FGFInternalSuccessCallback> SimpleSuccessCallbacks;
	TMap<FGuid, FBP_GFApiCallback> BlueprintCallbacks; // Store blueprint callbacks
#pragma endregion
};