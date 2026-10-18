// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetBase.h"

void UWidgetBase::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UWidgetBase::NativeConstruct()
{
	Super::NativeConstruct();


}

void UWidgetBase::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UWidgetBase::ShowWidget(bool A)
{
	if (A)
		SetVisibility(ESlateVisibility::Visible);
	else
		SetVisibility(ESlateVisibility::Hidden);
}
