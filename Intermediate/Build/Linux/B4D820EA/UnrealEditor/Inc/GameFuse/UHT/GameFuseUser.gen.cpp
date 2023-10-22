// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameFuse/Public/GameFuseUser.h"
#include "Engine/Classes/Engine/GameInstance.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameFuseUser() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UGameInstanceSubsystem();
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
		{ "Comment", "/**\n * \n */" },
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
	DEFINE_FUNCTION(UGameFuseUser::execDownloadPurchaseStoreItems)
	{
		P_GET_UBOOL(Z_Param_bChainedFromLogin);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DownloadPurchaseStoreItems(Z_Param_bChainedFromLogin,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execDownloadAttributes)
	{
		P_GET_UBOOL(Z_Param_bChainedFromLogin);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->DownloadAttributes(Z_Param_bChainedFromLogin,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execGetLeaderboard)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_Limit);
		P_GET_UBOOL(Z_Param_OnePerUser);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->GetLeaderboard(Z_Param_Limit,Z_Param_OnePerUser,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execAddLeaderboardEntry)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_LeaderboardName);
		P_GET_PROPERTY(FIntProperty,Z_Param_OurScore);
		P_GET_TMAP(FString,FString,Z_Param_ExtraAttributes);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->AddLeaderboardEntry(Z_Param_LeaderboardName,Z_Param_OurScore,Z_Param_ExtraAttributes,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execRemoveStoreItem)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_StoreItemId);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->RemoveStoreItem(Z_Param_StoreItemId,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execPurchaseStoreItem)
	{
		P_GET_PROPERTY(FIntProperty,Z_Param_StoreItemId);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		P_THIS->PurchaseStoreItem(Z_Param_StoreItemId,FUserCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseUser::execGetPurchasedStoreItems)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UGameFuseStoreItem*>*)Z_Param__Result=P_THIS->GetPurchasedStoreItems();
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
	DEFINE_FUNCTION(UGameFuseUser::execIsSignedIn)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(bool*)Z_Param__Result=P_THIS->IsSignedIn();
		P_NATIVE_END;
	}
	void UGameFuseUser::StaticRegisterNativesUGameFuseUser()
	{
		UClass* Class = UGameFuseUser::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "AddCredits", &UGameFuseUser::execAddCredits },
			{ "AddLeaderboardEntry", &UGameFuseUser::execAddLeaderboardEntry },
			{ "AddScore", &UGameFuseUser::execAddScore },
			{ "DownloadAttributes", &UGameFuseUser::execDownloadAttributes },
			{ "DownloadPurchaseStoreItems", &UGameFuseUser::execDownloadPurchaseStoreItems },
			{ "GetAttributes", &UGameFuseUser::execGetAttributes },
			{ "GetAttributesKeys", &UGameFuseUser::execGetAttributesKeys },
			{ "GetAttributeValue", &UGameFuseUser::execGetAttributeValue },
			{ "GetCredits", &UGameFuseUser::execGetCredits },
			{ "GetLastLogin", &UGameFuseUser::execGetLastLogin },
			{ "GetLeaderboard", &UGameFuseUser::execGetLeaderboard },
			{ "GetNumberOfLogins", &UGameFuseUser::execGetNumberOfLogins },
			{ "GetPurchasedStoreItems", &UGameFuseUser::execGetPurchasedStoreItems },
			{ "GetScore", &UGameFuseUser::execGetScore },
			{ "GetUsername", &UGameFuseUser::execGetUsername },
			{ "IsSignedIn", &UGameFuseUser::execIsSignedIn },
			{ "PurchaseStoreItem", &UGameFuseUser::execPurchaseStoreItem },
			{ "RemoveAttribute", &UGameFuseUser::execRemoveAttribute },
			{ "RemoveStoreItem", &UGameFuseUser::execRemoveStoreItem },
			{ "SetAttribute", &UGameFuseUser::execSetAttribute },
			{ "SetCredits", &UGameFuseUser::execSetCredits },
			{ "SetScore", &UGameFuseUser::execSetScore },
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
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddCredits_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3984834726
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::NewProp_AddCredits,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_AddCredits_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
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
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ExtraAttributes_MetaData[];
#endif
		static const UECodeGen_Private::FMapPropertyParams NewProp_ExtraAttributes;
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_LeaderboardName = { "LeaderboardName", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddLeaderboardEntry_Parms, LeaderboardName), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_LeaderboardName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_LeaderboardName_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_OurScore_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_OurScore = { "OurScore", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddLeaderboardEntry_Parms, OurScore), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_OurScore_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_OurScore_MetaData)) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_ExtraAttributes_ValueProp = { "ExtraAttributes", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 1, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_ExtraAttributes_Key_KeyProp = { "ExtraAttributes_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_ExtraAttributes_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_ExtraAttributes = { "ExtraAttributes", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddLeaderboardEntry_Parms, ExtraAttributes), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_ExtraAttributes_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_ExtraAttributes_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddLeaderboardEntry_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3984834726
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_LeaderboardName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_OurScore,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_ExtraAttributes_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_ExtraAttributes_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry_Statics::NewProp_ExtraAttributes,
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
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_AddScore_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventAddScore_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3984834726
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
	struct Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics
	{
		struct GameFuseUser_eventDownloadAttributes_Parms
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
	void Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::NewProp_bChainedFromLogin_SetBit(void* Obj)
	{
		((GameFuseUser_eventDownloadAttributes_Parms*)Obj)->bChainedFromLogin = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::NewProp_bChainedFromLogin = { "bChainedFromLogin", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(GameFuseUser_eventDownloadAttributes_Parms), &Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::NewProp_bChainedFromLogin_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventDownloadAttributes_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3984834726
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::NewProp_bChainedFromLogin,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "DownloadAttributes", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::GameFuseUser_eventDownloadAttributes_Parms), Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_DownloadAttributes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_DownloadAttributes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics
	{
		struct GameFuseUser_eventDownloadPurchaseStoreItems_Parms
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
	void Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::NewProp_bChainedFromLogin_SetBit(void* Obj)
	{
		((GameFuseUser_eventDownloadPurchaseStoreItems_Parms*)Obj)->bChainedFromLogin = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::NewProp_bChainedFromLogin = { "bChainedFromLogin", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(GameFuseUser_eventDownloadPurchaseStoreItems_Parms), &Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::NewProp_bChainedFromLogin_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventDownloadPurchaseStoreItems_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3984834726
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::NewProp_bChainedFromLogin,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "DownloadPurchaseStoreItems", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::GameFuseUser_eventDownloadPurchaseStoreItems_Parms), Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems_Statics::FuncParams);
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
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetAttributesKeys", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::GameFuseUser_eventGetAttributesKeys_Parms), Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys_Statics::Function_MetaDataParams)) };
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
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetAttributeValue", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::GameFuseUser_eventGetAttributeValue_Parms), Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetAttributeValue_Statics::Function_MetaDataParams)) };
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
	struct Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics
	{
		struct GameFuseUser_eventGetLeaderboard_Parms
		{
			int32 Limit;
			bool OnePerUser;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Limit_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_Limit;
		static void NewProp_OnePerUser_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_OnePerUser;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::NewProp_Limit_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::NewProp_Limit = { "Limit", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventGetLeaderboard_Parms, Limit), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::NewProp_Limit_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::NewProp_Limit_MetaData)) };
	void Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::NewProp_OnePerUser_SetBit(void* Obj)
	{
		((GameFuseUser_eventGetLeaderboard_Parms*)Obj)->OnePerUser = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::NewProp_OnePerUser = { "OnePerUser", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(GameFuseUser_eventGetLeaderboard_Parms), &Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::NewProp_OnePerUser_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventGetLeaderboard_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3984834726
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::NewProp_Limit,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::NewProp_OnePerUser,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|User" },
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetLeaderboard", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::GameFuseUser_eventGetLeaderboard_Parms), Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseUser_GetLeaderboard()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseUser_GetLeaderboard_Statics::FuncParams);
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
		{ "ModuleRelativePath", "Public/GameFuseUser.h" },
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
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseUser, nullptr, "GetPurchasedStoreItems", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::GameFuseUser_eventGetPurchasedStoreItems_Parms), Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems_Statics::Function_MetaDataParams)) };
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
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::NewProp_StoreItemId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::NewProp_StoreItemId = { "StoreItemId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventPurchaseStoreItem_Parms, StoreItemId), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::NewProp_StoreItemId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::NewProp_StoreItemId_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventPurchaseStoreItem_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3984834726
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem_Statics::NewProp_StoreItemId,
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::NewProp_SetKey = { "SetKey", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventRemoveAttribute_Parms, SetKey), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::NewProp_SetKey_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::NewProp_SetKey_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_RemoveAttribute_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventRemoveAttribute_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3984834726
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
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::NewProp_StoreItemId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::NewProp_StoreItemId = { "StoreItemId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventRemoveStoreItem_Parms, StoreItemId), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::NewProp_StoreItemId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::NewProp_StoreItemId_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventRemoveStoreItem_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3984834726
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem_Statics::NewProp_StoreItemId,
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetKey = { "SetKey", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSetAttribute_Parms, SetKey), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetKey_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetKey_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetValue = { "SetValue", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSetAttribute_Parms, SetValue), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_SetValue_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_SetAttribute_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSetAttribute_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3984834726
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
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_SetCredits_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSetCredits_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3984834726
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
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseUser_SetScore_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseUser_eventSetScore_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3984834726
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
		{ &Z_Construct_UFunction_UGameFuseUser_AddCredits, "AddCredits" }, // 573850645
		{ &Z_Construct_UFunction_UGameFuseUser_AddLeaderboardEntry, "AddLeaderboardEntry" }, // 1462898267
		{ &Z_Construct_UFunction_UGameFuseUser_AddScore, "AddScore" }, // 64722292
		{ &Z_Construct_UFunction_UGameFuseUser_DownloadAttributes, "DownloadAttributes" }, // 1246951983
		{ &Z_Construct_UFunction_UGameFuseUser_DownloadPurchaseStoreItems, "DownloadPurchaseStoreItems" }, // 4115978435
		{ &Z_Construct_UFunction_UGameFuseUser_GetAttributes, "GetAttributes" }, // 2331468312
		{ &Z_Construct_UFunction_UGameFuseUser_GetAttributesKeys, "GetAttributesKeys" }, // 576053237
		{ &Z_Construct_UFunction_UGameFuseUser_GetAttributeValue, "GetAttributeValue" }, // 1966803216
		{ &Z_Construct_UFunction_UGameFuseUser_GetCredits, "GetCredits" }, // 735744228
		{ &Z_Construct_UFunction_UGameFuseUser_GetLastLogin, "GetLastLogin" }, // 2634675336
		{ &Z_Construct_UFunction_UGameFuseUser_GetLeaderboard, "GetLeaderboard" }, // 981821585
		{ &Z_Construct_UFunction_UGameFuseUser_GetNumberOfLogins, "GetNumberOfLogins" }, // 2271225899
		{ &Z_Construct_UFunction_UGameFuseUser_GetPurchasedStoreItems, "GetPurchasedStoreItems" }, // 706773379
		{ &Z_Construct_UFunction_UGameFuseUser_GetScore, "GetScore" }, // 2903990249
		{ &Z_Construct_UFunction_UGameFuseUser_GetUsername, "GetUsername" }, // 1739003403
		{ &Z_Construct_UFunction_UGameFuseUser_IsSignedIn, "IsSignedIn" }, // 2035348427
		{ &Z_Construct_UFunction_UGameFuseUser_PurchaseStoreItem, "PurchaseStoreItem" }, // 4043728593
		{ &Z_Construct_UFunction_UGameFuseUser_RemoveAttribute, "RemoveAttribute" }, // 4234902772
		{ &Z_Construct_UFunction_UGameFuseUser_RemoveStoreItem, "RemoveStoreItem" }, // 134199549
		{ &Z_Construct_UFunction_UGameFuseUser_SetAttribute, "SetAttribute" }, // 2416717839
		{ &Z_Construct_UFunction_UGameFuseUser_SetCredits, "SetCredits" }, // 2733884127
		{ &Z_Construct_UFunction_UGameFuseUser_SetScore, "SetScore" }, // 1406374322
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseUser_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IncludePath", "GameFuseUser.h" },
		{ "IsBlueprintBase", "true" },
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
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameFuseUser);
	UGameFuseUser::~UGameFuseUser() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameFuseUser, UGameFuseUser::StaticClass, TEXT("UGameFuseUser"), &Z_Registration_Info_UClass_UGameFuseUser, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameFuseUser), 1803963738U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_1844102677(TEXT("/Script/GameFuse"),
		Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
