// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingWidget.h"

void UBuildingWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UBuildingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(BuildingButton_0))
	{
		BuildingButton_0->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_0);
		mTA_Button.Add(BuildingButton_0);
	}
	if (IsValid(BuildingButton_1))
	{
		BuildingButton_1->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_1);
		mTA_Button.Add(BuildingButton_1);
	}
	if (IsValid(BuildingButton_2))
	{
		BuildingButton_2->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_2);
		mTA_Button.Add(BuildingButton_2);
	}
	if (IsValid(BuildingButton_3))
	{
		BuildingButton_3->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_3);
		mTA_Button.Add(BuildingButton_3);
	}
	if (IsValid(BuildingButton_4))
	{
		BuildingButton_4->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_4);
		mTA_Button.Add(BuildingButton_4);
	}
	if (IsValid(BuildingButton_5))
	{
		BuildingButton_5->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_5);
		mTA_Button.Add(BuildingButton_5);
	}
	if (IsValid(BuildingButton_6))
	{
		BuildingButton_6->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_6);
		mTA_Button.Add(BuildingButton_6);
	}

	SetSwitcherIndex(0);

}

void UBuildingWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UBuildingWidget::SetSwitcherIndex(int32 Index)
{
	if (!CHECK(BuildingSwitcher))
		return;

	int32 Num = BuildingSwitcher->GetNumWidgets();

	if (Num < 1)
		return;

	while (Index < 0)
		Index += Num;

	mSwitcherIndex = Index % Num;
	
	BuildingSwitcher->SetActiveWidgetIndex(mSwitcherIndex);

	int32 Max = mTA_Button.Num();
	for (int32 i = 0; i < Max; ++i)
	{
		FButtonStyle Style = mTA_Button[i]->GetStyle();
		if (i == mSwitcherIndex)
			Style.Normal.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0.75));
		else
			Style.Normal.TintColor = FSlateColor(FLinearColor(1, 1, 1, 0.5));
		mTA_Button[i]->SetStyle(Style);
	}

}

void UBuildingWidget::NextPageWidget(bool A)
{
	if (GetVisibility() != ESlateVisibility::Visible) return;

	if (A) mSwitcherIndex += 1;
	else mSwitcherIndex -= 1;

	SetSwitcherIndex(mSwitcherIndex);
}
