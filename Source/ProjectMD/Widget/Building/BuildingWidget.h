// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../WidgetBase.h"
#include "BuildingWidget.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMD_API UBuildingWidget : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> BuildingButton_0;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> BuildingButton_1;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> BuildingButton_2;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> BuildingButton_3;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> BuildingButton_4;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> BuildingButton_5;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UButton> BuildingButton_6;
	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UWidgetSwitcher> BuildingSwitcher;

	int32 mSwitcherIndex = 0;

protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	void SetSwitcherIndex(int32 Index);

public:
	void NextPageWidget(bool A);

protected:
	UFUNCTION()
	void ClickBuildingButton_0() { SetSwitcherIndex(0); }
	UFUNCTION()
	void ClickBuildingButton_1() { SetSwitcherIndex(1); }
	UFUNCTION()
	void ClickBuildingButton_2() { SetSwitcherIndex(2); }
	UFUNCTION()
	void ClickBuildingButton_3() { SetSwitcherIndex(3); }
	UFUNCTION()
	void ClickBuildingButton_4() { SetSwitcherIndex(4); }
	UFUNCTION()
	void ClickBuildingButton_5() { SetSwitcherIndex(5); }
	UFUNCTION()
	void ClickBuildingButton_6() { SetSwitcherIndex(6); }
	
};
