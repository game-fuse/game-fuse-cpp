/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "Library/GameFuseUtilities.h"

#include "Library/GameFuseLog.h"
#include "Interfaces/IHttpResponse.h"
#include "Library/GameFuseStructLibrary.h"



void GameFuseUtilities::ConvertJsonToMap(TMap<FString, FString>& InMap, const FString& JsonString)
{

	InMap.Empty();

	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid()) {
		// Reserve memory in the map to avoid reallocations
		InMap.Reserve(JsonObject->Values.Num());

		// Iterate over the JSON object's key-value pairs
		for (const auto& JsonField : JsonObject->Values) {
			const FString& Key = JsonField.Key;
			const TSharedPtr<FJsonValue>& JsonValue = JsonField.Value;

			// Check if the JSON value is a string
			if (JsonValue.IsValid() && JsonValue->Type == EJson::String) {
				// Access the string value directly
				const FString& Value = JsonValue->AsString();

				// Add the key-value pair to the map without unnecessary copies
				InMap.Emplace(Key, Value);
			} else {
				UE_LOG(LogGameFuse, Error, TEXT("Invalid JSON value for key: %s \n Input String :\n %s"), *Key, *JsonString);
			}
		}
	}
}


bool GameFuseUtilities::ConvertJsonToGameData(FGFGameData& InGameData, const TSharedPtr<FJsonObject>& JsonObject)
{

	if (!JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid JSON object for GameData conversion"));
		return false;
	}

	JsonObject->TryGetNumberField(TEXT("id"), InGameData.Id);
	JsonObject->TryGetStringField(TEXT("token"), InGameData.Token);
	JsonObject->TryGetStringField(TEXT("name"), InGameData.Name);
	JsonObject->TryGetStringField(TEXT("description"), InGameData.Description);

	return true;

}

bool GameFuseUtilities::ConvertJsonToUserData(FGFUserData& InUserData, const TSharedPtr<FJsonObject>& JsonObject)
{
	if (!JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid JSON object for UserData conversion"));
		return false;
	}

	JsonObject->TryGetNumberField(TEXT("id"), InUserData.Id);
	JsonObject->TryGetStringField(TEXT("username"), InUserData.Username);
	JsonObject->TryGetNumberField(TEXT("number_of_logins"), InUserData.NumberOfLogins);
	JsonObject->TryGetStringField(TEXT("authentication_token"), InUserData.AuthenticationToken);
	JsonObject->TryGetNumberField(TEXT("score"), InUserData.Score);
	JsonObject->TryGetNumberField(TEXT("credits"), InUserData.Credits);
	JsonObject->TryGetStringField(TEXT("last_login"), InUserData.LastLogin);

	return true;
}

bool GameFuseUtilities::ConvertJsonToUserData(FGFUserData& InUserData, const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to deserialize JSON string to JSON object"));
		return false;
	}

	return ConvertJsonToUserData(InUserData, JsonObject);
}

bool GameFuseUtilities::ConvertJsonToStoreItem(FGFStoreItem& InStoreItem, const TSharedPtr<FJsonValue>& JsonValue)
{
	if (JsonValue->Type != EJson::Object) {
		UE_LOG(LogGameFuse, Error, TEXT("Fetching Store Items Failed to parse JSON Items"));
		return false;
	}

	const TSharedPtr<FJsonObject> JsonObject = JsonValue->AsObject();

	JsonObject->TryGetStringField(TEXT("name"), InStoreItem.Name);
	JsonObject->TryGetStringField(TEXT("category"), InStoreItem.Category);
	JsonObject->TryGetStringField(TEXT("description"), InStoreItem.Description);
	JsonObject->TryGetStringField(TEXT("icon_url"), InStoreItem.IconUrl);

	JsonObject->TryGetNumberField(TEXT("id"), InStoreItem.Id);
	JsonObject->TryGetNumberField(TEXT("cost"), InStoreItem.Cost);

	return true;
}

