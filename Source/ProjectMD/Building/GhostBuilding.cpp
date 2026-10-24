// Fill out your copyright notice in the Description page of Project Settings.


#include "GhostBuilding.h"
#include "../Subsystem/BuildingSubsystem.h"

AGhostBuilding::AGhostBuilding()
{
	PrimaryActorTick.bCanEverTick = true;

	mRoot = MyObject(USceneComponent, "Root");
	mBox = MyObject(UBoxComponent, "Box");
	mMesh = MyObject(USkeletalMeshComponent, "Mesh");

	SetRootComponent(mRoot);
	mBox->SetupAttachment(mRoot);
	mMesh->SetupAttachment(mRoot);

	mBox->SetCollisionProfileName(TEXT("GhostBuiding"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

}

void AGhostBuilding::BeginPlay()
{
	Super::BeginPlay();
	
	UBuildingSubsystem* BS = GetGameInstance()->GetSubsystem<UBuildingSubsystem>();
	if (!CHECK(BS))
		return;

	BS->OnGetBuildingTag.AddDynamic(this, &AGhostBuilding::SetBuildingTag);
}

void AGhostBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGhostBuilding::SetBuildingTag(FGameplayTag Tag)
{
	Test(__FUNCTION__);
}

