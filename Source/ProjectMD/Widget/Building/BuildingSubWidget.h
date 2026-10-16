// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../WidgetBase.h"
#include "../../DataTable/BuildingData.h"
#include "BuildingSubWidget.generated.h"

UENUM(BlueprintType)
enum class EBuildingType :uint8
{
	Miner,
	Crafting,
	Storage,
	Power,
	Structure,
	Light,
	ETC
};

struct FBuildingCategoryInfo
{
	UUserWidget* CategoryWidget;
	int32 Order;
};

struct FBuildingSlotInfo
{
	UUserWidget* SlotWidget;
	int32 SecondOrder;
	int32 ThirdOrder;
};

UCLASS()
class PROJECTMD_API UBuildingSubWidget : public UWidgetBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBuildingType mBuildingType;

	UPROPERTY(meta = (BindWidgetOptional))
	TObjectPtr<UWrapBox> SlotWrap;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> BuildingSlotWidgetClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UUserWidget> BuildingCategoryWidgetClass;
	
	TArray<FGameplayTag> mTA_BuildingTag;

	TArray<FString> mTA_BuildingCategory;
	TArray<FBuildingCategoryInfo> mTA_BuildingCategoryInfo;
	TArray<FBuildingSlotInfo> mTA_BuildingSlotInfo;


protected:
	virtual void NativeOnInitialized() override;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

protected:
	UFUNCTION()
	void UpdateBuildingWidget(FGameplayTag Tag);
	void SetCategoryWidget(FString Text, int32 Order);
	void SetSlotWidget(FGameplayTag Tag, int32 SecondOrder, int32 ThirdOrder);
	void SortBuildingWidget();
	void UpdateMinerWidget(FGameplayTag Tag);

};
