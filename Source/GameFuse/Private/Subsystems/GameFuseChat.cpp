#include "Subsystems/GameFuseChat.h"
#include "API/ChatAPIHandler.h"

#include "Subsystems/GameFuseManager.h"
#include "Subsystems/GameFuseUser.h"

#include "Library/GameFuseLog.h"
#include "Library/GameFuseUtilities.h"
#include "JsonObjectConverter.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonReader.h"
#include "Serialization/JsonSerializer.h"

void UGameFuseChat::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	RequestHandler = NewObject<UChatAPIHandler>();
	UE_LOG(LogGameFuse, Log, TEXT("Game Fuse Chat Subsystem Initialized"));
}

void UGameFuseChat::Deinitialize()
{
	Super::Deinitialize();
}

void UGameFuseChat::StoreBlueprintCallback(const FGuid& RequestId, const FBP_GFApiCallback& Callback)
{
	if (Callback.IsBound()) {
		BlueprintCallbacks.Add(RequestId, Callback);
	}
}

void UGameFuseChat::ExecuteBlueprintCallback(const FGFAPIResponse& Response)
{
	if (BlueprintCallbacks.Contains(Response.RequestId)) {
		BlueprintCallbacks[Response.RequestId].ExecuteIfBound(Response);
		BlueprintCallbacks.Remove(Response.RequestId);
	}
}

