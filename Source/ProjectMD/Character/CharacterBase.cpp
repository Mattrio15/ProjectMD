// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"
#include "Component/DefaultInputComponent.h"
#include "Component/WidgetInputComponent.h"
#include "Component/BuildingInputComponent.h"
#include "Component/BuildingComponent.h"

ACharacterBase::ACharacterBase()
{
	PrimaryActorTick.bCanEverTick = true;

	mArm = MyObject(USpringArmComponent, "Arm");
	mCamera = MyObject(UCameraComponent, "Camera");

	mArm->SetupAttachment(RootComponent);
	mCamera->SetupAttachment(mArm);
	mArm->TargetArmLength = 200;
	mArm->SetRelativeLocation(FVector(0, 0, 75));
	mCamera->SetRelativeLocation(FVector(0, 75, 0));

	mDefaultInputComponent = MyObject(UDefaultInputComponent, "DefaultInputComponent");
	mWidgetInputComponent = MyObject(UWidgetInputComponent, "WidgetInputComponent");
	mBuildingInputComponent = MyObject(UBuildingInputComponent, "BuildingInputComponent");

	mBuildingComponent = MyObject(UBuildingComponent, "BuildingComponent");

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;

	bUseControllerRotationYaw = false;

	mArm->bUsePawnControlRotation = true;

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Character"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

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

	if (!CHECK(mDefaultInputComponent) || !CHECK(mWidgetInputComponent) || !CHECK(mBuildingInputComponent))
		return;

	mDefaultInputComponent->BindAction(PlayerInputComponent);
	mWidgetInputComponent->BindAction(PlayerInputComponent);
	mBuildingInputComponent->BindAction(PlayerInputComponent);

	ConnectMapping(true, false, false);

}

void ACharacterBase::ConnectMapping(bool Default, bool Widget, bool Building)
{
	if (!CHECK(mDefaultInputComponent) || !CHECK(mWidgetInputComponent) || !CHECK(mBuildingInputComponent))
		return;

	mDefaultInputComponent->ConnectMapping(Default);
	mWidgetInputComponent->ConnectMapping(Widget);
	mBuildingInputComponent->ConnectMapping(Building);

}
