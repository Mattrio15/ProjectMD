// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingComponent.h"
#include "../../Subsystem/BuildingSubsystem.h"
#include "../../Building/GhostBuilding.h"

UBuildingComponent::UBuildingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;

}


void UBuildingComponent::BeginPlay()
{
	Super::BeginPlay();

	UBuildingSubsystem* BS = GetWorld()->GetGameInstance()->GetSubsystem<UBuildingSubsystem>();
	if (!CHECK(BS))
		return;

	BS->OnGetBuildingTag.AddDynamic(this, &UBuildingComponent::SetBuildingTag);

	mGhostBuilding = GetWorld()->SpawnActor<AGhostBuilding>(AGhostBuilding::StaticClass());
	if (!CHECK(mGhostBuilding))
		return;

	mGhostBuilding->SetActorHiddenInGame(true);

}

void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (!mOnGhostBuilding)
		return;

	mGhostBuilding->SetActorLocation(mGhostBuildingLocation);
	mGhostBuilding->SetActorRotation(mGhostBuildingRotation);

}

void UBuildingComponent::SetBuildingTag(FGameplayTag Tag)
{
	mBuildingTag = Tag;

	if (!CHECK(mGhostBuilding))
		return;

	mGhostBuilding->SetActorHiddenInGame(false);

	mOnGhostBuilding = true;

}

FRotator UBuildingComponent::GetGhostBuildingRotation()
{
	if (CHECK(mGhostBuilding))
		return mGhostBuilding->GetActorRotation();

	return FRotator();
}

void UBuildingComponent::SetRealBuilding()
{
	UBuildingSubsystem* BS = GetWorld()->GetGameInstance()->GetSubsystem<UBuildingSubsystem>();
	if (!CHECK(BS))
		return;

	FBuildingData Data;
	if (!BS->GetBuildingData(mBuildingTag, Data))
		return;

	if (!Data.SpawnActorClass)
		return;

	AActor* RealBuilding = GetWorld()->SpawnActor(Data.SpawnActorClass);
	RealBuilding->SetActorLocation(mGhostBuildingLocation);
	RealBuilding->SetActorRotation(mGhostBuildingRotation);
}
