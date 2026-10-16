// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSubWidget.h"
#include "BuildingSlotWidget.h"
#include "BuildingCategoryWidget.h"
#include "../../Character/CharacterControllerBase.h"
#include "../../GameInstanceBase.h"

void UBuildingSubWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UBuildingSubWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ACharacterControllerBase* CC = Cast<ACharacterControllerBase>(GetOwningPlayer());
	if (IsValid(CC))
		CC->OnBuildingUnlock.AddDynamic(this, &UBuildingSubWidget::UpdateBuildingWidget);

}

void UBuildingSubWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

}

void UBuildingSubWidget::UpdateBuildingWidget(FGameplayTag Tag)
{
	switch (mBuildingType)
	{
	case EBuildingType::Miner: UpdateMinerWidget(Tag); break;
	case EBuildingType::Crafting:
		break;
	case EBuildingType::Storage:
		break;
	case EBuildingType::Power:
		break;
	case EBuildingType::Structure:
		break;
	case EBuildingType::Light:
		break;
	case EBuildingType::ETC:
		break;
	default:
		break;
	}


}

void UBuildingSubWidget::SetCategoryWidget(FString Text, int32 Order)
{
	if (mTA_BuildingCategory.Contains(Text))
		return;
	mTA_BuildingCategory.Add(Text);
	UBuildingCategoryWidget* CategoryWidget = CreateWidget<UBuildingCategoryWidget>(this, BuildingCategoryWidgetClass);
	if (!IsValid(CategoryWidget))
	{
		CHECK(" CategoryWidget");
		return;
	}

	CategoryWidget->SetCategoryText(FText::FromString(Text));

	FBuildingCategoryInfo Info;
	Info.CategoryWidget = CategoryWidget;
	Info.Order = Order;
	mTA_BuildingCategoryInfo.Add(Info);

	mTA_BuildingCategoryInfo.Sort([](const FBuildingCategoryInfo& A, const FBuildingCategoryInfo& B) {return A.Order < B.Order; });
}

void UBuildingSubWidget::SetSlotWidget(FGameplayTag Tag, int32 SecondOrder, int32 ThirdOrder)
{
	UBuildingSlotWidget* SlotWidget = CreateWidget<UBuildingSlotWidget>(this, BuildingSlotWidgetClass);
	if (!IsValid(SlotWidget))
	{
		CHECK(" SlotWidget");
		return;
	}

	SlotWidget->SetBuildingSlotTag(Tag);

	FBuildingSlotInfo Info;
	Info.SlotWidget = SlotWidget;
	Info.SecondOrder = SecondOrder;
	Info.ThirdOrder = ThirdOrder;
	mTA_BuildingSlotInfo.Add(Info);

	mTA_BuildingSlotInfo.Sort([](const FBuildingSlotInfo& A, const FBuildingSlotInfo& B) {return A.ThirdOrder < B.ThirdOrder; });

}

void UBuildingSubWidget::SortBuildingWidget()
{
	SlotWrap->ClearChildren();
	int32 CategoryMaxIndex = mTA_BuildingCategoryInfo.Num();
	int32 SlotMaxIndex = mTA_BuildingSlotInfo.Num();
	for (int32 i = 0; i < CategoryMaxIndex; ++i)
	{
		UUserWidget* CategoryWidget = mTA_BuildingCategoryInfo[i].CategoryWidget;
		if(IsValid(CategoryWidget))
			SlotWrap->AddChild(CategoryWidget);

		for (int32 j = 0; j < SlotMaxIndex; ++j)
		{
			if (mTA_BuildingSlotInfo[j].SecondOrder != mTA_BuildingCategoryInfo[i].Order)
				continue;
			UUserWidget* SlotWidget = mTA_BuildingSlotInfo[j].SlotWidget;
			if (IsValid(SlotWidget))
				SlotWrap->AddChild(SlotWidget);
		}

	}
}

void UBuildingSubWidget::UpdateMinerWidget(FGameplayTag Tag)
{
	if (mTA_BuildingTag.Contains(Tag))
		return;

	mTA_BuildingTag.Add(Tag);

	FString TagString = Tag.ToString();

	FBuildingData Data;
	UGameInstanceBase* GI = GetGameInstance<UGameInstanceBase>();
	if (!IsValid(GI) || !GI->GetBuildingData(Tag,Data))
	{
		CHECK(" GI");
		return;
	}

	FString Text = Data.Category.ToString();
	SetCategoryWidget(Text, Data.SecondOrder);
	SetSlotWidget(Tag, Data.SecondOrder, Data.ThirdOrder);
	SortBuildingWidget();

}
