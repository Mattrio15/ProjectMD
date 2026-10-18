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

void AMainHUD::ShowMouse(bool A)
{
	APlayerController* PC = GetOwningPlayerController();
	if (!CHECK(PC))
		return;
	ACharacterBase* CB = Cast<ACharacterBase>(PC->GetCharacter());
	if (!CHECK(CB))
		return;

	PC->bShowMouseCursor = A;

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

FPlayerMode* AMainHUD::GetPlayerMode(EPlayerMode Mode)
{
	if (!CHECK(mPlayerModeTable))
		return nullptr;

	TArray<FPlayerMode*> PlayerModeArray;
	mPlayerModeTable->GetAllRows<FPlayerMode>(TEXT(__FUNCTION__), PlayerModeArray);

	int32 Max = PlayerModeArray.Num();
	for (int32 i = 0; i < Max; ++i)
	{
		FPlayerMode* PlayerMode = PlayerModeArray[i];
		if (PlayerMode->Mode == Mode)
			return PlayerMode;
	}

	return nullptr;
}

void AMainHUD::SetPlayerMode(EPlayerMode Mode)
{
	APlayerController* PC = GetOwningPlayerController();
	if (!CHECK(PC))
		return;
	ACharacterBase* CB = Cast<ACharacterBase>(PC->GetCharacter());
	if (!CHECK(CB))
		return;
	if (!CHECK(mMainWidget))
		return;

	FPlayerMode* PlayerMode = GetPlayerMode(Mode);
	if (!PlayerMode)
		return;

	ShowMouse(PlayerMode->ShowMouse);

	CB->ConnectMapping(PlayerMode->DefaultInput, PlayerMode->WidgetInput, PlayerMode->BuildingModeInput);

	int32 Max = PlayerMode->WidgetVisibility.Num();
	for (int32 i = 0; i < Max; ++i)
	{
		FWidgetVisibilityInfo Info = PlayerMode->WidgetVisibility[i];
		mMainWidget->ShowWidget(Info.WidgetType, Info.Visibility);
	}

}

void AMainHUD::NextPageWidget(bool A)
{
	if (IsValid(mMainWidget))
		mMainWidget->NextPageWidget(A);
}
