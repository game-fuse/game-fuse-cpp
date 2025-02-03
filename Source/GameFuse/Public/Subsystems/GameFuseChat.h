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
DECLARE_DELEGATE_OneParam(FGFMessageListCallback, const TArray<FGFMessage>&);

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
	void BP_CreateChat(const TArray<FString>& ParticipantIds, const FString& InitialMessage, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	void BP_SendMessage(int32 ChatId, const FString& Message, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	void BP_MarkMessageAsRead(int32 MessageId, FGFSuccessCallback Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat", meta = (AdvancedDisplay = "Page"))
	void BP_FetchAllChats(FGFSuccessCallback Callback, int32 Page = 1);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat", meta = (AdvancedDisplay = "Page"))
	void BP_FetchMessages(int32 ChatId, FGFSuccessCallback Callback, int32 Page = 1);

	// C++ callable functions with typed callbacks
	FGuid CreateChat(const TArray<FString>& ParticipantIds, const FString& InitialMessage, FGFChatCallback TypedCallback);
	FGuid SendMessage(int32 ChatId, const FString& Message, FGFMessageCallback TypedCallback);
	FGuid MarkMessageAsRead(int32 MessageId, FGFSuccessCallback SuccessCallback);
	FGuid FetchAllChats(int32 Page = 1, FGFChatListCallback TypedCallback = {});
	FGuid FetchMessages(int32 ChatId, FGFMessageListCallback TypedCallback, int32 Page = 1);

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

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	const TArray<FGFMessage>& GetChatMessages() const
	{
		return ChatMessages;
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
	TArray<FGFMessage> ChatMessages;

	// Internal response handlers
	void HandleChatResponse(FGFAPIResponse Response);
	void HandleMessageResponse(FGFAPIResponse Response);
	void HandleChatListResponse(FGFAPIResponse Response);
	void HandleMessageListResponse(FGFAPIResponse Response);
	void HandleSuccessResponse(FGFAPIResponse Response);

	// User callbacks storage
	TMap<FGuid, FGFChatCallback> ChatCallbacks;
	TMap<FGuid, FGFMessageCallback> MessageCallbacks;
	TMap<FGuid, FGFChatListCallback> ChatListCallbacks;
	TMap<FGuid, FGFMessageListCallback> MessageListCallbacks;
	TMap<FGuid, FGFSuccessCallback> SuccessCallbacks;
};