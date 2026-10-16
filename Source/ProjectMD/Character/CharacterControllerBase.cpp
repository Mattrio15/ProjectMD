// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterControllerBase.h"

void ACharacterControllerBase::BeginPlay()
{
	Super::BeginPlay();

	IConsoleManager::Get().RegisterConsoleCommand(
		TEXT("UnlockBuilding"),
		TEXT("해금 치트 ex : UnlockBuilding Building.Miner.Stone"),
		FConsoleCommandWithArgsDelegate::CreateUObject(this, &ACharacterControllerBase::CheatUnlockBuilding),
		ECVF_Cheat
	);
}

void ACharacterControllerBase::CheatUnlockBuilding(const TArray<FString>& Args)
{
	if (Args.Num() == 0)
	{
		Log("사용법 : UnlockBuilding [태그이름]");
		return;
	}
	FString TagStr = Args[0];
	FGameplayTag TargetTag = FGameplayTag::RequestGameplayTag(FName(*TagStr), false);

	if (!TargetTag.IsValid())
	{
		Log("유효하지 않은 태그 : %s", *TagStr);
		return;
	}

	AddUnlockTag(TargetTag);

}

void ACharacterControllerBase::AddUnlockTag(FGameplayTag Tag)
{
	if (!TestUnlockTag.HasTag(Tag))
	{
		TestUnlockTag.AddTag(Tag);
		OnBuildingUnlock.Broadcast(Tag);
	}

}
