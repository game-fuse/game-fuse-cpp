// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameFuse_init() {}
	GAMEFUSE_API UFunction* Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature();
	GAMEFUSE_API UFunction* Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature();
	static FPackageRegistrationInfo Z_Registration_Info_UPackage__Script_GameFuse;
	FORCENOINLINE UPackage* Z_Construct_UPackage__Script_GameFuse()
	{
		if (!Z_Registration_Info_UPackage__Script_GameFuse.OuterSingleton)
		{
			static UObject* (*const SingletonFuncArray[])() = {
				(UObject* (*)())Z_Construct_UDelegateFunction_GameFuse_ManagerCallback__DelegateSignature,
				(UObject* (*)())Z_Construct_UDelegateFunction_GameFuse_UserCallback__DelegateSignature,
			};
			static const UECodeGen_Private::FPackageParams PackageParams = {
				"/Script/GameFuse",
				SingletonFuncArray,
				UE_ARRAY_COUNT(SingletonFuncArray),
				PKG_CompiledIn | 0x00000000,
				0xF7AC041C,
				0x807160B8,
				METADATA_PARAMS(nullptr, 0)
			};
			UECodeGen_Private::ConstructUPackage(Z_Registration_Info_UPackage__Script_GameFuse.OuterSingleton, PackageParams);
		}
		return Z_Registration_Info_UPackage__Script_GameFuse.OuterSingleton;
	}
	static FRegisterCompiledInInfo Z_CompiledInDeferPackage_UPackage__Script_GameFuse(Z_Construct_UPackage__Script_GameFuse, TEXT("/Script/GameFuse"), Z_Registration_Info_UPackage__Script_GameFuse, CONSTRUCT_RELOAD_VERSION_INFO(FPackageReloadVersionInfo, 0xF7AC041C, 0x807160B8));
PRAGMA_ENABLE_DEPRECATION_WARNINGS
