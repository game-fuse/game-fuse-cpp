#include "GameFuseTests.h"

#include "Library/GameFuseLog.h"

#define LOCTEXT_NAMESPACE "FGameFuseTestsModule"

struct FLogCategoryLogGameFuse LogGameFuse;

void FGameFuseTestsModule::StartupModule()
{}

void FGameFuseTestsModule::ShutdownModule()
{}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FGameFuseTestsModule, GameFuseTests)