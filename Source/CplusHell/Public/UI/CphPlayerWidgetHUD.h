// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CphPlayerWidgetHUD.generated.h"

/**
 * In game user interface
 */
UCLASS()
class CPLUSHELL_API UCphPlayerWidgetHUD final : public UUserWidget
{
    GENERATED_BODY()

public:
    // Progress bar value in UI
    UFUNCTION(BlueprintCallable, Category="UI")
    float GetHealthRatio() const;
};