FGuid UGameFuseChat::MarkMessageAsRead(int32 MessageId, FGFSuccessCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to mark message as read"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->MarkMessageAsRead(MessageId, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		ActionCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseChat::FetchAllChats(int32 Page, FGFChatListCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to fetch chats"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleChatListResponse(Response);
	});

	FGuid RequestId = RequestHandler->FetchAllChats(GameFuseUser->GetUserData(), Page, InternalCallback);
	if (TypedCallback.IsBound()) {
		ChatListCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

void UGameFuseChat::HandleChatResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle chat response: %s"), *Response.ResponseStr);
		if (ChatCallbacks.Contains(Response.RequestId)) {
			ChatCallbacks[Response.RequestId].ExecuteIfBound(FGFChat());
			ChatCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	FGFChat Chat;
	if (!GameFuseUtilities::ConvertJsonToChat(Chat, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse chat data"));
		if (ChatCallbacks.Contains(Response.RequestId)) {
			ChatCallbacks[Response.RequestId].ExecuteIfBound(FGFChat());
			ChatCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (ChatCallbacks.Contains(Response.RequestId)) {
		ChatCallbacks[Response.RequestId].ExecuteIfBound(Chat);
		ChatCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseChat::HandleChatListResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle chat list response: %s"), *Response.ResponseStr);
		if (ChatListCallbacks.Contains(Response.RequestId)) {
			ChatListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFChat>());
			ChatListCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	// If the response is empty or indicates no chats, return empty array
	if (Response.ResponseStr.IsEmpty() || Response.ResponseStr == "[]" || Response.ResponseStr == "null") {
		if (ChatListCallbacks.Contains(Response.RequestId)) {
			ChatListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFChat>());
			ChatListCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	// Parse the chats from the response
	AllChats.Empty();
	if (!GameFuseUtilities::ConvertJsonToChats(AllChats, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse chats from response"));
		if (ChatListCallbacks.Contains(Response.RequestId)) {
			ChatListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFChat>());
			ChatListCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	if (ChatListCallbacks.Contains(Response.RequestId)) {
		ChatListCallbacks[Response.RequestId].ExecuteIfBound(AllChats);
		ChatListCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseChat::HandleActionResponse(FGFAPIResponse Response)
{
	if (ActionCallbacks.Contains(Response.RequestId)) {
		ActionCallbacks[Response.RequestId].ExecuteIfBound(Response.bSuccess);
		ActionCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseChat::HandleMessageResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle message response: %s"), *Response.ResponseStr);
		if (MessageCallbacks.Contains(Response.RequestId)) {
			MessageCallbacks[Response.RequestId].ExecuteIfBound(FGFMessage());
			MessageCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	FGFMessage Message;
	if (!GameFuseUtilities::ConvertJsonToMessage(Message, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse message from response"));
		if (MessageCallbacks.Contains(Response.RequestId)) {
			MessageCallbacks[Response.RequestId].ExecuteIfBound(FGFMessage());
			MessageCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	// Add the message to the cached messages
	ChatMessages.Add(Message);

	if (MessageCallbacks.Contains(Response.RequestId)) {
		MessageCallbacks[Response.RequestId].ExecuteIfBound(Message);
		MessageCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

FGuid UGameFuseChat::CreateChat(const TArray<FString>& Usernames, const FString& InitialMessage, FGFChatCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to create a chat"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleChatResponse(Response);
	});

	// Create a message object from the string
	FGFMessage Message;
	Message.Text = InitialMessage;

	FGuid RequestId = RequestHandler->CreateChat(Usernames, Message, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		ChatCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseChat::SendMessage(int32 ChatId, const FString& Text, FGFMessageCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to send a message"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleMessageResponse(Response);
	});

	// Create a message object from the string
	FGFMessage Message;
	Message.Text = Text;

	FGuid RequestId = RequestHandler->SendMessage(ChatId, Message, GameFuseUser->GetUserData(), InternalCallback);
	if (TypedCallback.IsBound()) {
		MessageCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

void UGameFuseChat::BP_CreateChat(const TArray<FString>& ParticipantIds, const FString& InitialMessage, const FBP_GFApiCallback& Callback)
{
	FGFChatCallback TypedCallback;
	FGuid RequestId = CreateChat(ParticipantIds, InitialMessage, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseChat::BP_SendMessage(int32 ChatId, const FString& Message, const FBP_GFApiCallback& Callback)
{
	FGFMessageCallback TypedCallback;
	FGuid RequestId = SendMessage(ChatId, Message, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseChat::BP_MarkMessageAsRead(int32 MessageId, const FBP_GFApiCallback& Callback)
{
	FGFSuccessCallback TypedCallback;
	FGuid RequestId = MarkMessageAsRead(MessageId, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

void UGameFuseChat::BP_FetchAllChats(int32 Page, const FBP_GFApiCallback& Callback)
{
	FGFChatListCallback TypedCallback;
	FGuid RequestId = FetchAllChats(Page, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}

FGuid UGameFuseChat::FetchMessages(int32 ChatId, int32 Page, FGFMessageListCallback TypedCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to fetch messages"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleMessageListResponse(Response);
	});

	FGuid RequestId = RequestHandler->FetchMessages(ChatId, GameFuseUser->GetUserData(), Page, InternalCallback);
	if (TypedCallback.IsBound()) {
		MessageListCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

void UGameFuseChat::HandleMessageListResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle message list response: %s"), *Response.ResponseStr);
		if (MessageListCallbacks.Contains(Response.RequestId)) {
			MessageListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFMessage>());
			MessageListCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	// If the response is empty or indicates no messages, return empty array
	if (Response.ResponseStr.IsEmpty() || Response.ResponseStr == "[]" || Response.ResponseStr == "null") {
		if (MessageListCallbacks.Contains(Response.RequestId)) {
			MessageListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFMessage>());
			MessageListCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	// Parse the messages from the response
	ChatMessages.Empty();
	if (!GameFuseUtilities::ConvertJsonToMessages(ChatMessages, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse messages from response"));
		if (MessageListCallbacks.Contains(Response.RequestId)) {
			MessageListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFMessage>());
			MessageListCallbacks.Remove(Response.RequestId);
		}
		// Execute the blueprint callback after handling the error
		ExecuteBlueprintCallback(Response);
		return;
	}

	if (MessageListCallbacks.Contains(Response.RequestId)) {
		MessageListCallbacks[Response.RequestId].ExecuteIfBound(ChatMessages);
		MessageListCallbacks.Remove(Response.RequestId);
	}

	// Execute the blueprint callback after all processing is done
	ExecuteBlueprintCallback(Response);
}

void UGameFuseChat::BP_FetchMessages(int32 ChatId, int32 Page, const FBP_GFApiCallback& Callback)
{
	FGFMessageListCallback TypedCallback;
	FGuid RequestId = FetchMessages(ChatId, Page, TypedCallback);
	StoreBlueprintCallback(RequestId, Callback);
}
