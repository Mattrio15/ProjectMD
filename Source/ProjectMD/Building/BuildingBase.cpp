// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingBase.h"

ABuildingBase::ABuildingBase()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = MyObject(USceneComponent, "Root");
	mBox = MyObject(UBoxComponent, "Box");
	mMesh = MyObject(USkeletalMeshComponent, "Mesh");

	SetRootComponent(mRoot);
	mBox->SetupAttachment(mRoot);
	mMesh->SetupAttachment(mRoot);

	mBox->SetCollisionProfileName(TEXT("RealBuilding"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void ABuildingBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABuildingBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

