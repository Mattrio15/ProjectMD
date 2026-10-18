// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingSlotWidget.h"
#include "../../DataTable/BuildingData.h"
#include "../../GameInstanceBase.h"
#include "../../Character/MainHUD.h"
#include "../../Character/CharacterBase.h"

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
	if (!CHECK(GI) || !GI->GetBuildingData(Tag, Data))
		return;

	TestText->SetText(Data.Name);

}

void UBuildingSlotWidget::OnButtonClick()
{
	APlayerController* PC = GetOwningPlayer();
	AMainHUD* HUD = PC->GetHUD<AMainHUD>();
	HUD->SetPlayerMode(EPlayerMode::BuildingMode);

	ACharacterBase* CB = Cast<ACharacterBase>(PC->GetCharacter());
	CB->SetBuildingTag(mBuildingTag);

}
