#pragma once

#include "CoreMinimal.h"
#include "API/APIRequestHandler.h"
#include "Library/GameFuseStructLibrary.h"
#include "Library/GameFuseEnumLibrary.h"
#include "ChatAPIHandler.generated.h"

/**
 * API Handler for GameFuse Chat functionality
 */
UCLASS()
class GAMEFUSE_API UChatAPIHandler : public UAPIRequestHandler
{
	GENERATED_BODY()

public:

	// Create a direct chat with another user
	FGuid CreateChat(const TArray<FString>& Usernames, const FGFMessage& InitialMessage, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Send a message in a chat
	FGuid SendMessage(int32 ChatId, const FGFMessage& Message, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Mark a message as read
	FGuid MarkMessageAsRead(int32 MessageId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Fetch a specific chat
	FGuid FetchChat(int32 ChatId, const FGFUserData& UserData, const FGFApiCallback& Callback);

	// Fetch all chats for the current user
	FGuid FetchAllChats(const FGFUserData& UserData, const int32 Page, const FGFApiCallback& Callback);
};