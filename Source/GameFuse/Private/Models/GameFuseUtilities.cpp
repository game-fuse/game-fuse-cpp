/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "Models/GameFuseUtilities.h"

TMap<FString, FString> GameFuseUtilities::ConvertJsonToMap(const FString& JsonString)
{
	TMap<FString, FString> TempMap;

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonString);

	if (FJsonSerializer::Deserialize(JsonReader, JsonObject) && JsonObject.IsValid())
	{
		for (auto JsonField = JsonObject->Values.CreateConstIterator(); JsonField; ++JsonField)
		{
			const FString Key = JsonField.Key();
			FString Value;

			if (JsonObject->TryGetStringField(Key, Value))
			{
				TempMap.Add(Key, Value);
			}
		}
	}

	return TempMap;
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

FString GameFuseUtilities::MakeStrRequestBody(const FString AuthenticationToken, const FString MapBody, const TMap<FString, FString>& OurMap)
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
		return EGFCoreAPIResponseType::SetUpGame;
	if (JsonObject->HasField(TEXT("leaderboard_entries")))
		return EGFCoreAPIResponseType::ListLeaderboardEntries;
	if (JsonObject->HasField(TEXT("store_items")))
		return EGFCoreAPIResponseType::ListStoreItems;
	if (JsonObject->HasField(TEXT("mailer_response")))
		return EGFCoreAPIResponseType::ForgotPassword;
	return EGFCoreAPIResponseType::None;
}

EGFUserAPIResponseType GameFuseUtilities::DetermineUserAPIResponseType(const TSharedPtr<FJsonObject>& JsonObject)
{
	if (JsonObject->HasField(TEXT("id")) && JsonObject->HasField(TEXT("username")))
		return EGFUserAPIResponseType::Login;
	if (JsonObject->HasField(TEXT("game_user_attributes")))
		return EGFUserAPIResponseType::Attributes;
	if (JsonObject->HasField(TEXT("game_user_store_items")))
		return EGFUserAPIResponseType::StoreItems;
	if (JsonObject->HasField(TEXT("leaderboard_entries")))
		return EGFUserAPIResponseType::LeaderboardEntries;
	if (JsonObject->HasField(TEXT("credits")))
		return EGFUserAPIResponseType::Credits;
	if (JsonObject->HasField(TEXT("score")))
		return EGFUserAPIResponseType::Score;
	return EGFUserAPIResponseType::None;
}
