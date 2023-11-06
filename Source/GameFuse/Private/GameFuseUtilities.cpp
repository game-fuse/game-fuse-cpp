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

    UE_LOG(LogTemp, Error, TEXT("GameFuse Utilities Converted Map To Json Str : %s"), *JsonString);
    
    return JsonString;
}

