// C plus Hell Learning Game, All Right Reserved.


#include "Pickups/CphHealthPickup.h"

#include "Components/CphHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All)

bool ACphHealthPickup::AddSomeBuffsTo(APawn* Pawn)
{
    if (!Pawn)
        return false;
    
    UE_LOG(LogHealthPickup, Display, TEXT("%s step on HealthPickup"),
               *Pawn->GetName())
    
    UCphHealthComponent* HealthComponent =
        GetCphPlayerHealthComponent(Pawn);
    if (!HealthComponent || !HealthComponent->IsAlive()) return false;
    
    return HealthComponent->TryToAddHealth(HealthAmount);
}

UCphHealthComponent* ACphHealthPickup::GetCphPlayerHealthComponent(
    AActor* SomeActor) const
{
    if (!SomeActor) return nullptr;

    UActorComponent* Component = SomeActor->GetComponentByClass(
        UCphHealthComponent::StaticClass());
    return Cast<UCphHealthComponent>(Component);
}
