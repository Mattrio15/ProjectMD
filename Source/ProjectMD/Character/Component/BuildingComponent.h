// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Component_Info.h"
#include "Components/ActorComponent.h"
#include "BuildingComponent.generated.h"

class AGhostBuilding;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PROJECTMD_API UBuildingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UBuildingComponent();

protected:
	UPROPERTY()
	FGameplayTag mBuildingTag;

	UPROPERTY()
	TObjectPtr<AGhostBuilding> mGhostBuilding;

	bool mOnGhostBuilding = false;
	FVector mGhostBuildingLocation;
	FRotator mGhostBuildingRotation;

protected:
	virtual void BeginPlay() override;

public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UFUNCTION()
	void SetBuildingTag(FGameplayTag Tag);

public: // Set 함수들
	void SetGhostBuildingLocation(const FVector& Location) { mGhostBuildingLocation = Location; }
	void SetGhostBuildingRotation(const FRotator& Rotation) { mGhostBuildingRotation = Rotation; }

public: // Get 함수들
	FRotator GetGhostBuildingRotation();

public:
	void SetRealBuilding();
	
		
};
