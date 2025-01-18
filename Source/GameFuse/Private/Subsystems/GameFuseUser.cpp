/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "Subsystems/GameFuseUser.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
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

FGuid UGameFuseUser::SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	const FGFGameData& GameData = GameFuseManager->GetGameData();
	return RequestHandler->SignUp(Email, Password, PasswordConfirmation, Username, GameData.Id, GameData.Token, Callback);
}

FGuid UGameFuseUser::SignUp(const FGFGameData& GameData, const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->SignUp(Email, Password, PasswordConfirmation, Username, GameData.Id, GameData.Token, Callback);
}

FGuid UGameFuseUser::SignIn(const FString& Email, const FString& Password, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	const FGFGameData& GameData = GameFuseManager->GetGameData();
	return RequestHandler->SignIn(Email, Password, GameData.Id, GameData.Token, Callback);
}

FGuid UGameFuseUser::SignIn(const FGFGameData& GameData, const FString& Email, const FString& Password, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->SignIn(Email, Password, GameData.Id, GameData.Token, Callback);
}

void UGameFuseUser::LogOut(const FString& SaveSlotName)
{
	UE_LOG(LogGameFuse, Log, TEXT("User %i Logging Out"), UserData.Id);
	UserData = FGFUserData();

	if (UGameplayStatics::DoesSaveGameExist(SaveSlotName, 0)) {
		UGameplayStatics::DeleteGameInSlot(SaveSlotName, 0);
		UE_LOG(LogGameFuse, Log, TEXT("User Logged Out Successfully"), UserData.Id);
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

TArray<FGFStoreItem>& UGameFuseUser::GetPurchasedStoreItems()
{
	return PurchasedStoreItems;
}

FGuid UGameFuseUser::AddCredits(const int AddCredits, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->AddCredits(AddCredits, UserData, Callback);
}

FGuid UGameFuseUser::SetCredits(const int SetCredits, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->SetCredits(SetCredits, UserData, Callback);
}

FGuid UGameFuseUser::PurchaseStoreItem(const FGFStoreItem& StoreItem, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->PurchaseStoreItem(StoreItem.Id, UserData, Callback);
}

FGuid UGameFuseUser::PurchaseStoreItemWithId(const int StoreItemId, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->PurchaseStoreItem(StoreItemId, UserData, Callback);
}

FGuid UGameFuseUser::RemoveStoreItem(const FGFStoreItem& StoreItem, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->RemoveStoreItem(StoreItem.Id, UserData, Callback);
}

FGuid UGameFuseUser::RemoveStoreItemWithId(const int StoreItemId, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->RemoveStoreItem(StoreItemId, UserData, Callback);
}

FGuid UGameFuseUser::FetchPurchasedStoreItems(FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->FetchPurchaseStoreItems(UserData, Callback);
}

#pragma endregion

#pragma region Attributes

TMap<FString, FString>& UGameFuseUser::GetAttributes()
{
	return Attributes;
}

TArray<FString> UGameFuseUser::GetAttributesKeys() const
{
	TArray<FString> KeysArray;
	KeysArray.Reserve(Attributes.Num()); // Optional: Reserving memory for efficiency
	Attributes.GenerateKeyArray(KeysArray);
	return KeysArray;
}

TMap<FString, FString>& UGameFuseUser::GetDirtyAttributes()
{
	return DirtyAttributes;
}

FString UGameFuseUser::GetAttributeValue(const FString Key) const
{
	return Attributes.FindRef(Key);
}

FGuid UGameFuseUser::SetAttribute(const FString& SetKey, const FString& SetValue, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->SetAttribute(SetKey, SetValue, UserData, Callback);
}

void UGameFuseUser::SetAttributeLocal(const FString& SetKey, const FString& SetValue, FGFApiCallback Callback)
{
	DirtyAttributes.Add(SetKey, SetValue);
	FString Set_Dirty_Attribute_Message = FString::Printf(TEXT("Setting Dirty Attribute (local-and-temporary) : %s : %s"), *SetKey, *SetValue);
	UE_LOG(LogGameFuse, Log, TEXT("%s"), *Set_Dirty_Attribute_Message);
	Callback.Broadcast(FGFAPIResponse(true, Set_Dirty_Attribute_Message));
}

FGuid UGameFuseUser::RemoveAttribute(const FString& SetKey, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->RemoveAttribute(SetKey, UserData, Callback);
}

FGuid UGameFuseUser::FetchAttributes(FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->FetchAttributes(UserData, Callback);
}

FGuid UGameFuseUser::SyncLocalAttributes(FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->SyncLocalAttributes(DirtyAttributes, UserData, Callback);
}

#pragma endregion

#pragma region Leaderboard & Score

int32 UGameFuseUser::GetScore() const
{
	return UserData.Score;
}

const TArray<FGFLeaderboardEntry>& UGameFuseUser::GetLeaderboardEntries()
{
	return LeaderboardEntries;
}

FGuid UGameFuseUser::AddScore(const int AddScore, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->AddScore(AddScore, UserData, Callback);
}

FGuid UGameFuseUser::SetScore(const int SetScore, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->SetScore(SetScore, UserData, Callback);
}

FGuid UGameFuseUser::AddLeaderboardEntry(const FString& LeaderboardName, const int OurScore, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return AddLeaderboardEntryWithAttributes(LeaderboardName, OurScore, TMap<FString, FString>(), Callback);
}

FGuid UGameFuseUser::AddLeaderboardEntryWithAttributes(const FString& LeaderboardName, const int OurScore, const TMap<FString, FString>& ExtraAttributes, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->AddLeaderboardEntry(LeaderboardName, OurScore, ExtraAttributes, UserData, Callback);
}

FGuid UGameFuseUser::ClearLeaderboardEntry(const FString& LeaderboardName, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->ClearLeaderboardEntry(LeaderboardName, UserData, Callback);
}

FGuid UGameFuseUser::FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, FGFApiCallback Callback)
{
	Callback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	return RequestHandler->FetchMyLeaderboardEntries(Limit, bOnePerUser, UserData, Callback);
}

#pragma endregion

#pragma region Blueprint Wrapper Functions

void UGameFuseUser::WrapBlueprintCallback(const FBP_GFApiCallback& Callback, FGFApiCallback& InternalCallback)
{
	InternalCallback.AddUObject(this, &UGameFuseUser::InternalResponseManager);
	InternalCallback.AddLambda([Callback](const FGFAPIResponse& ResponseData) {
		Callback.ExecuteIfBound(ResponseData);
	});
}

void UGameFuseUser::BP_SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& Username, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	SignUp(Email, Password, PasswordConfirmation, Username, InternalCallback);
}

