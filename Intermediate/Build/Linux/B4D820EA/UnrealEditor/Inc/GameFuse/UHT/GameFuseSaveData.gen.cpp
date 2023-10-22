// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameFuse/Public/GameFuseSaveData.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameFuseSaveData() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_USaveGame();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseSaveData();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseSaveData_NoRegister();
	UPackage* Z_Construct_UPackage__Script_GameFuse();
// End Cross Module References
	void UGameFuseSaveData::StaticRegisterNativesUGameFuseSaveData()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGameFuseSaveData);
	UClass* Z_Construct_UClass_UGameFuseSaveData_NoRegister()
	{
		return UGameFuseSaveData::StaticClass();
	}
	struct Z_Construct_UClass_UGameFuseSaveData_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_NumberOfLogins_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_NumberOfLogins;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_LastLogin_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_LastLogin;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_AuthenticationToken_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_AuthenticationToken;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Username_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Username;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Score_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Score;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Credits_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Credits;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Id_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Id;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGameFuseSaveData_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USaveGame,
		(UObject* (*)())Z_Construct_UPackage__Script_GameFuse,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseSaveData_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "GameFuseSaveData.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/GameFuseSaveData.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_NumberOfLogins_MetaData[] = {
		{ "Category", "GameFuseSaveData" },
		{ "ModuleRelativePath", "Public/GameFuseSaveData.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_NumberOfLogins = { "NumberOfLogins", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameFuseSaveData, NumberOfLogins), METADATA_PARAMS(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_NumberOfLogins_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_NumberOfLogins_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_LastLogin_MetaData[] = {
		{ "Category", "GameFuseSaveData" },
		{ "ModuleRelativePath", "Public/GameFuseSaveData.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_LastLogin = { "LastLogin", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameFuseSaveData, LastLogin), METADATA_PARAMS(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_LastLogin_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_LastLogin_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_AuthenticationToken_MetaData[] = {
		{ "Category", "GameFuseSaveData" },
		{ "ModuleRelativePath", "Public/GameFuseSaveData.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_AuthenticationToken = { "AuthenticationToken", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameFuseSaveData, AuthenticationToken), METADATA_PARAMS(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_AuthenticationToken_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_AuthenticationToken_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Username_MetaData[] = {
		{ "Category", "GameFuseSaveData" },
		{ "ModuleRelativePath", "Public/GameFuseSaveData.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Username = { "Username", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameFuseSaveData, Username), METADATA_PARAMS(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Username_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Username_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Score_MetaData[] = {
		{ "Category", "GameFuseSaveData" },
		{ "ModuleRelativePath", "Public/GameFuseSaveData.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Score = { "Score", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameFuseSaveData, Score), METADATA_PARAMS(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Score_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Score_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Credits_MetaData[] = {
		{ "Category", "GameFuseSaveData" },
		{ "ModuleRelativePath", "Public/GameFuseSaveData.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Credits = { "Credits", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameFuseSaveData, Credits), METADATA_PARAMS(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Credits_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Credits_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Id_MetaData[] = {
		{ "Category", "GameFuseSaveData" },
		{ "ModuleRelativePath", "Public/GameFuseSaveData.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameFuseSaveData, Id), METADATA_PARAMS(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Id_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Id_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGameFuseSaveData_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_NumberOfLogins,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_LastLogin,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_AuthenticationToken,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Username,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Score,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Credits,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameFuseSaveData_Statics::NewProp_Id,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGameFuseSaveData_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameFuseSaveData>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameFuseSaveData_Statics::ClassParams = {
		&UGameFuseSaveData::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		Z_Construct_UClass_UGameFuseSaveData_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseSaveData_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGameFuseSaveData_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseSaveData_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGameFuseSaveData()
	{
		if (!Z_Registration_Info_UClass_UGameFuseSaveData.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameFuseSaveData.OuterSingleton, Z_Construct_UClass_UGameFuseSaveData_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGameFuseSaveData.OuterSingleton;
	}
	template<> GAMEFUSE_API UClass* StaticClass<UGameFuseSaveData>()
	{
		return UGameFuseSaveData::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameFuseSaveData);
	UGameFuseSaveData::~UGameFuseSaveData() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseSaveData_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseSaveData_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameFuseSaveData, UGameFuseSaveData::StaticClass, TEXT("UGameFuseSaveData"), &Z_Registration_Info_UClass_UGameFuseSaveData, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameFuseSaveData), 3991051655U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseSaveData_h_1031895105(TEXT("/Script/GameFuse"),
		Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseSaveData_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseSaveData_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
