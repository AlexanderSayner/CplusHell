// C plus Hell Learning Game, All Right Reserved.


#include "UI/CphGameHUD.h"

#include "Blueprint/UserWidget.h"
#include "Engine/Canvas.h"

// Widget drawing
void ACphGameHUD::DrawHUD()
{
    Super::DrawHUD();

    DrawCrossHair();
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

// Drawing the cross
void ACphGameHUD::DrawCrossHair()
{
    const TInterval<float> Center(Canvas->SizeX * 0.5f, Canvas->SizeY * 0.5f);

    const float HalfLineSize = 10.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LinearColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize,
             Center.Max,
             Center.Min + HalfLineSize,
             Center.Max,
             LinearColor,
             LineThickness);
    DrawLine(Center.Min,
             Center.Max - HalfLineSize,
             Center.Min,
             Center.Max + HalfLineSize,
             LinearColor,
             LineThickness);
}
