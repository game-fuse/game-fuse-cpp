/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "Library/GameFuseUtilities.h"
#include "Interfaces/IHttpResponse.h"
#include "Library/GameFuseEnumLibrary.h"
#include "Library/GameFuseLog.h"
#include "Interfaces/IHttpResponse.h"
#include "Library/GameFuseStructLibrary.h"


#pragma region Struct => JSON Conversion

bool GameFuseUtilities::ConvertGameRoundToJson(const FGFGameRound& GameRound, const TSharedPtr<FJsonObject>& JsonObject)
{
	// required fields
	JsonObject->SetNumberField("game_user_id", GameRound.GameUserId);

	if (GameRound.StartTime != FDateTime()) {
		JsonObject->SetStringField("start_time", GameRound.StartTime.ToIso8601());
	}
	if (GameRound.EndTime != FDateTime()) {
		JsonObject->SetStringField("end_time", GameRound.EndTime.ToIso8601());
	}

	JsonObject->SetNumberField("score", GameRound.Score);

	if (GameRound.Place >= 0) {
		JsonObject->SetNumberField("place", GameRound.Place);
	}

	if (!GameRound.GameType.IsEmpty()) {
		JsonObject->SetStringField("game_type", GameRound.GameType);
	} else { // special case since it's marked as not required, but the request will fail without it
		UE_LOG(LogGameFuse, Warning, TEXT("GameRoundToJson: Missing required field 'game_type', adding default value"));
		JsonObject->SetStringField("game_type", "default");
	}

	if (GameRound.bMultiplayer) {
		JsonObject->SetBoolField("multiplayer", GameRound.bMultiplayer);
	}
	if (GameRound.MultiplayerGameRoundId >= 0) {
		JsonObject->SetNumberField("multiplayer_game_round_id", GameRound.MultiplayerGameRoundId);
	}

	if (!GameRound.Metadata.IsEmpty()) {
		JsonObject->SetObjectField("metadata", ConvertMapToJsonObject(GameRound.Metadata));
	}

	return true;
}

bool GameFuseUtilities::ConvertGroupToJson(const FGFGroup& Group, const TSharedPtr<FJsonObject>& JsonObject)
{
	JsonObject->SetStringField("name", Group.Name);
	JsonObject->SetStringField("group_type", Group.GroupType);
	JsonObject->SetNumberField("max_group_size", Group.MaxGroupSize);
	JsonObject->SetBoolField("can_auto_join", Group.bCanAutoJoin);
	JsonObject->SetBoolField("is_invite_only", Group.bIsInviteOnly);
	JsonObject->SetBoolField("searchable", Group.bSearchable);
	JsonObject->SetBoolField("admins_only_can_create_attributes", Group.bAdminsOnlyCanCreateAttributes);

	return true;
}

#pragma endregion

#pragma region JSON => Struct Conversion

bool GameFuseUtilities::ConvertJsonToGameData(FGFGameData& InGameData, const FString& JsonString)
{
	if (JsonString.IsEmpty()) {
		UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameData: Empty JSON string"));
		return false;
	}

	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameData: Failed to parse JSON string: %s"), *JsonString);
		return false;
	}

	return ConvertJsonToGameData(InGameData, JsonObject);
}


bool GameFuseUtilities::ConvertJsonToGameData(FGFGameData& InGameData, const TSharedPtr<FJsonObject>& JsonObject)
{

	if (!JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid JSON object for GameData conversion"));
		return false;
	}

	JsonObject->TryGetNumberField(TEXT("id"), InGameData.Id);
	JsonObject->TryGetStringField(TEXT("token"), InGameData.Token);
	JsonObject->TryGetStringField(TEXT("name"), InGameData.Name);
	JsonObject->TryGetStringField(TEXT("description"), InGameData.Description);

	return true;
}

bool GameFuseUtilities::ConvertJsonToUserData(FGFUserData& InUserData, const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToUserData: Failed to parse JSON string: %s"), *JsonString);
		return false;
	}

	return ConvertJsonToUserData(InUserData, JsonObject);
}

