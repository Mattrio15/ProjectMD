// Fill out your copyright notice in the Description page of Project Settings.


#include "WidgetInputComponent.h"
#include "../CharacterBase.h"
#include "../MainHUD.h"

UWidgetInputComponent::UWidgetInputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ObjectFinder(UInputMappingContext, IMC_Widget, "/Script/EnhancedInput.InputMappingContext'/Game/Input/Widget/IMC_Widget.IMC_Widget'");
	if (IMC_Widget.Succeeded())
		mIMC_Widget = IMC_Widget.Object;

	ObjectFinder(UInputAction, IA_BuildingClose, "/Script/EnhancedInput.InputAction'/Game/Input/Widget/IA_BuildingClose.IA_BuildingClose'");
	if (IA_BuildingClose.Succeeded())
		mIA_BuildingClose = IA_BuildingClose.Object;

	ObjectFinder(UInputAction, IA_NextPage, "/Script/EnhancedInput.InputAction'/Game/Input/Widget/IA_NextPage.IA_NextPage'");
	if (IA_NextPage.Succeeded())
		mIA_NextPage = IA_NextPage.Object;


	ObjectFinder(UInputMappingContext, IMC_Miner, "/Script/EnhancedInput.InputMappingContext'/Game/Input/Widget/MinerWidget/IMC_Miner.IMC_Miner'");
	if (IMC_Miner.Succeeded())
		mIMC_Miner = IMC_Miner.Object;

	ObjectFinder(UInputAction, IA_MinerClose, "/Script/EnhancedInput.InputAction'/Game/Input/Widget/MinerWidget/IA_MinerClose.IA_MinerClose'");
	if (IA_MinerClose.Succeeded())
		mIA_MinerClose = IA_MinerClose.Object;

}

void UWidgetInputComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UWidgetInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UWidgetInputComponent::BindAction(UInputComponent* InputComponent)
{
	mCharacter = GetOwner<ACharacterBase>();
	if (!CHECK(mCharacter))
		return;

	mController = mCharacter->GetController<APlayerController>();
	if (!CHECK(mController))
		return;

	AMainHUD* HUD = mController->GetHUD<AMainHUD>();
	if (CHECK(HUD))
		mHUD = HUD;

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	if (!CHECK(Input))
		return;

	if (IsValid(mIA_BuildingClose))
		Input->BindAction(mIA_BuildingClose, ETriggerEvent::Started, this, &UWidgetInputComponent::BuildingClose);

	if (IsValid(mIA_NextPage))
		Input->BindAction(mIA_NextPage, ETriggerEvent::Started, this, &UWidgetInputComponent::NextPage);



	if (CHECK(mIA_MinerClose))
		Input->BindAction(mIA_MinerClose, ETriggerEvent::Started, this, &UWidgetInputComponent::MinerClose);

}

void UWidgetInputComponent::ConnectMapping(bool A)
{
	UInputMappingContext* Context = nullptr;

	if (!CHECK(mHUD))
		return;

	EPlayerMode Mode = mHUD->GetPlayerMode();

	switch (Mode)
	{
	case EPlayerMode::BuildingWidget: Context = mIMC_Widget; break;
	case EPlayerMode::MinerWidget: Context = mIMC_Miner; break;

	default:
		break;
	}


	if (ULocalPlayer* LP = mController->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* EILPS = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (A)
				EILPS->AddMappingContext(Context, 1);
			else
			{
				EILPS->RemoveMappingContext(mIMC_Widget);
				EILPS->RemoveMappingContext(mIMC_Miner);
			}
		}
	}
}

void UWidgetInputComponent::BuildingClose(const FInputActionInstance& Instance)
{
	if (!CHECK(mController) || !CHECK(mCharacter) || !CHECK(mHUD))
		return;

	mHUD->SetPlayerMode(EPlayerMode::Default);

}

void UWidgetInputComponent::NextPage(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();

	bool Next = Value > 0 ? true : false;

	if (!CHECK(mController) ||!CHECK(mHUD))
		return;
		
	mHUD->NextPageWidget(Next);

}

void UWidgetInputComponent::MinerClose(const FInputActionInstance& Instance)
{
	if (CHECK(mHUD))
		mHUD->SetPlayerMode(EPlayerMode::Default);
}
