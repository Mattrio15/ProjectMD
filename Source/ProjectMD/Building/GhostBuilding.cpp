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

	mBox->SetCollisionProfileName(TEXT("GhostBuilding"));
	mMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	mBox->bHiddenInGame = false;

	mMesh->SetRelativeScale3D(FVector(4));

}

void AGhostBuilding::BeginPlay()
{
	Super::BeginPlay();
	
	UBuildingSubsystem* BS = GetGameInstance()->GetSubsystem<UBuildingSubsystem>();
	if (!CHECK(BS))
		return;

	BS->OnGetBuildingTag.AddDynamic(this, &AGhostBuilding::SetBuildingTag);

	mBox->OnComponentBeginOverlap.AddDynamic(this, &AGhostBuilding::BoxBeginOverlap);
	mBox->OnComponentEndOverlap.AddDynamic(this, &AGhostBuilding::BoxEndOverlap);

}

void AGhostBuilding::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGhostBuilding::SetBuildingTag(FGameplayTag Tag)
{
	UBuildingSubsystem* BS = GetGameInstance()->GetSubsystem<UBuildingSubsystem>();
	if (!CHECK(BS))
		return;

	FBuildingData Data;
	if (!BS->GetBuildingData(Tag, Data))
		return;

	USkeletalMesh* Mesh = Data.Mesh;
	if (!CHECK(Mesh))
		return;

	mMesh->SetSkeletalMesh(Mesh);
	mBox->SetBoxExtent(FVector(50));
	mBox->SetRelativeLocation(FVector(0, 0, 50));

}

void AGhostBuilding::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AGhostBuilding::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}
