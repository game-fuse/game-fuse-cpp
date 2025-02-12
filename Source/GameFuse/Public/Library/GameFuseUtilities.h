/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#pragma once

#include "CoreMinimal.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Interfaces/IHttpRequest.h"
#include "Library/GameFuseEnumLibrary.h"
#include "Library/GameFuseStructLibrary.h"


class GAMEFUSE_API GameFuseUtilities
{
public:

#pragma region Struct => JSON Conversion
	/**
	 * Converts a GameRound into a JSON object
	 * @param GameRound The GameRound to convert
	 * @param JsonObject The JSON object to store the data
	 * @return true if successful
	 */
	static bool ConvertGameRoundToJson(const FGFGameRound& GameRound, const TSharedPtr<FJsonObject>& JsonObject);

	/**
	 * Converts a Group into a JSON object
	 * @param Group The Group to convert
	 * @param JsonObject The JSON object to store the data
	 * @return true if successful
	 */
	static bool ConvertGroupToJson(const FGFGroup& Group, const TSharedPtr<FJsonObject>& JsonObject);
	static bool ConvertJsonToGameData(FGFGameData& InGameData, const FString& JsonString);

#pragma endregion
#pragma region JSON => Struct Conversion

	/**
	 * Converts a JSON object into GameData
	 * @param InGameData GameData struct to store converted data
	 * @param JsonObject The JSON object to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToGameData(FGFGameData& InGameData, const TSharedPtr<FJsonObject>& JsonObject);

	/**
	 * Converts a JSON string into UserData
	 * @param InUserData UserData struct to store converted data
	 * @param JsonString The JSON string to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToUserData(FGFUserData& InUserData, const FString& JsonString);

	/**
	 * Converts a JSON object into UserData
	 * @param InUserData UserData struct to store converted data
	 * @param JsonObject The JSON object to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToUserData(FGFUserData& InUserData, const TSharedPtr<FJsonObject>& JsonObject);

	/**
	 * Converts a JSON value into a StoreItem
	 * @param InStoreItem StoreItem struct to store converted data
	 * @param JsonValue The JSON value to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToStoreItem(FGFStoreItem& InStoreItem, const TSharedPtr<FJsonValue>& JsonValue);

	static bool ConvertJsonStringToStringMap(const FString& String, TMap<FString, FString>& Map);
	/**
	 * Converts a JSON value into a LeaderboardEntry
	 * @param InLeaderboardItem LeaderboardEntry struct to store converted data
	 * @param JsonValue The JSON value to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToLeaderboardEntry(FGFLeaderboardEntry& InLeaderboardItem, const TSharedPtr<FJsonValue>& JsonValue);

	static bool ConvertJsonToLeaderboardEntries(TArray<FGFLeaderboardEntry>& InLeaderboardArray, const FString& JsonString);
	/**
	 * Converts a JSON value into list of LeaderboardEntries
	 * @param InLeaderboardItem LeaderboardEntry struct to store converted data
	 * @param JsonValue The JSON value to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToLeaderboardEntries(TArray<FGFLeaderboardEntry>& InLeaderboardArray, const TSharedPtr<FJsonObject>& JsonObject);

	/**
	 * Converts a LeaderboardEntry into a JSON object
	 * @param LeaderboardItem The LeaderboardEntry to convert
	 * @param JsonObject The JSON object to store the data
	 * @return true if successful
	 */
	static bool ConvertLeaderboardItemToJson(const FGFLeaderboardEntry& LeaderboardItem, TSharedPtr<FJsonObject>& JsonObject);

	/**
	 * Converts a JSON object into a single friend request
	 * @param OutRequest FriendRequest struct to store converted data
	 * @param JsonObject The JSON object to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToFriendRequest(FGFFriendRequest& OutRequest, const TSharedPtr<FJsonObject>& JsonObject);


#pragma endregion

#pragma region Game Rounds

	/**
	 * Converts a JSON string into a GameRound
	 * @param InGameRound GameRound struct to store converted data
	 * @param JsonString The JSON string to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToGameRound(FGFGameRound& InGameRound, const FString& JsonString);

	/**
	 * Converts a JSON object into a GameRound
	 * @param InGameRound GameRound struct to store converted data
	 * @param JsonObject The JSON object to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToGameRound(FGFGameRound& InGameRound, const TSharedPtr<FJsonObject>& JsonObject);


	/**
	 * Converts a JSON array into an array of GameRounds
	 * @param GameRounds Array to store converted data
	 * @param JsonString The JSON string to convert
	 * @return true if successful
	 */
	static bool ConvertJsonArrayToGameRounds(TArray<FGFGameRound>& GameRounds, const FString& JsonString);


