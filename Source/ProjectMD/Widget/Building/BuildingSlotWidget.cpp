// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSlotWidget.h"
#include "../../DataTable/BuildingData.h"
#include "../../GameInstanceBase.h"

void UBuildingSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(BuildingSlotButton))
		BuildingSlotButton->OnClicked.AddDynamic(this, &UBuildingSlotWidget::OnButtonClick);

}

void UBuildingSlotWidget::SetBuildingSlotTag(FGameplayTag Tag)
{
	FBuildingData Data;
	UGameInstanceBase* GI = GetGameInstance<UGameInstanceBase>();
	if (!IsValid(GI) || !GI->GetBuildingData(Tag,Data))
	{
		CHECK(" GI or Data");
		return;
	}

	TestText->SetText(Data.Name);

}

void UBuildingSlotWidget::OnButtonClick()
{


}
