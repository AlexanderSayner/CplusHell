// C plus Hell Learning Game, All Right Reserved.


#include "Pickups/CphAmmoPickup.h"

#include "Components/CphHealthComponent.h"
#include "Components/CphWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All)

bool ACphAmmoPickup::AddSomeBuffsTo(APawn* Pawn)
{
    if (!Pawn) return false;

    UE_LOG(LogAmmoPickup, Display, TEXT("%s step on AmmoPickup"),
           *Pawn->GetName())

    UCphHealthComponent* HealthComponent =
        GetCphPlayerHealthComponent(Pawn);
    if (!HealthComponent || !HealthComponent->IsAlive()) return false;

    UCphWeaponComponent* WeaponComponent =
        GetCphPlayerComponent(Pawn);
    if (!WeaponComponent) return false;
    
    return WeaponComponent->TryToAddAmmo(WeaponType, BulletsAmount);
}

UCphWeaponComponent* ACphAmmoPickup::GetCphPlayerComponent(
    AActor* SomeActor) const
{
    if (!SomeActor) return nullptr;

    UActorComponent* Component = SomeActor->GetComponentByClass(
        UCphWeaponComponent::StaticClass());
    return Cast<UCphWeaponComponent>(Component);
}

UCphHealthComponent* ACphAmmoPickup::GetCphPlayerHealthComponent(
    AActor* SomeActor) const
{
    if (!SomeActor) return nullptr;

    UActorComponent* Component = SomeActor->GetComponentByClass(
        UCphHealthComponent::StaticClass());
    return Cast<UCphHealthComponent>(Component);
}