void UGameFuseUser::BP_SignIn(const FString& Email, const FString& Password, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	SignIn(Email, Password, InternalCallback);
}

void UGameFuseUser::BP_AddCredits(const int Credits, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	AddCredits(Credits, InternalCallback);
}

void UGameFuseUser::BP_SetCredits(const int Credits, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	SetCredits(Credits, InternalCallback);
}

void UGameFuseUser::BP_AddScore(const int Score, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	AddScore(Score, InternalCallback);
}

void UGameFuseUser::BP_SetScore(const int Score, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	SetScore(Score, InternalCallback);
}

void UGameFuseUser::BP_SetAttribute(const FString& Key, const FString& Value, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	SetAttribute(Key, Value, InternalCallback);
}

void UGameFuseUser::BP_SetAttributeLocal(const FString& Key, const FString& Value, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	SetAttributeLocal(Key, Value, InternalCallback);
}

void UGameFuseUser::BP_RemoveAttribute(const FString& Key, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	RemoveAttribute(Key, InternalCallback);
}

void UGameFuseUser::BP_FetchPurchasedStoreItems(FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	FetchPurchasedStoreItems(InternalCallback);
}

void UGameFuseUser::BP_RemoveStoreItemWithId(const int StoreItemId, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	RemoveStoreItemWithId(StoreItemId, InternalCallback);
}

void UGameFuseUser::BP_PurchaseStoreItemWithId(const int StoreItemId, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	PurchaseStoreItemWithId(StoreItemId, InternalCallback);
}

void UGameFuseUser::BP_PurchaseStoreItem(const FGFStoreItem& StoreItem, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	PurchaseStoreItem(StoreItem, InternalCallback);
}

void UGameFuseUser::BP_RemoveStoreItem(const FGFStoreItem& StoreItem, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	RemoveStoreItem(StoreItem, InternalCallback);
}

