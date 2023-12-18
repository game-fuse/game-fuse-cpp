/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "GameFuseUtilities.h"

TMap<FString, FString> GameFuseUtilities::ConvertJsonToMap(const FString &JsonString)
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

FString GameFuseUtilities::MakeStrRequestBody(const FString AuthenticationToken, const FString MapBody,
    const TMap<FString, FString>& OurMap)
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