bool GameFuseUtilities::ConvertJsonToUserData(FGFUserData& InUserData, const TSharedPtr<FJsonObject>& JsonObject)
{
	if (!JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid JSON object for UserData conversion"));
		return false;
	}

	// Extract basic user data
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
	if (JsonValue->Type != EJson::Object) {
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

bool GameFuseUtilities::ConvertJsonStringToStringMap(const FString& String, TMap<FString, FString>& Map)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(String);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to deserialize JSON string to JSON object"));
		return false;
	}

	return ConvertJsonObjectToStringMap(JsonObject, Map);
}

bool GameFuseUtilities::ConvertJsonToLeaderboardEntry(FGFLeaderboardEntry& InLeaderboardItem, const TSharedPtr<FJsonValue>& JsonValue)
{
	if (JsonValue->Type != EJson::Object) {
		return false;
	}

	const TSharedPtr<FJsonObject>& JsonObject = JsonValue->AsObject();

	InLeaderboardItem.LeaderboardName = JsonObject->GetStringField(TEXT("leaderboard_name"));
	InLeaderboardItem.Username = JsonObject->GetStringField(TEXT("username"));
	InLeaderboardItem.Score = JsonObject->GetNumberField(TEXT("score"));
	InLeaderboardItem.GameUserId = JsonObject->GetNumberField(TEXT("game_user_id"));
	InLeaderboardItem.DateTime = JsonObject->GetStringField(TEXT("created_at"));

	// Convert metadata from JSON
	FString MetadataString;
	if (JsonObject->TryGetStringField(TEXT("metadata"), MetadataString)) {
		const TSharedPtr<FJsonObject>& MetaDataObject = JsonValue->AsObject();
		return ConvertJsonStringToStringMap(MetadataString, InLeaderboardItem.Metadata);
	}

	return true;
}

bool GameFuseUtilities::ConvertJsonToLeaderboardEntries(TArray<FGFLeaderboardEntry>& InLeaderboardArray, const FString& JsonString)
{
	if (JsonString.IsEmpty()) {
		UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Empty JSON string"));
		return false;
	}

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Failed to parse JSON string: %s"), *JsonString);
		return false;
	}

	return ConvertJsonToLeaderboardEntries(InLeaderboardArray, JsonObject);
}

bool GameFuseUtilities::ConvertJsonToLeaderboardEntries(TArray<FGFLeaderboardEntry>& InLeaderboardArray, const TSharedPtr<FJsonObject>& JsonObject)
{
	if (!JsonObject->HasField(TEXT("leaderboard_entries"))) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid JSON object for LeaderboardEntries conversion"));
		return false;
	}

	const TArray<TSharedPtr<FJsonValue>>* JsonArray;
	if (!JsonObject->TryGetArrayField(TEXT("leaderboard_entries"), JsonArray)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get leaderboard_entries array from JSON"));
		return false;
	}

	for (const TSharedPtr<FJsonValue>& JsonValue : *JsonArray) {
		FGFLeaderboardEntry LeaderboardEntry;
		if (ConvertJsonToLeaderboardEntry(LeaderboardEntry, JsonValue)) {
			InLeaderboardArray.Add(LeaderboardEntry);
		}
	}

	return true;
}

bool GameFuseUtilities::ConvertLeaderboardItemToJson(const FGFLeaderboardEntry& LeaderboardItem, TSharedPtr<FJsonObject>& JsonObject)
{
	if (LeaderboardItem.LeaderboardName.IsEmpty()) {
		UE_LOG(LogGameFuse, Error, TEXT("Leaderboard name is required"));
		return false;
	}
	JsonObject->SetStringField(TEXT("leaderboard_name"), LeaderboardItem.LeaderboardName);
	JsonObject->SetNumberField(TEXT("score"), LeaderboardItem.Score);
	// Convert metadata to JSON
	if (!LeaderboardItem.Metadata.IsEmpty()) {
		TSharedPtr<FJsonObject> MetadataObject = ConvertMapToJsonObject(LeaderboardItem.Metadata);
		JsonObject->SetObjectField(TEXT("metadata"), MetadataObject);
	}

	return true;
}

