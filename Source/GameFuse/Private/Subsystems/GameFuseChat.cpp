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
}

void UGameFuseChat::Deinitialize()
{
	Super::Deinitialize();
}


FGuid UGameFuseChat::MarkMessageAsRead(int32 MessageId, FGFSuccessCallback SuccessCallback)
{
	UGameFuseUser* GameFuseUser = GetGameInstance()->GetSubsystem<UGameFuseUser>();
	if (!GameFuseUser || !GameFuseUser->IsSignedIn()) {
		UE_LOG(LogGameFuse, Error, TEXT("User must be signed in to mark a message as read"));
		return FGuid();
	}

	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleSuccessResponse(Response);
	});

	FGuid RequestId = RequestHandler->MarkMessageAsRead(MessageId, GameFuseUser->GetUserData(), InternalCallback);
	if (SuccessCallback.IsBound()) {
		SuccessCallbacks.Add(RequestId, SuccessCallback);
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
		return;
	}

	// Clear existing chats
	DirectChats.Empty();
	GroupChats.Empty();

	// If the response is empty or indicates no chats, return empty arrays
	if (Response.ResponseStr.IsEmpty() || Response.ResponseStr == "[]" || Response.ResponseStr == "null") {
		if (ChatListCallbacks.Contains(Response.RequestId)) {
			ChatListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFChat>());
			ChatListCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	TArray<FGFChat> AllChats;
	if (!GameFuseUtilities::ConvertJsonToChats(AllChats, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse chat list"));
		if (ChatListCallbacks.Contains(Response.RequestId)) {
			ChatListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFChat>());
			ChatListCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	// Separate chats into direct and group chats
	for (const FGFChat& Chat : AllChats) {
		if (Chat.Participants.Num() > 2) {
			GroupChats.Add(Chat);
		} else {
			DirectChats.Add(Chat);
		}
	}

	if (ChatListCallbacks.Contains(Response.RequestId)) {
		ChatListCallbacks[Response.RequestId].ExecuteIfBound(AllChats);
		ChatListCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseChat::HandleSuccessResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle success response: %s"), *Response.ResponseStr);
		if (SuccessCallbacks.Contains(Response.RequestId)) {
			SuccessCallbacks[Response.RequestId].ExecuteIfBound(false);
			SuccessCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (SuccessCallbacks.Contains(Response.RequestId)) {
		SuccessCallbacks[Response.RequestId].ExecuteIfBound(true);
		SuccessCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseChat::HandleMessageResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to handle message response: %s"), *Response.ResponseStr);
		if (MessageCallbacks.Contains(Response.RequestId)) {
			MessageCallbacks[Response.RequestId].ExecuteIfBound(FGFMessage());
			MessageCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	TSharedPtr<FJsonObject> JsonObject;
	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response.ResponseStr);
	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse message response"));
		if (MessageCallbacks.Contains(Response.RequestId)) {
			MessageCallbacks[Response.RequestId].ExecuteIfBound(FGFMessage());
			MessageCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	FGFMessage Message;
	if (!GameFuseUtilities::ConvertJsonToMessage(Message, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse message data"));
		if (MessageCallbacks.Contains(Response.RequestId)) {
			MessageCallbacks[Response.RequestId].ExecuteIfBound(FGFMessage());
			MessageCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (MessageCallbacks.Contains(Response.RequestId)) {
		MessageCallbacks[Response.RequestId].ExecuteIfBound(Message);
		MessageCallbacks.Remove(Response.RequestId);
	}
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

void UGameFuseChat::BP_CreateChat(const TArray<FString>& Usernames, const FString& InitialMessage, FGFSuccessCallback Callback)
{
	FGFChatCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const FGFChat&) {
		Callback.ExecuteIfBound(true);
	});
	CreateChat(Usernames, InitialMessage, TypedCallback);
}

void UGameFuseChat::BP_SendMessage(int32 ChatId, const FString& Message, FGFSuccessCallback Callback)
{
	FGFMessageCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const FGFMessage&) {
		Callback.ExecuteIfBound(true);
	});
	SendMessage(ChatId, Message, TypedCallback);
}

void UGameFuseChat::BP_MarkMessageAsRead(int32 MessageId, FGFSuccessCallback Callback)
{
	FGFSuccessCallback TypedCallback;
	MarkMessageAsRead(MessageId, TypedCallback);
}

void UGameFuseChat::BP_FetchAllChats(FGFSuccessCallback Callback, int32 Page)
{
	FGFChatListCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFChat>&) {
		Callback.ExecuteIfBound(true);
	});
	FetchAllChats(Page);
}

FGuid UGameFuseChat::FetchMessages(int32 ChatId, FGFMessageListCallback TypedCallback, int32 Page)
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
		UE_LOG(LogGameFuse, Error, TEXT("Failed to fetch messages: %s"), *Response.ResponseStr);
		if (MessageListCallbacks.Contains(Response.RequestId)) {
			MessageListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFMessage>());
			MessageListCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	// Clear existing messages
	ChatMessages.Empty();

	// If the response is empty or indicates no messages, return empty array
	if (Response.ResponseStr.IsEmpty() || Response.ResponseStr == "[]" || Response.ResponseStr == "null") {
		if (MessageListCallbacks.Contains(Response.RequestId)) {
			MessageListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFMessage>());
			MessageListCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (!GameFuseUtilities::ConvertJsonToMessages(ChatMessages, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse messages list"));
		if (MessageListCallbacks.Contains(Response.RequestId)) {
			MessageListCallbacks[Response.RequestId].ExecuteIfBound(TArray<FGFMessage>());
			MessageListCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (MessageListCallbacks.Contains(Response.RequestId)) {
		MessageListCallbacks[Response.RequestId].ExecuteIfBound(ChatMessages);
		MessageListCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseChat::BP_FetchMessages(int32 ChatId, FGFSuccessCallback Callback, int32 Page)
{
	FGFMessageListCallback TypedCallback;
	TypedCallback.BindLambda([Callback](const TArray<FGFMessage>&) {
		Callback.ExecuteIfBound(true);
	});
	FetchMessages(ChatId, TypedCallback, Page);
}
