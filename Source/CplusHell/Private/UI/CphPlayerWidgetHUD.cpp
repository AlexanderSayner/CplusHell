// C plus Hell Learning Game, All Right Reserved.


#include "UI/CphPlayerWidgetHUD.h"

#include "Components/CphHealthComponent.h"
#include "Components/CphWeaponComponent.h"

// Progress bar value in UI
float UCphPlayerWidgetHUD::GetHealthRatio() const
{
    const UCphHealthComponent* HealthComponent = GetHealthComponent();
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

//
bool UCphPlayerWidgetHUD::IsPlayerAlive() const
{
    // Then health runs out, Spectator Pawn takes control of the Player Controller
    // After which HealthComponent equals nullptr and HealthComponent->IsAlive() is useless 
    const UCphHealthComponent* HealthComponent = GetHealthComponent();
    return HealthComponent && HealthComponent->IsAlive();
}

//
bool UCphPlayerWidgetHUD::IsPlayerSpectating() const
{
    const APlayerController* Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}

// Init delegate for red screen effect on damage
bool UCphPlayerWidgetHUD::Initialize()
{
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(
            this, &UCphPlayerWidgetHUD::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
    return Super::Initialize();
}

// Returns nullptr if fails
UCphWeaponComponent* UCphPlayerWidgetHUD::GetWeaponComponent() const
{
    const APawn* Player = GetOwningPlayerPawn();
    if (!Player) return nullptr;

    UActorComponent* Component = Player->GetComponentByClass(
        UCphWeaponComponent::StaticClass());
    // nullptr Cast returns nullptr
    UCphWeaponComponent* WeaponComponent = Cast<UCphWeaponComponent>(Component);

    return WeaponComponent;
}

// Returns nullptr if fails
UCphHealthComponent* UCphPlayerWidgetHUD::GetHealthComponent() const
{
    const APawn* Player = GetOwningPlayerPawn();
    if (!Player) return nullptr;

    UActorComponent* Component = Player->GetComponentByClass(
        UCphHealthComponent::StaticClass());
    // nullptr Cast returns nullptr
    UCphHealthComponent* HealthComponent = Cast<UCphHealthComponent>(Component);

    return HealthComponent;
}

// Delegate subscriber for red screen UI animation
void UCphPlayerWidgetHUD::OnHealthChanged(float Health, const float Delta)
{
    if (Delta < 0.0f)
    {
        OnTakeDamage();
    }
}

// Delegate subscriber initializing OnHealthChanged subscriber for new Pawn
void UCphPlayerWidgetHUD::OnNewPawn(APawn* NewPawn)
{
    if (!NewPawn) return;

    UActorComponent* Component = NewPawn->FindComponentByClass(
        UCphHealthComponent::StaticClass());
    UCphHealthComponent* HealthComponent = Cast<UCphHealthComponent>(Component);
    if (HealthComponent &&
        !HealthComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HealthComponent->OnHealthChanged.AddUObject(
            this, &UCphPlayerWidgetHUD::OnHealthChanged);
    }
}
