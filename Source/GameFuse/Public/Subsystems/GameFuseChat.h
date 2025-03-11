#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Library/GameFuseStructLibrary.h"
#include "API/ChatAPIHandler.h"

#include "GameFuseChat.generated.h"

// Single-cast delegates for user callbacks
DECLARE_DELEGATE_OneParam(FGFChatCallback, const FGFChat&);
DECLARE_DELEGATE_OneParam(FGFChatListCallback, const TArray<FGFChat>&);
DECLARE_DELEGATE_OneParam(FGFMessageListCallback, const TArray<FGFMessage>&);
DECLARE_DELEGATE_OneParam(FGFMessageCallback, const FGFMessage&);


UCLASS()
class GAMEFUSE_API UGameFuseChat : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:

	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;

	// Blueprint Callable Functions
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	void BP_CreateChat(const TArray<FString>& ParticipantIds, const FString& InitialMessage, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	void BP_SendMessage(int32 ChatId, const FString& Message, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	void BP_MarkMessageAsRead(int32 MessageId, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat", meta = (AdvancedDisplay = "Page"))
	void BP_FetchAllChats(int32 Page, const FBP_GFApiCallback& Callback);

	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat", meta = (AdvancedDisplay = "Page"))
	void BP_FetchMessages(int32 ChatId, int32 Page, const FBP_GFApiCallback& Callback);

	// C++ callable functions with typed callbacks
	FGuid CreateChat(const TArray<FString>& ParticipantIds, const FString& InitialMessage, FGFChatCallback TypedCallback);
	FGuid SendMessage(int32 ChatId, const FString& Message, FGFMessageCallback TypedCallback);
	FGuid MarkMessageAsRead(int32 MessageId, FGFSuccessCallback TypedCallback);
	FGuid FetchAllChats(int32 Page, FGFChatListCallback TypedCallback);
	FGuid FetchMessages(int32 ChatId, int32 Page, FGFMessageListCallback TypedCallback);

	// Getters for cached data
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	const TArray<FGFChat>& GetAllChats() const
	{
		return AllChats;
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

	// Clear cached chat data
	void ClearChatData()
	{
		AllChats.Empty();
		ChatMessages.Empty();
	}

private:

	UPROPERTY()
	TObjectPtr<UChatAPIHandler> RequestHandler;

	// Cached chat data
	TArray<FGFChat> AllChats;
	TArray<FGFMessage> ChatMessages;

	// Internal response handlers
	void HandleChatResponse(FGFAPIResponse Response);
	void HandleChatListResponse(FGFAPIResponse Response);
	void HandleMessageListResponse(FGFAPIResponse Response);
	void HandleMessageResponse(FGFAPIResponse Response);
	void HandleActionResponse(FGFAPIResponse Response);

	// User callbacks storage
	TMap<FGuid, FGFChatCallback> ChatCallbacks;
	TMap<FGuid, FGFChatListCallback> ChatListCallbacks;
	TMap<FGuid, FGFMessageListCallback> MessageListCallbacks;
	TMap<FGuid, FGFMessageCallback> MessageCallbacks;
	TMap<FGuid, FGFSuccessCallback> ActionCallbacks;

	/** Map to store blueprint callbacks by request ID */
	TMap<FGuid, FBP_GFApiCallback> BlueprintCallbacks;

	/**
	 * @brief Stores the blueprint callback in the BlueprintCallbacks map
	 * @param RequestId The request ID to associate with the callback
	 * @param Callback The blueprint callback to store
	 */
	void StoreBlueprintCallback(const FGuid& RequestId, const FBP_GFApiCallback& Callback);

	/**
	 * @brief Executes the blueprint callback associated with the given request ID
	 * @param Response The API response to pass to the callback
	 */
	void ExecuteBlueprintCallback(const FGFAPIResponse& Response);
};