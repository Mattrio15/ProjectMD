// Fill out your copyright notice in the Description page of Project Settings.


#include "MainHUD.h"
#include "CharacterBase.h"

void AMainHUD::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PC = GetOwningPlayerController();
	
	if (mMainWidgetClass && PC)
	{
		mMainWidget = CreateWidget<UMainWidget>(PC, mMainWidgetClass);
		if (IsValid(mMainWidget))
			mMainWidget->AddToViewport();
	}

}

void AMainHUD::ToggleWidget(EWidgetType Type)
{
	if (IsValid(mMainWidget))
	{
		ESlateVisibility Visibility = mMainWidget->ToggleWidget(Type);
		if (Visibility == ESlateVisibility::Visible)
			ShowMouse(true);
		else
			ShowMouse(false);
	}
}

void AMainHUD::NextPageWidget(bool A)
{
	if (IsValid(mMainWidget))
		mMainWidget->NextPageWidget(A);
}

void AMainHUD::ShowMouse(bool A)
{
	APlayerController* PC = GetOwningPlayerController();
	if (!IsValid(PC))
	{
		CHECK(" PC");
		return;
	}
	ACharacterBase* CB = Cast<ACharacterBase>(PC->GetCharacter());
	if (!IsValid(CB))
	{
		CHECK(" CB");
		return;
	}
	
	PC->bShowMouseCursor = A;
	CB->ConnectMapping(!A);
	if (A)
	{
		FInputModeGameAndUI Mode;
		Mode.SetHideCursorDuringCapture(false);
		PC->SetInputMode(Mode);
	}
	else
	{
		FInputModeGameOnly Mode;
		PC->SetInputMode(Mode);
	}

}
