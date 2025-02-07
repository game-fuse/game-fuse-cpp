/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#pragma once

#include "CoreMinimal.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"
#include "Interfaces/IHttpRequest.h"
#include "Library/GameFuseEnumLibrary.h"
#include "Library/GameFuseStructLibrary.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"
#include "Serialization/JsonWriter.h"

class GAMEFUSE_API GameFuseUtilities
{
public:

	static void ConvertJsonToMap(TMap<FString, FString>& InMap, const FString& JsonString);

	static bool ConvertJsonToGameData(FGFGameData& InGameData, const TSharedPtr<FJsonObject>& JsonObject);

	static bool ConvertJsonToUserData(FGFUserData& InUserData, const TSharedPtr<FJsonObject>& JsonObject);

	static bool ConvertJsonToStoreItem(FGFStoreItem& InStoreItem, const TSharedPtr<FJsonValue>& JsonValue);

	static bool ConvertJsonToLeaderboardItem(FGFLeaderboardEntry& InLeaderboardItem, const TSharedPtr<FJsonValue>& JsonValue);

	/**
	 * Converts a LeaderboardEntry into a JSON object
	 * @param LeaderboardItem The LeaderboardEntry to convert
	 * @param JsonObject The JSON object to store the data
	 * @return true if successful
	 */
	static bool ConvertLeaderboardItemToJson(const FGFLeaderboardEntry& LeaderboardItem, TSharedPtr<FJsonObject>& JsonObject);


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


#pragma endregion
};