bool GameFuseUtilities::ConvertJsonToFriendRequests(TArray<FGFFriendRequest>& OutRequests, const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to deserialize JSON string to JSON object"));
		return false;
	}

	const TArray<TSharedPtr<FJsonValue>>* JsonArray;
	if (!JsonObject->TryGetArrayField(TEXT("incoming_friend_requests"), JsonArray) &&
		!JsonObject->TryGetArrayField(TEXT("outgoing_friend_requests"), JsonArray)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get friend_requests array from JSON"));
		return false;
	}

	OutRequests.Empty();
	for (const TSharedPtr<FJsonValue>& JsonValue : *JsonArray) {
		if (const TSharedPtr<FJsonObject> RequestObject = JsonValue->AsObject()) {
			FGFFriendRequest Request;
			if (ConvertJsonToFriendRequest(Request, RequestObject)) {
				OutRequests.Add(Request);
			}
		}
	}

	return true;
}

bool GameFuseUtilities::ConvertJsonToFriendsList(TArray<FGFUserData>& OutFriends, const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to deserialize JSON string to JSON object"));
		return false;
	}

	const TArray<TSharedPtr<FJsonValue>>* JsonArray;
	if (!JsonObject->TryGetArrayField(TEXT("friends"), JsonArray)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get friends array from JSON"));
		return false;
	}

	OutFriends.Empty();
	for (const TSharedPtr<FJsonValue>& JsonValue : *JsonArray) {
		if (const TSharedPtr<FJsonObject> FriendObject = JsonValue->AsObject()) {
			FGFUserData Friend;
			if (ConvertJsonToUserData(Friend, FriendObject)) {
				OutFriends.Add(Friend);
			}
		}
	}

	return true;
}

bool GameFuseUtilities::ConvertJsonToFriendRequest(FGFFriendRequest& OutRequest, const TSharedPtr<FJsonObject>& JsonObject)
{
	if (!JsonObject.IsValid()) {
		return false;
	}

	// Get the friendship ID
	JsonObject->TryGetNumberField(TEXT("friendship_id"), OutRequest.FriendshipId);

	// Get the status if present
	FString StatusStr;
	if (JsonObject->TryGetStringField(TEXT("status"), StatusStr)) {
		if (StatusStr == TEXT("accepted")) {
			OutRequest.Status = EGFInviteRequestStatus::Accepted;
		} else if (StatusStr == TEXT("declined")) {
			OutRequest.Status = EGFInviteRequestStatus::Declined;
		}

	} else {
		OutRequest.Status = EGFInviteRequestStatus::None;
	}

	// Get the request creation time
	FString CreatedAtStr;
	if (JsonObject->TryGetStringField(TEXT("created_at"), CreatedAtStr)) {
		OutRequest.RequestCreatedAt = StringToDateTime(CreatedAtStr);
	}

	// Create and populate the OtherUser data

	if (!ConvertJsonToUserData(OutRequest.OtherUser, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse OtherUser data from JSON"));
		return false;
	}

	return true;
}

#pragma endregion

#pragma region Game Rounds

bool GameFuseUtilities::ConvertJsonToGameRound(FGFGameRound& InGameRound, const FString& JsonString)
{
	if (JsonString.IsEmpty()) {
		UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Empty JSON string"));
		return false;
	}

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Failed to parse JSON string: %s"), *JsonString);
		return false;
	}

	return ConvertJsonToGameRound(InGameRound, JsonObject);
}

