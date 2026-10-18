// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Game_Info.h"
#include "../Widget/MainWidget.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UMainWidget;

UENUM(BlueprintType)
enum class EPlayerMode :uint8
{
	Default,
	BuildingWidget,
	BuildingMode
};

USTRUCT(BlueprintType)
struct FWidgetVisibilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EWidgetType WidgetType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Visibility;
};

USTRUCT(BlueprintType)
struct FPlayerMode:public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "플레이어 모드")
	EPlayerMode Mode;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "마우스 보이기")
	bool ShowMouse;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "입력 모드")
	bool DefaultInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "입력 모드")
	bool WidgetInput;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "입력 모드")
	bool BuildingModeInput;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "위젯 보이기")
	TArray<FWidgetVisibilityInfo> WidgetVisibility;

	FPlayerMode()
	{
		WidgetVisibility.Emplace(FWidgetVisibilityInfo(EWidgetType::Building, false));
		WidgetVisibility.Emplace(FWidgetVisibilityInfo(EWidgetType::BuildingMode, false));
	}

};

UCLASS()
class PROJECTMD_API AMainHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMainWidget> mMainWidgetClass;
	UPROPERTY()
	TObjectPtr<UMainWidget> mMainWidget;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<UDataTable> mPlayerModeTable;

		
public:
	virtual void BeginPlay() override;

protected:
	void ShowMouse(bool A);
	FPlayerMode* GetPlayerMode(EPlayerMode Mode);

public:
	void SetPlayerMode(EPlayerMode Mode);

	void NextPageWidget(bool A);


};
