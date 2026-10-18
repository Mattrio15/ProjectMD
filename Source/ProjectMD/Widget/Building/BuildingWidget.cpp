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
		BuildingButton_0->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_0);
	if (IsValid(BuildingButton_1))
		BuildingButton_1->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_1);
	if (IsValid(BuildingButton_2))
		BuildingButton_2->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_2);
	if (IsValid(BuildingButton_3))
		BuildingButton_3->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_3);
	if (IsValid(BuildingButton_4))
		BuildingButton_4->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_4);
	if (IsValid(BuildingButton_5))
		BuildingButton_5->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_5);
	if (IsValid(BuildingButton_6))
		BuildingButton_6->OnClicked.AddDynamic(this, &UBuildingWidget::ClickBuildingButton_6);


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

}

void UBuildingWidget::NextPageWidget(bool A)
{
	if (GetVisibility() != ESlateVisibility::Visible) return;

	if (A) mSwitcherIndex += 1;
	else mSwitcherIndex -= 1;

	SetSwitcherIndex(mSwitcherIndex);
}