bool GameFuseUtilities::ConvertJsonToGameRound(FGFGameRound& InGameRound, const TSharedPtr<FJsonObject>& JsonObject)
{
	if (!JsonObject->HasField(TEXT("id")) || !JsonObject->HasField(TEXT("game_user_id"))) {
		UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Missing required fields"));
		return false;
	}

	JsonObject->TryGetNumberField(TEXT("id"), InGameRound.Id);
	JsonObject->TryGetNumberField(TEXT("game_user_id"), InGameRound.GameUserId);

	// Optional fields with default values
	FString StartTime;
	if (JsonObject->TryGetStringField(TEXT("start_time"), StartTime)) {
		InGameRound.StartTime = StringToDateTime(StartTime);
	}

	FString EndTime;
	if (JsonObject->TryGetStringField(TEXT("end_time"), EndTime)) {
		InGameRound.EndTime = StringToDateTime(EndTime);
	}

	JsonObject->TryGetNumberField(TEXT("score"), InGameRound.Score);
	JsonObject->TryGetNumberField(TEXT("place"), InGameRound.Place);
	JsonObject->TryGetStringField(TEXT("game_type"), InGameRound.GameType);

	if (JsonObject->HasField(TEXT("metadata")) && !ConvertJsonObjectToStringMap(JsonObject, InGameRound.Metadata, "metadata")) {
		UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Failed to convert metadata to map"));
		return false;
	}

	JsonObject->TryGetNumberField(TEXT("multiplayer_game_round_id"), InGameRound.MultiplayerGameRoundId);

	if (InGameRound.MultiplayerGameRoundId > 0) {
		const TArray<TSharedPtr<FJsonValue>>* RankingArray;
		JsonObject->TryGetArrayField(TEXT("rankings"), RankingArray);
		if (!ConvertJsonArrayToGameRoundRankings(RankingArray, InGameRound.Rankings)) {
			UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Failed to convert rankings to array"));
			return false;
		}
	}

	return true;
}


bool GameFuseUtilities::ConvertJsonArrayToGameRoundRankings(const TArray<TSharedPtr<FJsonValue>>* JsonRankings,
															TArray<FGFGameRoundRanking>& OutRankings)
{
	for (const auto& JsonRanking : *JsonRankings) {
		const TSharedPtr<FJsonObject>* RankingObj;
		if (JsonRanking->TryGetObject(RankingObj)) {
			FGFGameRoundRanking Ranking;

			if (!(*RankingObj)->TryGetNumberField(TEXT("place"), Ranking.Place)) {
				// null represented with -1;
				UE_LOG(LogGameFuse, Log, TEXT("null place represented with -1"));
				Ranking.Place = -1;
			}
			(*RankingObj)->TryGetNumberField(TEXT("score"), Ranking.Score);

			FString StartTimeStr, EndTimeStr;
			if ((*RankingObj)->TryGetStringField(TEXT("start_time"), StartTimeStr)) {
				Ranking.StartTime = StringToDateTime(StartTimeStr);
			}
			if ((*RankingObj)->TryGetStringField(TEXT("end_time"), EndTimeStr)) {
				Ranking.EndTime = StringToDateTime(EndTimeStr);
			}

			// Parse user data
			const TSharedPtr<FJsonObject>* UserObj;
			if ((*RankingObj)->TryGetObjectField(TEXT("user"), UserObj)) {
				ConvertJsonToUserData(Ranking.User, *UserObj);
			}

			OutRankings.Emplace(Ranking);
		} else {
			UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonArrayToGameRoundRankings: Invalid ranking object"));
			return false;
		}
	}
	return true;
}

bool GameFuseUtilities::ConvertJsonToGameRounds(TArray<FGFGameRound>& InGameRounds, const FString& JsonString)
{
	if (JsonString.IsEmpty()) {
		UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonToGameRound: Empty JSON string"));
		return false;
	}

	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to deserialize game rounds JSON string to JSON object"));
		return false;
	}

	const TArray<TSharedPtr<FJsonValue>>* JsonArray;
	if (!JsonObject->TryGetArrayField(TEXT("game_rounds"), JsonArray)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get game rounds array from JSON"));
		return false;
	}

	for (const TSharedPtr<FJsonValue>& JsonValue : *JsonArray) {
		if (JsonValue->Type != EJson::Object) {
			UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonArrayToGameRounds: Invalid JSON value"));
			return false;
		}

		FGFGameRound GameRound;
		if (ConvertJsonToGameRound(GameRound, JsonValue->AsObject().ToSharedRef())) {
			InGameRounds.Emplace(GameRound);
		} else {
			UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonArrayToGameRounds: Failed to convert JSON value to GameRound"));
			return false;
		}
	}

	return true;
}

#pragma endregion

#pragma region Groups

