// C plus Hell Learning Game, All Right Reserved.


#include "UI/CphGameHUD.h"

#include "Blueprint/UserWidget.h"

// Widget drawing
void ACphGameHUD::DrawHUD()
{
    Super::DrawHUD();
}

// Progress bar value in UI
void ACphGameHUD::BeginPlay()
{
    Super::BeginPlay();

    checkf(PlayerWidgetClassHUD,
           TEXT("It is better to set any UI in BP_CphGameHUD blueprint"))

    UUserWidget* PlayerWidgetHUD =
        CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClassHUD);
    if (PlayerWidgetHUD)
    {
        PlayerWidgetHUD->AddToViewport();
    }
}
