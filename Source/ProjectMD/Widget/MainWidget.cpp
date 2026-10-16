// Fill out your copyright notice in the Description page of Project Settings.


#include "MainWidget.h"
#include "Building/BuildingWidget.h"

void UMainWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UMainWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UMainWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

UWidgetBase* UMainWidget::GetWidget(EWidgetType Type)
{
	switch (Type)
	{
	case EWidgetType::None: return nullptr;
	case EWidgetType::Building: return WBP_Building;

	default:
		break;
	}

	return nullptr;
}

ESlateVisibility UMainWidget::ToggleWidget(EWidgetType Type)
{
	UWidgetBase* Widget = GetWidget(Type);
	if (IsValid(Widget))
	{
		Widget->ToggleWidget();
		return Widget->GetVisibility();
	}

	return ESlateVisibility::Hidden;
}

void UMainWidget::NextPageWidget(bool A)
{
	if (IsValid(WBP_Building))
	{
		UBuildingWidget* Widget = Cast<UBuildingWidget>(WBP_Building);
		if (IsValid(Widget))
			Widget->NextPageWidget(A);
	}
}
