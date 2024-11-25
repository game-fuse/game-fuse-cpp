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
#include "Objects/GameFuseSignData.h"
#include "Models/GameFuseUtilities.h"
#include "Subsystems/GameFuseManager.h"



#pragma region Subsystem Overloads



void UGameFuseUser::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);

	RequestHandler = NewObject<UUserAPIHandler>();
	if (const UGameFuseSaveData* LoadedSaveGame = Cast<UGameFuseSaveData>(UGameplayStatics::LoadGameFromSlot("GameFuseSaveSlot", 0)))
	{

		UserData = LoadedSaveGame->UserData;
		// AddAuthenticationHeader();
		UE_LOG(LogGameFuse, Log, TEXT("Game Fuse Subsystem Loaded"));
	}


	GameFuseManager = GetGameInstance()->GetSubsystem<UGameFuseManager>();
}

void UGameFuseUser::Deinitialize()
{
	Super::Deinitialize();
}

#pragma endregion

#pragma region Game Fuse User Getters

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

int32 UGameFuseUser::GetScore() const
{
	return UserData.Score;
}

int32 UGameFuseUser::GetCredits() const
{
	return UserData.Credits;
}

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

TArray<FGFStoreItem>& UGameFuseUser::GetPurchasedStoreItems()
{
	return PurchasedStoreItems;
}

const TArray<FGFLeaderboardEntry>& UGameFuseUser::GetLeaderboardEntries()
{
	return LeaderboardEntries;
}

FString UGameFuseUser::GetAuthenticationToken() const
{
	return UserData.AuthenticationToken;
}


#pragma endregion

#pragma region BP Delegate wrapper functions

void UGameFuseUser::WrapBlueprintCallback(const FBP_GFApiCallback& Callback, FGFApiCallback& InternalCallback)
{
	InternalCallback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);
	InternalCallback.Add(Callback);
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

void UGameFuseUser::BP_FetchPurchasedStoreItems(bool bChainedFromLogin, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	FetchPurchasedStoreItems(bChainedFromLogin, InternalCallback);
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

void UGameFuseUser::BP_AddLeaderboardEntry(const FString& LeaderboardName, const int Score, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	AddLeaderboardEntry(LeaderboardName, Score, InternalCallback);
}

void UGameFuseUser::BP_AddLeaderboardEntryWithAttributes(const FString& LeaderboardName, const int Score, TMap<FString, FString> ExtraAttributes, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	AddLeaderboardEntryWithAttributes(LeaderboardName, Score, ExtraAttributes, InternalCallback);
}

void UGameFuseUser::BP_RemoveStoreItem(const FGFStoreItem& StoreItem, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	RemoveStoreItem(StoreItem, InternalCallback);
}

void UGameFuseUser::BP_ClearLeaderboardEntry(const FString& LeaderboardName, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	ClearLeaderboardEntry(LeaderboardName, InternalCallback);
}



void UGameFuseUser::BP_FetchAttributes(bool bChainedFromLogin, FBP_GFApiCallback Callback)
{
	FGFApiCallback InternalCallback;
	WrapBlueprintCallback(Callback, InternalCallback);
	FetchAttributes(bChainedFromLogin, InternalCallback);
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
#pragma region Game Fuse User SignUp and SignIn



void UGameFuseUser::SignUp(const FString& Email, const FString& Password, const FString& PasswordConfirmation, const FString& OurUsername, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);
	const FGFGameData& GameData = GameFuseManager->GetGameData();
	RequestHandler->SignUp(Email, Password, PasswordConfirmation, OurUsername, GameData.Id, GameData.Token, Callback);
}


void UGameFuseUser::SignIn(const FString& Email, const FString& Password, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);
	const FGFGameData& GameData = GameFuseManager->GetGameData();
	RequestHandler->SignIn(Email, Password, GameData.Id, GameData.Token, Callback);
}

void UGameFuseUser::LogOut()
{
	UE_LOG(LogGameFuse, Log, TEXT("User %i Logging Out"), UserData.Id);
	UserData = FGFUserData();

	bool bSuccess = UGameplayStatics::DeleteGameInSlot("GameFuseSaveSlot", 0);

	if (bSuccess)
	{
		UE_LOG(LogGameFuse, Log, TEXT("User Logged Out"));
	}
	else
	{
		UE_LOG(LogGameFuse, Error, TEXT("User Failed To Log Out"));
	}
}


#pragma endregion

#pragma region Game Fuse User Sending Requests

