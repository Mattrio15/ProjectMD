// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Game_Info.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UDefaultInputComponent;
class UWidgetInputComponent;
class UBuildingInputComponent;

class UBuildingComponent;

UCLASS()
class PROJECTMD_API ACharacterBase : public ACharacter
{
	GENERATED_BODY()

public:
	ACharacterBase();

protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<USpringArmComponent> mArm;
	UPROPERTY(EditAnywhere)
	TObjectPtr<UCameraComponent> mCamera;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UDefaultInputComponent> mDefaultInputComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UWidgetInputComponent> mWidgetInputComponent;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBuildingInputComponent> mBuildingInputComponent;

	UPROPERTY()
	TObjectPtr<UBuildingComponent> mBuildingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UAnimInstance> mAnim;

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void ConnectMapping(bool Default, bool Widget, bool Building);
	void SetBuildingTag(FGameplayTag Tag);

public:
	UCameraComponent* GetCamera() { return mCamera; }

};
