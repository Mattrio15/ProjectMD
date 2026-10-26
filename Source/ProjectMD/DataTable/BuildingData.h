#pragma once

#include "../Game_Info.h"
#include "BuildingData.generated.h"

USTRUCT(BlueprintType)
struct FBuildingCostItem
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag ItemTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Count = 1;

};

UENUM(BlueprintType)
enum class EBuildingType:uint8
{
	Miner,
	Crafting,
	Storage,
	Power,
	Structure,
	Light,
	ETC
};

USTRUCT(BlueprintType)
struct FBuildingData:public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Desc;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* Image;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> SpawnActorClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<USkeletalMesh> Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FBuildingCostItem> CostList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BuildTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<FGameplayTag> UnlockTag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Category;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EBuildingType FirstOrder;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 SecondOrder = 0;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ThirdOrder = 0;


};