void UGameFuseUser::BP_AddLeaderboardEntry(const FString& LeaderboardName, const int Score, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	AddLeaderboardEntry(LeaderboardName, Score, InternalCallback);
}

void UGameFuseUser::BP_AddLeaderboardEntryWithAttributes(const FString& LeaderboardName, const int Score, TMap<FString, FString>& ExtraAttributes, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	AddLeaderboardEntryWithAttributes(LeaderboardName, Score, ExtraAttributes, InternalCallback);
}

void UGameFuseUser::BP_ClearLeaderboardEntry(const FString& LeaderboardName, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	ClearLeaderboardEntry(LeaderboardName, InternalCallback);
}

void UGameFuseUser::BP_FetchAttributes(FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	FetchAttributes(InternalCallback);
}

void UGameFuseUser::BP_FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	FetchMyLeaderboardEntries(Limit, bOnePerUser, InternalCallback);
}

void UGameFuseUser::BP_SyncLocalAttributes(FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	SyncLocalAttributes(InternalCallback);
}

#pragma endregion

#pragma region Internal Response Handlers

void UGameFuseUser::InternalResponseManager(FGFAPIResponse ResponseData)
{
	if (!ResponseData.bSuccess) {
		UE_LOG(LogGameFuse, Error, TEXT("API Response Failed: %s"), *ResponseData.ResponseStr);
		return;
	}

	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseData.ResponseStr);
	TSharedPtr<FJsonObject> JsonObject;

	if (!FJsonSerializer::Deserialize(Reader, JsonObject)) {
		UE_LOG(LogGameFuse, Error, TEXT("Failed To Parse JSON Response From API"));
		return;
	}
	EGFUserAPIResponseType ResponseType = GameFuseUtilities::DetermineUserAPIResponseType(JsonObject);
	switch (ResponseType) {
		case (EGFUserAPIResponseType::Login):
			SetLoginInternal(JsonObject);
			break;
		case (EGFUserAPIResponseType::Attributes):
			SetAttributesInternal(JsonObject);
			break;
		case (EGFUserAPIResponseType::StoreItems):
			SetCreditsInternal(JsonObject);
			SetStoreItemsInternal(JsonObject);
			break;
		case (EGFUserAPIResponseType::LeaderboardEntries):
			SetLeaderboardsInternal(JsonObject);
			break;
		case (EGFUserAPIResponseType::Credits):
			SetCreditsInternal(JsonObject);
			break;
		case (EGFUserAPIResponseType::Score):
			SetScoresInternal(JsonObject);
			break;
		default:
			UE_LOG(LogGameFuse, Warning, TEXT("Unknown Response Data"));
	}
}

void UGameFuseUser::SetLoginInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	UE_LOG(LogGameFuse, Warning, TEXT("User Log in Token Response: %s"), *JsonObject->GetStringField(TEXT("authentication_token")));
	const bool bSuccess = GameFuseUtilities::ConvertJsonToUserData(UserData, JsonObject);

	if (bSuccess) {
		UserData.bSignedIn = true;

		UGameFuseSaveData* SaveGameInstance = Cast<UGameFuseSaveData>(UGameplayStatics::CreateSaveGameObject(UGameFuseSaveData::StaticClass()));
		SaveGameInstance->UserData = UserData;

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "GameFuseSaveSlot", 0);
		UE_LOG(LogGameFuse, Log, TEXT("Saved Login Data Into SlotName:GameFuseSaveSlot UserIndex:0"));
	} else {
		UE_LOG(LogGameFuse, Error, TEXT("User Parse Login Response Failed !"));
	}
}

void UGameFuseUser::SetCreditsInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	const int32 NewCredits = UKismetStringLibrary::Conv_StringToInt(JsonObject->GetStringField(TEXT("credits")));

	if (UGameFuseSaveData* SaveGameInstance = Cast<UGameFuseSaveData>(UGameplayStatics::LoadGameFromSlot("GameFuseSaveSlot", 0))) {
		UserData.Credits = NewCredits;
		SaveGameInstance->UserData.Credits = NewCredits;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "GameFuseSaveSlot", 0);
		UE_LOG(LogGameFuse, Log, TEXT("Updated The Credits Into SlotName:GameFuseSaveSlot UserIndex:0"));
	} else {
		UE_LOG(LogGameFuse, Error, TEXT("User Failed To Update Credits !"));
	}
}