bool GameFuseUtilities::ConvertJsonToGroupAttribute(FGFGroupAttribute& InAttribute, const TSharedPtr<FJsonObject>& JsonObject)
{
	if (!JsonObject.IsValid()) {
		return false;
	}

	JsonObject->TryGetNumberField(TEXT("id"), InAttribute.Id);
	JsonObject->TryGetStringField(TEXT("key"), InAttribute.Key);
	JsonObject->TryGetStringField(TEXT("value"), InAttribute.Value);
	JsonObject->TryGetNumberField(TEXT("creator_id"), InAttribute.CreatorId); // Server sends creator_id but it's actually the group ID
	JsonObject->TryGetBoolField(TEXT("can_edit"), InAttribute.bCanEdit);

	return true;
}

bool GameFuseUtilities::ConvertJsonArrayToGroupAttributes(TArray<FGFGroupAttribute>& InAttributes, const TArray<TSharedPtr<FJsonValue>>* JsonArray)
{
	if (!JsonArray) {
		return false;
	}

	InAttributes.Empty();
	for (const auto& JsonValue : *JsonArray) {
		if (JsonValue->Type != EJson::Object) {
			continue;
		}

		FGFGroupAttribute Attribute;
		if (ConvertJsonToGroupAttribute(Attribute, JsonValue->AsObject())) {
			InAttributes.Add(Attribute);
		}
	}

	return true;
}

bool GameFuseUtilities::ConvertJsonToGroupAttributeResponse(TArray<FGFGroupAttribute>& OutAttributes, const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to deserialize JSON string to JSON object"));
		return false;
	}

	const TArray<TSharedPtr<FJsonValue>>* AttributesArray;
	if (!JsonObject->TryGetArrayField(TEXT("attributes"), AttributesArray)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get attributes array from JSON"));
		return false;
	}

	return ConvertJsonArrayToGroupAttributes(OutAttributes, AttributesArray);
}

bool GameFuseUtilities::ConvertJsonToGroup(FGFGroup& InGroup, const TSharedPtr<FJsonObject>& JsonObject)
{
	if (!JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid JSON object for Group conversion"));
		return false;
	}

	JsonObject->TryGetNumberField(TEXT("id"), InGroup.Id);
	JsonObject->TryGetStringField(TEXT("name"), InGroup.Name);
	JsonObject->TryGetStringField(TEXT("group_type"), InGroup.GroupType);
	JsonObject->TryGetNumberField(TEXT("max_group_size"), InGroup.MaxGroupSize);
	JsonObject->TryGetBoolField(TEXT("can_auto_join"), InGroup.bCanAutoJoin);
	JsonObject->TryGetBoolField(TEXT("is_invite_only"), InGroup.bIsInviteOnly);
	JsonObject->TryGetBoolField(TEXT("searchable"), InGroup.bSearchable);
	JsonObject->TryGetBoolField(TEXT("admins_only_can_create_attributes"), InGroup.bAdminsOnlyCanCreateAttributes);
	JsonObject->TryGetNumberField(TEXT("member_count"), InGroup.MemberCount);

	// Convert members array
	const TArray<TSharedPtr<FJsonValue>>* MembersArray;
	if (JsonObject->TryGetArrayField(TEXT("members"), MembersArray)) {
		InGroup.Members.Empty();
		for (const auto& JsonValue : *MembersArray) {
			if (JsonValue->Type != EJson::Object) {
				continue;
			}

			FGFUserData Member;
			if (ConvertJsonToUserData(Member, JsonValue->AsObject())) {
				InGroup.Members.Add(Member);
			}
		}
	}

	// Convert admins array
	const TArray<TSharedPtr<FJsonValue>>* AdminsArray;
	if (JsonObject->TryGetArrayField(TEXT("admins"), AdminsArray)) {
		InGroup.Admins.Empty();
		for (const auto& JsonValue : *AdminsArray) {
			if (JsonValue->Type != EJson::Object) {
				continue;
			}

			FGFUserData Admin;
			if (ConvertJsonToUserData(Admin, JsonValue->AsObject())) {
				InGroup.Admins.Add(Admin);
			}
		}
	}

	// Convert attributes array
	const TArray<TSharedPtr<FJsonValue>>* AttributesArray;
	if (JsonObject->TryGetArrayField(TEXT("attributes"), AttributesArray)) {
		ConvertJsonArrayToGroupAttributes(InGroup.Attributes, AttributesArray);
	}

	return true;
}

