// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingInputComponent.h"
#include "../CharacterBase.h"

UBuildingInputComponent::UBuildingInputComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

	ObjectFinder(UInputMappingContext, IMC_Building, "/Script/EnhancedInput.InputMappingContext'/Game/Input/Building/IMC_Building.IMC_Building'");
	if (IMC_Building.Succeeded())
		mIMC_Building = IMC_Building.Object;

	ObjectFinder(UInputAction, IA_BuildingRotation, "/Script/EnhancedInput.InputAction'/Game/Input/Building/IA_BuildingRotation.IA_BuildingRotation'");
	if (IA_BuildingRotation.Succeeded())
		mIA_BuildingRotation = IA_BuildingRotation.Object;

}

void UBuildingInputComponent::BeginPlay()
{
	Super::BeginPlay();

}

void UBuildingInputComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!mOnBuildingInputComponent)
		return;
	
	FHitResult Result;
	FVector Start = mCamera->GetComponentLocation();
	FVector End = Start + mCamera->GetForwardVector() * 750;
	bool Collision = GetWorld()->LineTraceSingleByProfile(Result, Start, End, TEXT("GhostBuilding"));
	FColor Color = Collision ? FColor::Red : FColor::Green;
	if(Collision)
		End = Result.ImpactPoint;
	else
	{
		DrawDebugSphere(GetWorld(), End, 10, 10, Color, false, 1);
		GetWorld()->LineTraceSingleByProfile(Result, End, End + FVector(0, 0, -10000), TEXT("GhostBuilding"));
		End = Result.ImpactPoint;
	}
	DrawDebugSphere(GetWorld(), End, 10, 10, Color, false, 1);

}

void UBuildingInputComponent::BindAction(UInputComponent* InputComponent)
{
	mCharacter = GetOwner<ACharacterBase>();
	if (!CHECK(mCharacter))
		return;

	mCamera = mCharacter->GetCamera();

	mController = mCharacter->GetController<APlayerController>();
	if (!CHECK(mController))
		return;

	UEnhancedInputComponent* Input = Cast<UEnhancedInputComponent>(InputComponent);
	if (!CHECK(Input))
		return;

	if (IsValid(mIA_BuildingRotation))
		Input->BindAction(mIA_BuildingRotation, ETriggerEvent::Triggered, this, &UBuildingInputComponent::BuildingRotation);

}

void UBuildingInputComponent::ConnectMapping(bool A)
{
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
}

void UBuildingInputComponent::BuildingRotation(const FInputActionInstance& Instance)
{
	float Value = Instance.GetValue().Get<float>();

	Test("Value : %f", Value);
}

