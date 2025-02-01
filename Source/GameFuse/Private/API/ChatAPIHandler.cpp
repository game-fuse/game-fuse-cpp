#include "API/ChatAPIHandler.h"
#include "Subsystems/GameFuseManager.h"
#include "Library/GameFuseLog.h"
#include "Library/GameFuseUtilities.h"


FGuid UChatAPIHandler::CreateChat(const TArray<FString>& Usernames, const FGFMessage& InitialMessage, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	TArray<TSharedPtr<FJsonValue>> UsernameArray;
	for (const FString& Username : Usernames) {
		UsernameArray.Add(MakeShared<FJsonValueString>(Username));
	}
	JsonObject->SetArrayField(TEXT("usernames"), UsernameArray);
	JsonObject->SetStringField(TEXT("text"), InitialMessage.Text);

	SetAuthHeader(UserData.AuthenticationToken);
	return SendRequest(TEXT("/chats"), TEXT("POST"), Callback, JsonObject);
}

FGuid UChatAPIHandler::SendMessage(int32 ChatId, const FGFMessage& Message, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}

	TSharedPtr<FJsonObject> JsonObject = MakeShared<FJsonObject>();
	JsonObject->SetStringField(TEXT("text"), Message.Text);

	SetAuthHeader(UserData.AuthenticationToken);
	const FString Endpoint = FString::Printf(TEXT("/chats/%d/messages"), ChatId);
	return SendRequest(Endpoint, TEXT("POST"), Callback, JsonObject);
}

FGuid UChatAPIHandler::MarkMessageAsRead(const int32 MessageId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/messages/%d/mark_as_read"), MessageId);
	UE_LOG(LogGameFuse, Verbose, TEXT("Marking message %d as read in chat"), MessageId);
	return SendRequest(ApiEndpoint, TEXT("POST"), Callback);
}

FGuid UChatAPIHandler::FetchChat(const int32 ChatId, const FGFUserData& UserData, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/chats/%d"), ChatId);
	UE_LOG(LogGameFuse, Verbose, TEXT("Fetching chat with ID: %d"), ChatId);
	return SendRequest(ApiEndpoint, TEXT("GET"), Callback);
}

FGuid UChatAPIHandler::FetchAllChats(const FGFUserData& UserData, const int32 Page, const FGFApiCallback& Callback)
{
	if (!VerifyUserData(UserData)) {
		return FGuid();
	}
	SetAuthHeader(UserData.AuthenticationToken);

	const FString ApiEndpoint = FString::Printf(TEXT("/chats/page/%d"), Page);
	UE_LOG(LogGameFuse, Verbose, TEXT("Fetching all chats for user (page %d)"), Page);
	return SendRequest(ApiEndpoint, TEXT("GET"), Callback);
}
