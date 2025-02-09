/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "Subsystems/GameFuseUser.h"
#include "Kismet/GameplayStatics.h"
#include "Library/GameFuseLog.h"
#include "Library/GameFuseUtilities.h"
#include "Objects/GameFuseSignData.h"
#include "Subsystems/GameFuseManager.h"

#pragma region Subsystem Initialization

void UGameFuseUser::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	RequestHandler = NewObject<UUserAPIHandler>();
	if (const UGameFuseSaveData* LoadedSaveGame = Cast<UGameFuseSaveData>(UGameplayStatics::LoadGameFromSlot("GameFuseSaveSlot", 0))) {
		UserData = LoadedSaveGame->UserData;
		UE_LOG(LogGameFuse, Log, TEXT("Game Fuse Subsystem Loaded"));
	}

	GameFuseManager = GetGameInstance()->GetSubsystem<UGameFuseManager>();
}

void UGameFuseUser::Deinitialize()
{
	Super::Deinitialize();
}

#pragma endregion

#pragma region Core User Data & Authentication

const FGFUserData& UGameFuseUser::GetUserData() const
{
	return UserData;
}

bool UGameFuseUser::IsSignedIn() const
{
	return UserData.bSignedIn;
}

int32 UGameFuseUser::GetNumberOfLogins() const
{
	return UserData.NumberOfLogins;
}

FString UGameFuseUser::GetLastLogin() const
{
	return UserData.LastLogin;
}

FString UGameFuseUser::GetUsername() const
{
	return UserData.Username;
}

FString UGameFuseUser::GetAuthenticationToken() const
{
	return UserData.AuthenticationToken;
}

FGuid UGameFuseUser::SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FGFUserDataCallback TypedCallback)
{
	const FGFGameData& GameData = GameFuseManager->GetGameData();
	return SignUp(GameData, Email, Password, PasswordConfirmation, Username, TypedCallback);
}

FGuid UGameFuseUser::SignUp(const FGFGameData& GameData, const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FGFUserDataCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleUserDataResponse(Response);
		HandleUserLogin(Response);
	});

	FGuid RequestId = RequestHandler->SignUp(Email, Password, PasswordConfirmation, Username, GameData.Id, GameData.Token, InternalCallback);
	if (TypedCallback.IsBound()) {
		LoginCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseUser::SignIn(const FString& Email, const FString& Password, FGFUserDataCallback TypedCallback)
{
	const FGFGameData& GameData = GameFuseManager->GetGameData();
	return SignIn(GameData, Email, Password, TypedCallback);
}

FGuid UGameFuseUser::SignIn(const FGFGameData& GameData, const FString& Email, const FString& Password, FGFUserDataCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleUserDataResponse(Response);
		HandleUserLogin(Response);
	});

	FGuid RequestId = RequestHandler->SignIn(Email, Password, GameData.Id, GameData.Token, InternalCallback);
	if (TypedCallback.IsBound()) {
		LoginCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

void UGameFuseUser::LogOut(const FString& SaveSlotName)
{
	UE_LOG(LogGameFuse, Log, TEXT("User %i Logging Out"), UserData.Id);
	UserData = FGFUserData();

	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0)) {
		UGameplayStatics::DeleteGameInSlot(SaveSlotName, 0);
		UE_LOG(LogGameFuse, Log, TEXT("User Logged Out Successfully"));
	} else {
		UE_LOG(LogGameFuse, Log, TEXT("Save slot %s does not exist"), *SaveSlotName);
	}
}

#pragma endregion

#pragma region Store & Credits

int32 UGameFuseUser::GetCredits() const
{
	return UserData.Credits;
}

const TArray<FGFStoreItem>& UGameFuseUser::GetPurchasedStoreItems() const
{
	return PurchasedStoreItems;
}

