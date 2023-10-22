// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GameFuse/Public/GameFuseStoreItem.h"
PRAGMA_DISABLE_DEPRECATION_WARNINGS
void EmptyLinkFunctionForGeneratedCodeGameFuseStoreItem() {}
// Cross Module References
	COREUOBJECT_API UClass* Z_Construct_UClass_UObject();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseStoreItem();
	GAMEFUSE_API UClass* Z_Construct_UClass_UGameFuseStoreItem_NoRegister();
	UPackage* Z_Construct_UPackage__Script_GameFuse();
// End Cross Module References
	DEFINE_FUNCTION(UGameFuseStoreItem::execGetIconUrl)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetIconUrl();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseStoreItem::execGetId)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetId();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseStoreItem::execGetCost)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(int32*)Z_Param__Result=P_THIS->GetCost();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseStoreItem::execGetDescription)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetDescription();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseStoreItem::execGetCategory)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetCategory();
		P_NATIVE_END;
	}
	DEFINE_FUNCTION(UGameFuseStoreItem::execGetName)
	{
		P_FINISH;
		P_NATIVE_BEGIN;
		*(FString*)Z_Param__Result=P_THIS->GetName();
		P_NATIVE_END;
	}
	void UGameFuseStoreItem::StaticRegisterNativesUGameFuseStoreItem()
	{
		UClass* Class = UGameFuseStoreItem::StaticClass();
		static const FNameNativePtrPair Funcs[] = {
			{ "GetCategory", &UGameFuseStoreItem::execGetCategory },
			{ "GetCost", &UGameFuseStoreItem::execGetCost },
			{ "GetDescription", &UGameFuseStoreItem::execGetDescription },
			{ "GetIconUrl", &UGameFuseStoreItem::execGetIconUrl },
			{ "GetId", &UGameFuseStoreItem::execGetId },
			{ "GetName", &UGameFuseStoreItem::execGetName },
		};
		FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
	}
	struct Z_Construct_UFunction_UGameFuseStoreItem_GetCategory_Statics
	{
		struct GameFuseStoreItem_eventGetCategory_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseStoreItem_GetCategory_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseStoreItem_eventGetCategory_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseStoreItem_GetCategory_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseStoreItem_GetCategory_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseStoreItem_GetCategory_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseStoreItem.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseStoreItem_GetCategory_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseStoreItem, nullptr, "GetCategory", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseStoreItem_GetCategory_Statics::GameFuseStoreItem_eventGetCategory_Parms), Z_Construct_UFunction_UGameFuseStoreItem_GetCategory_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseStoreItem_GetCategory_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseStoreItem_GetCategory_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseStoreItem_GetCategory_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseStoreItem_GetCategory()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseStoreItem_GetCategory_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseStoreItem_GetCost_Statics
	{
		struct GameFuseStoreItem_eventGetCost_Parms
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
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UGameFuseStoreItem_GetCost_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseStoreItem_eventGetCost_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseStoreItem_GetCost_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseStoreItem_GetCost_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseStoreItem_GetCost_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseStoreItem.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseStoreItem_GetCost_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseStoreItem, nullptr, "GetCost", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseStoreItem_GetCost_Statics::GameFuseStoreItem_eventGetCost_Parms), Z_Construct_UFunction_UGameFuseStoreItem_GetCost_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseStoreItem_GetCost_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseStoreItem_GetCost_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseStoreItem_GetCost_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseStoreItem_GetCost()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseStoreItem_GetCost_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseStoreItem_GetDescription_Statics
	{
		struct GameFuseStoreItem_eventGetDescription_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseStoreItem_GetDescription_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseStoreItem_eventGetDescription_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseStoreItem_GetDescription_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseStoreItem_GetDescription_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseStoreItem_GetDescription_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseStoreItem.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseStoreItem_GetDescription_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseStoreItem, nullptr, "GetDescription", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseStoreItem_GetDescription_Statics::GameFuseStoreItem_eventGetDescription_Parms), Z_Construct_UFunction_UGameFuseStoreItem_GetDescription_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseStoreItem_GetDescription_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseStoreItem_GetDescription_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseStoreItem_GetDescription_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseStoreItem_GetDescription()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseStoreItem_GetDescription_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl_Statics
	{
		struct GameFuseStoreItem_eventGetIconUrl_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseStoreItem_eventGetIconUrl_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseStoreItem.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseStoreItem, nullptr, "GetIconUrl", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl_Statics::GameFuseStoreItem_eventGetIconUrl_Parms), Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseStoreItem_GetId_Statics
	{
		struct GameFuseStoreItem_eventGetId_Parms
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
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UGameFuseStoreItem_GetId_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseStoreItem_eventGetId_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseStoreItem_GetId_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseStoreItem_GetId_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseStoreItem_GetId_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseStoreItem.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseStoreItem_GetId_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseStoreItem, nullptr, "GetId", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseStoreItem_GetId_Statics::GameFuseStoreItem_eventGetId_Parms), Z_Construct_UFunction_UGameFuseStoreItem_GetId_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseStoreItem_GetId_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseStoreItem_GetId_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseStoreItem_GetId_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseStoreItem_GetId()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseStoreItem_GetId_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	struct Z_Construct_UFunction_UGameFuseStoreItem_GetName_Statics
	{
		struct GameFuseStoreItem_eventGetName_Parms
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
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UGameFuseStoreItem_GetName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(GameFuseStoreItem_eventGetName_Parms, ReturnValue), METADATA_PARAMS(nullptr, 0) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGameFuseStoreItem_GetName_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGameFuseStoreItem_GetName_Statics::NewProp_ReturnValue,
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UFunction_UGameFuseStoreItem_GetName_Statics::Function_MetaDataParams[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseStoreItem.h" },
	};
#endif
	const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGameFuseStoreItem_GetName_Statics::FuncParams = { (UObject*(*)())Z_Construct_UClass_UGameFuseStoreItem, nullptr, "GetName", nullptr, nullptr, sizeof(Z_Construct_UFunction_UGameFuseStoreItem_GetName_Statics::GameFuseStoreItem_eventGetName_Parms), Z_Construct_UFunction_UGameFuseStoreItem_GetName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseStoreItem_GetName_Statics::PropPointers), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04020401, 0, 0, METADATA_PARAMS(Z_Construct_UFunction_UGameFuseStoreItem_GetName_Statics::Function_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UFunction_UGameFuseStoreItem_GetName_Statics::Function_MetaDataParams)) };
	UFunction* Z_Construct_UFunction_UGameFuseStoreItem_GetName()
	{
		static UFunction* ReturnFunction = nullptr;
		if (!ReturnFunction)
		{
			UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGameFuseStoreItem_GetName_Statics::FuncParams);
		}
		return ReturnFunction;
	}
	IMPLEMENT_CLASS_NO_AUTO_REGISTRATION(UGameFuseStoreItem);
	UClass* Z_Construct_UClass_UGameFuseStoreItem_NoRegister()
	{
		return UGameFuseStoreItem::StaticClass();
	}
	struct Z_Construct_UClass_UGameFuseStoreItem_Statics
	{
		static UObject* (*const DependentSingletons[])();
		static const FClassFunctionLinkInfo FuncInfo[];
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[];
#endif
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Name_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Name;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Category_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Category;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Description_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_Description;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Cost_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Cost;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_Id_MetaData[];
#endif
		static const UECodeGen_Private::FIntPropertyParams NewProp_Id;
#if WITH_METADATA
		static const UECodeGen_Private::FMetaDataPairParam NewProp_IconUrl_MetaData[];
#endif
		static const UECodeGen_Private::FStrPropertyParams NewProp_IconUrl;
		static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
		static const FCppClassTypeInfoStatic StaticCppClassTypeInfo;
		static const UECodeGen_Private::FClassParams ClassParams;
	};
	UObject* (*const Z_Construct_UClass_UGameFuseStoreItem_Statics::DependentSingletons[])() = {
		(UObject* (*)())Z_Construct_UClass_UObject,
		(UObject* (*)())Z_Construct_UPackage__Script_GameFuse,
	};
	const FClassFunctionLinkInfo Z_Construct_UClass_UGameFuseStoreItem_Statics::FuncInfo[] = {
		{ &Z_Construct_UFunction_UGameFuseStoreItem_GetCategory, "GetCategory" }, // 1781943104
		{ &Z_Construct_UFunction_UGameFuseStoreItem_GetCost, "GetCost" }, // 3730482684
		{ &Z_Construct_UFunction_UGameFuseStoreItem_GetDescription, "GetDescription" }, // 3239769031
		{ &Z_Construct_UFunction_UGameFuseStoreItem_GetIconUrl, "GetIconUrl" }, // 3130494786
		{ &Z_Construct_UFunction_UGameFuseStoreItem_GetId, "GetId" }, // 864531770
		{ &Z_Construct_UFunction_UGameFuseStoreItem_GetName, "GetName" }, // 4048080417
	};
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseStoreItem_Statics::Class_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Comment", "/**\n * \n */" },
		{ "IncludePath", "GameFuseStoreItem.h" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Public/GameFuseStoreItem.h" },
	};
