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

	UPROPERTY()
	TObjectPtr<UMaterialInstance> mEnableMaterial;
	UPROPERTY()
	TObjectPtr<UMaterialInstance> mDisableMaterial;

	FGameplayTag mBuildingTag;

	int32 mOverlapCount = 0;

	bool mCanBuilding = true;

	UPROPERTY()
	TObjectPtr<UArrowComponent> mTestArrow;


protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	bool GetCanBuilding() { return mCanBuilding; }

protected:
	UFUNCTION()
	void SetBuildingTag(FGameplayTag Tag);

	void SetGhostMaterial(bool A);

	UFUNCTION()
	void BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);


};
