// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../BuildingBase.h"
#include "MinerBase.generated.h"

class UWidgetBase;

UCLASS()
class PROJECTMD_API AMinerBase : public ABuildingBase
{
	GENERATED_BODY()

public:
	AMinerBase();

public:
	virtual void Interaction(AActor* Interactor) override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UWidgetBase> mMinerWidgetClass;
	UPROPERTY()
	TObjectPtr<UWidgetBase> mMinerWidget;



	
};
