// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Widget_Info.h"
#include "Blueprint/UserWidget.h"
#include "WidgetBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMD_API UWidgetBase : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

public:
	void ToggleWidget();


};
