// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSlotWidget.h"
#include "../../DataTable/BuildingData.h"
#include "../../Subsystem/BuildingSubsystem.h"
#include "../../Character/MainHUD.h"

void UBuildingSlotWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(BuildingSlotButton))
		BuildingSlotButton->OnClicked.AddDynamic(this, &UBuildingSlotWidget::OnButtonClick);

}

void UBuildingSlotWidget::SetBuildingSlotTag(FGameplayTag Tag)
{
	mBuildingTag = Tag;

	FBuildingData Data;

	UBuildingSubsystem* BS = GetGameInstance()->GetSubsystem<UBuildingSubsystem>();
	if (!CHECK(BS) || !BS->GetBuildingData(mBuildingTag, Data))
		return;

	TestText->SetText(Data.Name);

}

void UBuildingSlotWidget::OnButtonClick()
{
	APlayerController* PC = GetOwningPlayer();
	AMainHUD* HUD = PC->GetHUD<AMainHUD>();
	HUD->SetPlayerMode(EPlayerMode::BuildingMode);

	UBuildingSubsystem* BS = GetGameInstance()->GetSubsystem<UBuildingSubsystem>();
	if (!CHECK(BS))
		return;
	BS->OnGetBuildingTag.Broadcast(mBuildingTag);

}
