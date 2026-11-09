// Fill out your copyright notice in the Description page of Project Settings.


#include "MinerBase.h"
#include "../../Widget/WidgetBase.h"
#include "../../Character/MainHUD.h"

AMinerBase::AMinerBase()
{

}

void AMinerBase::Interaction(AActor* Interactor)
{
	APlayerController* PC = Cast<APlayerController>(Interactor);

	if (!CHECK(PC) || !mMinerWidgetClass)
		return;
	
	AMainHUD* HUD = PC->GetHUD<AMainHUD>();
	if (!CHECK(HUD))
		return;

	mMinerWidget = CreateWidget<UWidgetBase>(PC, mMinerWidgetClass);

	mMinerWidget->AddToViewport(0);
	mMinerWidget->SetVisibility(ESlateVisibility::Hidden);

	HUD->SetPlayerMode(EPlayerMode::MinerWidget);


}
