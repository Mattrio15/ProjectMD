// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingMinerBase.h"

ABuildingMinerBase::ABuildingMinerBase()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = MyObject(USceneComponent, "Root");
	mBox = MyObject(UBoxComponent, "Box");
	mMesh = MyObject(USkeletalMeshComponent, "Mesh");

	SetRootComponent(mRoot);
	mBox->SetupAttachment(mRoot);
	mMesh->SetupAttachment(mRoot);

	mBox->SetCollisionProfileName(TEXT("BuildingMiner"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ABuildingMinerBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABuildingMinerBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