#endif
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Name_MetaData[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseStoreItem.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Name = { "Name", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameFuseStoreItem, Name), METADATA_PARAMS(Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Name_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Name_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Category_MetaData[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseStoreItem.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Category = { "Category", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameFuseStoreItem, Category), METADATA_PARAMS(Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Category_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Category_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Description_MetaData[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseStoreItem.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Description = { "Description", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameFuseStoreItem, Description), METADATA_PARAMS(Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Description_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Description_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Cost_MetaData[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseStoreItem.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Cost = { "Cost", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameFuseStoreItem, Cost), METADATA_PARAMS(Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Cost_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Cost_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Id_MetaData[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseStoreItem.h" },
	};
#endif
	const UECodeGen_Private::FIntPropertyParams Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Id = { "Id", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameFuseStoreItem, Id), METADATA_PARAMS(Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Id_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Id_MetaData)) };
#if WITH_METADATA
	const UECodeGen_Private::FMetaDataPairParam Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_IconUrl_MetaData[] = {
		{ "Category", "GameFuse|StoreItem" },
		{ "ModuleRelativePath", "Public/GameFuseStoreItem.h" },
	};
#endif
	const UECodeGen_Private::FStrPropertyParams Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_IconUrl = { "IconUrl", nullptr, (EPropertyFlags)0x0010000000000014, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, 1, nullptr, nullptr, STRUCT_OFFSET(UGameFuseStoreItem, IconUrl), METADATA_PARAMS(Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_IconUrl_MetaData, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_IconUrl_MetaData)) };
	const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGameFuseStoreItem_Statics::PropPointers[] = {
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Name,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Category,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Description,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Cost,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_Id,
		(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGameFuseStoreItem_Statics::NewProp_IconUrl,
	};
	const FCppClassTypeInfoStatic Z_Construct_UClass_UGameFuseStoreItem_Statics::StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGameFuseStoreItem>::IsAbstract,
	};
	const UECodeGen_Private::FClassParams Z_Construct_UClass_UGameFuseStoreItem_Statics::ClassParams = {
		&UGameFuseStoreItem::StaticClass,
		nullptr,
		&StaticCppClassTypeInfo,
		DependentSingletons,
		FuncInfo,
		Z_Construct_UClass_UGameFuseStoreItem_Statics::PropPointers,
		nullptr,
		UE_ARRAY_COUNT(DependentSingletons),
		UE_ARRAY_COUNT(FuncInfo),
		UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseStoreItem_Statics::PropPointers),
		0,
		0x001000A0u,
		METADATA_PARAMS(Z_Construct_UClass_UGameFuseStoreItem_Statics::Class_MetaDataParams, UE_ARRAY_COUNT(Z_Construct_UClass_UGameFuseStoreItem_Statics::Class_MetaDataParams))
	};
	UClass* Z_Construct_UClass_UGameFuseStoreItem()
	{
		if (!Z_Registration_Info_UClass_UGameFuseStoreItem.OuterSingleton)
		{
			UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGameFuseStoreItem.OuterSingleton, Z_Construct_UClass_UGameFuseStoreItem_Statics::ClassParams);
		}
		return Z_Registration_Info_UClass_UGameFuseStoreItem.OuterSingleton;
	}
	template<> GAMEFUSE_API UClass* StaticClass<UGameFuseStoreItem>()
	{
		return UGameFuseStoreItem::StaticClass();
	}
	DEFINE_VTABLE_PTR_HELPER_CTOR(UGameFuseStoreItem);
	UGameFuseStoreItem::~UGameFuseStoreItem() {}
	struct Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseStoreItem_h_Statics
	{
		static const FClassRegisterCompiledInInfo ClassInfo[];
	};
	const FClassRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseStoreItem_h_Statics::ClassInfo[] = {
		{ Z_Construct_UClass_UGameFuseStoreItem, UGameFuseStoreItem::StaticClass, TEXT("UGameFuseStoreItem"), &Z_Registration_Info_UClass_UGameFuseStoreItem, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGameFuseStoreItem), 1698361220U) },
	};
	static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseStoreItem_h_949434336(TEXT("/Script/GameFuse"),
		Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseStoreItem_h_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseStoreItem_h_Statics::ClassInfo),
		nullptr, 0,
		nullptr, 0);
PRAGMA_ENABLE_DEPRECATION_WARNINGS
