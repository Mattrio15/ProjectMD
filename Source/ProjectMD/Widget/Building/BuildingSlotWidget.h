// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../WidgetBase.h"
#include "BuildingSlotWidget.generated.h"

class UBuildingSubWidget;

UCLASS()
class PROJECTMD_API UBuildingSlotWidget : public UWidgetBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta =(BindWidgetOptional))
	TObjectPtr<UTextBlock> TestText;
	UPROPERTY()
	FGameplayTag mBuildingTag;

public:
	void SetBuildingSlotTag(FGameplayTag Tag);

};
