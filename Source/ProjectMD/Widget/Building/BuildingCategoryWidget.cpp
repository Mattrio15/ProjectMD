// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingCategoryWidget.h"

void UBuildingCategoryWidget::SetCategoryText(FText Text)
{
	if (IsValid(CategoryText))
		CategoryText->SetText(Text);
}
