#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Library/GameFuseStructLibrary.h"
#include "API/ChatAPIHandler.h"

#include "GameFuseChat.generated.h"

// Single-cast delegates for user callbacks
DECLARE_DELEGATE_OneParam(FGFChatCallback, const FGFChat&);
DECLARE_DELEGATE_OneParam(FGFChatListCallback, const TArray<FGFChat>&);
DECLARE_DELEGATE_OneParam(FGFMessageCallback, const FGFMessage&);

// Blueprint callback
DECLARE_DYNAMIC_DELEGATE_OneParam(FBP_GFChatCallback, bool, bSuccess);

UCLASS()
class GAMEFUSE_API UGameFuseChat : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Blueprint Callable Functions
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	void BP_CreateChat(const TArray<FString>& Usernames, const FString& InitialMessage, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	void BP_SendMessage(int32 ChatId, const FString& Message, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	void BP_MarkMessageAsRead(int32 MessageId, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	void BP_FetchChat(int32 ChatId, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat", meta=(AdvancedDisplay="Page"))
	void BP_FetchAllChats(FGFSuccessCallback Callback, int32 Page = 1);

	// C++ callable functions with typed callbacks
	FGuid CreateChat(const TArray<FString>& Usernames, const FString& InitialMessage, FGFChatCallback TypedCallback);
	FGuid SendMessage(int32 ChatId, const FString& Text, FGFMessageCallback TypedCallback);
	FGuid MarkMessageAsRead(int32 MessageId, FGFSuccessCallback SuccessCallback);
	FGuid FetchChat(int32 ChatId, FGFChatCallback TypedCallback);
	FGuid FetchAllChats(FGFChatListCallback TypedCallback, int32 Page = 1);

	// Getters for cached data
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	const TArray<FGFChat>& GetDirectChats() const
	{
		return DirectChats;
	}

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	const TArray<FGFChat>& GetGroupChats() const
	{
		return GroupChats;
	}

	TObjectPtr<UChatAPIHandler> GetRequestHandler() const
	{
		return RequestHandler;
	}

protected:

	UPROPERTY()
	TObjectPtr<UChatAPIHandler> RequestHandler;

	// Cached chat data
	TArray<FGFChat> DirectChats;
	TArray<FGFChat> GroupChats;

	// Internal response handlers
	void HandleChatResponse(FGFAPIResponse Response);
	void HandleMessageResponse(FGFAPIResponse Response);
	void HandleChatListResponse(FGFAPIResponse Response);
	void HandleSuccessResponse(FGFAPIResponse Response);

	// User callbacks storage
	TMap<FGuid, FGFChatCallback> ChatCallbacks;
	TMap<FGuid, FGFMessageCallback> MessageCallbacks;
	TMap<FGuid, FGFChatListCallback> ChatListCallbacks;
	TMap<FGuid, FGFSuccessCallback> SuccessCallbacks;
};