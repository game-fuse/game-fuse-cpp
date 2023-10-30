// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonWriter.h"
#include "Serialization/JsonSerializer.h"
#include "Dom/JsonObject.h"
#include "Dom/JsonValue.h"

/**
 * 
 */
class GAMEFUSE_API GameFuseUtilities
{
public:

	static TMap<FString, FString> ConvertJsonToMap(const FString& JsonString);
	static FString ConvertMapToJsonStr(const TMap<FString, FString>& OurMap);

};
