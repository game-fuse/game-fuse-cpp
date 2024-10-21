#pragma once

#include "CoreMinimal.h"
#include "Library/GameFuseStructLibrary.h"

#include "GameFuseTestsUtilities.generated.h"

UCLASS(meta = (Hidden, HideDropDown))
class GAMEFUSETESTS_API UGameFuseTestsUtilities : public UObject
{
	GENERATED_BODY()
public:
	static void CleanUpTestData();


};