void UGameFuseUser::AddCredits(const int AddCredits, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->AddCredits(AddCredits, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::SetCredits(const int SetCredits, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->SetCredits(SetCredits, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::AddScore(const int AddScore, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->AddScore(AddScore, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::SetScore(const int SetScore, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->SetScore(SetScore, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::SetAttribute(const FString& SetKey, const FString& SetValue, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->SetAttribute(SetKey, SetValue, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::SetAttributeLocal(const FString& SetKey, const FString& SetValue, FGFApiCallback Callback)
{
	DirtyAttributes.Add(SetKey, SetValue);

	FString Set_Dirty_Attribute_Message = FString::Printf(TEXT("Setting Dirty Attribute (local-and-temporary) : %s : %s"), *SetKey, *SetValue);

	UE_LOG(LogGameFuse, Log, TEXT("%s"), *Set_Dirty_Attribute_Message);

	Callback.Broadcast(FGFAPIResponse(true, Set_Dirty_Attribute_Message));
}


void UGameFuseUser::SyncLocalAttributes(FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->SyncLocalAttributes(DirtyAttributes, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::RemoveAttribute(const FString& SetKey, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->RemoveAttribute(SetKey, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::PurchaseStoreItem(const FGFStoreItem& StoreItem, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->PurchaseStoreItem(StoreItem.Id, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::PurchaseStoreItemWithId(const int StoreItemId, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->PurchaseStoreItem(StoreItemId, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::RemoveStoreItem(const FGFStoreItem& StoreItem, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->RemoveStoreItem(StoreItem.Id, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::RemoveStoreItemWithId(const int StoreItemId, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->RemoveStoreItem(StoreItemId, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::AddLeaderboardEntryWithAttributes(const FString& LeaderboardName, const int OurScore, TMap<FString, FString> ExtraAttributes, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->AddLeaderboardEntry(LeaderboardName, OurScore, &ExtraAttributes, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::AddLeaderboardEntry(const FString& LeaderboardName, const int OurScore, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->AddLeaderboardEntry(LeaderboardName, OurScore, nullptr, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::FetchMyLeaderboardEntries(const int Limit, bool bOnePerUser, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->FetchMyLeaderboardEntries(Limit, bOnePerUser, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::ClearLeaderboardEntry(const FString& LeaderboardName, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->ClearLeaderboardEntry(LeaderboardName, UserData.Id, UserData.AuthenticationToken, Callback);
}



void UGameFuseUser::FetchAttributes(bool bChainedFromLogin, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->FetchAttributes(bChainedFromLogin, UserData.Id, UserData.AuthenticationToken, Callback);
}


void UGameFuseUser::FetchPurchasedStoreItems(const bool bChainedFromLogin, FGFApiCallback Callback)
{
	Callback.AddUniqueDynamic(this, &UGameFuseUser::InternalResponseManager);

	RequestHandler->FetchPurchaseStoreItems(bChainedFromLogin, UserData.Id, UserData.AuthenticationToken, Callback);
}


#pragma endregion
#pragma region Game Fuse User Setters

void UGameFuseUser::InternalResponseManager(FGFAPIResponse ResponseData)
{
	if (!ResponseData.bSuccess)
	{
		UE_LOG(LogGameFuse, Error, TEXT("API Response Failed: %s"), *ResponseData.ResponseStr);
		return;
	}

	const TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseData.ResponseStr);
	TSharedPtr<FJsonObject> JsonObject;

	if (!FJsonSerializer::Deserialize(Reader, JsonObject))
	{
		UE_LOG(LogGameFuse, Error, TEXT("Failed To Parse JSON Response From API"));
		return;
	}

	switch (GameFuseUtilities::DetermineUserAPIResponseType(JsonObject))
	{
		//switch on EGF_UserAPIResponse
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
	const bool bSuccess = GameFuseUtilities::ConvertJsonToUserData(UserData, JsonObject);

	if (bSuccess)
	{
		UserData.bSignedIn = true;

		UGameFuseSaveData* SaveGameInstance = Cast<UGameFuseSaveData>(UGameplayStatics::CreateSaveGameObject(UGameFuseSaveData::StaticClass()));
		SaveGameInstance->UserData = UserData;

		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "GameFuseSaveSlot", 0);
		UE_LOG(LogGameFuse, Log, TEXT("Saved Login Data Into SlotName:GameFuseSaveSlot UserIndex:0"));
	}
	else
	{
		UE_LOG(LogGameFuse, Error, TEXT("User Parse Login Response Failed !"));
	}
}

void UGameFuseUser::SetCreditsInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	const int32 NewCredits = UKismetStringLibrary::Conv_StringToInt(JsonObject->GetStringField(TEXT("credits")));

	if (UGameFuseSaveData* SaveGameInstance = Cast<UGameFuseSaveData>(UGameplayStatics::LoadGameFromSlot("GameFuseSaveSlot", 0)))
	{
		UserData.Credits = NewCredits;
		SaveGameInstance->UserData.Credits = NewCredits;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "GameFuseSaveSlot", 0);
		UE_LOG(LogGameFuse, Log, TEXT("Updated The Credits Into SlotName:GameFuseSaveSlot UserIndex:0"));
	}
	else
	{
		UE_LOG(LogGameFuse, Error, TEXT("User Failed To Update Credits !"));
	}
}

void UGameFuseUser::SetScoresInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	const int32 NewScores = UKismetStringLibrary::Conv_StringToInt(JsonObject->GetStringField(TEXT("score")));

	if (UGameFuseSaveData* SaveGameInstance = Cast<UGameFuseSaveData>(UGameplayStatics::LoadGameFromSlot("GameFuseSaveSlot", 0)))
	{
		UserData.Score = NewScores;
		SaveGameInstance->UserData.Score = NewScores;
		UGameplayStatics::SaveGameToSlot(SaveGameInstance, "GameFuseSaveSlot", 0);
		UE_LOG(LogGameFuse, Log, TEXT("Updated The Scores Into SlotName:GameFuseSaveSlot UserIndex:0"));
	}
	else
	{
		UE_LOG(LogGameFuse, Error, TEXT("User Failed To Update Scores !"));
	}
}


void UGameFuseUser::SetAttributesInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	Attributes.Empty();

	if (const TArray<TSharedPtr<FJsonValue>>* AttributeArray; JsonObject->TryGetArrayField(TEXT("game_user_attributes"), AttributeArray))
	{
		for (const TSharedPtr<FJsonValue>& AttributeValue : *AttributeArray)
		{
			if (AttributeValue->Type == EJson::Object)
			{
				const TSharedPtr<FJsonObject> AttributeObject = AttributeValue->AsObject();
				FString Key = "";
				FString Value = "";

				// Extract key and value from the JSON object
				AttributeObject->TryGetStringField(TEXT("key"), Key);
				AttributeObject->TryGetStringField(TEXT("value"), Value);

				// Add to the attribute map
				Attributes.Add(Key, Value);
				UE_LOG(LogGameFuse, Log, TEXT("User SetAttributes : %s : %s"), *Key, *Value);
			}
			else
			{
				UE_LOG(LogGameFuse, Error, TEXT("User Failed to parse JSON"));
				return;
			}
		}
		UE_LOG(LogGameFuse, Log, TEXT("User Attributes Updated : %i"), Attributes.Num());
	}
	else
	{
		UE_LOG(LogGameFuse, Error, TEXT("User Failed To Parse JSON"));
	}
}

void UGameFuseUser::SetStoreItemsInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	PurchasedStoreItems.Empty();

	if (const TArray<TSharedPtr<FJsonValue>>* AttributeArray; JsonObject->TryGetArrayField(TEXT("game_user_store_items"), AttributeArray))
	{
		PurchasedStoreItems.Reserve(AttributeArray->Num());
		for (const TSharedPtr<FJsonValue>& AttributeValue : *AttributeArray)
		{
			size_t newIndex = PurchasedStoreItems.AddDefaulted();

			bool bSuccess = GameFuseUtilities::ConvertJsonToStoreItem(PurchasedStoreItems[newIndex], AttributeValue);

			if (!bSuccess)
			{
				PurchasedStoreItems.RemoveAt(newIndex);
			}
		}
		UE_LOG(LogGameFuse, Log, TEXT("User Store Items Updated : %i"), Attributes.Num());
	}
	else
	{
		UE_LOG(LogGameFuse, Error, TEXT("User Failed To Parse JSON"));
	}
}

/** Response is mixed leaderboard entries from many leaderboards*/
void UGameFuseUser::SetLeaderboardsInternal(const TSharedPtr<FJsonObject>& JsonObject)
{
	LeaderboardEntries.Empty();
	if (!JsonObject->HasField(TEXT("leaderboard_entries")))
	{
		UE_LOG(LogGameFuse, Error, TEXT("Fetching Users Leaderboard Entries Failed to parse JSON"));
		return;
	}

	const TArray<TSharedPtr<FJsonValue>>& AttributeArray = JsonObject->GetArrayField(TEXT("leaderboard_entries"));
	if (AttributeArray.Num() == 0)
	{
		return;
	}


	LeaderboardEntries.Reserve(AttributeArray.Num());


	for (const TSharedPtr<FJsonValue>& AttributeValue : AttributeArray)
	{
		size_t newIndex = LeaderboardEntries.AddDefaulted();
		const bool bSuccess = GameFuseUtilities::ConvertJsonToLeaderboardItem(LeaderboardEntries[newIndex], AttributeValue);

		if (!bSuccess)
		{
			LeaderboardEntries.RemoveAt(newIndex);
		}

	}
	UE_LOG(LogGameFuse, Log, TEXT("Fetched User Leaderboard Entries. Amount : %d"), LeaderboardEntries.Num());

}