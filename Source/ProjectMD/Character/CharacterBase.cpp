// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Component/DefaultInputComponent.h"
#include "Component/WidgetInputComponent.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	mArm = MyObject(USpringArmComponent, "Arm");
	mCamera = MyObject(UCameraComponent, "Camera");

	mArm->SetupAttachment(RootComponent);
	mCamera->SetupAttachment(mArm);

	mDefaultInputComponent = MyObject(UDefaultInputComponent, "DefaultInputComponent");
	mWidgetInputComponent = MyObject(UWidgetInputComponent, "WidgetInputComponent");

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	mArm->bUsePawnControlRotation = true;

}

void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(mAnim))
		GetMesh()->SetAnimInstanceClass(mAnim);
}

void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (!IsValid(mDefaultInputComponent))
	{
		CHECK(" DefaultInput");
		return;
	}
	if (!IsValid(mWidgetInputComponent))
	{
		CHECK(" WidgetInput");
		return;
	}

	mDefaultInputComponent->InitComponent(this, PlayerInputComponent);
	mWidgetInputComponent->InitComponent(this, PlayerInputComponent);

}

void ACharacterBase::ConnectMapping(bool A)
{
	if (IsValid(mDefaultInputComponent))
		mDefaultInputComponent->ConnectMapping(A);
}

