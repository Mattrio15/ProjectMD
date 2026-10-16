// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Component_Info.h"
#include "../../Widget/Widget_Info.h"
#include "Components/ActorComponent.h"
#include "WidgetInputComponent.generated.h"

class ACharacterBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMD_API UWidgetInputComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UWidgetInputComponent();

protected:
	UPROPERTY()
	TObjectPtr<ACharacterBase> mCharacter;
	UPROPERTY()
	TObjectPtr<APlayerController> mController;

	UPROPERTY()
	TObjectPtr<UInputMappingContext> mIMC_Widget;
	UPROPERTY()
	TObjectPtr<UInputAction> mIA_Building;
	UPROPERTY()
	TObjectPtr<UInputAction> mIA_NextPage;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	void InitComponent(ACharacterBase* Character, UInputComponent* InputComponent);
	void BindAction(UInputComponent* InputComponent);
	void ConnectMapping(bool A);

protected:
	void Building(const FInputActionInstance& Instance);
	void NextPage(const FInputActionInstance& Instance);
		
};