bool GameFuseUtilities::ConvertJsonToGroup(FGFGroup& InGroup, const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to deserialize JSON string to JSON object"));
		return false;
	}

	return ConvertJsonToGroup(InGroup, JsonObject);
}

bool GameFuseUtilities::ConvertJsonArrayToGroups(TArray<FGFGroup>& InGroups, const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to deserialize JSON string to JSON object"));
		return false;
	}

	const TArray<TSharedPtr<FJsonValue>>* JsonArray;
	if (!JsonObject->TryGetArrayField(TEXT("groups"), JsonArray)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to get groups array from JSON"));
		return false;
	}

	InGroups.Empty();
	for (const auto& JsonValue : *JsonArray) {
		if (JsonValue->Type != EJson::Object) {
			continue;
		}

		FGFGroup Group;
		if (ConvertJsonToGroup(Group, JsonValue->AsObject())) {
			InGroups.Add(Group);
		}
	}

	return true;
}

#pragma endregion

#pragma region Group Connections

bool GameFuseUtilities::ConvertJsonToGroupConnection(FGFGroupConnection& InConnection, const TSharedPtr<FJsonObject>& JsonObject)
{
	if (!JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Invalid JSON object for group connection"));
		return false;
	}

	JsonObject->TryGetNumberField(TEXT("id"), InConnection.Id);

	// Convert status string to enum
	FString StatusStr;
	if (JsonObject->TryGetStringField(TEXT("status"), StatusStr)) {
		if (StatusStr == TEXT("accepted")) {
			InConnection.Status = EGFInviteRequestStatus::Accepted;
		} else if (StatusStr == TEXT("declined")) {
			InConnection.Status = EGFInviteRequestStatus::Declined;
		} else if (StatusStr == TEXT("pending")) {
			InConnection.Status = EGFInviteRequestStatus::Pending;
		} else {
			InConnection.Status = EGFInviteRequestStatus::None;
		}
	} else {
		InConnection.Status = EGFInviteRequestStatus::None;
	}

	// Get the user data if present
	const TSharedPtr<FJsonObject>* UserObject;
	if (JsonObject->TryGetObjectField(TEXT("user"), UserObject)) {
		if (!ConvertJsonToUserData(InConnection.User, *UserObject)) {
			UE_LOG(LogGameFuse, Error, TEXT("Failed to parse user data in group connection"));
			return false;
		}
	}

	return true;
}

bool GameFuseUtilities::ConvertJsonToGroupConnection(FGFGroupConnection& InConnection, const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to deserialize JSON string to JSON object"));
		return false;
	}

	return ConvertJsonToGroupConnection(InConnection, JsonObject);
}

#pragma endregion

#pragma region Utility Functions

TSharedPtr<FJsonObject> GameFuseUtilities::ConvertMapToJsonObject(const TMap<FString, FString>& Map)
{
	if (Map.Num() == 0) {
		return nullptr;
	}


	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	for (const auto& Pair : Map) {
		JsonObject->SetStringField(Pair.Key, Pair.Value);
	}
	return JsonObject;
}