void UGameFuseUser::SetScoresInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	const int32 NewScores = UKismetStringLibrary::Conv_StringToInt(JsonObject->GetStringField(TEXT("score")));

	if (UGameFuseSaveData* SaveGameInstance = Cast<UGameFuseSaveData>(UGameplayStatics::LoadGameFromSlot("GameFuseSaveSlot", 0))) {
		UserData.Score = NewScores;
		SaveGameInstance->UserData.Score = NewScores;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "GameFuseSaveSlot", 0);
		UE_LOG(LogGameFuse, Log, TEXT("Updated The Scores Into SlotName:GameFuseSaveSlot UserIndex:0"));
	} else {
		UE_LOG(LogGameFuse, Error, TEXT("User Failed To Update Scores !"));
	}
}

void UGameFuseUser::SetAttributesInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	Attributes.Empty();

	if (const TArray<TSharedPtr<FJsonValue>>* AttributeArray; JsonObject->TryGetArrayField(TEXT("game_user_attributes"), AttributeArray)) {
		for (const TSharedPtr<FJsonValue>& AttributeValue : *AttributeArray) {
			if (AttributeValue->Type == EJson::Object) {
				const TSharedPtr<FJsonObject> AttributeObject = AttributeValue->AsObject();
				FString Key = "";
				FString Value = "";

				// Extract key and value from the JSON object
				AttributeObject->TryGetStringField(TEXT("key"), Key);
				AttributeObject->TryGetStringField(TEXT("value"), Value);

				// Add to the attribute map
				Attributes.Add(Key, Value);
				UE_LOG(LogGameFuse, Log, TEXT("User SetAttributes : %s : %s"), *Key, *Value);
			} else {
				UE_LOG(LogGameFuse, Error, TEXT("User Failed to parse JSON"));
				return;
			}
		}
		UE_LOG(LogGameFuse, Log, TEXT("User Attributes Updated : %i"), Attributes.Num());
	} else {
		UE_LOG(LogGameFuse, Error, TEXT("User Failed To Parse JSON"));
	}
}

void UGameFuseUser::SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	PurchasedStoreItems.Empty();

	if (const TArray<TSharedPtr<FJsonValue>>* AttributeArray; JsonObject->TryGetArrayField(TEXT("game_user_store_items"), AttributeArray)) {
		PurchasedStoreItems.Reserve(AttributeArray->Num());
		for (const TSharedPtr<FJsonValue>& AttributeValue : *AttributeArray) {
			size_t newIndex = PurchasedStoreItems.AddDefaulted();
			bool bSuccess = GameFuseUtilities::ConvertJsonToStoreItem(PurchasedStoreItems[newIndex], AttributeValue);

			if (!bSuccess) {
				PurchasedStoreItems.RemoveAt(newIndex);
			}
		}
		UE_LOG(LogGameFuse, Log, TEXT("User Store Items Updated : %i"), Attributes.Num());
	} else {
		UE_LOG(LogGameFuse, Error, TEXT("User Failed To Parse JSON"));
	}
}

/** Response is mixed leaderboard entries from many leaderboards*/
void UGameFuseUser::SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	LeaderboardEntries.Empty();
	if (!JsonObject->HasField(TEXT("leaderboard_entries"))) {
		UE_LOG(LogGameFuse, Error, TEXT("Fetching Users Leaderboard Entries Failed to parse JSON"));
		return;
	}

	const TArray<TSharedPtr<FJsonValue>>& AttributeArray = JsonObject->GetArrayField(TEXT("leaderboard_entries"));
	if (AttributeArray.Num() == 0) {
		return;
	}

	LeaderboardEntries.Reserve(AttributeArray.Num());

	for (const TSharedPtr<FJsonValue>& AttributeValue : AttributeArray) {
		size_t newIndex = LeaderboardEntries.AddDefaulted();
		const bool bSuccess = GameFuseUtilities::ConvertJsonToLeaderboardItem(LeaderboardEntries[newIndex], AttributeValue);

		if (!bSuccess) {
			LeaderboardEntries.RemoveAt(newIndex);
		}
	}
	UE_LOG(LogGameFuse, Log, TEXT("Fetched User Leaderboard Entries. Amount : %d"), LeaderboardEntries.Num());
}

#pragma endregion