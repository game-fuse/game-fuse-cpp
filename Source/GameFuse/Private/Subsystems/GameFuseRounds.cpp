#include "Subsystems/GameFuseRounds.h"
#include "Library/GameFuseLog.h"
#include "Library/GameFuseUtilities.h"
#include "Subsystems/GameFuseManager.h"
#include "Subsystems/GameFuseUser.h"

void UGameFuseRounds::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RequestHandler = NewObject<URoundsAPIHandler>();
	UE_LOG(LogGameFuse, Log, TEXT("Game Fuse Rounds Subsystem Initialized"));
}

void UGameFuseRounds::Deinitialize()
{
	Super::Deinitialize();
}

void UGameFuseRounds::StoreBlueprintCallback(const FGuid& RequestId, const FBP_GFApiCallback& Callback)
{
	if (Callback.IsBound()) {
		BlueprintCallbacks.Add(RequestId, Callback);
	}
}

void UGameFuseRounds::ExecuteBlueprintCallback(const FGFAPIResponse& Response)
{
	if (BlueprintCallbacks.Contains(Response.RequestId)) {
		BlueprintCallbacks[Response.RequestId].ExecuteIfBound(Response);
		BlueprintCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseRounds::BP_CreateGameRound(const FGFGameRound& GameRound, const FBP_GFApiCallback& Callback)
{
	FGFGameRoundCallback TypedCallback;
	FGuid RequestId = CreateGameRound(GameRound, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

FGuid UGameFuseRounds::CreateGameRound(const FGFGameRound& GameRound, FGFGameRoundCallback TypedCallback)
{
	if (const UGameFuseUser* User = GetGameInstance()->GetSubsystem<UGameFuseUser>()) {
		return CreateGameRound(GameRound, User->GetUserData(), TypedCallback);
	}
	return FGuid();
}

FGuid UGameFuseRounds::CreateGameRound(const FGFGameRound& GameRound, const FGFUserData& UserData, FGFGameRoundCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleGameRoundResponse(Response);
	});

	FGuid RequestId = RequestHandler->CreateGameRound(UserData, GameRound, InternalCallback);
	if (TypedCallback.IsBound()) {
		GameRoundCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

void UGameFuseRounds::BP_FetchGameRound(const int32 RoundId, const FBP_GFApiCallback& Callback)
{
	FGFGameRoundCallback TypedCallback;
	FGuid RequestId = FetchGameRound(RoundId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

FGuid UGameFuseRounds::FetchGameRound(const int32 RoundId, FGFGameRoundCallback TypedCallback)
{
	if (const UGameFuseUser* User = GetGameInstance()->GetSubsystem<UGameFuseUser>()) {
		FGFApiCallback InternalCallback;
		InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
			HandleGameRoundResponse(Response);
		});

		FGuid RequestId = RequestHandler->FetchGameRound(RoundId, User->GetUserData(), InternalCallback);
		if (TypedCallback.IsBound()) {
			GameRoundCallbacks.Add(RequestId, TypedCallback);
		}
		return RequestId;
	}
	return FGuid();
}

void UGameFuseRounds::BP_UpdateGameRound(const int32 RoundId, const FGFGameRound& GameRound, const FBP_GFApiCallback& Callback)
{
	FGFGameRoundCallback TypedCallback;
	FGuid RequestId = UpdateGameRound(RoundId, GameRound, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

FGuid UGameFuseRounds::UpdateGameRound(const int32 RoundId, const FGFGameRound& GameRound, FGFGameRoundCallback TypedCallback)
{
	if (const UGameFuseUser* User = GetGameInstance()->GetSubsystem<UGameFuseUser>()) {
		FGFApiCallback InternalCallback;
		InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
			HandleGameRoundResponse(Response);
		});

		FGuid RequestId = RequestHandler->UpdateGameRound(RoundId, User->GetUserData(), GameRound, InternalCallback);
		if (TypedCallback.IsBound()) {
			GameRoundCallbacks.Add(RequestId, TypedCallback);
		}
		return RequestId;
	}
	return FGuid();
}

void UGameFuseRounds::BP_FetchUserGameRounds(const FBP_GFApiCallback& Callback)
{
	FGFGameRoundListCallback TypedCallback;
	FGuid RequestId = FetchUserGameRounds(TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

FGuid UGameFuseRounds::FetchUserGameRounds(FGFGameRoundListCallback TypedCallback)
{
	if (const UGameFuseUser* User = GetGameInstance()->GetSubsystem<UGameFuseUser>()) {
		FGFApiCallback InternalCallback;
		InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
			HandleGameRoundListResponse(Response);
		});

		FGuid RequestId = RequestHandler->FetchUserGameRounds(User->GetUserData(), InternalCallback);
		if (TypedCallback.IsBound()) {
			GameRoundListCallbacks.Add(RequestId, TypedCallback);
		}
		return RequestId;
	}
	return FGuid();
}

void UGameFuseRounds::BP_DeleteGameRound(const int32 RoundId, const FBP_GFApiCallback& Callback)
{
	FGFGameRoundActionCallback TypedCallback;
	FGuid RequestId = DeleteGameRound(RoundId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

FGuid UGameFuseRounds::DeleteGameRound(const int32 RoundId, FGFGameRoundActionCallback TypedCallback)
{
	if (const UGameFuseUser* User = GetGameInstance()->GetSubsystem<UGameFuseUser>()) {
		FGFApiCallback InternalCallback;
		InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
			HandleDeleteResponse(Response);
		});

		FGuid RequestId = RequestHandler->DeleteGameRound(RoundId, User->GetUserData(), InternalCallback);
		if (TypedCallback.IsBound()) {
			GameRoundActionCallbacks.Add(RequestId, TypedCallback);
		}

		// optimistically remove gameround from cache
		UserGameRounds.RemoveAll([RoundId](const FGFGameRound& Round) {
			return Round.Id == RoundId;
		});

		return RequestId;
	}
	return FGuid();
}

void UGameFuseRounds::HandleGameRoundResponse(FGFAPIResponse Response)
{
	// Execute the blueprint callback regardless of success
	ExecuteBlueprintCallback(Response);

	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle game round response: %s"), *Response.ResponseStr);
		if (GameRoundCallbacks.Contains(Response.RequestId)) {
			GameRoundCallbacks[Response.RequestId].ExecuteIfBound(FGFGameRound());
			GameRoundCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	FGFGameRound GameRound;
	if (!GameFuseUtilities::ConvertJsonToGameRound(GameRound, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse game round from response"));
		if (GameRoundCallbacks.Contains(Response.RequestId)) {
			GameRoundCallbacks[Response.RequestId].ExecuteIfBound(FGFGameRound());
			GameRoundCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	// Update the cached rounds data
	bool bFoundExisting = false;
	for (int32 i = 0; i < UserGameRounds.Num(); ++i) {
		if (UserGameRounds[i].Id == GameRound.Id) {
			UserGameRounds[i] = GameRound;
			bFoundExisting = true;
			break;
		}
	}

	// If this is a new round, add it to the cache
	if (!bFoundExisting) {
		UserGameRounds.Add(GameRound);
	}

	if (GameRoundCallbacks.Contains(Response.RequestId)) {
		GameRoundCallbacks[Response.RequestId].ExecuteIfBound(GameRound);
		GameRoundCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseRounds::HandleGameRoundListResponse(FGFAPIResponse Response)
{
	// Execute the blueprint callback regardless of success
	ExecuteBlueprintCallback(Response);

	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle game round list response: %s"), *Response.ResponseStr);
		if (GameRoundListCallbacks.Contains(Response.RequestId)) {
			GameRoundListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFGameRound>());
			GameRoundListCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	UserGameRounds.Empty();

	if (!GameFuseUtilities::ConvertJsonToGameRounds(UserGameRounds, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse game rounds from response"));
		if (GameRoundListCallbacks.Contains(Response.RequestId)) {
			GameRoundListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFGameRound>());
			GameRoundListCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (GameRoundListCallbacks.Contains(Response.RequestId)) {
		GameRoundListCallbacks[Response.RequestId].ExecuteIfBound(UserGameRounds);
		GameRoundListCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseRounds::HandleDeleteResponse(FGFAPIResponse Response)
{
	// Execute the blueprint callback regardless of success
	ExecuteBlueprintCallback(Response);

	if (GameRoundActionCallbacks.Contains(Response.RequestId)) {
		GameRoundActionCallbacks[Response.RequestId].ExecuteIfBound(Response.bSuccess);
		GameRoundActionCallbacks.Remove(Response.RequestId);
	}
}