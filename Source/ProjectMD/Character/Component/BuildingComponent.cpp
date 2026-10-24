// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingComponent.h"
#include "../../Subsystem/BuildingSubsystem.h"

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
}

void UBuildingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void UBuildingComponent::SetBuildingTag(FGameplayTag Tag)
{
	Test(__FUNCTION__);
}

