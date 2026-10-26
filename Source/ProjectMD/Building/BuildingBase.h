// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Building_Info.h"
#include "GameFramework/Actor.h"
#include "BuildingBase.generated.h"

UCLASS()
class PROJECTMD_API ABuildingBase : public AActor
{
	GENERATED_BODY()
	
public:
	ABuildingBase();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> mRoot;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> mBox;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USkeletalMeshComponent> mMesh;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
