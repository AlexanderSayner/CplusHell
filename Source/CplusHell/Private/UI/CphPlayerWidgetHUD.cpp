// C plus Hell Learning Game, All Right Reserved.


#include "UI/CphPlayerWidgetHUD.h"

#include "Components/CphHealthComponent.h"

// Progress bar value in UI
float UCphPlayerWidgetHUD::GetHealthRatio() const
{
    const APawn* Player = GetOwningPlayerPawn();
    if (!Player) return 0.0f;

    const UActorComponent* Component =
        Player->GetComponentByClass(UCphHealthComponent::StaticClass());
    // nullptr Cast returns nullptr
    const UCphHealthComponent* const HealthComponent =
        Cast<UCphHealthComponent>(Component);
    if (!HealthComponent) return 0.0f;

    return HealthComponent->GetHealthRatio();
}
