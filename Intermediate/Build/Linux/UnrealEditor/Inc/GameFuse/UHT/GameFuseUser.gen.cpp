// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameFuse/Public/GameFuseUser.h"
#include "../../Source/Runtime/Engine/Classes/Engine/GameInstance.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameFuseUser() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseLeaderboardEntry_NoRegister();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseStoreItem_NoRegister();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseUser();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseUser_NoRegister();
	GAMEFUSE_API UFunction* Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_GameFuse();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics
	{
		struct _Script_GameFuse_eventUserCallback_Parms
		{
			bool bSuccess;
			FString Response;
		};
		static void NewProp_bSuccess_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bSuccess;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Response_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Response;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::NewProp_bSuccess_SetBit(void* Obj)
	{
		((_Script_GameFuse_eventUserCallback_Parms*)Obj)->bSuccess = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(_Script_GameFuse_eventUserCallback_Parms), &Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::NewProp_bSuccess_SetBit, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::NewProp_Response_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::NewProp_Response = { "Response", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(_Script_GameFuse_eventUserCallback_Parms, Response), METADATA_PARAMS(Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::NewProp_Response_MetaData, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::NewProp_Response_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::NewProp_bSuccess,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::NewProp_Response,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_GameFuse, nullptr, "UserCallback__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::_Script_GameFuse_eventUserCallback_Parms), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FUserCallback_DelegateWrapper(const FScriptDelegate& UserCallback, bool bSuccess, const FString& Response)
{
	struct _Script_GameFuse_eventUserCallback_Parms
	{
		bool bSuccess;
		FString Response;
	};
	_Script_GameFuse_eventUserCallback_Parms Parms;
	Parms.bSuccess=bSuccess ? true : false;
	Parms.Response=Response;
	UserCallback.ProcessDelegate<UObject>(&Parms);
}
	DEFINE_FUNCTION(UGameFuseUser::execFetchPurchaseStoreItems)
	{
		P_GET_UBOOL(Z_Param_bChainedFromLogin);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->FetchPurchaseStoreItems(Z_Param_bChainedFromLogin,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execFetchAttributes)
	{
		P_GET_UBOOL(Z_Param_bChainedFromLogin);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->FetchAttributes(Z_Param_bChainedFromLogin,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execFetchMyLeaderboardEntries)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Limit);
		P_GET_UBOOL(Z_Param_bOnePerUser);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->FetchMyLeaderboardEntries(Z_Param_Limit,Z_Param_bOnePerUser,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execClearLeaderboardEntry)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_LeaderboardName);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->ClearLeaderboardEntry(Z_Param_LeaderboardName,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execAddLeaderboardEntryWithAttributes)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_LeaderboardName);
		P_GET_PROPERTY(FIntProperty,Z_Param_OurScore);
		P_GET_TMAP_REF(FString,FString,Z_Param_Out_ExtraAttributes);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddLeaderboardEntryWithAttributes(Z_Param_LeaderboardName,Z_Param_OurScore,Z_Param_Out_ExtraAttributes,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execAddLeaderboardEntry)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_LeaderboardName);
		P_GET_PROPERTY(FIntProperty,Z_Param_OurScore);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddLeaderboardEntry(Z_Param_LeaderboardName,Z_Param_OurScore,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execRemoveStoreItem)
	{
		P_GET_OBJECT(UGameFuseStoreItem,Z_Param_StoreItem);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->RemoveStoreItem(Z_Param_StoreItem,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execRemoveStoreItemWithId)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_StoreItemId);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->RemoveStoreItemWithId(Z_Param_StoreItemId,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execPurchaseStoreItem)
	{
		P_GET_OBJECT(UGameFuseStoreItem,Z_Param_StoreItem);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->PurchaseStoreItem(Z_Param_StoreItem,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execPurchaseStoreItemWithId)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_StoreItemId);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->PurchaseStoreItemWithId(Z_Param_StoreItemId,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execRemoveAttribute)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_SetKey);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->RemoveAttribute(Z_Param_SetKey,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execSetAttribute)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_SetKey);
		P_GET_PROPERTY(FStrProperty,Z_Param_SetValue);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetAttribute(Z_Param_SetKey,Z_Param_SetValue,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execSetScore)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_SetScore);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetScore(Z_Param_SetScore,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execAddScore)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_AddScore);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddScore(Z_Param_AddScore,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execSetCredits)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_SetCredits);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SetCredits(Z_Param_SetCredits,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execAddCredits)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_AddCredits);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddCredits(Z_Param_AddCredits,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execIsSignedIn)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsSignedIn();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execSignIn)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Email);
		P_GET_PROPERTY(FStrProperty,Z_Param_Password);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SignIn(Z_Param_Email,Z_Param_Password,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execSignUp)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Email);
		P_GET_PROPERTY(FStrProperty,Z_Param_Password);
		P_GET_PROPERTY(FStrProperty,Z_Param_PasswordConfirmation);
		P_GET_PROPERTY(FStrProperty,Z_Param_Username);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->SignUp(Z_Param_Email,Z_Param_Password,Z_Param_PasswordConfirmation,Z_Param_Username,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execGetLeaderboards)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UGameFuseLeaderboardEntry*>*)Z_Param__Result=P_THIS->GetLeaderboards();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execGetPurchasedStoreItems)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UGameFuseStoreItem*>*)Z_Param__Result=P_THIS->GetPurchasedStoreItems();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execGetAttributeValue)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Key);
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetAttributeValue(Z_Param_Key);
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execGetAttributesKeys)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<FString>*)Z_Param__Result=P_THIS->GetAttributesKeys();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execGetAttributes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TMap<FString,FString>*)Z_Param__Result=P_THIS->GetAttributes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execGetCredits)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetCredits();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execGetScore)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetScore();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execGetUsername)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetUsername();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execGetLastLogin)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetLastLogin();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execGetNumberOfLogins)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetNumberOfLogins();
		P_NATIVE_END;
	}
	void UGameFuseUser::StaticRegisterNativesUGameFuseUser()
	{
		UClass* Class = UGameFuseUser::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddCredits", &UGameFuseUser::execAddCredits },
			{ "AddLeaderboardEntry", &UGameFuseUser::execAddLeaderboardEntry },
			{ "AddLeaderboardEntryWithAttributes", &UGameFuseUser::execAddLeaderboardEntryWithAttributes },
			{ "AddScore", &UGameFuseUser::execAddScore },
			{ "ClearLeaderboardEntry", &UGameFuseUser::execClearLeaderboardEntry },
			{ "FetchAttributes", &UGameFuseUser::execFetchAttributes },
			{ "FetchMyLeaderboardEntries", &UGameFuseUser::execFetchMyLeaderboardEntries },
			{ "FetchPurchaseStoreItems", &UGameFuseUser::execFetchPurchaseStoreItems },
			{ "GetAttributes", &UGameFuseUser::execGetAttributes },
			{ "GetAttributesKeys", &UGameFuseUser::execGetAttributesKeys },
			{ "GetAttributeValue", &UGameFuseUser::execGetAttributeValue },
			{ "GetCredits", &UGameFuseUser::execGetCredits },
			{ "GetLastLogin", &UGameFuseUser::execGetLastLogin },
			{ "GetLeaderboards", &UGameFuseUser::execGetLeaderboards },
			{ "GetNumberOfLogins", &UGameFuseUser::execGetNumberOfLogins },
			{ "GetPurchasedStoreItems", &UGameFuseUser::execGetPurchasedStoreItems },
			{ "GetScore", &UGameFuseUser::execGetScore },
			{ "GetUsername", &UGameFuseUser::execGetUsername },
			{ "IsSignedIn", &UGameFuseUser::execIsSignedIn },
			{ "PurchaseStoreItem", &UGameFuseUser::execPurchaseStoreItem },
			{ "PurchaseStoreItemWithId", &UGameFuseUser::execPurchaseStoreItemWithId },
			{ "RemoveAttribute", &UGameFuseUser::execRemoveAttribute },
			{ "RemoveStoreItem", &UGameFuseUser::execRemoveStoreItem },
			{ "RemoveStoreItemWithId", &UGameFuseUser::execRemoveStoreItemWithId },
			{ "SetAttribute", &UGameFuseUser::execSetAttribute },
			{ "SetCredits", &UGameFuseUser::execSetCredits },
			{ "SetScore", &UGameFuseUser::execSetScore },
			{ "SignIn", &UGameFuseUser::execSignIn },
			{ "SignUp", &UGameFuseUser::execSignUp },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics
	{
		struct GameFuseUser_eventAddCredits_Parms
		{
			int32 AddCredits;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AddCredits_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_AddCredits;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::NewProp_AddCredits_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::NewProp_AddCredits = { "AddCredits", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddCredits_Parms, AddCredits), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::NewProp_AddCredits_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::NewProp_AddCredits_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddCredits_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::NewProp_AddCredits,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "Comment", "//> Action Requests\n" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
		{ "ToolTip", "> Action Requests" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "AddCredits", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::GameFuseUser_eventAddCredits_Parms), Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_AddCredits()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics
	{
		struct GameFuseUser_eventAddLeaderboardEntry_Parms
		{
			FString LeaderboardName;
			int32 OurScore;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LeaderboardName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_LeaderboardName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OurScore_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_OurScore;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_LeaderboardName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_LeaderboardName = { "LeaderboardName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddLeaderboardEntry_Parms, LeaderboardName), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_LeaderboardName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_LeaderboardName_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_OurScore_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_OurScore = { "OurScore", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddLeaderboardEntry_Parms, OurScore), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_OurScore_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_OurScore_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddLeaderboardEntry_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_LeaderboardName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_OurScore,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "AddLeaderboardEntry", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::GameFuseUser_eventAddLeaderboardEntry_Parms), Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics
	{
		struct GameFuseUser_eventAddLeaderboardEntryWithAttributes_Parms
		{
			FString LeaderboardName;
			int32 OurScore;
			TMap<FString,FString> ExtraAttributes;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LeaderboardName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_LeaderboardName;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_OurScore_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_OurScore;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ExtraAttributes_ValueProp;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ExtraAttributes_Key_KeyProp;
		static const UECodeGen_Private::FMapPropertyParams NewProp_ExtraAttributes;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_LeaderboardName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_LeaderboardName = { "LeaderboardName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddLeaderboardEntryWithAttributes_Parms, LeaderboardName), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_LeaderboardName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_LeaderboardName_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_OurScore_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_OurScore = { "OurScore", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddLeaderboardEntryWithAttributes_Parms, OurScore), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_OurScore_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_OurScore_MetaData)) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_ExtraAttributes_ValueProp = { "ExtraAttributes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 1, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_ExtraAttributes_Key_KeyProp = { "ExtraAttributes_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_ExtraAttributes = { "ExtraAttributes", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddLeaderboardEntryWithAttributes_Parms, ExtraAttributes), EMapPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddLeaderboardEntryWithAttributes_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_LeaderboardName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_OurScore,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_ExtraAttributes_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_ExtraAttributes_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_ExtraAttributes,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "AddLeaderboardEntryWithAttributes", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::GameFuseUser_eventAddLeaderboardEntryWithAttributes_Parms), Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04420401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_AddScore_Statics
	{
		struct GameFuseUser_eventAddScore_Parms
		{
			int32 AddScore;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AddScore_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_AddScore;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::NewProp_AddScore_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::NewProp_AddScore = { "AddScore", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddScore_Parms, AddScore), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::NewProp_AddScore_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::NewProp_AddScore_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddScore_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::NewProp_AddScore,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "AddScore", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::GameFuseUser_eventAddScore_Parms), Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_AddScore()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics
	{
		struct GameFuseUser_eventClearLeaderboardEntry_Parms
		{
			FString LeaderboardName;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LeaderboardName_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_LeaderboardName;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::NewProp_LeaderboardName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::NewProp_LeaderboardName = { "LeaderboardName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventClearLeaderboardEntry_Parms, LeaderboardName), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::NewProp_LeaderboardName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::NewProp_LeaderboardName_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventClearLeaderboardEntry_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::NewProp_LeaderboardName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "ClearLeaderboardEntry", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::GameFuseUser_eventClearLeaderboardEntry_Parms), Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics
	{
		struct GameFuseUser_eventFetchAttributes_Parms
		{
			bool bChainedFromLogin;
			FScriptDelegate CompletionCallback;
		};
		static void NewProp_bChainedFromLogin_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bChainedFromLogin;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::NewProp_bChainedFromLogin_SetBit(void* Obj)
	{
		((GameFuseUser_eventFetchAttributes_Parms*)Obj)->bChainedFromLogin = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::NewProp_bChainedFromLogin = { "bChainedFromLogin", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(GameFuseUser_eventFetchAttributes_Parms), &Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::NewProp_bChainedFromLogin_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventFetchAttributes_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::NewProp_bChainedFromLogin,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "FetchAttributes", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::GameFuseUser_eventFetchAttributes_Parms), Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_FetchAttributes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_FetchAttributes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics
	{
		struct GameFuseUser_eventFetchMyLeaderboardEntries_Parms
		{
			int32 Limit;
			bool bOnePerUser;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Limit_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_Limit;
		static void NewProp_bOnePerUser_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bOnePerUser;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::NewProp_Limit_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::NewProp_Limit = { "Limit", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventFetchMyLeaderboardEntries_Parms, Limit), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::NewProp_Limit_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::NewProp_Limit_MetaData)) };
	void Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::NewProp_bOnePerUser_SetBit(void* Obj)
	{
		((GameFuseUser_eventFetchMyLeaderboardEntries_Parms*)Obj)->bOnePerUser = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::NewProp_bOnePerUser = { "bOnePerUser", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(GameFuseUser_eventFetchMyLeaderboardEntries_Parms), &Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::NewProp_bOnePerUser_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventFetchMyLeaderboardEntries_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::NewProp_Limit,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::NewProp_bOnePerUser,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "FetchMyLeaderboardEntries", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::GameFuseUser_eventFetchMyLeaderboardEntries_Parms), Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics
	{
		struct GameFuseUser_eventFetchPurchaseStoreItems_Parms
		{
			bool bChainedFromLogin;
			FScriptDelegate CompletionCallback;
		};
		static void NewProp_bChainedFromLogin_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bChainedFromLogin;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::NewProp_bChainedFromLogin_SetBit(void* Obj)
	{
		((GameFuseUser_eventFetchPurchaseStoreItems_Parms*)Obj)->bChainedFromLogin = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::NewProp_bChainedFromLogin = { "bChainedFromLogin", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(GameFuseUser_eventFetchPurchaseStoreItems_Parms), &Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::NewProp_bChainedFromLogin_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventFetchPurchaseStoreItems_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::NewProp_bChainedFromLogin,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "FetchPurchaseStoreItems", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::GameFuseUser_eventFetchPurchaseStoreItems_Parms), Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics
	{
		struct GameFuseUser_eventGetAttributes_Parms
		{
			TMap<FString,FString> ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_ValueProp;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Key_KeyProp;
		static const UECodeGen_Private::FMapPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::NewProp_ReturnValue_ValueProp = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 1, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::NewProp_ReturnValue_Key_KeyProp = { "ReturnValue_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventGetAttributes_Parms, ReturnValue), EMapPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::NewProp_ReturnValue_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::NewProp_ReturnValue_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetAttributes", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::GameFuseUser_eventGetAttributes_Parms), Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_GetAttributes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_GetAttributes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics
	{
		struct GameFuseUser_eventGetAttributesKeys_Parms
		{
			TArray<FString> ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventGetAttributesKeys_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetAttributesKeys", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::GameFuseUser_eventGetAttributesKeys_Parms), Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics
	{
		struct GameFuseUser_eventGetAttributeValue_Parms
		{
			FString Key;
			FString ReturnValue;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Key_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Key;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::NewProp_Key_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::NewProp_Key = { "Key", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventGetAttributeValue_Parms, Key), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::NewProp_Key_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::NewProp_Key_MetaData)) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventGetAttributeValue_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::NewProp_Key,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetAttributeValue", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::GameFuseUser_eventGetAttributeValue_Parms), Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_GetAttributeValue()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_GetCredits_Statics
	{
		struct GameFuseUser_eventGetCredits_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UGameFuseUser_GetCredits_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventGetCredits_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_GetCredits_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetCredits_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_GetCredits_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetCredits_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetCredits", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetCredits_Statics::GameFuseUser_eventGetCredits_Parms), Z_Construct_UFunction_UGameFuseUser_GetCredits_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetCredits_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetCredits_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetCredits_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_GetCredits()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_GetCredits_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_GetLastLogin_Statics
	{
		struct GameFuseUser_eventGetLastLogin_Parms
		{
			FString ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_GetLastLogin_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventGetLastLogin_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_GetLastLogin_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetLastLogin_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_GetLastLogin_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetLastLogin_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetLastLogin", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetLastLogin_Statics::GameFuseUser_eventGetLastLogin_Parms), Z_Construct_UFunction_UGameFuseUser_GetLastLogin_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetLastLogin_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetLastLogin_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetLastLogin_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_GetLastLogin()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_GetLastLogin_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics
	{
		struct GameFuseUser_eventGetLeaderboards_Parms
		{
			TArray<UGameFuseLeaderboardEntry*> ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UGameFuseLeaderboardEntry_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventGetLeaderboards_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetLeaderboards", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics::GameFuseUser_eventGetLeaderboards_Parms), Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_GetLeaderboards()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_GetLeaderboards_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins_Statics
	{
		struct GameFuseUser_eventGetNumberOfLogins_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventGetNumberOfLogins_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "Comment", "//> Getters\n" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
		{ "ToolTip", "> Getters" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetNumberOfLogins", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins_Statics::GameFuseUser_eventGetNumberOfLogins_Parms), Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics
	{
		struct GameFuseUser_eventGetPurchasedStoreItems_Parms
		{
			TArray<UGameFuseStoreItem*> ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UGameFuseStoreItem_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventGetPurchasedStoreItems_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetPurchasedStoreItems", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::GameFuseUser_eventGetPurchasedStoreItems_Parms), Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_GetScore_Statics
	{
		struct GameFuseUser_eventGetScore_Parms
		{
			int32 ReturnValue;
		};
		static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UGameFuseUser_GetScore_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventGetScore_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_GetScore_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetScore_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_GetScore_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetScore_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetScore", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetScore_Statics::GameFuseUser_eventGetScore_Parms), Z_Construct_UFunction_UGameFuseUser_GetScore_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetScore_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetScore_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetScore_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_GetScore()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_GetScore_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_GetUsername_Statics
	{
		struct GameFuseUser_eventGetUsername_Parms
		{
			FString ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_GetUsername_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventGetUsername_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_GetUsername_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetUsername_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_GetUsername_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetUsername_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetUsername", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetUsername_Statics::GameFuseUser_eventGetUsername_Parms), Z_Construct_UFunction_UGameFuseUser_GetUsername_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetUsername_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetUsername_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetUsername_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_GetUsername()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_GetUsername_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics
	{
		struct GameFuseUser_eventIsSignedIn_Parms
		{
			bool ReturnValue;
		};
		static void NewProp_ReturnValue_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	void Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics::NewProp_ReturnValue_SetBit(void* Obj)
	{
		((GameFuseUser_eventIsSignedIn_Parms*)Obj)->ReturnValue = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(GameFuseUser_eventIsSignedIn_Parms), &Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "IsSignedIn", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics::GameFuseUser_eventIsSignedIn_Parms), Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x54020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_IsSignedIn()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_IsSignedIn_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics
	{
		struct GameFuseUser_eventPurchaseStoreItem_Parms
		{
			const UGameFuseStoreItem* StoreItem;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_StoreItem_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_StoreItem;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::NewProp_StoreItem_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::NewProp_StoreItem = { "StoreItem", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventPurchaseStoreItem_Parms, StoreItem), Z_Construct_UClass_UGameFuseStoreItem_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::NewProp_StoreItem_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::NewProp_StoreItem_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventPurchaseStoreItem_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::NewProp_StoreItem,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "PurchaseStoreItem", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::GameFuseUser_eventPurchaseStoreItem_Parms), Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics
	{
		struct GameFuseUser_eventPurchaseStoreItemWithId_Parms
		{
			int32 StoreItemId;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_StoreItemId_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_StoreItemId;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::NewProp_StoreItemId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::NewProp_StoreItemId = { "StoreItemId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventPurchaseStoreItemWithId_Parms, StoreItemId), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::NewProp_StoreItemId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::NewProp_StoreItemId_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventPurchaseStoreItemWithId_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::NewProp_StoreItemId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "PurchaseStoreItemWithId", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::GameFuseUser_eventPurchaseStoreItemWithId_Parms), Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics
	{
		struct GameFuseUser_eventRemoveAttribute_Parms
		{
			FString SetKey;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SetKey_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_SetKey;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::NewProp_SetKey_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::NewProp_SetKey = { "SetKey", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventRemoveAttribute_Parms, SetKey), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::NewProp_SetKey_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::NewProp_SetKey_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventRemoveAttribute_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::NewProp_SetKey,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "RemoveAttribute", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::GameFuseUser_eventRemoveAttribute_Parms), Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_RemoveAttribute()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics
	{
		struct GameFuseUser_eventRemoveStoreItem_Parms
		{
			const UGameFuseStoreItem* StoreItem;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_StoreItem_MetaData[];
#endif
		static const UECodeGen_Private::FObjectPropertyParams NewProp_StoreItem;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::NewProp_StoreItem_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::NewProp_StoreItem = { "StoreItem", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventRemoveStoreItem_Parms, StoreItem), Z_Construct_UClass_UGameFuseStoreItem_NoRegister, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::NewProp_StoreItem_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::NewProp_StoreItem_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventRemoveStoreItem_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::NewProp_StoreItem,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "RemoveStoreItem", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::GameFuseUser_eventRemoveStoreItem_Parms), Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics
	{
		struct GameFuseUser_eventRemoveStoreItemWithId_Parms
		{
			int32 StoreItemId;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_StoreItemId_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_StoreItemId;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::NewProp_StoreItemId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::NewProp_StoreItemId = { "StoreItemId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventRemoveStoreItemWithId_Parms, StoreItemId), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::NewProp_StoreItemId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::NewProp_StoreItemId_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventRemoveStoreItemWithId_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::NewProp_StoreItemId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "RemoveStoreItemWithId", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::GameFuseUser_eventRemoveStoreItemWithId_Parms), Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics
	{
		struct GameFuseUser_eventSetAttribute_Parms
		{
			FString SetKey;
			FString SetValue;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SetKey_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_SetKey;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SetValue_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_SetValue;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetKey_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetKey = { "SetKey", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSetAttribute_Parms, SetKey), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetKey_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetKey_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetValue = { "SetValue", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSetAttribute_Parms, SetValue), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetValue_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSetAttribute_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetKey,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetValue,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "SetAttribute", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::GameFuseUser_eventSetAttribute_Parms), Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_SetAttribute()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics
	{
		struct GameFuseUser_eventSetCredits_Parms
		{
			int32 SetCredits;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SetCredits_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_SetCredits;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::NewProp_SetCredits_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::NewProp_SetCredits = { "SetCredits", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSetCredits_Parms, SetCredits), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::NewProp_SetCredits_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::NewProp_SetCredits_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSetCredits_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::NewProp_SetCredits,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "SetCredits", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::GameFuseUser_eventSetCredits_Parms), Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_SetCredits()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_SetScore_Statics
	{
		struct GameFuseUser_eventSetScore_Parms
		{
			int32 SetScore;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_SetScore_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_SetScore;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::NewProp_SetScore_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::NewProp_SetScore = { "SetScore", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSetScore_Parms, SetScore), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::NewProp_SetScore_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::NewProp_SetScore_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSetScore_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::NewProp_SetScore,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "SetScore", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::GameFuseUser_eventSetScore_Parms), Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_SetScore()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_SignIn_Statics
	{
		struct GameFuseUser_eventSignIn_Parms
		{
			FString Email;
			FString Password;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Email_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Email;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Password_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Password;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::NewProp_Email_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::NewProp_Email = { "Email", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSignIn_Parms, Email), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::NewProp_Email_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::NewProp_Email_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::NewProp_Password_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::NewProp_Password = { "Password", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSignIn_Parms, Password), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::NewProp_Password_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::NewProp_Password_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSignIn_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::NewProp_Email,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::NewProp_Password,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "SignIn", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::GameFuseUser_eventSignIn_Parms), Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_SignIn()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_SignIn_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_SignUp_Statics
	{
		struct GameFuseUser_eventSignUp_Parms
		{
			FString Email;
			FString Password;
			FString PasswordConfirmation;
			FString Username;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Email_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Email;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Password_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Password;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_PasswordConfirmation_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_PasswordConfirmation;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Username_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Username;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Email_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Email = { "Email", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSignUp_Parms, Email), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Email_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Email_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Password_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Password = { "Password", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSignUp_Parms, Password), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Password_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Password_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_PasswordConfirmation_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_PasswordConfirmation = { "PasswordConfirmation", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSignUp_Parms, PasswordConfirmation), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_PasswordConfirmation_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_PasswordConfirmation_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Username_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Username = { "Username", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSignUp_Parms, Username), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Username_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Username_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSignUp_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3291937769
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Email,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Password,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_PasswordConfirmation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_Username,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "Comment", "//> Sign\n" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
		{ "ToolTip", "> Sign" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "SignUp", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::GameFuseUser_eventSignUp_Parms), Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_SignUp()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_SignUp_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGameFuseUser);
	UClass* Z_Construct_UClass_UGameFuseUser_NoRegister()
	{
		return UGameFuseUser::StaticClass();
	}
	struct Z_Construct_UClass_UGameFuseUser_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGameFuseUser_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UGameInstanceSubsystem,
		(UObject* (*)())Z_Construct_UPackage__Script_GameFuse,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGameFuseUser_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGameFuseUser_AddCredits, "AddCredits" }, // 917344188
		{ &Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry, "AddLeaderboardEntry" }, // 1885196233
		{ &Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntryWithAttributes, "AddLeaderboardEntryWithAttributes" }, // 341226292
		{ &Z_Construct_UFunction_UGameFuseUser_AddScore, "AddScore" }, // 3984658073
		{ &Z_Construct_UFunction_UGameFuseUser_ClearLeaderboardEntry, "ClearLeaderboardEntry" }, // 2273234150
		{ &Z_Construct_UFunction_UGameFuseUser_FetchAttributes, "FetchAttributes" }, // 1733551221
		{ &Z_Construct_UFunction_UGameFuseUser_FetchMyLeaderboardEntries, "FetchMyLeaderboardEntries" }, // 3725571930
		{ &Z_Construct_UFunction_UGameFuseUser_FetchPurchaseStoreItems, "FetchPurchaseStoreItems" }, // 2642972382
		{ &Z_Construct_UFunction_UGameFuseUser_GetAttributes, "GetAttributes" }, // 2331468312
		{ &Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys, "GetAttributesKeys" }, // 266678129
		{ &Z_Construct_UFunction_UGameFuseUser_GetAttributeValue, "GetAttributeValue" }, // 2377477569
		{ &Z_Construct_UFunction_UGameFuseUser_GetCredits, "GetCredits" }, // 735744228
		{ &Z_Construct_UFunction_UGameFuseUser_GetLastLogin, "GetLastLogin" }, // 2634675336
		{ &Z_Construct_UFunction_UGameFuseUser_GetLeaderboards, "GetLeaderboards" }, // 1820653288
		{ &Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins, "GetNumberOfLogins" }, // 1474415961
		{ &Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems, "GetPurchasedStoreItems" }, // 993342999
		{ &Z_Construct_UFunction_UGameFuseUser_GetScore, "GetScore" }, // 2903990249
		{ &Z_Construct_UFunction_UGameFuseUser_GetUsername, "GetUsername" }, // 1739003403
		{ &Z_Construct_UFunction_UGameFuseUser_IsSignedIn, "IsSignedIn" }, // 2035348427
		{ &Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem, "PurchaseStoreItem" }, // 2321281983
		{ &Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItemWithId, "PurchaseStoreItemWithId" }, // 3915995086
		{ &Z_Construct_UFunction_UGameFuseUser_RemoveAttribute, "RemoveAttribute" }, // 2934963441
		{ &Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem, "RemoveStoreItem" }, // 838024466
		{ &Z_Construct_UFunction_UGameFuseUser_RemoveStoreItemWithId, "RemoveStoreItemWithId" }, // 4284249546
		{ &Z_Construct_UFunction_UGameFuseUser_SetAttribute, "SetAttribute" }, // 1146801940
		{ &Z_Construct_UFunction_UGameFuseUser_SetCredits, "SetCredits" }, // 2746509091
		{ &Z_Construct_UFunction_UGameFuseUser_SetScore, "SetScore" }, // 2667271554
		{ &Z_Construct_UFunction_UGameFuseUser_SignIn, "SignIn" }, // 2670250306
		{ &Z_Construct_UFunction_UGameFuseUser_SignUp, "SignUp" }, // 2817305122
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseUser_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GameFuseUser.h" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGameFuseUser_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameFuseUser>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameFuseUser_Statics::ClassParams = {
		&UGameFuseUser::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGameFuseUser_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseUser_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGameFuseUser()
	{
		if (!Z_Registration_Info_UClass_UGameFuseUser.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameFuseUser.OuterSingleton, Z_Construct_UClass_UGameFuseUser_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGameFuseUser.OuterSingleton;
	}
	template<> GAMEFUSE_API UClass* StaticClass<UGameFuseUser>()
	{
		return UGameFuseUser::StaticClass();
	}
	UGameFuseUser::UGameFuseUser() {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameFuseUser);
	UGameFuseUser::~UGameFuseUser() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameFuseUser, UGameFuseUser::StaticClass, TEXT("UGameFuseUser"), &Z_Registration_Info_UClass_UGameFuseUser, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameFuseUser), 706418481U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_1620091232(TEXT("/Script/GameFuse"),
		Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
