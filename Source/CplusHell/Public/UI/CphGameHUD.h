// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CphGameHUD.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSHELL_API ACphGameHUD final : public AHUD
{
    GENERATED_BODY()

public:
    virtual void DrawHUD() override;

private:
    // Drawing the cross
    void DrawCrossHair();
};
