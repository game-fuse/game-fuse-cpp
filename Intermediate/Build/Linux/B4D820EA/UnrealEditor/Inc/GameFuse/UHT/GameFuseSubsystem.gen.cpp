// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameFuse/Public/GameFuseSubsystem.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameFuseSubsystem() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_USubsystem();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseSubsystem();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseSubsystem_NoRegister();
	UPackage* Z_Construct_UPackage__Script_GameFuse();
// End Cross Module References
	void UGameFuseSubsystem::StaticRegisterNativesUGameFuseSubsystem()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGameFuseSubsystem);
	UClass* Z_Construct_UClass_UGameFuseSubsystem_NoRegister()
	{
		return UGameFuseSubsystem::StaticClass();
	}
	struct Z_Construct_UClass_UGameFuseSubsystem_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGameFuseSubsystem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_USubsystem,
		(UObject* (*)())Z_Construct_UPackage__Script_GameFuse,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseSubsystem_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "GameFuseSubsystem.h" },
		{ "ModuleRelativePath", "Public/GameFuseSubsystem.h" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGameFuseSubsystem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameFuseSubsystem>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameFuseSubsystem_Statics::ClassParams = {
		&UGameFuseSubsystem::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		nullptr,
		nullptr,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		0,
		0,
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGameFuseSubsystem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseSubsystem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGameFuseSubsystem()
	{
		if (!Z_Registration_Info_UClass_UGameFuseSubsystem.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameFuseSubsystem.OuterSingleton, Z_Construct_UClass_UGameFuseSubsystem_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGameFuseSubsystem.OuterSingleton;
	}
	template<> GAMEFUSE_API UClass* StaticClass<UGameFuseSubsystem>()
	{
		return UGameFuseSubsystem::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameFuseSubsystem);
	UGameFuseSubsystem::~UGameFuseSubsystem() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseSubsystem_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseSubsystem_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameFuseSubsystem, UGameFuseSubsystem::StaticClass, TEXT("UGameFuseSubsystem"), &Z_Registration_Info_UClass_UGameFuseSubsystem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameFuseSubsystem), 1582939773U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseSubsystem_h_2503749775(TEXT("/Script/GameFuse"),
		Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseSubsystem_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseSubsystem_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
