// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostBuilding.h"

AGhostBuilding::AGhostBuilding()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = MyObject(USceneComponent, "Root");
	mMesh = MyObject(USkeletalMeshComponent, "Mesh");

	SetRootComponent(mRoot);
	mMesh->SetupAttachment(mRoot);


}

void AGhostBuilding::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGhostBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