FString GameFuseUtilities::ConvertMapToJsonStr(const TMap<FString, FString>& OurMap)
{
	const TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject);

	for (const TPair<FString, FString>& Pair : OurMap) {
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
	for (const auto& Attribute : OurMap) {
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
	if (JsonObject->HasField(TEXT("id")) && JsonObject->HasField(TEXT("game_variables"))) {
		return EGFCoreAPIResponseType::SetUpGame;
	}
	if (JsonObject->HasField(TEXT("leaderboard_entries"))) {
		return EGFCoreAPIResponseType::ListLeaderboardEntries;
	}
	if (JsonObject->HasField(TEXT("store_items"))) {
		return EGFCoreAPIResponseType::ListStoreItems;
	}
	if (JsonObject->HasField(TEXT("mailer_response"))) {
		return EGFCoreAPIResponseType::ForgotPassword;
	}
	return EGFCoreAPIResponseType::None;
}

EGFUserAPIResponseType GameFuseUtilities::DetermineUserAPIResponseType(const TSharedPtr<FJsonObject>& JsonObject)
{
	if (JsonObject->HasField(TEXT("id")) && JsonObject->HasField(TEXT("username")) && JsonObject->HasField(TEXT("authentication_token"))) {
		return EGFUserAPIResponseType::Login;
	}
	if (JsonObject->HasField(TEXT("game_user_attributes"))) {
		return EGFUserAPIResponseType::Attributes;
	}
	if (JsonObject->HasField(TEXT("game_user_store_items"))) {
		return EGFUserAPIResponseType::StoreItems;
	}
	if (JsonObject->HasField(TEXT("leaderboard_entries"))) {
		return EGFUserAPIResponseType::LeaderboardEntries;
	}
	if (JsonObject->HasField(TEXT("credits"))) {
		return EGFUserAPIResponseType::Credits;
	}
	if (JsonObject->HasField(TEXT("score"))) {
		return EGFUserAPIResponseType::Score;
	}
	return EGFUserAPIResponseType::None;
}

void GameFuseUtilities::LogRequest(FHttpRequestPtr HttpRequest)
{
	UE_LOG(LogGameFuse, Log, TEXT("=========   URL   ========= \n %s"), *(HttpRequest->GetURL()));
	UE_LOG(LogGameFuse, Log, TEXT("METHOD == %s"), *(HttpRequest->GetVerb()));
	UE_LOG(LogGameFuse, Log, TEXT("========= HEADERS ========="))
	for (const FString& currHeader : HttpRequest->GetAllHeaders()) {
		UE_LOG(LogGameFuse, Log, TEXT("%s"), *currHeader);
	}

	// Log the content body if it exists
	TArray<uint8> ContentArray = HttpRequest->GetContent();
	if (!ContentArray.IsEmpty()) {
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
	for (const auto& Pair : Headers) {
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
	if (FieldKey.IsEmpty()) {
		// assume the object is the map
		for (const auto& Pair : JsonObject->Values) {
			if (Pair.Value.IsValid() && Pair.Value->Type == EJson::String) {
				InMap.Add(Pair.Key, Pair.Value->AsString());
			}
		}
		return true;
	}


	// if field is null, return success and skip
	if (JsonObject->HasTypedField(FStringView(FieldKey), EJson::Null)) {
		UE_LOG(LogGameFuse, Log, TEXT("ConvertJsonObjectToStringMap: %s field is null, skipping"), *FieldKey);
		return true;
	}

	// if FieldKey is not empty, assume the object is a field in the map
	// aka the json object looks like {"field_key": {"key1": "value1", "key2": "value2"}}
	const TSharedPtr<FJsonObject>* SrcJsonObject = nullptr;
	if (JsonObject->TryGetObjectField(FStringView(FieldKey), SrcJsonObject)) {
		if (!SrcJsonObject->IsValid()) {
			UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonObjectToStringMap: Invalid object value for field: %s"), *FieldKey);
			return false;
		}

		if ((*SrcJsonObject)->Values.Num() == 0) {
			UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonObjectToStringMap: object was empty: %s"), *FieldKey);
			return true;
		}

		for (const auto& Pair : (*SrcJsonObject)->Values) {
			if (!Pair.Value.IsValid()) {
				UE_LOG(LogGameFuse, Warning, TEXT("ConvertJsonObjectToStringMap: Invalid object value for key: %s"), *Pair.Key);
				continue;
			}

			FString ValueStr;
			if (Pair.Value->TryGetString(ValueStr)) {
				InMap.Add(Pair.Key, ValueStr);
			}
		}
		return true;
	}
	return true;
}

bool GameFuseUtilities::ConvertJsonToStoreItems(TArray<FGFStoreItem>& InStoreItems, const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse store items JSON response"));
		return false;
	}

	// Parse store items array
	const TArray<TSharedPtr<FJsonValue>>* StoreItemsArray;
	if (!JsonObject->TryGetArrayField(TEXT("game_user_store_items"), StoreItemsArray)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to find game_user_store_items array in response"));
		return false;
	}

	// Convert each store item
	for (const auto& ItemValue : *StoreItemsArray) {
		FGFStoreItem StoreItem;
		if (ConvertJsonToStoreItem(StoreItem, ItemValue)) {
			InStoreItems.Add(StoreItem);
		}
	}

	return true;
}

bool GameFuseUtilities::ConvertJsonToAttributes(FGFAttributeList& InAttributes, const FString& JsonString)
{
	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid()) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse attributes JSON response"));
		return false;
	}


	// Parse attributes object
	const TArray<TSharedPtr<FJsonValue>>* AttributesValues;
	if (!JsonObject->TryGetArrayField(TEXT("game_user_attributes"), AttributesValues)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to find game_user_attributes object in response"));
		return false;
	}

	// Convert attributes to map
	return ConvertJsonArrayToAttributes(InAttributes, AttributesValues);
}

