// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Component_Info.h"
#include "Components/ActorComponent.h"
#include "DefaultInputComponent.generated.h"

class ACharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMD_API UDefaultInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDefaultInputComponent();

protected:
	UPROPERTY()
	TObjectPtr<ACharacterBase> mCharacter;
	UPROPERTY()
	TObjectPtr<APlayerController> mController;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInputMappingContext> mIMC_Default;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInputAction> mIA_Move;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInputAction> mIA_CameraRotation;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UInputAction> mIA_Jump;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void InitComponent(ACharacterBase* Character, UInputComponent* InputComponent);
	void BindAction(UInputComponent* InputComponent);
	void ConnectMapping(bool A);
	
protected:
	void Move(const FInputActionInstance& Instance);
	void CameraRotation(const FInputActionInstance& Instance);
	void Jump(const FInputActionInstance& Instance);
	


};
