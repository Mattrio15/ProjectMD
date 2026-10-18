// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "WidgetBase.h"
#include "MainWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMD_API UMainWidget : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UWidgetBase> WBP_Building;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UWidgetBase> WBP_BuildingMode;

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UWidgetBase* GetWidget(EWidgetType Type);

public:
	void ShowWidget(EWidgetType Type, bool A);
	void NextPageWidget(bool A);

};
