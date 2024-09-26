/**
 *  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "GameFuse.h"

#define LOCTEXT_NAMESPACE "FGameFuseModule"



void FGameFuseModule::StartupModule()
{
	UE_LOG(LogCore, Display, TEXT("GameFuse ====> StartupModule"));
	
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FGameFuseModule::ShutdownModule()
{
	UE_LOG(LogCore, Display, TEXT("GameFuse ====> ShutdownModule"));
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FGameFuseModule, GameFuse)