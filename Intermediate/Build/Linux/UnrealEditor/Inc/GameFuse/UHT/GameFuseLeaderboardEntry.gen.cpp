// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameFuse/Public/GameFuseLeaderboardEntry.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameFuseLeaderboardEntry() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseLeaderboardEntry();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseLeaderboardEntry_NoRegister();
	UPackage* Z_Construct_UPackage__Script_GameFuse();
// End Cross Module References
	DEFINE_FUNCTION(UGameFuseLeaderboardEntry::execGetTimestamp)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetTimestamp();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseLeaderboardEntry::execGetExtraAttributes)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetExtraAttributes();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseLeaderboardEntry::execGetLeaderboardName)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetLeaderboardName();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseLeaderboardEntry::execGetScore)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetScore();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseLeaderboardEntry::execGetUsername)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetUsername();
		P_NATIVE_END;
	}
	void UGameFuseLeaderboardEntry::StaticRegisterNativesUGameFuseLeaderboardEntry()
	{
		UClass* Class = UGameFuseLeaderboardEntry::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetExtraAttributes", &UGameFuseLeaderboardEntry::execGetExtraAttributes },
			{ "GetLeaderboardName", &UGameFuseLeaderboardEntry::execGetLeaderboardName },
			{ "GetScore", &UGameFuseLeaderboardEntry::execGetScore },
			{ "GetTimestamp", &UGameFuseLeaderboardEntry::execGetTimestamp },
			{ "GetUsername", &UGameFuseLeaderboardEntry::execGetUsername },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes_Statics
	{
		struct GameFuseLeaderboardEntry_eventGetExtraAttributes_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseLeaderboardEntry_eventGetExtraAttributes_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseLeaderboardEntry.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseLeaderboardEntry, nullptr, "GetExtraAttributes", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes_Statics::GameFuseLeaderboardEntry_eventGetExtraAttributes_Parms), Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName_Statics
	{
		struct GameFuseLeaderboardEntry_eventGetLeaderboardName_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseLeaderboardEntry_eventGetLeaderboardName_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseLeaderboardEntry.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseLeaderboardEntry, nullptr, "GetLeaderboardName", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName_Statics::GameFuseLeaderboardEntry_eventGetLeaderboardName_Parms), Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore_Statics
	{
		struct GameFuseLeaderboardEntry_eventGetScore_Parms
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
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseLeaderboardEntry_eventGetScore_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseLeaderboardEntry.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseLeaderboardEntry, nullptr, "GetScore", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore_Statics::GameFuseLeaderboardEntry_eventGetScore_Parms), Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp_Statics
	{
		struct GameFuseLeaderboardEntry_eventGetTimestamp_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseLeaderboardEntry_eventGetTimestamp_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseLeaderboardEntry.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseLeaderboardEntry, nullptr, "GetTimestamp", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp_Statics::GameFuseLeaderboardEntry_eventGetTimestamp_Parms), Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername_Statics
	{
		struct GameFuseLeaderboardEntry_eventGetUsername_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseLeaderboardEntry_eventGetUsername_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseLeaderboardEntry.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseLeaderboardEntry, nullptr, "GetUsername", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername_Statics::GameFuseLeaderboardEntry_eventGetUsername_Parms), Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGameFuseLeaderboardEntry);
	UClass* Z_Construct_UClass_UGameFuseLeaderboardEntry_NoRegister()
	{
		return UGameFuseLeaderboardEntry::StaticClass();
	}
	struct Z_Construct_UClass_UGameFuseLeaderboardEntry_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGameFuseLeaderboardEntry_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_GameFuse,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGameFuseLeaderboardEntry_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetExtraAttributes, "GetExtraAttributes" }, // 550409053
		{ &Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetLeaderboardName, "GetLeaderboardName" }, // 400526235
		{ &Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetScore, "GetScore" }, // 2747335720
		{ &Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetTimestamp, "GetTimestamp" }, // 598927734
		{ &Z_Construct_UFunction_UGameFuseLeaderboardEntry_GetUsername, "GetUsername" }, // 3385964450
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseLeaderboardEntry_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "GameFuseLeaderboardEntry.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/GameFuseLeaderboardEntry.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGameFuseLeaderboardEntry_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameFuseLeaderboardEntry>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameFuseLeaderboardEntry_Statics::ClassParams = {
		&UGameFuseLeaderboardEntry::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UGameFuseLeaderboardEntry_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseLeaderboardEntry_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGameFuseLeaderboardEntry()
	{
		if (!Z_Registration_Info_UClass_UGameFuseLeaderboardEntry.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameFuseLeaderboardEntry.OuterSingleton, Z_Construct_UClass_UGameFuseLeaderboardEntry_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGameFuseLeaderboardEntry.OuterSingleton;
	}
	template<> GAMEFUSE_API UClass* StaticClass<UGameFuseLeaderboardEntry>()
	{
		return UGameFuseLeaderboardEntry::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameFuseLeaderboardEntry);
	UGameFuseLeaderboardEntry::~UGameFuseLeaderboardEntry() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseLeaderboardEntry_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseLeaderboardEntry_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameFuseLeaderboardEntry, UGameFuseLeaderboardEntry::StaticClass, TEXT("UGameFuseLeaderboardEntry"), &Z_Registration_Info_UClass_UGameFuseLeaderboardEntry, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameFuseLeaderboardEntry), 2203802685U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseLeaderboardEntry_h_461279981(TEXT("/Script/GameFuse"),
		Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseLeaderboardEntry_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseLeaderboardEntry_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
