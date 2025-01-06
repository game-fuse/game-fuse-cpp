#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Library/GameFuseStructLibrary.h"
#include "API/RoundsAPIHandler.h"
#include "GameFuseRounds.generated.h"

UCLASS()
class GAMEFUSE_API UGameFuseRounds : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	//> Subsystem Initialization and Deinitialization
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	//> Blueprint Callable Functions
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_CreateGameRound(const FGFGameRound& GameRound, const bool bMultiplayer, FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_GetGameRound(const int32 RoundId, FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_UpdateGameRound(const int32 RoundId, const FGFGameRound& GameRound, FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_GetUserGameRounds(FBP_GFApiCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Rounds")
	void BP_DeleteGameRound(const int32 RoundId, FBP_GFApiCallback Callback);

	// C++ callable functions
	FGuid CreateGameRound(const FGFGameRound& GameRound, const bool bMultiplayer, FGFApiCallback Callback);
	FGuid GetGameRound(const int32 RoundId, FGFApiCallback Callback);
	FGuid UpdateGameRound(const int32 RoundId, const FGFGameRound& GameRound, FGFApiCallback Callback);
	FGuid GetUserGameRounds(FGFApiCallback Callback);
	FGuid DeleteGameRound(const int32 RoundId, FGFApiCallback Callback);

private:

	UPROPERTY()
	URoundsAPIHandler* RequestHandler;

	static void WrapBlueprintCallback(const FBP_GFApiCallback& Callback, FGFApiCallback& InternalCallback);
};