/**
*  Copyright (c) 2024-09-30 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFuseEnumLibrary.generated.h"

// enum conversion code thanks to https://github.com/ShadowfallStudios/ALS-Community/blob/main/Source/ALSV4_CPP/Public/Library/ALSCharacterEnumLibrary.h

/* Returns the enumeration index. */
template <typename Enumeration>
static FORCEINLINE int32 GetEnumerationIndex(const Enumeration InValue)
{
	return StaticEnum<Enumeration>()->GetIndexByValue(static_cast<int64>(InValue));
}

/* Returns the enumeration value as string. */
template <typename Enumeration>
static FORCEINLINE FString GetEnumerationToString(const Enumeration InValue)
{
	return StaticEnum<Enumeration>()->GetNameStringByValue(static_cast<int64>(InValue));
}

UENUM(meta = (ScriptName = "GF_UserAPIResponseType"))
enum class EGFUserAPIResponseType : uint8
{
	None,
	Login,
	Attributes,
	LeaderboardEntries,
	StoreItems,
	Credits,
	Score
};

UENUM(meta = (ScriptName = "GF_CoreAPIResponseType"))
enum class EGFCoreAPIResponseType : uint8
{
	None,
	SetUpGame,
	ListLeaderboardEntries,
	ListStoreItems,
	ForgotPassword,
};