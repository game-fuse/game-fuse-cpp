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
	void Initialize(FSubsystemCollectionBase& Collection) override;
	void Deinitialize() override;

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

private:

	UPROPERTY()
	URoundsAPIHandler* RequestHandler;

	static void WrapBlueprintCallback(const FBP_GFApiCallback& Callback, FGFApiCallback& InternalCallback);
};