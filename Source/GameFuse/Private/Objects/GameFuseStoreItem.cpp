/**
*  Copyright (c) 2023-11-06 GameFuse
 *  All rights reserved.
 *
 *  https://GameFuse.co/
 *  https://github.com/game-fuse/game-fuse-cpp
 */

#include "Objects/GameFuseStoreItem.h"

FString UGameFuseStoreItem::GetName()
{
	return Name;
}

FString UGameFuseStoreItem::GetCategory()
{
	return Category;
}

FString UGameFuseStoreItem::GetDescription()
{
	return Description;
}

int32 UGameFuseStoreItem::GetCost()
{
	return Cost;
}

int32 UGameFuseStoreItem::GetId()
{
	return Id;
}

FString UGameFuseStoreItem::GetIconUrl()
{
	return IconUrl;
}