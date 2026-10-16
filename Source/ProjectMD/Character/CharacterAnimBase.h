// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Game_Info.h"
#include "Animation/AnimInstance.h"
#include "CharacterAnimBase.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTMD_API UCharacterAnimBase : public UAnimInstance
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool mIsMoving = false;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool mIsInAir = false;


};
