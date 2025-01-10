#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Library/GameFuseStructLibrary.h"
#include "API/RoundsAPIHandler.h"
#include "GameFuseRounds.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameRoundResponseNative, const FGFGameRound&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameRoundListResponseNative, const TArray<FGFGameRound>&);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnGameRoundDeleteResponseNative, bool);

UCLASS()
class GAMEFUSE_API UGameFuseRounds : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	//> Blueprint Callable Functions
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_CreateGameRound(const FGFGameRound& GameRound, FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_GetGameRound(int32 RoundId, FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_UpdateGameRound(int32 RoundId, const FGFGameRound& GameRound, FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_GetUserGameRounds(FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_DeleteGameRound(int32 RoundId, FBP_GFApiCallback Callback);

	// C++ callable functions
	FGuid CreateGameRound(const FGFGameRound& GameRound, FGFApiCallback Callback);
	FGuid GetGameRound(int32 RoundId, FGFApiCallback Callback);
	FGuid UpdateGameRound(int32 RoundId, const FGFGameRound& GameRound, FGFApiCallback Callback);
	FGuid GetUserGameRounds(FGFApiCallback Callback);
	FGuid DeleteGameRound(int32 RoundId, FGFApiCallback Callback);

	// Native delegates for response handling
	FOnGameRoundResponseNative OnGameRoundResponse;
	FOnGameRoundListResponseNative OnGameRoundListResponse;
	FOnGameRoundDeleteResponseNative OnGameRoundDeleteResponse;

	TObjectPtr<UAPIRequestHandler> GetRequestHandler()
	{
		return RequestHandler;
	}

private:

	TObjectPtr<URoundsAPIHandler> RequestHandler;
	static void WrapBlueprintCallback(const FBP_GFApiCallback& Callback, FGFApiCallback& InternalCallback);

	// Internal response handlers that will trigger the delegates
	void HandleGameRoundResponse(FGFAPIResponse Response);
	void HandleGameRoundListResponse(FGFAPIResponse Response);
	void HandleDeleteResponse(FGFAPIResponse Response);
};