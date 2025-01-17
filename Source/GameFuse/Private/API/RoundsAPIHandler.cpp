#include "API/RoundsAPIHandler.h"
#include "Library/GameFuseLog.h"
#include "Library/GameFuseUtilities.h"



FGuid URoundsAPIHandler::CreateGameRound(const FGFUserData& UserData, const FGFGameRound& GameRound, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	if (GameFuseUtilities::ConvertGameRoundToJson(GameRound, JsonObject)) {
		JsonObject->SetNumberField("game_user_id", UserData.Id);
		UE_LOG(LogGameFuse, Verbose, TEXT("Creating new game round"));
		return SendRequest("/game_rounds", "POST", Callback, JsonObject);
	}
	UE_LOG(LogGameFuse, Error, TEXT("Failed to serialize game round data"));
	return FGuid();
}

FGuid URoundsAPIHandler::GetGameRound(int32 RoundId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/game_rounds/%d"), RoundId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Getting game round with ID: %d"), RoundId);
	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid URoundsAPIHandler::UpdateGameRound(int32 RoundId, const FGFUserData& UserData,
                                         const FGFGameRound& GameRound, const FGFApiCallback& Callback)
{
	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/game_rounds/%d"), RoundId);

	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	if (GameFuseUtilities::ConvertGameRoundToJson(GameRound, JsonObject)) {
		JsonObject->SetNumberField("game_user_id", UserData.Id);
		UE_LOG(LogGameFuse, Verbose, TEXT("Updating game round with ID: %d"), RoundId);
		return SendRequest(ApiEndpoint, "PUT", Callback, JsonObject);
	}

	UE_LOG(LogGameFuse, Error, TEXT("Failed to serialize game round data"));
	return FGuid();
}

FGuid URoundsAPIHandler::GetUserGameRounds(const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	SetAuthHeader(UserData.AuthenticationToken);
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	const FString ApiEndpoint = FString::Printf(TEXT("/game_rounds?user_id=%d"), UserData.Id);

	UE_LOG(LogGameFuse, Verbose, TEXT("Getting game rounds for user ID: %d"), UserData.Id);
	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid URoundsAPIHandler::DeleteGameRound(int32 RoundId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/game_rounds/%d"), RoundId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Deleting game round with ID: %d"), RoundId);
	return SendRequest(ApiEndpoint, "DELETE", Callback);
}