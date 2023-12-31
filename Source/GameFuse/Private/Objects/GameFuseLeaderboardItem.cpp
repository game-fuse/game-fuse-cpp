/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "Objects/GameFuseLeaderboardItem.h"

UGameFuseLeaderboardItem::UGameFuseLeaderboardItem():
	LeaderboardName(""),
	Score(0),
	Username(""),
	GameUserId(0),
	ExtraAttributes(""),
	DateTime("")
{
}

FString UGameFuseLeaderboardItem::GetUsername()
{
	return Username;
}

int32 UGameFuseLeaderboardItem::GetScore()
{
	return Score;
}

FString UGameFuseLeaderboardItem::GetLeaderboardName()
{
	return LeaderboardName;
}

FString UGameFuseLeaderboardItem::GetExtraAttributes()
{
	return ExtraAttributes;
}

FString UGameFuseLeaderboardItem::GetTimestamp()
{
	return DateTime;
}
