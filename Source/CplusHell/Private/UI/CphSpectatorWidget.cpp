// C plus Hell Learning Game, All Right Reserved.


#include "UI/CphSpectatorWidget.h"

#include "Components/CphRespawnComponent.h"

bool UCphSpectatorWidget::GetRespawnTime(int32& CountdownTime) const
{
    UActorComponent* Component = GetOwningPlayer()->FindComponentByClass(
        UCphRespawnComponent::StaticClass());
    UCphRespawnComponent* RespawnComponent = Cast<UCphRespawnComponent>(
        Component);
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress())
        return false;

    CountdownTime = RespawnComponent->GetRespawnCountdown();
    return true;
}
