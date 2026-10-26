// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building_Info.h"
#include "GameFramework/Actor.h"
#include "GhostBuilding.generated.h"

UCLASS()
class PROJECTMD_API AGhostBuilding : public AActor
{
	GENERATED_BODY()
	
public:
	AGhostBuilding();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> mRoot;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> mBox;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> mMesh;

	FGameplayTag mBuildingTag;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

protected:
	UFUNCTION()
	void SetBuildingTag(FGameplayTag Tag);
	UFUNCTION()
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
