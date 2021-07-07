// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CphGameHUD.generated.h"

/**
 * In game UI drawing
 * 
 * UCphPlayerWidgetHUD (User Interface) contains logic for WBP_GameInterfaceHUD designer
 * PlayerWidgetClassHUD that is set in BP_CphGameHUD as WBP_GameInterfaceHUD drawn by CphGameHUD
 * BP_CphGameHUD is set up in World Settings like thing that can draw an interface
 *
 * BP_CphGameHUD is main controller for countless User Interfaces just like WBP_GameInterfaceHUD
 */
UCLASS()
class CPLUSHELL_API ACphGameHUD final : public AHUD
{
    GENERATED_BODY()

public:
    // Widget drawing
    virtual void DrawHUD() override;

protected:
    // Accessible widgets 
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    TSubclassOf<UUserWidget> PlayerWidgetClassHUD;

    // Creating player HUD widget
    virtual void BeginPlay() override;
};
