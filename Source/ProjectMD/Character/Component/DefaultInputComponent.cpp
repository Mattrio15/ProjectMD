// Fill out your copyright notice in the Description page of Project Settings.


#include "DefaultInputComponent.h"
#include "../CharacterBase.h"
#include "../MainHUD.h"

UDefaultInputComponent::UDefaultInputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ObjectFinder(UInputMappingContext, IMC_Default, "/Script/EnhancedInput.InputMappingContext'/Game/Input/Default/IMC_Default.IMC_Default'");
	if (IMC_Default.Succeeded())
		mIMC_Default = IMC_Default.Object;
	
	ObjectFinder(UInputAction, IA_Move, "/Script/EnhancedInput.InputAction'/Game/Input/Default/IA_Default_Move.IA_Default_Move'");
	if (IA_Move.Succeeded())
		mIA_Move = IA_Move.Object;
	
	ObjectFinder(UInputAction, IA_CameraRotation, "/Script/EnhancedInput.InputAction'/Game/Input/Default/IA_CameraRotation.IA_CameraRotation'");
	if (IA_CameraRotation.Succeeded())
		mIA_CameraRotation = IA_CameraRotation.Object;
	
	ObjectFinder(UInputAction, IA_Jump, "/Script/EnhancedInput.InputAction'/Game/Input/Default/IA_Default_Jump.IA_Default_Jump'");
	if (IA_Jump.Succeeded())
		mIA_Jump = IA_Jump.Object;

	ObjectFinder(UInputAction, IA_Building, "/Script/EnhancedInput.InputAction'/Game/Input/Default/IA_Building.IA_Building'");
	if (IA_Building.Succeeded())
		mIA_Building = IA_Building.Object;

}

void UDefaultInputComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UDefaultInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UDefaultInputComponent::BindAction(UInputComponent* InputComponent)
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

	if(IsValid(mIA_Move))
		Input->BindAction(mIA_Move, ETriggerEvent::Triggered, this, &UDefaultInputComponent::Move);

	if (IsValid(mIA_CameraRotation))
		Input->BindAction(mIA_CameraRotation, ETriggerEvent::Triggered, this, &UDefaultInputComponent::CameraRotation);

	if (IsValid(mIA_Jump))
		Input->BindAction(mIA_Jump, ETriggerEvent::Started, this, &UDefaultInputComponent::Jump);

	if (IsValid(mIA_Building))
		Input->BindAction(mIA_Building, ETriggerEvent::Started, this, &UDefaultInputComponent::Building);

}

void UDefaultInputComponent::ConnectMapping(bool A)
{
	if (ULocalPlayer* LP = mController->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* EILPS = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (A)
				EILPS->AddMappingContext(mIMC_Default, 0);
			else
				EILPS->RemoveMappingContext(mIMC_Default);
		}
	}
}

void UDefaultInputComponent::Move(const FInputActionInstance& Instance)
{
	FVector2D Value = Instance.GetValue().Get<FVector2D>();
	
	if (!CHECK(mCharacter))
		return;

	float Yaw = mCharacter->GetControlRotation().Yaw;
	FRotator Rot = FRotator(0, Yaw, 0);
	
	FVector ForwardVector = FRotationMatrix(Rot).GetUnitAxis(EAxis::X);
	FVector RightVector = FRotationMatrix(Rot).GetUnitAxis(EAxis::Y);
	
	mCharacter->AddMovementInput(ForwardVector, Value.X);
	mCharacter->AddMovementInput(RightVector, Value.Y);

}

void UDefaultInputComponent::CameraRotation(const FInputActionInstance& Instance)
{
	FVector2D Value = Instance.GetValue().Get<FVector2D>();

	if (!CHECK(mCharacter))
		return;

	mCharacter->AddControllerPitchInput(-Value.Y);
	mCharacter->AddControllerYawInput(Value.X);
	
}

void UDefaultInputComponent::Jump(const FInputActionInstance& Instance)
{
	if (!CHECK(mCharacter))
		return;

	mCharacter->Jump();

}

void UDefaultInputComponent::Building(const FInputActionInstance& Instance)
{
	if (!CHECK(mController) || !CHECK(mCharacter))
		return;

	AMainHUD* HUD = mController->GetHUD<AMainHUD>();
	if (!CHECK(HUD))
		return;
	
	HUD->SetPlayerMode(EPlayerMode::BuildingWidget);

}
