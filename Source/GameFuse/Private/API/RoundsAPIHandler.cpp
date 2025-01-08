#include "API/RoundsAPIHandler.h"
#include "Library/GameFuseLog.h"
#include "Library/GameFuseUtilities.h"
#include "JsonObjectConverter.h"

FGuid URoundsAPIHandler::CreateGameRound(const FGFUserData& UserData, const FGFGameRound& GameRound,
                                         const bool bMultiplayer, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	if (FJsonObjectConverter::UStructToJsonObject(FGFGameRound::StaticStruct(), &GameRound, JsonObject)) {
		JsonObject->SetNumberField("game_user_id", UserData.Id);
		if (bMultiplayer) {
			JsonObject->SetBoolField("multiplayer", true);
		}

		UE_LOG(LogGameFuse, Verbose, TEXT("Creating new game round"));
		return SendRequest("/game_rounds", "POST", Callback, JsonObject);
	}

	UE_LOG(LogGameFuse, Error, TEXT("Failed to serialize game round data"));
	return FGuid();
}

FGuid URoundsAPIHandler::GetGameRound(const int32 RoundId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/game_rounds/%d"), RoundId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Getting game round with ID: %d"), RoundId);
	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid URoundsAPIHandler::UpdateGameRound(const int32 RoundId, const FGFUserData& UserData,
                                         const FGFGameRound& GameRound, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/game_rounds/%d"), RoundId);

	TSharedRef<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	if (FJsonObjectConverter::UStructToJsonObject(FGFGameRound::StaticStruct(), &GameRound, JsonObject)) {
		UE_LOG(LogGameFuse, Verbose, TEXT("Updating game round with ID: %d"), RoundId);
		return SendRequest(ApiEndpoint, "PUT", Callback, JsonObject);
	}

	UE_LOG(LogGameFuse, Error, TEXT("Failed to serialize game round data"));
	return FGuid();
}

FGuid URoundsAPIHandler::GetUserGameRounds(const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	const FString ApiEndpoint = FString::Printf(TEXT("/game_rounds?user_id=%d"), UserData.Id);

	UE_LOG(LogGameFuse, Verbose, TEXT("Getting game rounds for user ID: %d"), UserData.Id);
	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid URoundsAPIHandler::DeleteGameRound(const int32 RoundId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	const FString ApiEndpoint = FString::Printf(TEXT("/game_rounds/%d"), RoundId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Deleting game round with ID: %d"), RoundId);
	return SendRequest(ApiEndpoint, "DELETE", Callback);
}