// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Component_Info.h"
#include "Components/ActorComponent.h"
#include "BuildingInputComponent.generated.h"

class ACharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMD_API UBuildingInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UBuildingInputComponent();

protected:
	UPROPERTY()
	TObjectPtr<ACharacterBase> mCharacter;
	UPROPERTY()
	TObjectPtr<APlayerController> mController;

	UPROPERTY()
	TObjectPtr<UInputMappingContext> mIMC_Building;
	UPROPERTY()
	TObjectPtr<UInputAction> mIA_BuildingRotation;

	UPROPERTY()
	TObjectPtr<UCameraComponent> mCamera;



	bool mOnBuildingInputComponent = false;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void BindAction(UInputComponent* InputComponent);
	void ConnectMapping(bool A);

protected:
	void BuildingRotation(const FInputActionInstance& Instance);

};
