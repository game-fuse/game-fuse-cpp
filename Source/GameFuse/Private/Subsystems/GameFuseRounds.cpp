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

void UGameFuseRounds::BP_CreateGameRound(const FGFGameRound& GameRound, const bool bMultiplayer, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	CreateGameRound(GameRound, bMultiplayer, InternalCallback);
}

FGuid UGameFuseRounds::CreateGameRound(const FGFGameRound& GameRound, const bool bMultiplayer, FGFApiCallback Callback)
{
	if (const UGameFuseUser* User = GetGameInstance()->GetSubsystem<UGameFuseUser>()) {

		return RequestHandler->CreateGameRound(User->GetUserData(), GameRound, bMultiplayer, Callback);

	}
	return FGuid();
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
		return RequestHandler->GetUserGameRounds(User->GetUserData(), Callback);
	}
	return FGuid();
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
		return RequestHandler->DeleteGameRound(RoundId, User->GetUserData(), Callback);
	}
	return FGuid();
}