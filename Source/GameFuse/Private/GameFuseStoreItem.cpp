// Fill out your copyright notice in the Description page of Project Settings.


#include "GameFuseStoreItem.h"


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