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

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	if (!CHECK(Input))
		return;

	if (IsValid(mIA_BuildingClose))
		Input->BindAction(mIA_BuildingClose, ETriggerEvent::Started, this, &UWidgetInputComponent::BuildingClose);

	if (IsValid(mIA_NextPage))
		Input->BindAction(mIA_NextPage, ETriggerEvent::Started, this, &UWidgetInputComponent::NextPage);

}

void UWidgetInputComponent::ConnectMapping(bool A)
{
	if (ULocalPlayer* LP = mController->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* EILPS = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (A)
				EILPS->AddMappingContext(mIMC_Widget, 1);
			else
				EILPS->RemoveMappingContext(mIMC_Widget);
		}
	}
}

void UWidgetInputComponent::BuildingClose(const FInputActionInstance& Instance)
{
	if (!CHECK(mController) || !CHECK(mCharacter))
		return;

	AMainHUD* HUD = mController->GetHUD<AMainHUD>();
	if (!CHECK(HUD))
		return;
	
	HUD->SetPlayerMode(EPlayerMode::Default);

}

void UWidgetInputComponent::NextPage(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();

	bool Next = Value > 0 ? true : false;

	if (!CHECK(mController))
		return;

	AMainHUD* HUD = mController->GetHUD<AMainHUD>();
	if (!CHECK(HUD))
		return;
	
	HUD->NextPageWidget(Next);

}
