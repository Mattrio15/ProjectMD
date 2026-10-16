// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Game_Info.h"
#include "../Widget/MainWidget.h"
#include "GameFramework/HUD.h"
#include "MainHUD.generated.h"

class UMainWidget;

UCLASS()
class PROJECTMD_API AMainHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UMainWidget> mMainWidgetClass;
	UPROPERTY()
	TObjectPtr<UMainWidget> mMainWidget;

		
public:
	virtual void BeginPlay() override;

public:
	void ToggleWidget(EWidgetType Type);
	void NextPageWidget(bool A);

protected:
	void ShowMouse(bool A);

};
