/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "GameFuseLeaderboardEntry.h"

UGameFuseLeaderboardEntry::UGameFuseLeaderboardEntry():
	LeaderboardName(""),
	Score(0),
	Username(""),
	GameUserId(0),
	ExtraAttributes(""),
	DateTime("")
{
}

FString UGameFuseLeaderboardEntry::GetUsername()
{
	return Username;
}

int32 UGameFuseLeaderboardEntry::GetScore()
{
	return Score;
}

FString UGameFuseLeaderboardEntry::GetLeaderboardName()
{
	return LeaderboardName;
}

FString UGameFuseLeaderboardEntry::GetExtraAttributes()
{
	return ExtraAttributes;
}

FString UGameFuseLeaderboardEntry::GetTimestamp()
{
	return DateTime;
}
