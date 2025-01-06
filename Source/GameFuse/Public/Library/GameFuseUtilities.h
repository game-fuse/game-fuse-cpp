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

	static void ConvertJsonToMap(TMap<FString, FString>& InMap, const FString& JsonString);

	static bool ConvertJsonToGameData(FGFGameData& InGameData, const TSharedPtr<FJsonObject>& JsonObject);

	static bool ConvertJsonToUserData(FGFUserData& InUserData, const TSharedPtr<FJsonObject>& JsonObject);

	static bool ConvertJsonToStoreItem(FGFStoreItem& InStoreItem, const TSharedPtr<FJsonValue>& JsonValue);

	static bool ConvertJsonToLeaderboardItem(FGFLeaderboardEntry& InLeaderboardItem, const TSharedPtr<FJsonValue>& JsonValue);

	// static bool ConvertJsonToGameRoundRankings(const TArray<TSharedPtr<FJsonValue>>& JsonRankings, TArray<FGFGameRoundRanking>& OutRankings);

	static FString ConvertMapToJsonStr(const TMap<FString, FString>& OurMap);

	static FString MakeStrRequestBody(const FString& AuthenticationToken, const FString& MapBody, const TMap<FString, FString>& OurMap);

	static EGFCoreAPIResponseType DetermineCoreAPIResponseType(const TSharedPtr<FJsonObject>& JsonObject);

	static EGFUserAPIResponseType DetermineUserAPIResponseType(const TSharedPtr<FJsonObject>& JsonObject);

	static void LogRequest(FHttpRequestPtr HttpRequest);
	static void LogResponse(FHttpResponsePtr HttpResponse);
	static void LogHeaders(const TMap<FString, FString>& Headers);

	/** Convert FDateTime to ISO8601 string format */
	static FString DateTimeToString(const FDateTime& DateTime);

	/** Convert ISO8601 string to FDateTime */
	static FDateTime StringToDateTime(const FString& DateTimeStr);
};