// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingInputComponent.h"
#include "../CharacterBase.h"
#include "../MainHUD.h"

UBuildingInputComponent::UBuildingInputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ObjectFinder(UInputMappingContext, IMC_Building, "/Script/EnhancedInput.InputMappingContext'/Game/Input/Building/IMC_Building.IMC_Building'");
	if (IMC_Building.Succeeded())
		mIMC_Building = IMC_Building.Object;

	ObjectFinder(UInputAction, IA_BuildingRotation, "/Script/EnhancedInput.InputAction'/Game/Input/Building/IA_BuildingRotation.IA_BuildingRotation'");
	if (IA_BuildingRotation.Succeeded())
		mIA_BuildingRotation = IA_BuildingRotation.Object;

	ObjectFinder(UInputAction, IA_BuildingSet, "/Script/EnhancedInput.InputAction'/Game/Input/Building/IA_BuildingSet.IA_BuildingSet'");
	if (IA_BuildingSet.Succeeded())
		mIA_BuildingSet = IA_BuildingSet.Object;
		
	ObjectFinder(UInputAction, IA_BuildingCancel, "/Script/EnhancedInput.InputAction'/Game/Input/Building/IA_BuildingCancel.IA_BuildingCancel'");
	if (IA_BuildingCancel.Succeeded())
		mIA_BuildingCancel = IA_BuildingCancel.Object;

}

void UBuildingInputComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UBuildingInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!mOnBuildingInputComponent || !CHECK(mController) || !CHECK(mCharacter))
		return;
	
	FHitResult Result;
	FVector Start;
	FVector End;
	FRotator CameraRot;
	FVector Location;

	mController->GetPlayerViewPoint(Start, CameraRot);
	End = Start + CameraRot.Vector() * 750;

	bool Collision = GetWorld()->LineTraceSingleByProfile(Result, Start, End, TEXT("BuildingMode"));

	if (Collision)
		Location = Result.ImpactPoint;
	else
	{
		GetWorld()->LineTraceSingleByProfile(Result, End, End + FVector(0, 0, -10000), TEXT("BuildingMode"));
		Location = Result.ImpactPoint;
	}

	mCharacter->SetGhostBuildingLocation(Location);

}

void UBuildingInputComponent::BindAction(UInputComponent* InputComponent)
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

	if (CHECK(mIA_BuildingRotation))
		Input->BindAction(mIA_BuildingRotation, ETriggerEvent::Triggered, this, &UBuildingInputComponent::BuildingRotation);

	if (CHECK(mIA_BuildingSet))
		Input->BindAction(mIA_BuildingSet, ETriggerEvent::Started, this, &UBuildingInputComponent::BuildingSet);

	if (CHECK(mIA_BuildingCancel))
		Input->BindAction(mIA_BuildingCancel, ETriggerEvent::Started, this, &UBuildingInputComponent::BuildingCancel);

}

void UBuildingInputComponent::ConnectMapping(bool A)
{
	if (!CHECK(mController))
		return;

	if (ULocalPlayer* LP = mController->GetLocalPlayer())
	{
		if (UEnhancedInputLocalPlayerSubsystem* EILPS = LP->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>())
		{
			if (A)
				EILPS->AddMappingContext(mIMC_Building, 0);
			else
				EILPS->RemoveMappingContext(mIMC_Building);
		}
	}

	mOnBuildingInputComponent = A;
	if (!mOnBuildingInputComponent)
	{
		mCharacter->SetGhostBuildingLocation(FVector(0, 0, -10000));
		mCharacter->SetGhostBuildingRotation(FRotator(0, 0, 0));
	}
}

void UBuildingInputComponent::BuildingRotation(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();

	if (!CHECK(mCharacter))
		return;

	FRotator Rot = mCharacter->GetGhostBuildingRotation();

	Rot += FRotator(0, Value, 0);

	mCharacter->SetGhostBuildingRotation(Rot);
}

void UBuildingInputComponent::BuildingSet(const FInputActionInstance& Instance)
{
	if (CHECK(mCharacter))
		mCharacter->SetRealBuilding();
}

void UBuildingInputComponent::BuildingCancel(const FInputActionInstance& Instance)
{
	if (!mController)
		return;
	
	AMainHUD* HUD = mController->GetHUD<AMainHUD>();
	if (CHECK(HUD))
		HUD->SetPlayerMode(EPlayerMode::Default);

}