bool GameFuseUtilities::ConvertJsonArrayToAttributes(FGFAttributeList& InAttributes, const TArray<TSharedPtr<FJsonValue>>* Array)
{
	for (const auto& JsonValue : *Array) {
		if (JsonValue->Type != EJson::Object) {
			UE_LOG(LogGameFuse, Error, TEXT("Invalid JSON value in attributes array"));
			return false;
		}

		const TSharedPtr<FJsonObject>& JsonObject = JsonValue->AsObject();
		FString Key, Value;
		if (!JsonObject->HasField(TEXT("key")) || !JsonObject->HasField(TEXT("value"))) {
			UE_LOG(LogGameFuse, Error, TEXT("Missing key or value field in attribute object"));
			return false;
		}

		JsonObject->TryGetStringField(TEXT("key"), Key);
		JsonObject->TryGetStringField(TEXT("value"), Value);
		InAttributes.Attributes.Add(Key, Value);
	}


	return true;
}

bool GameFuseUtilities::ConvertJsonToGameVariables(TMap<FString, FString>& OutVariables, const TSharedPtr<FJsonObject>& JsonObject)
{
	OutVariables.Empty();

	if (!JsonObject.IsValid())
	{
		UE_LOG(LogGameFuse, Error, TEXT("Invalid JSON object for game variables"));
		return false;
	}

	const TArray<TSharedPtr<FJsonValue>>* GameVariablesArray = nullptr;
	if (!JsonObject->TryGetArrayField(TEXT("game_variables"), GameVariablesArray))
	{
		UE_LOG(LogGameFuse, Warning, TEXT("No game_variables field found in JSON"));
		return false;
	}

	for (const TSharedPtr<FJsonValue>& JsonValue : *GameVariablesArray)
	{
		const TSharedPtr<FJsonObject> VariableObject = JsonValue->AsObject();
		if (!VariableObject.IsValid())
		{
			continue;
		}

		FString Key = "";
		FString Value = "";

		if (VariableObject->TryGetStringField(TEXT("key"), Key) && VariableObject->TryGetStringField(TEXT("value"), Value))
		{
			OutVariables.Add(Key, Value);
		}
	}

	UE_LOG(LogGameFuse, Log, TEXT("Parsed %d game variables"), OutVariables.Num());
	return true;
}

bool GameFuseUtilities::ConvertJsonToGameVariables(TMap<FString, FString>& OutVariables, const FString& JsonString)
{
	OutVariables.Empty();

	if (JsonString.IsEmpty())
	{
		UE_LOG(LogGameFuse, Error, TEXT("Empty JSON string for game variables"));
		return false;
	}

	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(JsonString);
	TSharedPtr<FJsonObject> JsonObject;

	if (!FJsonSerializer::Deserialize(Reader, JsonObject) || !JsonObject.IsValid())
	{
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse JSON string for game variables"));
		return false;
	}

	return ConvertJsonToGameVariables(OutVariables, JsonObject);
}

#pragma endregion