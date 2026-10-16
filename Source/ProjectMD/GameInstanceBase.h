// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Game_Info.h"
#include "DataTable/BuildingData.h"
#include "Engine/GameInstance.h"
#include "GameInstanceBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMD_API UGameInstanceBase : public UGameInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UDataTable> mBuildingTable;

public:
	bool GetBuildingData(FGameplayTag Tag, FBuildingData& BuildingData);

};
