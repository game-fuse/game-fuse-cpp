#include "Subsystems/GameFuseRounds.h"

#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
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

void UGameFuseRounds::WrapBlueprintCallback(const FBP_GFApiCallback& Callback, FGFApiCallback& InternalCallback)
{
	InternalCallback.AddLambda([Callback](FGFAPIResponse ResponseData) {
		Callback.ExecuteIfBound(ResponseData);
	});
}

void UGameFuseRounds::BP_CreateGameRound(const FGFGameRound& GameRound, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	CreateGameRound(GameRound, InternalCallback);
}

FGuid UGameFuseRounds::CreateGameRound(const FGFGameRound& GameRound, FGFApiCallback Callback)
{
	if (const UGameFuseUser* User = GetGameInstance()->GetSubsystem<UGameFuseUser>()) {
		Callback.AddUObject(this, &UGameFuseRounds::HandleGameRoundResponse);
		return RequestHandler->CreateGameRound(User->GetUserData(), GameRound, Callback);
	}
	return FGuid();
}

void UGameFuseRounds::HandleGameRoundResponse(FGFAPIResponse Response)
{
	FGFGameRound GameRound;
	if (GameFuseUtilities::ConvertJsonToGameRound(GameRound, Response.ResponseStr)) {
		OnGameRoundResponse.Broadcast(GameRound);
	}
}

void UGameFuseRounds::BP_GetGameRound(const int32 RoundId, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	GetGameRound(RoundId, InternalCallback);
}

FGuid UGameFuseRounds::GetGameRound(const int32 RoundId, FGFApiCallback Callback)
{
	if (const UGameFuseUser* User = GetGameInstance()->GetSubsystem<UGameFuseUser>()) {
		Callback.AddUObject(this, &UGameFuseRounds::HandleGameRoundResponse);
		return RequestHandler->GetGameRound(RoundId, User->GetUserData(), Callback);
	}
	return FGuid();
}

void UGameFuseRounds::BP_UpdateGameRound(const int32 RoundId, const FGFGameRound& GameRound, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	UpdateGameRound(RoundId, GameRound, InternalCallback);
}

FGuid UGameFuseRounds::UpdateGameRound(const int32 RoundId, const FGFGameRound& GameRound, FGFApiCallback Callback)
{
	if (const UGameFuseUser* User = GetGameInstance()->GetSubsystem<UGameFuseUser>()) {
		Callback.AddUObject(this, &UGameFuseRounds::HandleGameRoundResponse);
		return RequestHandler->UpdateGameRound(RoundId, User->GetUserData(), GameRound, Callback);
	}
	return FGuid();
}

void UGameFuseRounds::BP_GetUserGameRounds(FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	GetUserGameRounds(InternalCallback);
}

FGuid UGameFuseRounds::GetUserGameRounds(FGFApiCallback Callback)
{
	if (const UGameFuseUser* User = GetGameInstance()->GetSubsystem<UGameFuseUser>()) {
		Callback.AddUObject(this, &UGameFuseRounds::HandleGameRoundListResponse);
		return RequestHandler->GetUserGameRounds(User->GetUserData(), Callback);
	}
	return FGuid();
}

void UGameFuseRounds::HandleGameRoundListResponse(FGFAPIResponse Response)
{
	TArray<FGFGameRound> GameRounds;
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.ResponseStr);

	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid()) {
		const TArray<TSharedPtr<FJsonValue>>* RoundsArray;
		if (JsonObject->TryGetArrayField(TEXT("rounds"), RoundsArray)) {
			for (const auto& RoundValue : *RoundsArray) {
				if (const TSharedPtr<FJsonObject>* RoundObject; RoundValue->TryGetObject(RoundObject)) {
					FString RoundString;
					if (const TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&RoundString);
						FJsonSerializer::Serialize(RoundObject->ToSharedRef(), Writer)) {
						FGFGameRound GameRound;
						if (GameFuseUtilities::ConvertJsonToGameRound(GameRound, RoundString)) {
							GameRounds.Add(GameRound);
						}
					}
				}
			}
		}
	}

	OnGameRoundListResponse.Broadcast(GameRounds);
}

void UGameFuseRounds::BP_DeleteGameRound(const int32 RoundId, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	DeleteGameRound(RoundId, InternalCallback);
}

FGuid UGameFuseRounds::DeleteGameRound(const int32 RoundId, FGFApiCallback Callback)
{
	if (const UGameFuseUser* User = GetGameInstance()->GetSubsystem<UGameFuseUser>()) {
		Callback.AddUObject(this, &UGameFuseRounds::HandleDeleteResponse);
		return RequestHandler->DeleteGameRound(RoundId, User->GetUserData(), Callback);
	}
	return FGuid();
}

void UGameFuseRounds::HandleDeleteResponse(FGFAPIResponse Response)
{
	TSharedPtr<FJsonObject> JsonObject;
	TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.ResponseStr);

	bool bSuccess = false;
	if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid()) {
		JsonObject->TryGetBoolField(TEXT("success"), bSuccess);
	}

	OnGameRoundDeleteResponse.Broadcast(bSuccess);
}