// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSubsystem.h"

void UBuildingSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	mBuildingTable = LoadObject<UDataTable>(nullptr, TEXT("/Script/Engine.DataTable'/Game/DataTable/DT_Building.DT_Building'"));

	if (!CHECK(mBuildingTable))
		return;

	TArray<FBuildingData*> TA_BuildingData;
	mBuildingTable->GetAllRows<FBuildingData>(TEXT(__FUNCTION__), TA_BuildingData);

	int32 Max = TA_BuildingData.Num();
	for (int32 i = 0; i < Max; ++i)
	{
		FBuildingData* Data = TA_BuildingData[i];
		mTM_BuildingData.Add(Data->Tag, *Data);
	}

}

bool UBuildingSubsystem::GetBuildingData(FGameplayTag Tag, FBuildingData& Data)
{
	if (!Tag.IsValid() || !mTM_BuildingData.Contains(Tag))
		return false;

	Data = mTM_BuildingData[Tag];

	return true;
}
