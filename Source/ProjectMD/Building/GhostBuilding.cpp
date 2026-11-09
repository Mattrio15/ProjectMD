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

	ObjectFinder(UMaterialInstance, EnableMaterial, "/Script/Engine.MaterialInstanceConstant'/Game/Material/Building/MI_GhostBuildingEnable.MI_GhostBuildingEnable'");
	if (EnableMaterial.Succeeded())
		mEnableMaterial = EnableMaterial.Object;

	ObjectFinder(UMaterialInstance, DisableMaterial, "/Script/Engine.MaterialInstanceConstant'/Game/Material/Building/MI_GhostBuildingDisable.MI_GhostBuildingDisable'");
	if (DisableMaterial.Succeeded())
		mDisableMaterial = DisableMaterial.Object;

	// 수정 및 지울 것
	mBox->bHiddenInGame = false;
	mMesh->SetRelativeScale3D(FVector(4));

	mTestArrow = MyObject(UArrowComponent, "TestArrow");
	mTestArrow->SetupAttachment(mBox);
	mTestArrow->bHiddenInGame = false;
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

	FVector BoxExtent = Data.BoxExtent;
	mBox->SetBoxExtent(BoxExtent);
	mBox->SetRelativeLocation(FVector(0, 0, BoxExtent.Z));

	SetGhostMaterial(true);

}

void AGhostBuilding::SetGhostMaterial(bool A)
{
	UMaterialInstance* MI = A ? mEnableMaterial : mDisableMaterial;

	if (!CHECK(MI) || !CHECK(mMesh))
		return;

	int32 Max = mMesh->GetNumMaterials();
	for (int32 i = 0; i < Max; ++i)
		mMesh->SetMaterial(i, MI);

	mCanBuilding = A;
}

void AGhostBuilding::BoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	SetGhostMaterial(false);
	mOverlapCount += 1;
}

void AGhostBuilding::BoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	mOverlapCount = FMath::Max(0, mOverlapCount - 1);
	if (mOverlapCount < 1)
		SetGhostMaterial(true);
}
