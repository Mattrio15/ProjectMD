#pragma once

#include "../Game_Info.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/VerticalBox.h"
#include "Components/ScrollBox.h"
#include "Components/CanvasPanel.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"

#include "Widget_Info.generated.h"


UENUM(BlueprintType)
enum class EWidgetType : uint8
{
	None,
	Building
};