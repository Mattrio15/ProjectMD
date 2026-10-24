// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../../Game_Info.h"
#include "GameFramework/Actor.h"
#include "BuildingMinerBase.generated.h"

UCLASS()
class PROJECTMD_API ABuildingMinerBase : public AActor
{
	GENERATED_BODY()
	
public:
	ABuildingMinerBase();

protected:
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USceneComponent> mRoot;
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UBoxComponent> mBox;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMeshComponent> mMesh;

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

};
