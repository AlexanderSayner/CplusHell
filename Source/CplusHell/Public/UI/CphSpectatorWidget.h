// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CphSpectatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSHELL_API UCphSpectatorWidget final : public UUserWidget
{
    GENERATED_BODY()

public:
    // Sets Countdown Time when it is possible to get it in Blueprint
    UFUNCTION(BlueprintCallable, Category="UI")
    bool GetRespawnTime(int32& CountdownTime) const;
};