bool GameFuseUtilities::ConvertJsonToLeaderboardItem(FGFLeaderboardEntry& InLeaderboardItem, const TSharedPtr<FJsonValue>& JsonValue)
{
	if (JsonValue->Type != EJson::Object) {
		UE_LOG(LogGameFuse, Error, TEXT("Fetching Leaderboard Items Failed to parse JSON Items"));
		return false;
	}

	const TSharedPtr<FJsonObject> JsonObject = JsonValue->AsObject();

	JsonObject->TryGetStringField(TEXT("username"), InLeaderboardItem.Username);
	JsonObject->TryGetStringField(TEXT("leaderboard_name"), InLeaderboardItem.LeaderboardName);
	JsonObject->TryGetStringField(TEXT("extra_attributes"), InLeaderboardItem.ExtraAttributes);

	JsonObject->TryGetNumberField(TEXT("score"), InLeaderboardItem.Score);
	JsonObject->TryGetNumberField(TEXT("game_user_id"), InLeaderboardItem.GameUserId);


	return true;
}

void GameFuseUtilities::ConvertJsonArrayToMap(TMap<FString, FString> Map, const TArray<TSharedPtr<FJsonValue>>& _JsonArray)
{
	Map.Empty();

	for (const TSharedPtr<FJsonValue>& JsonValue : _JsonArray) {
		UE_LOG(LogGameFuse, Log, TEXT("Converting JSON Array to Map"));
	}
}


bool GameFuseUtilities::ConvertJsonToGameRound(FGFGameRound& InGameRound, const FString& JsonString)
{
	if (JsonString.IsEmpty()) {
		UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Empty JSON string"));
		return false;
	}

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Failed to parse JSON string: %s"), *JsonString);
		return false;
	}

	// json object example {
	// 	"id": 101,
	// 	"game_user_id": 1,
	// 	"start_time": "2024-09-20T10:00:00Z",
	// 	"end_time": "2024-09-20T11:00:00Z",
	// 	"score": 1600,
	// 	"place": 2,
	// 	"game_type": "battle",
	// 	"metadata": {
	// 		"level": "Hard"
	// 	}
	// }

	// Required fields
	if (!JsonObject->HasField(TEXT("id")) || !JsonObject->HasField(TEXT("game_user_id"))) {
		UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Missing required fields"));
		return false;
	}

	JsonObject->TryGetNumberField(TEXT("id"), InGameRound.Id);
	JsonObject->TryGetNumberField(TEXT("game_user_id"), InGameRound.GameUserId);

	// Optional fields with default values
	FString StartTime;
	if (JsonObject->TryGetStringField(TEXT("start_time"), StartTime)) {
		InGameRound.StartTime = StringToDateTime(StartTime);
	}

	FString EndTime;
	if (JsonObject->TryGetStringField(TEXT("end_time"), EndTime)) {
		InGameRound.EndTime = StringToDateTime(EndTime);
	}

	JsonObject->TryGetNumberField(TEXT("score"), InGameRound.Score);
	JsonObject->TryGetNumberField(TEXT("place"), InGameRound.Place);
	JsonObject->TryGetStringField(TEXT("game_type"), InGameRound.GameType);
	JsonObject->TryGetNumberField(TEXT("multiplayer_game_round_id"), InGameRound.MultiplayerGameRoundId);

	// Handle metadata
	InGameRound.Metadata.Empty(); // Clear existing metadata

	if (!JsonObject->HasTypedField(TEXT("metadata"), EJson::Null)) {
		const TSharedPtr<FJsonObject>* MetadataObject = nullptr;
		if (JsonObject->TryGetObjectField(TEXT("metadata"), MetadataObject) && MetadataObject != nullptr) {
			if (!MetadataObject->IsValid()) {
				UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Invalid metadata object"));
				return false;
			}

			for (const auto& Pair : (*MetadataObject)->Values) {
				if (!Pair.Value.IsValid()) {
					UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Invalid metadata value for key: %s"), *Pair.Key);
					continue;
				}

				FString ValueStr;
				if (Pair.Value->TryGetString(ValueStr)) {
					InGameRound.Metadata.Add(Pair.Key, ValueStr);
				}
			}
		}
	} else {
		UE_LOG(LogGameFuse, Log, TEXT("ConvertJsonToGameRound: Metadata field is null"));
	}

	return true;
}

