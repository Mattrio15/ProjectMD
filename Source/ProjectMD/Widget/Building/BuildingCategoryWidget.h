// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../WidgetBase.h"
#include "BuildingCategoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMD_API UBuildingCategoryWidget : public UWidgetBase
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UTextBlock> CategoryText;

public:
	void SetCategoryText(FText Text);

};
