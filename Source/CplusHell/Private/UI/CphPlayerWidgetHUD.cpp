// C plus Hell Learning Game, All Right Reserved.


#include "UI/CphPlayerWidgetHUD.h"

#include "Components/CphHealthComponent.h"
#include "Components/CphWeaponComponent.h"

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

// Cross Hair and weapon interface icons for current weapon
bool UCphPlayerWidgetHUD::GetCurrentWeaponDataUI(FWeaponDataUI& UIData) const
{
    const UCphWeaponComponent* WeaponComponent = GetWeaponComponent();
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponDataUI(UIData);
}

// Returns false if not valid
bool UCphPlayerWidgetHUD::GetCurrentBulletsDataUI(FAmmoData& AmmoData) const
{
    const UCphWeaponComponent* WeaponComponent = GetWeaponComponent();
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponAmmoUI(AmmoData);
}

// Const for each weapon in game instance default ammo
bool UCphPlayerWidgetHUD::GetDefaultBulletsDataUI(FAmmoData& AmmoData) const
{
    const UCphWeaponComponent* WeaponComponent = GetWeaponComponent();
    if (!WeaponComponent) return false;

    return WeaponComponent->GetWeaponDefaultAmmoUI(AmmoData);
}

// Returns nullptr if fails
UCphWeaponComponent* UCphPlayerWidgetHUD::GetWeaponComponent() const
{
    const APawn* Player = GetOwningPlayerPawn();
    if (!Player) return nullptr;

    UActorComponent* Component = Player->GetComponentByClass(
        UCphWeaponComponent::StaticClass());
    UCphWeaponComponent* WeaponComponent =
        Cast<UCphWeaponComponent>(Component);

    return WeaponComponent;
}
