// Fill out your copyright notice in the Description page of Project Settings.


#include "GameInstanceBase.h"

bool UGameInstanceBase::GetBuildingData(FGameplayTag Tag, FBuildingData& BuildingData)
{
	if (!Tag.IsValid() || !IsValid(mBuildingTable))
		return false;

	if (mTM_BuildingData.Num() < 1)
	{
		TArray<FBuildingData*> BuildingDataArray;
		mBuildingTable->GetAllRows<FBuildingData>(TEXT(__FUNCTION__), BuildingDataArray);

		int32 Max = BuildingDataArray.Num();
		for (int32 i = 0; i < Max; ++i)
		{
			FBuildingData* Data = BuildingDataArray[i];
			FGameplayTag Tag = Data->Tag;
			mTM_BuildingData.Add(Tag, *Data);
		}
	}

	if (!mTM_BuildingData.Contains(Tag))
		return false;

	BuildingData = mTM_BuildingData[Tag];
	
	return true;
}
