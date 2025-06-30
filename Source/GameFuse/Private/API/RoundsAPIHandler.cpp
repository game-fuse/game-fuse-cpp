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
	if (!GameFuseUtilities::ConvertGameRoundToJson(GameRound, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to serialize game round data"));
		return FGuid();
	}
	JsonObject->SetNumberField("game_user_id", UserData.Id);

	UE_LOG(LogGameFuse, Verbose, TEXT("Creating new game round"));
	return SendRequest("/game_rounds", "POST", Callback, JsonObject);
}

FGuid URoundsAPIHandler::FetchGameRound(const int32 RoundId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/game_rounds/%d"), RoundId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Fetching game round with ID: %d"), RoundId);
	return SendRequest(ApiEndpoint, "GET", Callback);
}

FGuid URoundsAPIHandler::UpdateGameRound(const int32 RoundId, const FGFUserData& UserData,
										 const FGFGameRound& GameRound, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);
	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	if (!GameFuseUtilities::ConvertGameRoundToJson(GameRound, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to serialize game round data"));
		return FGuid();
	}
	const FString ApiEndpoint = FString::Printf(TEXT("/game_rounds/%d"), RoundId);
	JsonObject->SetNumberField("game_user_id", UserData.Id);
	UE_LOG(LogGameFuse, Verbose, TEXT("Updating game round with ID: %d"), RoundId);
	return SendRequest(ApiEndpoint, "PUT", Callback, JsonObject);
}

FGuid URoundsAPIHandler::FetchUserGameRounds(const int32 UserId, const FGFUserData& UserData, const FString& GameType,
                                             const int32 Page, const int32 PerPage, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData))
	{
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	TArray<FString> QueryParams;
	QueryParams.Add(FString::Printf(TEXT("user_id=%d"), UserId));

	if (!GameType.IsEmpty())
	{
		QueryParams.Add(FString::Printf(TEXT("game_type=%s"), *GameType));
	}
	if (Page > 0)
	{
		QueryParams.Add(FString::Printf(TEXT("page=%d"), Page));
	}
	if (PerPage > 0)
	{
		QueryParams.Add(FString::Printf(TEXT("per_page=%d"), PerPage));
	}

	FString Endpoint = FString::Printf(TEXT("/game_rounds?%s"), *FString::Join(QueryParams, TEXT("&")));

	UE_LOG(LogGameFuse, Verbose, TEXT("Fetching game rounds with endpoint: %s"), *Endpoint);
	return SendRequest(Endpoint, "GET", Callback);
}

FGuid URoundsAPIHandler::DeleteGameRound(const int32 RoundId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	SetAuthHeader(UserData.AuthenticationToken);
	const FString ApiEndpoint = FString::Printf(TEXT("/game_rounds/%d"), RoundId);

	UE_LOG(LogGameFuse, Verbose, TEXT("Deleting game round with ID: %d"), RoundId);
	return SendRequest(ApiEndpoint, "DELETE", Callback);
}