FGuid UGameFuseUser::AddCredits(const int32 AddCredits, FGFUserDataCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleUserDataResponse(Response);
	});

	FGuid RequestId = RequestHandler->AddCredits(AddCredits, UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		UserDataCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseUser::SetCredits(const int32 SetCredits, FGFUserDataCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleUserDataResponse(Response);
	});

	FGuid RequestId = RequestHandler->SetCredits(SetCredits, UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		UserDataCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseUser::PurchaseStoreItem(const int32 StoreItemId, FGFStoreItemsCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleStoreItemsResponse(Response);
	});

	FGuid RequestId = RequestHandler->PurchaseStoreItem(StoreItemId, UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		StoreItemsCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseUser::RemoveStoreItem(const int32 StoreItemId, FGFStoreItemsCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleUserActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->RemoveStoreItem(StoreItemId, UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		StoreItemsCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseUser::FetchPurchasedStoreItems(FGFStoreItemsCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleStoreItemsResponse(Response);
	});

	FGuid RequestId = RequestHandler->FetchPurchasedStoreItems(UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		StoreItemsCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

#pragma endregion

#pragma region Attributes

const TMap<FString, FString>& UGameFuseUser::GetAttributes() const
{
	return Attributes;
}

TArray<FString> UGameFuseUser::GetAttributesKeys() const
{
	TArray<FString> KeysArray;
	Attributes.GenerateKeyArray(KeysArray);
	return KeysArray;
}

const TMap<FString, FString>& UGameFuseUser::GetDirtyAttributes() const
{
	return LocalAttributes;
}

FString UGameFuseUser::GetAttributeValue(const FString Key) const
{
	return Attributes.FindRef(Key);
}

FGuid UGameFuseUser::SetAttribute(const FString& Key, const FString& Value, FGFAttributesCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleAttributesResponse(Response);
	});

	FGuid RequestId = RequestHandler->SetAttribute(Key, Value, UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		AttributesCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}


FGuid UGameFuseUser::SetAttributes(const TMap<FString, FString>& NewAttributes, FGFAttributesCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleAttributesResponse(Response);
	});

	FGuid RequestId = RequestHandler->SetAttributes(NewAttributes, UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		AttributesCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

void UGameFuseUser::SetAttributeLocal(const FString& SetKey, const FString& SetValue)
{
	LocalAttributes.Add(SetKey, SetValue);
	FString Set_Dirty_Attribute_Message = FString::Printf(TEXT("Setting Dirty Attribute (local-and-temporary) : %s : %s"), *SetKey, *SetValue);
	UE_LOG(LogGameFuse, Log, TEXT("%s"), *Set_Dirty_Attribute_Message);
}

FGuid UGameFuseUser::RemoveAttribute(const FString& SetKey, FGFAttributesCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleAttributesResponse(Response);
	});

	FGuid RequestId = RequestHandler->RemoveAttribute(SetKey, UserData, InternalCallback);
	return RequestId;
}

FGuid UGameFuseUser::FetchAttributes(FGFAttributesCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleAttributesResponse(Response);
	});

	FGuid RequestId = RequestHandler->FetchAttributes(UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		AttributesCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseUser::SyncLocalAttributes(FGFAttributesCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleAttributesResponse(Response);
	});

	FGuid RequestId = RequestHandler->FetchAttributes(UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		AttributesCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

#pragma endregion

#pragma region Leaderboard & Score

int32 UGameFuseUser::GetScore() const
{
	return UserData.Score;
}

const TArray<FGFLeaderboardEntry>& UGameFuseUser::GetLeaderboardEntries() const
{
	return LeaderboardEntries;
}

FGuid UGameFuseUser::AddScore(const int32 AddScore, FGFUserDataCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleUserDataResponse(Response);
	});

	FGuid RequestId = RequestHandler->AddScore(AddScore, UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		UserDataCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseUser::SetScore(const int32 SetScore, FGFUserDataCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleUserDataResponse(Response);
	});

	FGuid RequestId = RequestHandler->SetScore(SetScore, UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		UserDataCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseUser::AddLeaderboardEntry(const FString& LeaderboardName, const int32 Score, const TMap<FString, FString>& Metadata, FGFInternalSuccessCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleUserActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->AddLeaderboardEntry(LeaderboardName, Score, Metadata, UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		SimpleSuccessCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseUser::AddLeaderboardEntry(const FString& LeaderboardName, const int32 Score, FGFInternalSuccessCallback TypedCallback)
{
	return AddLeaderboardEntry(LeaderboardName, Score, TMap<FString, FString>(), TypedCallback);
}

FGuid UGameFuseUser::ClearLeaderboardEntry(const FString& LeaderboardName, FGFInternalSuccessCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleUserActionResponse(Response);
	});

	FGuid RequestId = RequestHandler->ClearLeaderboardEntry(LeaderboardName, UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		SimpleSuccessCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

FGuid UGameFuseUser::FetchMyLeaderboardEntries(const int32 Limit, bool bOnePerUser, FGFLeaderboardEntriesCallback TypedCallback)
{
	FGFApiCallback InternalCallback;
	InternalCallback.AddLambda([this](const FGFAPIResponse& Response) {
		HandleLeaderboardEntriesResponse(Response);
	});

	FGuid RequestId = RequestHandler->FetchMyLeaderboardEntries(Limit, bOnePerUser, UserData, InternalCallback);
	if (TypedCallback.IsBound()) {
		LeaderboardEntriesCallbacks.Add(RequestId, TypedCallback);
	}
	return RequestId;
}

#pragma endregion

#pragma region Blueprint Wrapper Functions

void UGameFuseUser::BP_SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FGFSuccessCallback Callback)
{
	FGFUserDataCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const FGFUserData& Data) {
		Callback.ExecuteIfBound(bSuccess);
	});
	SignUp(Email, Password, PasswordConfirmation, Username, TypedCallback);
}

