/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "Library/GameFuseUtilities.h"
#include "Interfaces/IHttpResponse.h"
#include "Library/GameFuseLog.h"


void GameFuseUtilities::ConvertJsonToMap(TMap<FString, FString>& InMap, const FString& JsonString)
{

	InMap.Empty();

	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		// Reserve memory in the map to avoid reallocations
		InMap.Reserve(JsonObject->Values.Num());

		// Iterate over the JSON object's key-value pairs
		for (const auto& JsonField : JsonObject->Values)
		{
			const FString& Key = JsonField.Key;
			const TSharedPtr<FJsonValue>& JsonValue = JsonField.Value;

			// Check if the JSON value is a string
			if (JsonValue.IsValid() && JsonValue->Type == EJson::String)
			{
				// Access the string value directly
				const FString& Value = JsonValue->AsString();

				// Add the key-value pair to the map without unnecessary copies
				InMap.Emplace(Key, Value);
			}
			else
			{
				UE_LOG(LogGameFuse, Error, TEXT("Invalid JSON value for key: %s \n Input String :\n %s"), *Key, *JsonString);
			}
		}
	}
}


bool GameFuseUtilities::ConvertJsonToGameData(FGFGameData& InGameData, const TSharedPtr<FJsonObject>& JsonObject)
{

	if (!JsonObject.IsValid())
	{
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
	if (!JsonObject.IsValid())
	{
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

bool GameFuseUtilities::ConvertJsonToStoreItem(FGFStoreItem& InStoreItem, const TSharedPtr<FJsonValue>& JsonValue)
{
	if (JsonValue->Type != EJson::Object)
	{
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
	if (JsonValue->Type != EJson::Object)
	{
		return false;
	}

	const TSharedPtr<FJsonObject>& JsonObject = JsonValue->AsObject();

	InLeaderboardItem.LeaderboardName = JsonObject->GetStringField(TEXT("leaderboard_name"));
	InLeaderboardItem.Username = JsonObject->GetStringField(TEXT("username"));
	InLeaderboardItem.Score = JsonObject->GetNumberField(TEXT("score"));
	InLeaderboardItem.GameUserId = JsonObject->GetNumberField(TEXT("game_user_id"));
	InLeaderboardItem.DateTime = JsonObject->GetStringField(TEXT("created_at"));

	// Convert metadata from JSON
	const TSharedPtr<FJsonObject>* MetadataObject;
	if (JsonObject->TryGetObjectField(TEXT("metadata"), MetadataObject))
	{
		ConvertJsonObjectToStringMap(*MetadataObject, InLeaderboardItem.Metadata);
	}

	return true;
}

bool GameFuseUtilities::ConvertLeaderboardItemToJson(const FGFLeaderboardEntry& LeaderboardItem, TSharedPtr<FJsonObject>& JsonObject)
{
	if (LeaderboardItem.LeaderboardName.IsEmpty())
	{
		UE_LOG(LogGameFuse, Error, TEXT("Leaderboard name is required"));
		return false;
	}
	JsonObject->SetStringField(TEXT("leaderboard_name"), LeaderboardItem.LeaderboardName);
	JsonObject->SetNumberField(TEXT("score"), LeaderboardItem.Score);
	// Convert metadata to JSON
	if (!LeaderboardItem.Metadata.IsEmpty())
	{
		TSharedPtr<FJsonObject> MetadataObject = ConvertMapToJsonObject(LeaderboardItem.Metadata);
		JsonObject->SetObjectField(TEXT("metadata"), MetadataObject);
	}

	return true;
}


#pragma region Utility Functions

TSharedPtr<FJsonObject> GameFuseUtilities::ConvertMapToJsonObject(const TMap<FString, FString>& Map)
{
	if (Map.Num() == 0)
	{
		return nullptr;
	}


	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	for (const auto& Pair : Map)
	{
		JsonObject->SetStringField(Pair.Key, Pair.Value);
	}
	return JsonObject;
}

FString GameFuseUtilities::ConvertMapToJsonStr(const TMap<FString, FString>& OurMap)
{
	const TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	for (const TPair<FString, FString>& Pair : OurMap)
	{
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
	for (const auto& Attribute : OurMap)
	{
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
	if (JsonObject->HasField(TEXT("id")) && JsonObject->HasField(TEXT("game_variables")))
	{
		return EGFCoreAPIResponseType::SetUpGame;
	}
	if (JsonObject->HasField(TEXT("leaderboard_entries")))
	{
		return EGFCoreAPIResponseType::ListLeaderboardEntries;
	}
	if (JsonObject->HasField(TEXT("store_items")))
	{
		return EGFCoreAPIResponseType::ListStoreItems;
	}
	if (JsonObject->HasField(TEXT("mailer_response")))
	{
		return EGFCoreAPIResponseType::ForgotPassword;
	}
	return EGFCoreAPIResponseType::None;
}

EGFUserAPIResponseType GameFuseUtilities::DetermineUserAPIResponseType(const TSharedPtr<FJsonObject>& JsonObject)
{
	if (JsonObject->HasField(TEXT("id")) && JsonObject->HasField(TEXT("username")) && JsonObject->HasField(TEXT("number_of_logins")))
	{
		return EGFUserAPIResponseType::Login;
	}
	if (JsonObject->HasField(TEXT("game_user_attributes")))
	{
		return EGFUserAPIResponseType::Attributes;
	}
	if (JsonObject->HasField(TEXT("game_user_store_items")))
	{
		return EGFUserAPIResponseType::StoreItems;
	}
	if (JsonObject->HasField(TEXT("leaderboard_entries")))
	{
		return EGFUserAPIResponseType::LeaderboardEntries;
	}
	if (JsonObject->HasField(TEXT("credits")))
	{
		return EGFUserAPIResponseType::Credits;
	}
	if (JsonObject->HasField(TEXT("score")))
	{
		return EGFUserAPIResponseType::Score;
	}
	return EGFUserAPIResponseType::None;
}

void GameFuseUtilities::LogRequest(FHttpRequestPtr HttpRequest)
{
	UE_LOG(LogGameFuse, Log, TEXT("=========   URL   ========= \n %s"), *(HttpRequest->GetURL()));
	UE_LOG(LogGameFuse, Log, TEXT("========= HEADERS ========="))
	for (const FString& currHeader : HttpRequest->GetAllHeaders())
	{
		UE_LOG(LogGameFuse, Log, TEXT("%s"), *currHeader);
	}

	// Log the content body if it exists
	TArray<uint8> ContentArray = HttpRequest->GetContent();
	if (!ContentArray.IsEmpty())
	{
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
	for (const auto& Pair : Headers)
	{
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

bool GameFuseUtilities::ConvertJsonObjectToStringMap(const TSharedPtr<FJsonObject>& JsonObject, TMap<FString, FString>& InMap, const FString& FieldKey)
{
	InMap.Empty(); // Clear existing metadata

	// if FieldKey is empty, assume the object is the map
	// aka the json object looks like {"key1": "value1", "key2": "value2"}
	if (FieldKey.IsEmpty())
	{
		// assume the object is the map
		for (const auto& Pair : JsonObject->Values)
		{
			if (Pair.Value.IsValid() && Pair.Value->Type == EJson::String)
			{
				InMap.Add(Pair.Key, Pair.Value->AsString());
			}
		}
		return true;
	}


	// if field is null, return success and skip
	if (JsonObject->HasTypedField(FStringView(FieldKey), EJson::Null))
	{
		UE_LOG(LogGameFuse, Log, TEXT("ConvertJsonToGameRound: %s field is null, skipping"), *FieldKey);
		return true;
	}

	// if FieldKey is not empty, assume the object is a field in the map
	// aka the json object looks like {"field_key": {"key1": "value1", "key2": "value2"}}
	const TSharedPtr<FJsonObject>* SrcJsonObject = nullptr;
	if (JsonObject->TryGetObjectField(FStringView(FieldKey), SrcJsonObject))
	{
		if (!SrcJsonObject->IsValid())
		{
			UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Invalid object value for field: %s"), *FieldKey);
			return false;
		}

		if ((*SrcJsonObject)->Values.Num() == 0)
		{
			UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: object was empty: %s"), *FieldKey);
			return true;
		}

		for (const auto& Pair : (*SrcJsonObject)->Values)
		{
			if (!Pair.Value.IsValid())
			{
				UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Invalid object value for key: %s"), *Pair.Key);
				continue;
			}

			FString ValueStr;
			if (Pair.Value->TryGetString(ValueStr))
			{
				InMap.Add(Pair.Key, ValueStr);
			}
		}
		return true;
	}
	return true;
}

#pragma endregion