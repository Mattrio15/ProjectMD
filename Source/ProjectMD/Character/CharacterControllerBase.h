// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Game_Info.h"
#include "GameFramework/PlayerController.h"
#include "CharacterControllerBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnBuildingUnlock, FGameplayTag, BuildingTag);

UCLASS()
class PROJECTMD_API ACharacterControllerBase : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	FGameplayTagContainer TestUnlockTag;

public:
	FOnBuildingUnlock OnBuildingUnlock;


protected:
	virtual void BeginPlay() override;

protected:
	void CheatUnlockBuilding(const TArray<FString>& Args);
	
public:
	UFUNCTION(BlueprintCallable)
	void AddUnlockTag(FGameplayTag Tag);

};
