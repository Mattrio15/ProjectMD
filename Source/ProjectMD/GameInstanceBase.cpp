// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceBase.h"

bool UGameInstanceBase::GetBuildingData(FGameplayTag Tag, FBuildingData& BuildingData)
{
	if (!Tag.IsValid() || !IsValid(mBuildingTable))
		return false;

	FName TagName = Tag.GetTagName();
	FBuildingData* BD = mBuildingTable->FindRow<FBuildingData>(TagName, __FUNCTION__);

	if (!BD)
		return false;

	BuildingData = *BD;
	return true;
}