void UGameFuseUser::BP_SignIn(const FString& Email, const FString& Password, FGFSuccessCallback Callback)
{
	FGFUserDataCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const FGFUserData& Data) {
		Callback.ExecuteIfBound(bSuccess);
	});
	SignIn(Email, Password, TypedCallback);
}

void UGameFuseUser::BP_AddCredits(const int32 Credits, FGFSuccessCallback Callback)
{
	FGFUserDataCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const FGFUserData& Data) {
		Callback.ExecuteIfBound(bSuccess);
	});
	AddCredits(Credits, TypedCallback);
}

void UGameFuseUser::BP_SetCredits(const int32 Credits, FGFSuccessCallback Callback)
{
	FGFUserDataCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const FGFUserData&) {
		Callback.ExecuteIfBound(bSuccess);
	});
	SetCredits(Credits, TypedCallback);
}

void UGameFuseUser::BP_AddScore(const int32 Score, FGFSuccessCallback Callback)
{
	FGFUserDataCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const FGFUserData& Data) {
		Callback.ExecuteIfBound(bSuccess);
	});
	AddScore(Score, TypedCallback);
}

void UGameFuseUser::BP_SetScore(const int32 Score, FGFSuccessCallback Callback)
{
	FGFUserDataCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const FGFUserData&) {
		Callback.ExecuteIfBound(bSuccess);
	});
	SetScore(Score, TypedCallback);
}

void UGameFuseUser::BP_SetAttribute(const FString& Key, const FString& Value, FGFSuccessCallback Callback)
{
	FGFAttributesCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const FGFAttributeList& AttributeList) {
		Callback.ExecuteIfBound(bSuccess);
	});
	SetAttribute(Key, Value, TypedCallback);
}

void UGameFuseUser::BP_SetAttributeLocal(const FString& Key, const FString& Value)
{
	// Store attribute locally
	LocalAttributes.Add(Key, Value);
}

void UGameFuseUser::BP_RemoveAttribute(const FString& Key, FGFSuccessCallback Callback)
{
	FGFAttributesCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const FGFAttributeList& AttributeList) {
		Callback.ExecuteIfBound(bSuccess);
	});
	RemoveAttribute(Key, TypedCallback);
}

void UGameFuseUser::BP_FetchPurchasedStoreItems(FGFSuccessCallback Callback)
{
	FGFStoreItemsCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const TArray<FGFStoreItem>& Items) {
		Callback.ExecuteIfBound(bSuccess);
	});
	FetchPurchasedStoreItems(TypedCallback);
}

void UGameFuseUser::BP_RemoveStoreItem(const int32 StoreItemId, FGFSuccessCallback Callback)
{
	FGFStoreItemsCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const TArray<FGFStoreItem>&) {
		Callback.ExecuteIfBound(bSuccess);
	});
	RemoveStoreItem(StoreItemId, TypedCallback);
}

void UGameFuseUser::BP_PurchaseStoreItem(const int32 StoreItemId, FGFSuccessCallback Callback)
{
	FGFStoreItemsCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess) {
		Callback.ExecuteIfBound(bSuccess);
	});
	PurchaseStoreItem(StoreItemId, TypedCallback);
}

