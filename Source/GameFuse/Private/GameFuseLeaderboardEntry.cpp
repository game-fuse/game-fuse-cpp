// Fill out your copyright notice in the Description page of Project Settings.


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
