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
	DEFINE_FUNCTION(UGameFuseManager::execGetGameFuseUserInstance)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(UGameFuseUser**)Z_Param__Result=UGameFuseManager::GetGameFuseUserInstance();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execDownloadStoreItems)
	{
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGameFuseManager::DownloadStoreItems(FManagerCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execSendPasswordResetEmail)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_email);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGameFuseManager::SendPasswordResetEmail(Z_Param_email,FManagerCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execSignIn)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_email);
		P_GET_PROPERTY(FStrProperty,Z_Param_password);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGameFuseManager::SignIn(Z_Param_email,Z_Param_password,FManagerCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execSignUp)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_email);
		P_GET_PROPERTY(FStrProperty,Z_Param_password);
		P_GET_PROPERTY(FStrProperty,Z_Param_password_confirmation);
		P_GET_PROPERTY(FStrProperty,Z_Param_username);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGameFuseManager::SignUp(Z_Param_email,Z_Param_password,Z_Param_password_confirmation,Z_Param_username,FManagerCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execGetGameStoreItems)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(TArray<UGameFuseStoreItem*>*)Z_Param__Result=UGameFuseManager::GetGameStoreItems();
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
		*(FString*)Z_Param__Result=UGameFuseManager::GetGameId();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseManager::execSetUpGame)
	{
		P_GET_PROPERTY(FStrProperty,Z_Param_gameId);
		P_GET_PROPERTY(FStrProperty,Z_Param_token);
		P_GET_PROPERTY(FDelegateProperty,Z_Param_CompletionCallback);
		P_FINISH;
		P_NATIVE_BEGIN;
		UGameFuseManager::SetUpGame(Z_Param_gameId,Z_Param_token,FManagerCallback(Z_Param_CompletionCallback));
		P_NATIVE_END;
	}
	void UGameFuseManager::StaticRegisterNativesUGameFuseManager()
	{
		UClass* Class = UGameFuseManager::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "DownloadStoreItems", &UGameFuseManager::execDownloadStoreItems },
			{ "GetGameDescription", &UGameFuseManager::execGetGameDescription },
			{ "GetGameFuseUserInstance", &UGameFuseManager::execGetGameFuseUserInstance },
			{ "GetGameId", &UGameFuseManager::execGetGameId },
			{ "GetGameName", &UGameFuseManager::execGetGameName },
			{ "GetGameStoreItems", &UGameFuseManager::execGetGameStoreItems },
			{ "SendPasswordResetEmail", &UGameFuseManager::execSendPasswordResetEmail },
			{ "SetUpGame", &UGameFuseManager::execSetUpGame },
			{ "SignIn", &UGameFuseManager::execSignIn },
			{ "SignUp", &UGameFuseManager::execSignUp },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems_Statics
	{
		struct GameFuseManager_eventDownloadStoreItems_Parms
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
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventDownloadStoreItems_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3598800245
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "DownloadStoreItems", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems_Statics::GameFuseManager_eventDownloadStoreItems_Parms), Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems_Statics::FuncParams);
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
	struct Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance_Statics
	{
		struct GameFuseManager_eventGetGameFuseUserInstance_Parms
		{
			UGameFuseUser* ReturnValue;
		};
		static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventGetGameFuseUserInstance_Parms, ReturnValue), Z_Construct_UClass_UGameFuseUser_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "GetGameFuseUserInstance", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance_Statics::GameFuseManager_eventGetGameFuseUserInstance_Parms), Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics
	{
		struct GameFuseManager_eventGetGameId_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventGetGameId_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_GetGameId_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
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
		static const UECodeGen_Private::FArrayPropertyParams NewProp_ReturnValue;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::NewProp_ReturnValue_Inner = { "ReturnValue", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, 0, Z_Construct_UClass_UGameFuseStoreItem_NoRegister, METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventGetGameStoreItems_Parms, ReturnValue), EArrayPropertyFlags::None, METADATA_PARAMS(nullptr, 0) };
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
	struct Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics
	{
		struct GameFuseManager_eventSendPasswordResetEmail_Parms
		{
			FString email;
			FScriptDelegate CompletionCallback;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_email;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::NewProp_email = { "email", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSendPasswordResetEmail_Parms, email), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSendPasswordResetEmail_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3598800245
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::NewProp_email,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
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
			FString gameId;
			FString token;
			FScriptDelegate CompletionCallback;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_gameId;
		static const UECodeGen_Private::FStrPropertyParams NewProp_token;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_gameId = { "gameId", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSetUpGame_Parms, gameId), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_token = { "token", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSetUpGame_Parms, token), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSetUpGame_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3598800245
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_gameId,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_token,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_SetUpGame_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
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
	struct Z_Construct_UFunction_UGameFuseManager_SignIn_Statics
	{
		struct GameFuseManager_eventSignIn_Parms
		{
			FString email;
			FString password;
			FScriptDelegate CompletionCallback;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_email;
		static const UECodeGen_Private::FStrPropertyParams NewProp_password;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::NewProp_email = { "email", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSignIn_Parms, email), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::NewProp_password = { "password", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSignIn_Parms, password), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSignIn_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3598800245
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::NewProp_email,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::NewProp_password,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "SignIn", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::GameFuseManager_eventSignIn_Parms), Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_SignIn()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_SignIn_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseManager_SignUp_Statics
	{
		struct GameFuseManager_eventSignUp_Parms
		{
			FString email;
			FString password;
			FString password_confirmation;
			FString username;
			FScriptDelegate CompletionCallback;
		};
		static const UECodeGen_Private::FStrPropertyParams NewProp_email;
		static const UECodeGen_Private::FStrPropertyParams NewProp_password;
		static const UECodeGen_Private::FStrPropertyParams NewProp_password_confirmation;
		static const UECodeGen_Private::FStrPropertyParams NewProp_username;
		static const UECodeGen_Private::FDelegatePropertyParams NewProp_CompletionCallback;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[];
#endif
		static const UECodeGen_Private::FFunctionParams FuncParams;
	};
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::NewProp_email = { "email", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSignUp_Parms, email), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::NewProp_password = { "password", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSignUp_Parms, password), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::NewProp_password_confirmation = { "password_confirmation", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSignUp_Parms, password_confirmation), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::NewProp_username = { "username", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSignUp_Parms, username), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FDelegatePropertyParams Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::NewProp_CompletionCallback = { "CompletionCallback", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Delegate, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseManager_eventSignUp_Parms, CompletionCallback), Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature, METADATA_PARAMS(nullptr, 0) }; // 3598800245
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::NewProp_email,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::NewProp_password,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::NewProp_password_confirmation,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::NewProp_username,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::NewProp_CompletionCallback,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse" },
		{ "ModuleRelativePath", "Public/GameFuseManager.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseManager, nullptr, "SignUp", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::GameFuseManager_eventSignUp_Parms), Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseManager_SignUp()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseManager_SignUp_Statics::FuncParams);
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
		{ &Z_Construct_UFunction_UGameFuseManager_DownloadStoreItems, "DownloadStoreItems" }, // 644704708
		{ &Z_Construct_UFunction_UGameFuseManager_GetGameDescription, "GetGameDescription" }, // 3367142294
		{ &Z_Construct_UFunction_UGameFuseManager_GetGameFuseUserInstance, "GetGameFuseUserInstance" }, // 264405527
		{ &Z_Construct_UFunction_UGameFuseManager_GetGameId, "GetGameId" }, // 1192683855
		{ &Z_Construct_UFunction_UGameFuseManager_GetGameName, "GetGameName" }, // 1663925133
		{ &Z_Construct_UFunction_UGameFuseManager_GetGameStoreItems, "GetGameStoreItems" }, // 2981482810
		{ &Z_Construct_UFunction_UGameFuseManager_SendPasswordResetEmail, "SendPasswordResetEmail" }, // 2742001394
		{ &Z_Construct_UFunction_UGameFuseManager_SetUpGame, "SetUpGame" }, // 2203805317
		{ &Z_Construct_UFunction_UGameFuseManager_SignIn, "SignIn" }, // 1819638887
		{ &Z_Construct_UFunction_UGameFuseManager_SignUp, "SignUp" }, // 3904347646
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
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameFuseManager);
	UGameFuseManager::~UGameFuseManager() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameFuseManager, UGameFuseManager::StaticClass, TEXT("UGameFuseManager"), &Z_Registration_Info_UClass_UGameFuseManager, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameFuseManager), 3433168015U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_4271469025(TEXT("/Script/GameFuse"),
		Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