void UGameFuseUser::BP_AddLeaderboardEntry(const FString& LeaderboardName, const int32 Score, const TMap<FString, FString>& Metadata, FGFSuccessCallback Callback)
{
	FGFInternalSuccessCallback TypedCallback;
	TypedCallback.AddLambda([Callback](bool bSuccess) {
		Callback.ExecuteIfBound(bSuccess);
	});
	AddLeaderboardEntry(LeaderboardName, Score, Metadata, TypedCallback);
}

void UGameFuseUser::BP_ClearLeaderboardEntry(const FString& LeaderboardName, FGFSuccessCallback Callback)
{
	FGFInternalSuccessCallback TypedCallback;
	TypedCallback.AddLambda([Callback](bool bSuccess) {
		Callback.ExecuteIfBound(bSuccess);
	});
	ClearLeaderboardEntry(LeaderboardName, TypedCallback);
}

void UGameFuseUser::BP_FetchAttributes(FGFSuccessCallback Callback)
{
	FGFAttributesCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const FGFAttributeList&) {
		Callback.ExecuteIfBound(bSuccess);
	});
	FetchAttributes(TypedCallback);
}

void UGameFuseUser::BP_FetchMyLeaderboardEntries(const int32 Limit, bool bOnePerUser, FGFSuccessCallback Callback)
{
	FGFLeaderboardEntriesCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const TArray<FGFLeaderboardEntry>& Entries) {
		Callback.ExecuteIfBound(bSuccess);
	});
	FetchMyLeaderboardEntries(Limit, bOnePerUser, TypedCallback);
}

void UGameFuseUser::BP_SyncLocalAttributes(FGFSuccessCallback Callback)
{
	FGFAttributesCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const FGFAttributeList& AttributeList) {
		Callback.ExecuteIfBound(bSuccess);
	});
	SyncLocalAttributes(TypedCallback);
}

void UGameFuseUser::BP_GetAttributes(FGFSuccessCallback Callback)
{
	FGFAttributesCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const FGFAttributeList&) {
		Callback.ExecuteIfBound(bSuccess);
	});
	FetchAttributes(TypedCallback);
}

void UGameFuseUser::BP_SetAttributes(const TMap<FString, FString>& NewAttributes, FGFSuccessCallback Callback)
{
	FGFAttributesCallback TypedCallback;
	TypedCallback.BindLambda([Callback](bool bSuccess, const FGFAttributeList&) {
		Callback.ExecuteIfBound(bSuccess);
	});
	SetAttributes(NewAttributes, TypedCallback);
}

#pragma endregion

#pragma region Response Handlers

bool UGameFuseUser::HandleUserDataResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("User data response failed: %s"), *Response.ResponseStr);
		if (UserDataCallbacks.Contains(Response.RequestId)) {
			UserDataCallbacks[Response.RequestId].Execute(false, FGFUserData());
			UserDataCallbacks.Remove(Response.RequestId);
		}
		return false;
	}

	// Parse and update user data
	FGFUserData NewUserData;
	if (!GameFuseUtilities::ConvertJsonToUserData(NewUserData, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse user data"));
		if (UserDataCallbacks.Contains(Response.RequestId)) {
			UserDataCallbacks[Response.RequestId].Execute(false, FGFUserData());
			UserDataCallbacks.Remove(Response.RequestId);
		}
		return false;
	}

	// Update the stored user data
	UserData = NewUserData;

	// Execute the specific callback for this request if it exists
	if (UserDataCallbacks.Contains(Response.RequestId)) {
		UserDataCallbacks[Response.RequestId].Execute(true, UserData);
		UserDataCallbacks.Remove(Response.RequestId);
	}

	return true;
}

