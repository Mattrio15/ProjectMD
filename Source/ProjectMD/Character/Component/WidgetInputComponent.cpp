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

	ObjectFinder(UInputAction, IA_Building, "/Script/EnhancedInput.InputAction'/Game/Input/Widget/IA_Building.IA_Building'");
	if (IA_Building.Succeeded())
		mIA_Building = IA_Building.Object;

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

void UWidgetInputComponent::InitComponent(ACharacterBase* Character, UInputComponent* InputComponent)
{
	mCharacter = Character;
	if (!IsValid(mCharacter))
	{
		CHECK(" mCharacter");
		return;
	}

	mController = mCharacter->GetController<APlayerController>();
	if (!IsValid(mController))
	{
		CHECK(" mController");
		return;
	}


	BindAction(InputComponent);

	ConnectMapping(true);
}

void UWidgetInputComponent::BindAction(UInputComponent* InputComponent)
{
	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);

	if (!IsValid(Input))
	{
		CHECK("Input");
		return;
	}

	if (IsValid(mIA_Building))
		Input->BindAction(mIA_Building, ETriggerEvent::Started, this, &UWidgetInputComponent::Building);

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

void UWidgetInputComponent::Building(const FInputActionInstance& Instance)
{
	AMainHUD* HUD = mController->GetHUD<AMainHUD>();

	if (!IsValid(HUD))
	{
		CHECK(" HUD");
		return;
	}

	HUD->ToggleWidget(EWidgetType::Building);

}

void UWidgetInputComponent::NextPage(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();

	bool Next = Value > 0 ? true : false;

	AMainHUD* HUD = mController->GetHUD<AMainHUD>();
	if (!IsValid(HUD))
	{
		CHECK(" HUD");
		return;
	}
	
	HUD->NextPageWidget(Next);

}
