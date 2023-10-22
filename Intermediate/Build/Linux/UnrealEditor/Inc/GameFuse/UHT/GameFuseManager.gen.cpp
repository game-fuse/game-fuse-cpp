// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameFuse/Public/GameFuseManager.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameFuseManager() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseLeaderboardEntry_NoRegister();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseManager();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseManager_NoRegister();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseStoreItem_NoRegister();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseUser_NoRegister();
	GAMEFUSE_API UFunction* Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature();
	UPackage* Z_Construct_UPackage__Script_GameFuse();
// End Cross Module References
	struct Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics
	{
		struct _Script_GameFuse_eventManagerCallback_Parms
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
	void Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::NewProp_bSuccess_SetBit(void* Obj)
	{
		((_Script_GameFuse_eventManagerCallback_Parms*)Obj)->bSuccess = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::NewProp_bSuccess = { "bSuccess", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(_Script_GameFuse_eventManagerCallback_Parms), &Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::NewProp_bSuccess_SetBit, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::NewProp_Response_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::NewProp_Response = { "Response", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(_Script_GameFuse_eventManagerCallback_Parms, Response), METADATA_PARAMS(Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::NewProp_Response_MetaData, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::NewProp_Response_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::NewProp_bSuccess,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::NewProp_Response,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::Function_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::FuncParams = { (UObject*(*)())Z_Construct_UPackage__Script_GameFuse, nullptr, "ManagerCallback__DelegateSignature", nullptr, nullptr, sizeof(Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::_Script_GameFuse_eventManagerCallback_Parms), Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00120000, 0, 0, METADATA_PARAMS(Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature_Statics::FuncParams);
		}
		return ReturnFunction;
	}
void FManagerCallback_DelegateWrapper(const FScriptDelegate& ManagerCallback, bool bSuccess, const FString& Response)
{
	struct _Script_GameFuse_eventManagerCallback_Parms
	{
		bool bSuccess;
		FString Response;
	};
	_Script_GameFuse_eventManagerCallback_Parms Parms;
	Parms.bSuccess=bSuccess ? true : false;
	Parms.Response=Response;
	ManagerCallback.ProcessDelegate<UObject>(&Parms);
}
	DEFINE_FUNCTION(UGameFuseManager::execFetchStoreItems)
	{
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGameFuseManager::FetchStoreItems(FManagerCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execFetchLeaderboardEntries)
	{
		P_GET_OBJECT(UGameFuseUser,Z_Param_GameFuseUser);
		P_GET_PROPERTY(FIntProperty,Z_Param_Limit);
		P_GET_UBOOL(Z_Param_bOnePerUser);
		P_GET_PROPERTY(FStrProperty,Z_Param_LeaderboardName);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGameFuseManager::FetchLeaderboardEntries(Z_Param_GameFuseUser,Z_Param_Limit,Z_Param_bOnePerUser,Z_Param_LeaderboardName,FManagerCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execFetchGameVariables)
	{
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGameFuseManager::FetchGameVariables(FManagerCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execSendPasswordResetEmail)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_Email);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGameFuseManager::SendPasswordResetEmail(Z_Param_Email,FManagerCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execGetLeaderboard)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UGameFuseLeaderboardEntry*>*)Z_Param__Result=UGameFuseManager::GetLeaderboard();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execGetGameStoreItems)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UGameFuseStoreItem*>*)Z_Param__Result=UGameFuseManager::GetGameStoreItems();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execGetGameVariables)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TMap<FString,FString>*)Z_Param__Result=UGameFuseManager::GetGameVariables();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execGetBaseURL)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=UGameFuseManager::GetBaseURL();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execGetGameToken)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=UGameFuseManager::GetGameToken();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execGetGameDescription)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=UGameFuseManager::GetGameDescription();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execGetGameName)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=UGameFuseManager::GetGameName();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execGetGameId)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=UGameFuseManager::GetGameId();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execSetUpGame)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_InGameId);
		P_GET_PROPERTY(FStrProperty,Z_Param_InToken);
		P_GET_UBOOL(Z_Param_bSeedStore);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGameFuseManager::SetUpGame(Z_Param_InGameId,Z_Param_InToken,Z_Param_bSeedStore,FManagerCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	void UGameFuseManager::StaticRegisterNativesUGameFuseManager()
	{
		UClass* Class = UGameFuseManager::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "FetchGameVariables", &UGameFuseManager::execFetchGameVariables },
			{ "FetchLeaderboardEntries", &UGameFuseManager::execFetchLeaderboardEntries },
			{ "FetchStoreItems", &UGameFuseManager::execFetchStoreItems },
			{ "GetBaseURL", &UGameFuseManager::execGetBaseURL },
			{ "GetGameDescription", &UGameFuseManager::execGetGameDescription },
			{ "GetGameId", &UGameFuseManager::execGetGameId },
			{ "GetGameName", &UGameFuseManager::execGetGameName },
			{ "GetGameStoreItems", &UGameFuseManager::execGetGameStoreItems },
			{ "GetGameToken", &UGameFuseManager::execGetGameToken },
			{ "GetGameVariables", &UGameFuseManager::execGetGameVariables },
			{ "GetLeaderboard", &UGameFuseManager::execGetLeaderboard },
			{ "SendPasswordResetEmail", &UGameFuseManager::execSendPasswordResetEmail },
			{ "SetUpGame", &UGameFuseManager::execSetUpGame },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGameFuseManager_FetchGameVariables_Statics
	{
		struct GameFuseManager_eventFetchGameVariables_Parms
		{
			FScriptDelegate CompletionCallback;
		};
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseManager_FetchGameVariables_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventFetchGameVariables_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3598800245
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_FetchGameVariables_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_FetchGameVariables_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_FetchGameVariables_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_FetchGameVariables_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "FetchGameVariables", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_FetchGameVariables_Statics::GameFuseManager_eventFetchGameVariables_Parms), Z_Construct_UFunction_UGameFuseManager_FetchGameVariables_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_FetchGameVariables_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_FetchGameVariables_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_FetchGameVariables_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_FetchGameVariables()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_FetchGameVariables_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics
	{
		struct GameFuseManager_eventFetchLeaderboardEntries_Parms
		{
			UGameFuseUser* GameFuseUser;
			int32 Limit;
			bool bOnePerUser;
			FString LeaderboardName;
			FScriptDelegate CompletionCallback;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_GameFuseUser;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Limit_MetaData[];
#endif
		static const UECodeGen_Private::FUnsizedIntPropertyParams NewProp_Limit;
		static void NewProp_bOnePerUser_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bOnePerUser;
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
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_GameFuseUser = { "GameFuseUser", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventFetchLeaderboardEntries_Parms, GameFuseUser), Z_Construct_UClass_UGameFuseUser_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_Limit_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FUnsizedIntPropertyParams Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_Limit = { "Limit", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventFetchLeaderboardEntries_Parms, Limit), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_Limit_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_Limit_MetaData)) };
	void Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_bOnePerUser_SetBit(void* Obj)
	{
		((GameFuseManager_eventFetchLeaderboardEntries_Parms*)Obj)->bOnePerUser = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_bOnePerUser = { "bOnePerUser", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(GameFuseManager_eventFetchLeaderboardEntries_Parms), &Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_bOnePerUser_SetBit, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_LeaderboardName_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_LeaderboardName = { "LeaderboardName", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventFetchLeaderboardEntries_Parms, LeaderboardName), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_LeaderboardName_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_LeaderboardName_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventFetchLeaderboardEntries_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3598800245
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_GameFuseUser,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_Limit,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_bOnePerUser,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_LeaderboardName,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "FetchLeaderboardEntries", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::GameFuseManager_eventFetchLeaderboardEntries_Parms), Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_FetchStoreItems_Statics
	{
		struct GameFuseManager_eventFetchStoreItems_Parms
		{
			FScriptDelegate CompletionCallback;
		};
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseManager_FetchStoreItems_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventFetchStoreItems_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3598800245
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_FetchStoreItems_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_FetchStoreItems_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_FetchStoreItems_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_FetchStoreItems_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "FetchStoreItems", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_FetchStoreItems_Statics::GameFuseManager_eventFetchStoreItems_Parms), Z_Construct_UFunction_UGameFuseManager_FetchStoreItems_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_FetchStoreItems_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_FetchStoreItems_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_FetchStoreItems_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_FetchStoreItems()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_FetchStoreItems_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_GetBaseURL_Statics
	{
		struct GameFuseManager_eventGetBaseURL_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_GetBaseURL_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventGetBaseURL_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_GetBaseURL_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetBaseURL_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_GetBaseURL_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_GetBaseURL_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "GetBaseURL", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_GetBaseURL_Statics::GameFuseManager_eventGetBaseURL_Parms), Z_Construct_UFunction_UGameFuseManager_GetBaseURL_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetBaseURL_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_GetBaseURL_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetBaseURL_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_GetBaseURL()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_GetBaseURL_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_GetGameDescription_Statics
	{
		struct GameFuseManager_eventGetGameDescription_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_GetGameDescription_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventGetGameDescription_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_GetGameDescription_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetGameDescription_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_GetGameDescription_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_GetGameDescription_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "GetGameDescription", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_GetGameDescription_Statics::GameFuseManager_eventGetGameDescription_Parms), Z_Construct_UFunction_UGameFuseManager_GetGameDescription_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameDescription_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_GetGameDescription_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameDescription_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_GetGameDescription()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_GetGameDescription_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics
	{
		struct GameFuseManager_eventGetGameId_Parms
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
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventGetGameId_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "Comment", "//> Getters\n" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
		{ "ToolTip", "> Getters" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "GetGameId", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::GameFuseManager_eventGetGameId_Parms), Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_GetGameId()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_GetGameName_Statics
	{
		struct GameFuseManager_eventGetGameName_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_GetGameName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventGetGameName_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_GetGameName_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetGameName_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_GetGameName_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_GetGameName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "GetGameName", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_GetGameName_Statics::GameFuseManager_eventGetGameName_Parms), Z_Construct_UFunction_UGameFuseManager_GetGameName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_GetGameName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_GetGameName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_GetGameName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics
	{
		struct GameFuseManager_eventGetGameStoreItems_Parms
		{
			TArray<UGameFuseStoreItem*> ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UGameFuseStoreItem_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventGetGameStoreItems_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::NewProp_ReturnValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::NewProp_ReturnValue_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "GetGameStoreItems", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::GameFuseManager_eventGetGameStoreItems_Parms), Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_GetGameToken_Statics
	{
		struct GameFuseManager_eventGetGameToken_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_GetGameToken_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventGetGameToken_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_GetGameToken_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetGameToken_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_GetGameToken_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_GetGameToken_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "GetGameToken", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_GetGameToken_Statics::GameFuseManager_eventGetGameToken_Parms), Z_Construct_UFunction_UGameFuseManager_GetGameToken_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameToken_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_GetGameToken_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameToken_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_GetGameToken()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_GetGameToken_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics
	{
		struct GameFuseManager_eventGetGameVariables_Parms
		{
			TMap<FString,FString> ReturnValue;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_ValueProp;
		static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue_Key_KeyProp;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[];
#endif
		static const UECodeGen_Private::FMapPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::NewProp_ReturnValue_ValueProp = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 1, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::NewProp_ReturnValue_Key_KeyProp = { "ReturnValue_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FMapPropertyParams Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventGetGameVariables_Parms, ReturnValue), EMapPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::NewProp_ReturnValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::NewProp_ReturnValue_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::NewProp_ReturnValue_ValueProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::NewProp_ReturnValue_Key_KeyProp,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "GetGameVariables", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::GameFuseManager_eventGetGameVariables_Parms), Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_GetGameVariables()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_GetGameVariables_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics
	{
		struct GameFuseManager_eventGetLeaderboard_Parms
		{
			TArray<UGameFuseLeaderboardEntry*> ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue_Inner;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_ReturnValue_MetaData[];
#endif
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UGameFuseLeaderboardEntry_NoRegister, METADATA_PARAMS(nullptr, 0) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::NewProp_ReturnValue_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000008000582, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventGetLeaderboard_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::NewProp_ReturnValue_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::NewProp_ReturnValue_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::NewProp_ReturnValue_Inner,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "GetLeaderboard", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::GameFuseManager_eventGetLeaderboard_Parms), Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_GetLeaderboard()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_GetLeaderboard_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics
	{
		struct GameFuseManager_eventSendPasswordResetEmail_Parms
		{
			FString Email;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Email_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Email;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::NewProp_Email_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::NewProp_Email = { "Email", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSendPasswordResetEmail_Parms, Email), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::NewProp_Email_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::NewProp_Email_MetaData)) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSendPasswordResetEmail_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3598800245
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::NewProp_Email,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "Comment", "//> Action Requests\n" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
		{ "ToolTip", "> Action Requests" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "SendPasswordResetEmail", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::GameFuseManager_eventSendPasswordResetEmail_Parms), Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics
	{
		struct GameFuseManager_eventSetUpGame_Parms
		{
			FString InGameId;
			FString InToken;
			bool bSeedStore;
			FScriptDelegate CompletionCallback;
		};
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InGameId_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InGameId;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_InToken_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_InToken;
		static void NewProp_bSeedStore_SetBit(void* Obj);
		static const UECodeGen_Private::FBoolPropertyParams NewProp_bSeedStore;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_InGameId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_InGameId = { "InGameId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSetUpGame_Parms, InGameId), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_InGameId_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_InGameId_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_InToken_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_InToken = { "InToken", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSetUpGame_Parms, InToken), METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_InToken_MetaData, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_InToken_MetaData)) };
	void Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_bSeedStore_SetBit(void* Obj)
	{
		((GameFuseManager_eventSetUpGame_Parms*)Obj)->bSeedStore = 1;
	}
	const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_bSeedStore = { "bSeedStore", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, sizeof(bool), sizeof(GameFuseManager_eventSetUpGame_Parms), &Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_bSeedStore_SetBit, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSetUpGame_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3598800245
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_InGameId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_InToken,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_bSeedStore,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "Comment", "//> GameSetup\n" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
		{ "ToolTip", "> GameSetup" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "SetUpGame", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::GameFuseManager_eventSetUpGame_Parms), Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_SetUpGame()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGameFuseManager);
	UClass* Z_Construct_UClass_UGameFuseManager_NoRegister()
	{
		return UGameFuseManager::StaticClass();
	}
	struct Z_Construct_UClass_UGameFuseManager_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGameFuseManager_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_GameFuse,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGameFuseManager_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGameFuseManager_FetchGameVariables, "FetchGameVariables" }, // 1006502824
		{ &Z_Construct_UFunction_UGameFuseManager_FetchLeaderboardEntries, "FetchLeaderboardEntries" }, // 1531265257
		{ &Z_Construct_UFunction_UGameFuseManager_FetchStoreItems, "FetchStoreItems" }, // 1149616511
		{ &Z_Construct_UFunction_UGameFuseManager_GetBaseURL, "GetBaseURL" }, // 1448150899
		{ &Z_Construct_UFunction_UGameFuseManager_GetGameDescription, "GetGameDescription" }, // 3367142294
		{ &Z_Construct_UFunction_UGameFuseManager_GetGameId, "GetGameId" }, // 362427455
		{ &Z_Construct_UFunction_UGameFuseManager_GetGameName, "GetGameName" }, // 1663925133
		{ &Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems, "GetGameStoreItems" }, // 1059972680
		{ &Z_Construct_UFunction_UGameFuseManager_GetGameToken, "GetGameToken" }, // 2100794383
		{ &Z_Construct_UFunction_UGameFuseManager_GetGameVariables, "GetGameVariables" }, // 2416164690
		{ &Z_Construct_UFunction_UGameFuseManager_GetLeaderboard, "GetLeaderboard" }, // 3078013743
		{ &Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail, "SendPasswordResetEmail" }, // 1149951864
		{ &Z_Construct_UFunction_UGameFuseManager_SetUpGame, "SetUpGame" }, // 78592678
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseManager_Statics::Class_MetaDataParams[] = {
		{ "IncludePath", "GameFuseManager.h" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGameFuseManager_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameFuseManager>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameFuseManager_Statics::ClassParams = {
		&UGameFuseManager::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UGameFuseManager_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseManager_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGameFuseManager()
	{
		if (!Z_Registration_Info_UClass_UGameFuseManager.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameFuseManager.OuterSingleton, Z_Construct_UClass_UGameFuseManager_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGameFuseManager.OuterSingleton;
	}
	template<> GAMEFUSE_API UClass* StaticClass<UGameFuseManager>()
	{
		return UGameFuseManager::StaticClass();
	}
	UGameFuseManager::UGameFuseManager(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameFuseManager);
	UGameFuseManager::~UGameFuseManager() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameFuseManager, UGameFuseManager::StaticClass, TEXT("UGameFuseManager"), &Z_Registration_Info_UClass_UGameFuseManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameFuseManager), 839841340U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_131272584(TEXT("/Script/GameFuse"),
		Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
