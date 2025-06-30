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
	/**
	 * Creates a new chat with participants (Blueprint version)
	 * @param ParticipantIds Array of user IDs to include in the chat
	 * @param InitialMessage The first message to send in the chat
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Create Chat", Category = "GameFuse|Chat")
	void BP_CreateChat(const TArray<FString>& ParticipantIds, const FString& InitialMessage, const FBP_GFApiCallback& Callback);

	/**
	 * Sends a message to a chat (Blueprint version)
	 * @param ChatId The ID of the chat to send the message to
	 * @param Message The message content to send
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Send Message", Category = "GameFuse|Chat")
	void BP_SendMessage(int32 ChatId, const FString& Message, const FBP_GFApiCallback& Callback);

	/**
	 * Marks a message as read (Blueprint version)
	 * @param MessageId The ID of the message to mark as read
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Mark Message As Read", Category = "GameFuse|Chat")
	void BP_MarkMessageAsRead(int32 MessageId, const FBP_GFApiCallback& Callback);

	/**
	 * Fetches all chats for the current user (Blueprint version)
	 * @param Page Page number for pagination
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch All Chats", Category = "GameFuse|Chat", meta = (Page = 1))
	void BP_FetchAllChats(int32 Page, const FBP_GFApiCallback& Callback);

	/**
	 * Fetches messages for a specific chat (Blueprint version)
	 * @param ChatId The ID of the chat to fetch messages from
	 * @param Page Page number for pagination
	 * @param Callback Blueprint callback executed when the request completes
	 */
	UFUNCTION(BlueprintCallable, DisplayName = "Fetch Messages", Category = "GameFuse|Chat", meta = (Page = 1))
	void BP_FetchMessages(int32 ChatId, int32 Page, const FBP_GFApiCallback& Callback);

	// C++ callable functions with typed callbacks
	/**
	 * Creates a new chat with participants
	 * @param ParticipantIds Array of user IDs to include in the chat
	 * @param InitialMessage The first message to send in the chat
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid CreateChat(const TArray<FString>& ParticipantIds, const FString& InitialMessage, FGFChatCallback TypedCallback);
	
	/**
	 * Sends a message to a chat
	 * @param ChatId The ID of the chat to send the message to
	 * @param Message The message content to send
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid SendMessage(int32 ChatId, const FString& Message, FGFMessageCallback TypedCallback);
	
	/**
	 * Marks a message as read
	 * @param MessageId The ID of the message to mark as read
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid MarkMessageAsRead(int32 MessageId, FGFSuccessCallback TypedCallback);
	
	/**
	 * Fetches all chats for the current user
	 * @param Page Page number for pagination
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid FetchAllChats(int32 Page, FGFChatListCallback TypedCallback);
	
	/**
	 * Fetches messages for a specific chat
	 * @param ChatId The ID of the chat to fetch messages from
	 * @param Page Page number for pagination
	 * @param TypedCallback Callback executed when the request completes
	 * @return Request ID for tracking
	 */
	FGuid FetchMessages(int32 ChatId, int32 Page, FGFMessageListCallback TypedCallback);

	// Getters for cached data
	/**
	 * Gets the cached list of all chats
	 * @return The last fetched list of all chats
	 */
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	const TArray<FGFChat>& GetAllChats() const
	{
		return AllChats;
	}

	/**
	 * Gets the cached list of chat messages
	 * @return The last fetched list of chat messages
	 */
	UFUNCTION(BlueprintCallable, Category = "GameFuse|Chat")
	const TArray<FGFMessage>& GetChatMessages() const
	{
		return ChatMessages;
	}

	/**
	 * Gets the request handler for direct API access
	 * @return Pointer to the chat API handler
	 */
	TObjectPtr<UChatAPIHandler> GetRequestHandler() const
	{
		return RequestHandler;
	}

	/**
	 * Clears all cached chat data
	 */
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
	/**
	 * Handles responses for single chat operations
	 * @param Response The API response to process
	 */
	void HandleChatResponse(FGFAPIResponse Response);
	
	/**
	 * Handles responses for chat list operations
	 * @param Response The API response to process
	 */
	void HandleChatListResponse(FGFAPIResponse Response);
	
	/**
	 * Handles responses for message list operations
	 * @param Response The API response to process
	 */
	void HandleMessageListResponse(FGFAPIResponse Response);
	
	/**
	 * Handles responses for single message operations
	 * @param Response The API response to process
	 */
	void HandleMessageResponse(FGFAPIResponse Response);
	
	/**
	 * Handles responses for action operations (like mark as read)
	 * @param Response The API response to process
	 */
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