bool GameFuseUtilities::GameRoundToJson(const FGFGameRound& GameRound, TSharedPtr<FJsonObject>& JsonObject)
{
	// required fields
	JsonObject->SetStringField("game_user_id", FString::FromInt(GameRound.GameUserId));

	if (GameRound.StartTime != FDateTime()) {
		JsonObject->SetStringField("start_time", GameRound.StartTime.ToIso8601());
	}
	if (GameRound.EndTime != FDateTime()) {
		JsonObject->SetStringField("end_time", GameRound.EndTime.ToIso8601());
	}

	JsonObject->SetNumberField("score", GameRound.Score);
	if (GameRound.Place >= 0) {
		JsonObject->SetNumberField("place", GameRound.Place);
	}
	if (!GameRound.GameType.IsEmpty()) {
		JsonObject->SetStringField("game_type", GameRound.GameType);
	}
	if (GameRound.MultiplayerGameRoundId >= 0) {
		JsonObject->SetNumberField("multiplayer_game_round_id", GameRound.MultiplayerGameRoundId);
	}

	if (!GameRound.Metadata.IsEmpty()) {
		JsonObject->SetObjectField("metadata", ConvertMapToJsonObject(GameRound.Metadata));
	}

	return true;
}

TSharedPtr<FJsonObject> GameFuseUtilities::ConvertMapToJsonObject(const TMap<FString, FString>& Map)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	for (const auto& Pair : Map) {
		JsonObject->SetStringField(Pair.Key, Pair.Value);
	}
	return JsonObject;
}

FString GameFuseUtilities::ConvertMapToJsonStr(const TMap<FString, FString>& OurMap)
{
	const TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	for (const TPair<FString, FString>& Pair : OurMap) {
		JsonObject->SetStringField(Pair.Key, Pair.Value);
	}

	FString JsonString = "";
	const TSharedRef<TJsonWriter<>> JsonWriter = TJsonWriterFactory<>::Create(&JsonString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), JsonWriter);

	return JsonString;
}

FString GameFuseUtilities::MakeStrRequestBody(const FString& AuthenticationToken, const FString& MapBody, const TMap<FString, FString>& OurMap)
{
	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());

	// Add the authentication token
	JsonObject->SetStringField(TEXT("authentication_token"), AuthenticationToken);

	// Create an array for attributes
	TArray<TSharedPtr<FJsonValue>> AttributesArray;

	// Populate the array with attributes
	for (const auto& Attribute : OurMap) {
		TSharedPtr<FJsonObject> AttrObject = MakeShareable(new FJsonObject());
		AttrObject->SetStringField(TEXT("key"), Attribute.Key);
		AttrObject->SetStringField(TEXT("value"), Attribute.Value);
		AttributesArray.Add(MakeShareable(new FJsonValueObject(AttrObject)));
	}

	// Add the attributes array to the main JSON object
	JsonObject->SetArrayField(MapBody, AttributesArray);

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	return OutputString;
}

//> Check JSON data to determine what response was received

EGFCoreAPIResponseType GameFuseUtilities::DetermineCoreAPIResponseType(const TSharedPtr<FJsonObject>& JsonObject)
{
	if (JsonObject->HasField(TEXT("id")) && JsonObject->HasField(TEXT("game_variables"))) {
		return EGFCoreAPIResponseType::SetUpGame;
	}
	if (JsonObject->HasField(TEXT("leaderboard_entries"))) {
		return EGFCoreAPIResponseType::ListLeaderboardEntries;
	}
	if (JsonObject->HasField(TEXT("store_items"))) {
		return EGFCoreAPIResponseType::ListStoreItems;
	}
	if (JsonObject->HasField(TEXT("mailer_response"))) {
		return EGFCoreAPIResponseType::ForgotPassword;
	}
	return EGFCoreAPIResponseType::None;
}

EGFUserAPIResponseType GameFuseUtilities::DetermineUserAPIResponseType(const TSharedPtr<FJsonObject>& JsonObject)
{
	if (JsonObject->HasField(TEXT("id")) && JsonObject->HasField(TEXT("username")) && JsonObject->HasField(TEXT("authentication_token"))) {
		return EGFUserAPIResponseType::Login;
	}
	if (JsonObject->HasField(TEXT("game_user_attributes"))) {
		return EGFUserAPIResponseType::Attributes;
	}
	if (JsonObject->HasField(TEXT("game_user_store_items"))) {
		return EGFUserAPIResponseType::StoreItems;
	}
	if (JsonObject->HasField(TEXT("leaderboard_entries"))) {
		return EGFUserAPIResponseType::LeaderboardEntries;
	}
	if (JsonObject->HasField(TEXT("credits"))) {
		return EGFUserAPIResponseType::Credits;
	}
	if (JsonObject->HasField(TEXT("score"))) {
		return EGFUserAPIResponseType::Score;
	}
	return EGFUserAPIResponseType::None;
}

