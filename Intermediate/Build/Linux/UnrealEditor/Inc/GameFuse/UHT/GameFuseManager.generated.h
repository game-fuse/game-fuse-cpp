// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "GameFuseManager.h"
#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS
 
class UGameFuseLeaderboardEntry;
class UGameFuseStoreItem;
class UGameFuseUser;
#ifdef GAMEFUSE_GameFuseManager_generated_h
#error "GameFuseManager.generated.h already included, missing '#pragma once' in GameFuseManager.h"
#endif
#define GAMEFUSE_GameFuseManager_generated_h

#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_22_DELEGATE \
GAMEFUSE_API void FManagerCallback_DelegateWrapper(const FScriptDelegate& ManagerCallback, bool bSuccess, const FString& Response);


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_SPARSE_DATA
#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_RPC_WRAPPERS \
 \
	DECLARE_FUNCTION(execFetchStoreItems); \
	DECLARE_FUNCTION(execFetchLeaderboardEntries); \
	DECLARE_FUNCTION(execFetchGameVariables); \
	DECLARE_FUNCTION(execSendPasswordResetEmail); \
	DECLARE_FUNCTION(execGetLeaderboard); \
	DECLARE_FUNCTION(execGetGameStoreItems); \
	DECLARE_FUNCTION(execGetGameVariables); \
	DECLARE_FUNCTION(execGetBaseURL); \
	DECLARE_FUNCTION(execGetGameToken); \
	DECLARE_FUNCTION(execGetGameDescription); \
	DECLARE_FUNCTION(execGetGameName); \
	DECLARE_FUNCTION(execGetGameId); \
	DECLARE_FUNCTION(execSetUpGame);


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
 \
	DECLARE_FUNCTION(execFetchStoreItems); \
	DECLARE_FUNCTION(execFetchLeaderboardEntries); \
	DECLARE_FUNCTION(execFetchGameVariables); \
	DECLARE_FUNCTION(execSendPasswordResetEmail); \
	DECLARE_FUNCTION(execGetLeaderboard); \
	DECLARE_FUNCTION(execGetGameStoreItems); \
	DECLARE_FUNCTION(execGetGameVariables); \
	DECLARE_FUNCTION(execGetBaseURL); \
	DECLARE_FUNCTION(execGetGameToken); \
	DECLARE_FUNCTION(execGetGameDescription); \
	DECLARE_FUNCTION(execGetGameName); \
	DECLARE_FUNCTION(execGetGameId); \
	DECLARE_FUNCTION(execSetUpGame);


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_ACCESSORS
#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUGameFuseManager(); \
	friend struct Z_Construct_UClass_UGameFuseManager_Statics; \
public: \
	DECLARE_CLASS(UGameFuseManager, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GameFuse"), NO_API) \
	DECLARE_SERIALIZER(UGameFuseManager)


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_INCLASS \
private: \
	static void StaticRegisterNativesUGameFuseManager(); \
	friend struct Z_Construct_UClass_UGameFuseManager_Statics; \
public: \
	DECLARE_CLASS(UGameFuseManager, UObject, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/GameFuse"), NO_API) \
	DECLARE_SERIALIZER(UGameFuseManager)


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGameFuseManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameFuseManager) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGameFuseManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameFuseManager); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGameFuseManager(UGameFuseManager&&); \
	NO_API UGameFuseManager(const UGameFuseManager&); \
public: \
	NO_API virtual ~UGameFuseManager();


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UGameFuseManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
private: \
	/** Private move- and copy-constructors, should never be used */ \
	NO_API UGameFuseManager(UGameFuseManager&&); \
	NO_API UGameFuseManager(const UGameFuseManager&); \
public: \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UGameFuseManager); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UGameFuseManager); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UGameFuseManager) \
	NO_API virtual ~UGameFuseManager();


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_25_PROLOG
#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_SPARSE_DATA \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_RPC_WRAPPERS \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_ACCESSORS \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_INCLASS \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


#define FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_SPARSE_DATA \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_ACCESSORS \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_INCLASS_NO_PURE_DECLS \
	FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h_28_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


template<> GAMEFUSE_API UClass* StaticClass<class UGameFuseManager>();

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_UnrealProjects_GameFusePlugin_Plugins_GameFuse_Source_GameFuse_Public_GameFuseManager_h


PRAGMA_ENABLE_DEPRECATION_WARNINGS
