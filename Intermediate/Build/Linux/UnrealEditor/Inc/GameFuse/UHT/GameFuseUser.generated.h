// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GameFuseUser.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
 
class UGameFuseLeaderboardEntry;
class UGameFuseStoreItem;
#ifdef GAMEFUSE_GameFuseUser_generated_h
#error "GameFuseUser.generated.h already included, missing '#pragma once' in GameFuseUser.h"
#endif
#define GAMEFUSE_GameFuseUser_generated_h

#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_21_DELEGATE \
GAMEFUSE_API void FUserCallback_DelegateWrapper(const FScriptDelegate& UserCallback, bool bSuccess, const FString& Response);


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_SPARSE_DATA
#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execFetchPurchaseStoreItems); \
	DECLARE_FUNCTION(execFetchAttributes); \
	DECLARE_FUNCTION(execFetchMyLeaderboardEntries); \
	DECLARE_FUNCTION(execClearLeaderboardEntry); \
	DECLARE_FUNCTION(execAddLeaderboardEntryWithAttributes); \
	DECLARE_FUNCTION(execAddLeaderboardEntry); \
	DECLARE_FUNCTION(execRemoveStoreItem); \
	DECLARE_FUNCTION(execRemoveStoreItemWithId); \
	DECLARE_FUNCTION(execPurchaseStoreItem); \
	DECLARE_FUNCTION(execPurchaseStoreItemWithId); \
	DECLARE_FUNCTION(execRemoveAttribute); \
	DECLARE_FUNCTION(execSetAttribute); \
	DECLARE_FUNCTION(execSetScore); \
	DECLARE_FUNCTION(execAddScore); \
	DECLARE_FUNCTION(execSetCredits); \
	DECLARE_FUNCTION(execAddCredits); \
	DECLARE_FUNCTION(execIsSignedIn); \
	DECLARE_FUNCTION(execSignIn); \
	DECLARE_FUNCTION(execSignUp); \
	DECLARE_FUNCTION(execGetLeaderboards); \
	DECLARE_FUNCTION(execGetPurchasedStoreItems); \
	DECLARE_FUNCTION(execGetAttributeValue); \
	DECLARE_FUNCTION(execGetAttributesKeys); \
	DECLARE_FUNCTION(execGetAttributes); \
	DECLARE_FUNCTION(execGetCredits); \
	DECLARE_FUNCTION(execGetScore); \
	DECLARE_FUNCTION(execGetUsername); \
	DECLARE_FUNCTION(execGetLastLogin); \
	DECLARE_FUNCTION(execGetNumberOfLogins);


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execFetchPurchaseStoreItems); \
	DECLARE_FUNCTION(execFetchAttributes); \
	DECLARE_FUNCTION(execFetchMyLeaderboardEntries); \
	DECLARE_FUNCTION(execClearLeaderboardEntry); \
	DECLARE_FUNCTION(execAddLeaderboardEntryWithAttributes); \
	DECLARE_FUNCTION(execAddLeaderboardEntry); \
	DECLARE_FUNCTION(execRemoveStoreItem); \
	DECLARE_FUNCTION(execRemoveStoreItemWithId); \
	DECLARE_FUNCTION(execPurchaseStoreItem); \
	DECLARE_FUNCTION(execPurchaseStoreItemWithId); \
	DECLARE_FUNCTION(execRemoveAttribute); \
	DECLARE_FUNCTION(execSetAttribute); \
	DECLARE_FUNCTION(execSetScore); \
	DECLARE_FUNCTION(execAddScore); \
	DECLARE_FUNCTION(execSetCredits); \
	DECLARE_FUNCTION(execAddCredits); \
	DECLARE_FUNCTION(execIsSignedIn); \
	DECLARE_FUNCTION(execSignIn); \
	DECLARE_FUNCTION(execSignUp); \
	DECLARE_FUNCTION(execGetLeaderboards); \
	DECLARE_FUNCTION(execGetPurchasedStoreItems); \
	DECLARE_FUNCTION(execGetAttributeValue); \
	DECLARE_FUNCTION(execGetAttributesKeys); \
	DECLARE_FUNCTION(execGetAttributes); \
	DECLARE_FUNCTION(execGetCredits); \
	DECLARE_FUNCTION(execGetScore); \
	DECLARE_FUNCTION(execGetUsername); \
	DECLARE_FUNCTION(execGetLastLogin); \
	DECLARE_FUNCTION(execGetNumberOfLogins);


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_ACCESSORS
#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameFuseUser(); \
	friend struct Z_Construct_UClass_UGameFuseUser_Statics; \
public: \
	DECLARE_CLASS(UGameFuseUser, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GameFuse"), NO_API) \
	DECLARE_SERIALIZER(UGameFuseUser)


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_INCLASS \
private: \
	static void StaticRegisterNativesUGameFuseUser(); \
	friend struct Z_Construct_UClass_UGameFuseUser_Statics; \
public: \
	DECLARE_CLASS(UGameFuseUser, UGameInstanceSubsystem, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GameFuse"), NO_API) \
	DECLARE_SERIALIZER(UGameFuseUser)


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGameFuseUser(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameFuseUser) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGameFuseUser); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameFuseUser); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGameFuseUser(UGameFuseUser&&); \
	NO_API UGameFuseUser(const UGameFuseUser&); \
public: \
	NO_API virtual ~UGameFuseUser();


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGameFuseUser(); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGameFuseUser(UGameFuseUser&&); \
	NO_API UGameFuseUser(const UGameFuseUser&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGameFuseUser); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameFuseUser); \
	DEFINE_DEFAULT_CONSTRUCTOR_CALL(UGameFuseUser) \
	NO_API virtual ~UGameFuseUser();


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_23_PROLOG
#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_SPARSE_DATA \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_RPC_WRAPPERS \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_ACCESSORS \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_INCLASS \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_SPARSE_DATA \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_ACCESSORS \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_INCLASS_NO_PURE_DECLS \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h_26_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GAMEFUSE_API UClass* StaticClass<class UGameFuseUser>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseUser_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
