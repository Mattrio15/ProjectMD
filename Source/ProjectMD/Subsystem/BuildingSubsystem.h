// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Game_Info.h"
#include "../DataTable/BuildingData.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BuildingSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetBuildingTag, FGameplayTag, Tag);

UCLASS()
class PROJECTMD_API UBuildingSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	TObjectPtr<UDataTable> mBuildingTable;
	UPROPERTY()
	TMap<FGameplayTag, FBuildingData> mTM_BuildingData;

public:
	FOnGetBuildingTag OnGetBuildingTag;

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection);

public:
	bool GetBuildingData(FGameplayTag Tag, FBuildingData& Data);

};