void GameFuseUtilities::LogRequest(FHttpRequestPtr HttpRequest)
{
	UE_LOG(LogGameFuse, Log, TEXT("=========   URL   ========= \n %s"), *(HttpRequest->GetURL()));
	UE_LOG(LogGameFuse, Log, TEXT("========= HEADERS ========="))
	for (const FString& currHeader : HttpRequest->GetAllHeaders()) {
		UE_LOG(LogGameFuse, Log, TEXT("%s"), *currHeader);
	}

	// Log the content body if it exists
	TArray<uint8> ContentArray = HttpRequest->GetContent();
	if (!ContentArray.IsEmpty()) {
		FString ContentBody = FString(UTF8_TO_TCHAR(reinterpret_cast<const char*>(ContentArray.GetData())));
		UE_LOG(LogGameFuse, Log, TEXT("========= CONTENT BODY ========="));
		UE_LOG(LogGameFuse, Log, TEXT("%s"), *ContentBody);
	}
}

void GameFuseUtilities::LogResponse(FHttpResponsePtr HttpResponse)
{
	UE_LOG(LogGameFuse, Log, TEXT("======== RESPONSE ========="))
	UE_LOG(LogGameFuse, Log, TEXT("=== ResponseCode : %i ===="), HttpResponse->GetResponseCode());
	UE_LOG(LogGameFuse, Log, TEXT("%s"), *HttpResponse->GetContentAsString());

}

void GameFuseUtilities::LogHeaders(const TMap<FString, FString>& Headers)
{
	UE_LOG(LogGameFuse, Log, TEXT("========= HEADERS ========="))
	for (const auto& Pair : Headers) {
		UE_LOG(LogGameFuse, Log, TEXT("%s : %s"), *Pair.Key, *Pair.Value);
	}
}

FString GameFuseUtilities::DateTimeToString(const FDateTime& DateTime)
{
	return DateTime.ToIso8601();
}

FDateTime GameFuseUtilities::StringToDateTime(const FString& DateTimeStr)
{
	FDateTime Result;
	FDateTime::ParseIso8601(*DateTimeStr, Result);
	return Result;
}

// bool GameFuseUtilities::ConvertJsonToGameRoundRankings(const TArray<TSharedPtr<FJsonValue>>& JsonRankings,
//     TArray<FGFGameRoundRanking>& OutRankings)
// {
// 	for (const auto& JsonRanking : JsonRankings)
// 	{
// 		const TSharedPtr<FJsonObject>* RankingObj;
// 		if (JsonRanking->TryGetObject(RankingObj))
// 		{
// 			FGFGameRoundRanking Ranking;
//
// 			(*RankingObj)->TryGetNumberField("place", Ranking.Place);
// 			(*RankingObj)->TryGetNumberField("score", Ranking.Score);
//
// 			FString StartTimeStr, EndTimeStr;
// 			if ((*RankingObj)->TryGetStringField("start_time", StartTimeStr))
// 			{
// 				Ranking.StartTime = StringToDateTime(StartTimeStr);
// 			}
// 			if ((*RankingObj)->TryGetStringField("end_time", EndTimeStr))
// 			{
// 				Ranking.EndTime = StringToDateTime(EndTimeStr);
// 			}
//
// 			// Parse user data
// 			const TSharedPtr<FJsonObject>* UserObj;
// 			if ((*RankingObj)->TryGetObjectField("user", UserObj))
// 			{
// 				(*UserObj)->TryGetNumberField("id", Ranking.User.Id);
// 				(*UserObj)->TryGetStringField("username", Ranking.User.Username);
// 				(*UserObj)->TryGetBoolField("signed_in", Ranking.User.bSignedIn);
// 			}
//
// 			OutRankings.Add(Ranking);
// 		}
// 	}
// 	return true;
// }