void UGameFuseUser::HandleStoreItemsResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Store items response failed: %s"), *Response.ResponseStr);
		if (StoreItemsCallbacks.Contains(Response.RequestId)) {
			StoreItemsCallbacks[Response.RequestId].Execute(false, TArray<FGFStoreItem>());
			StoreItemsCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	// Parse store items
	TArray<FGFStoreItem> NewStoreItems;
	if (!GameFuseUtilities::ConvertJsonToStoreItems(NewStoreItems, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse store items"));
		if (StoreItemsCallbacks.Contains(Response.RequestId)) {
			StoreItemsCallbacks[Response.RequestId].Execute(false, TArray<FGFStoreItem>());
			StoreItemsCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	// Update stored items and execute callback
	PurchasedStoreItems = NewStoreItems;
	if (StoreItemsCallbacks.Contains(Response.RequestId)) {
		StoreItemsCallbacks[Response.RequestId].Execute(true, NewStoreItems);
		StoreItemsCallbacks.Remove(Response.RequestId);
	}

	UE_LOG(LogGameFuse, Log, TEXT("Successfully retrieved %d store items"), NewStoreItems.Num());
}

void UGameFuseUser::HandleLeaderboardEntriesResponse(FGFAPIResponse Response)
{
	// existing list is not cleared even if the response is not successful
	LeaderboardEntries.Empty();
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Leaderboard entries response failed: %s"), *Response.ResponseStr);
		if (LeaderboardEntriesCallbacks.Contains(Response.RequestId)) {
			LeaderboardEntriesCallbacks[Response.RequestId].Execute(false, TArray<FGFLeaderboardEntry>());
			LeaderboardEntriesCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	if (GameFuseUtilities::ConvertJsonToLeaderboardEntries(LeaderboardEntries, Response.ResponseStr)) {
	}

	// Update stored entries and execute callback
	if (LeaderboardEntriesCallbacks.Contains(Response.RequestId)) {
		LeaderboardEntriesCallbacks[Response.RequestId].Execute(true, LeaderboardEntries);
		LeaderboardEntriesCallbacks.Remove(Response.RequestId);
	}

	UE_LOG(LogGameFuse, Log, TEXT("Successfully retrieved %d leaderboard entries"), LeaderboardEntries.Num());
}

void UGameFuseUser::HandleAttributesResponse(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("Attributes response failed: %s"), *Response.ResponseStr);
		if (AttributesCallbacks.Contains(Response.RequestId)) {
			AttributesCallbacks[Response.RequestId].Execute(false, FGFAttributeList());
			AttributesCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	// Parse attributes
	FGFAttributeList NewAttributes;
	if (!GameFuseUtilities::ConvertJsonToAttributes(NewAttributes, Response.ResponseStr)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed to parse attributes"));
		if (AttributesCallbacks.Contains(Response.RequestId)) {
			AttributesCallbacks[Response.RequestId].Execute(false, FGFAttributeList());
			AttributesCallbacks.Remove(Response.RequestId);
		}
		return;
	}

	// Update stored attributes and execute callback
	Attributes = NewAttributes.Attributes;
	if (AttributesCallbacks.Contains(Response.RequestId)) {
		AttributesCallbacks[Response.RequestId].Execute(true, NewAttributes);
		AttributesCallbacks.Remove(Response.RequestId);
	}

	UE_LOG(LogGameFuse, Log, TEXT("Successfully retrieved user attributes"));
}

void UGameFuseUser::HandleUserActionResponse(FGFAPIResponse Response)
{
	// Execute any registered callbacks
	if (SimpleSuccessCallbacks.Contains(Response.RequestId)) {
		SimpleSuccessCallbacks[Response.RequestId].Broadcast(Response.bSuccess);
		SimpleSuccessCallbacks.Remove(Response.RequestId);
	}
}

void UGameFuseUser::HandleUserLogin(FGFAPIResponse Response)
{
	if (!Response.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("User failed to login"));
		return;
	}
	UserData.bSignedIn = true;

	UGameFuseSaveData* SaveGameInstance = Cast<UGameFuseSaveData>(UGameplayStatics::CreateSaveGameObject(UGameFuseSaveData::StaticClass()));
	SaveGameInstance->UserData = UserData;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, "GameFuseSaveSlot", 0);
	UE_LOG(LogGameFuse, Log, TEXT("Saved Login Data Into SlotName:GameFuseSaveSlot UserIndex:0"));

	// Execute login callback with success
	if (LoginCallbacks.Contains(Response.RequestId)) {
		LoginCallbacks[Response.RequestId].Execute(true, UserData);
		LoginCallbacks.Remove(Response.RequestId);
	}

	// Log successful login
	UE_LOG(LogGameFuse, Log, TEXT("User successfully logged in: %s"), *UserData.Username);
}


#pragma endregion
