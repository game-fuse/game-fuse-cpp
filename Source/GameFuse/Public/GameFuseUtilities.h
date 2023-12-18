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

class GAMEFUSE_API GameFuseUtilities
{
public:

	static TMap<FString, FString> ConvertJsonToMap(const FString& JsonString);
	static FString ConvertMapToJsonStr(const TMap<FString, FString>& OurMap);

	static FString MakeStrRequestBody(const FString AuthenticationToken, const FString MapBody, const TMap<FString, FString>& OurMap);
	

};
