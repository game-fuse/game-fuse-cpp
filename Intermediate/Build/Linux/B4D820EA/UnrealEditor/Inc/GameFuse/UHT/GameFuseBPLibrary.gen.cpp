// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameFuse/Public/GameFuseBPLibrary.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameFuseBPLibrary() {}
// Cross Module References
	ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseBPLibrary();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseBPLibrary_NoRegister();
	UPackage* Z_Construct_UPackage__Script_GameFuse();
// End Cross Module References
	void UGameFuseBPLibrary::StaticRegisterNativesUGameFuseBPLibrary()
	{
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGameFuseBPLibrary);
	UClass* Z_Construct_UClass_UGameFuseBPLibrary_NoRegister()
	{
		return UGameFuseBPLibrary::StaticClass();
	}
	struct Z_Construct_UClass_UGameFuseBPLibrary_Statics
	{
		static UObject* (*const DependentSingletons[])();
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGameFuseBPLibrary_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
		(UObject* (*)())Z_Construct_UPackage__Script_GameFuse,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseBPLibrary_Statics::Class_MetaDataParams[] = {
		{ "Comment", "/**\n *  this class is for make the plugin blueprintable\n */" },
		{ "IncludePath", "GameFuseBPLibrary.h" },
		{ "ModuleRelativePath", "Public/GameFuseBPLibrary.h" },
		{ "ToolTip", "this class is for make the plugin blueprintable" },
	};
#endif
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGameFuseBPLibrary_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameFuseBPLibrary>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameFuseBPLibrary_Statics::ClassParams = {
		&UGameFuseBPLibrary::StaticClass,
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
		METADATA_PARAMS(Z_Construct_UClass_UGameFuseBPLibrary_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseBPLibrary_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGameFuseBPLibrary()
	{
		if (!Z_Registration_Info_UClass_UGameFuseBPLibrary.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameFuseBPLibrary.OuterSingleton, Z_Construct_UClass_UGameFuseBPLibrary_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGameFuseBPLibrary.OuterSingleton;
	}
	template<> GAMEFUSE_API UClass* StaticClass<UGameFuseBPLibrary>()
	{
		return UGameFuseBPLibrary::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameFuseBPLibrary);
	UGameFuseBPLibrary::~UGameFuseBPLibrary() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseBPLibrary_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseBPLibrary_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameFuseBPLibrary, UGameFuseBPLibrary::StaticClass, TEXT("UGameFuseBPLibrary"), &Z_Registration_Info_UClass_UGameFuseBPLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameFuseBPLibrary), 3703527512U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseBPLibrary_h_194750842(TEXT("/Script/GameFuse"),
		Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseBPLibrary_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseBPLibrary_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