	/**
	 * Converts a JSON array into an array of GameRoundRankings
	 * @param JsonRankings The JSON array to convert
	 * @param OutRankings Array to store converted data
	 * @return true if successful
	 */
	static bool ConvertJsonArrayToGameRoundRankings(const TArray<TSharedPtr<FJsonValue>>* JsonRankings, TArray<FGFGameRoundRanking>& OutRankings);


#pragma endregion

#pragma region Friends
	/**
	 * Converts a JSON array into a list of friend requests
	 * @param OutRequests Array to store the converted friend requests
	 * @param JsonString The JSON string to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToFriendRequests(TArray<FGFFriendRequest>& OutRequests, const FString& JsonString);

	/**
	 * Converts a JSON array into a list of friends
	 * @param OutFriends Array to store the converted friends list
	 * @param JsonString The JSON string to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToFriendsList(TArray<FGFUserData>& OutFriends, const FString& JsonString);

#pragma endregion

#pragma region Groups

	/**
	 * Converts a JSON object into a GroupAttribute
	 * @param InAttribute GroupAttribute struct to store converted data
	 * @param JsonObject The JSON object to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToGroupAttribute(FGFGroupAttribute& InAttribute, const TSharedPtr<FJsonObject>& JsonObject);

	/**
	 * Converts a JSON object into a GroupConnection
	 * @param InConnection GroupConnection struct to store converted data
	 * @param JsonObject The JSON object to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToGroupConnection(FGFGroupConnection& InConnection, const TSharedPtr<FJsonObject>& JsonObject);

	/**
	 * Converts a JSON string into a GroupConnection
	 * @param InConnection GroupConnection struct to store converted data
	 * @param JsonString The JSON string to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToGroupConnection(FGFGroupConnection& InConnection, const FString& JsonString);

	/**
	 * Converts a JSON array into an array of GroupAttributes
	 * @param InAttributes Array to store converted data
	 * @param JsonArray The JSON array to convert
	 * @return true if successful
	 */
	static bool ConvertJsonArrayToGroupAttributes(TArray<FGFGroupAttribute>& InAttributes, const TArray<TSharedPtr<FJsonValue>>* JsonArray);

	/**
	 * Converts a JSON object into a Group
	 * @param InGroup Group struct to store converted data
	 * @param JsonObject The JSON object to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToGroup(FGFGroup& InGroup, const TSharedPtr<FJsonObject>& JsonObject);

	/**
	 * Converts a JSON string into a Group
	 * @param InGroup Group struct to store converted data
	 * @param JsonString The JSON string to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToGroup(FGFGroup& InGroup, const FString& JsonString);

	/**
	 * Converts a JSON array into an array of Groups
	 * @param InGroups Array to store converted data
	 * @param JsonString The JSON string to convert
	 * @return true if successful
	 */
	static bool ConvertJsonArrayToGroups(TArray<FGFGroup>& InGroups, const FString& JsonString);

	/**
	 * Converts a JSON string into a GroupAttributeResponse
	 * @param OutAttributes Array to store the converted group attributes
	 * @param JsonString The JSON string to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToGroupAttributeResponse(TArray<FGFGroupAttribute>& OutAttributes, const FString& JsonString);

#pragma endregion

#pragma region Utility Functions

	/**
	 * Converts a map to a JSON string
	 * @param OurMap The map to convert
	 * @return The JSON string
	 */
	static FString ConvertMapToJsonStr(const TMap<FString, FString>& OurMap);

	/**
	 * Creates a request body string with authentication and map data
	 * @param AuthenticationToken The authentication token
	 * @param MapBody The map body key
	 * @param OurMap The map data
	 * @return The request body string
	 */
	static FString MakeStrRequestBody(const FString& AuthenticationToken, const FString& MapBody, const TMap<FString, FString>& OurMap);

	/**
	 * Determines the type of core API response from a JSON object
	 * @param JsonObject The JSON object to analyze
	 * @return The response type
	 */
	static EGFCoreAPIResponseType DetermineCoreAPIResponseType(const TSharedPtr<FJsonObject>& JsonObject);

	/**
	 * Determines the type of user API response from a JSON object
	 * @param JsonObject The JSON object to analyze
	 * @return The response type
	 */
	static EGFUserAPIResponseType DetermineUserAPIResponseType(const TSharedPtr<FJsonObject>& JsonObject);

	/**
	 * Logs HTTP request details
	 * @param HttpRequest The request to log
	 */
	static void LogRequest(FHttpRequestPtr HttpRequest);

	/**
	 * Logs HTTP response details
	 * @param HttpResponse The response to log
	 */
	static void LogResponse(FHttpResponsePtr HttpResponse);

	/**
	 * Logs HTTP headers
	 * @param Headers The headers to log
	 */
	static void LogHeaders(const TMap<FString, FString>& Headers);

	/**
	 * Convert FDateTime to ISO8601 string format
	 * @param DateTime The datetime to convert
	 * @return The ISO8601 formatted string
	 */
	static FString DateTimeToString(const FDateTime& DateTime);

	/**
	 * Convert ISO8601 string to FDateTime
	 * @param DateTimeStr The string to convert
	 * @return The parsed FDateTime
	 */
	static FDateTime StringToDateTime(const FString& DateTimeStr);

	/**
	 * Convert a map to a JSON object
	 * @param Map The map to convert
	 * @return The JSON object
	 */
	static TSharedPtr<FJsonObject> ConvertMapToJsonObject(const TMap<FString, FString>& Map);

	/**
	 * Converts a json object into a TMap<FString, FString>
	 * @param JsonObject Json Data
	 * @param InMap Map to store converted data
	 * @param FieldKey optional, if the data is nested in a field
	 * @return true if successful, or FieldKey is a null field (no data to convert)
	 */
	static bool ConvertJsonObjectToStringMap(const TSharedPtr<FJsonObject>& JsonObject, TMap<FString, FString>& InMap, const FString& FieldKey = "");

	/**
	 * Converts a JSON string into list of store items
	 * @param InStoreItems Array to store the converted store items
	 * @param JsonString The JSON string to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToStoreItems(TArray<FGFStoreItem>& InStoreItems, const FString& JsonString);


	/**
	 * Converts a JSON string into attributes
	 * @param InAttributes AttributeList struct to store converted data
	 * @param JsonString The JSON string to convert
	 * @return true if successful
	 */
	static bool ConvertJsonToAttributes(FGFAttributeList& InAttributes, const FString& JsonString);

	static bool ConvertJsonArrayToAttributes(FGFAttributeList& InAttributes, const TArray<TSharedPtr<FJsonValue>>* Array);

#pragma endregion
};