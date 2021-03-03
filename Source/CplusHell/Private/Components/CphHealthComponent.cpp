// C plus Hell Learning Game, All Right Reserved.


#include "Components/CphHealthComponent.h"

// Sets default values for this component's properties
UCphHealthComponent::UCphHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

// Returns value between zero and one
float UCphHealthComponent::GetHealthPercent() const
{
    return Health / MaxHealth;
}


// Called when the game starts
void UCphHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0)
    SetHealth(MaxHealth);

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(
            this, &UCphHealthComponent::OnTakeAnyDamage);
    }
}

// Set and translate to delegate
void UCphHealthComponent::SetHealth(const float NewHealth)
{
    // Health could not be less than 0 and more than available, if damage or heal is too big
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    // Print health changing
    OnHealthChanged.Broadcast(Health);
}

// Deals damage and starts healing
void UCphHealthComponent::OnTakeAnyDamage(AActor* DamagedActor,
                                          const float Damage,
                                          const UDamageType* DamageType,
                                          AController* InstigatedBy,
                                          AActor* DamageCauser)
{
    // Validation
    if (Damage <= 0.0f || !IsAlive())
        return;

    SetHealth(Health - Damage);

    if (!IsAlive())
    {
        OnDeath.Broadcast();
        // Stop healing
        if (GetWorld())
        {
            GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
        }
    }
    else if (AutoHeal)
    {
        // Start doing auto heal
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle,
                                               this,
                                               &UCphHealthComponent::HealUpdate,
                                               HealUpdateTime,
                                               true,
                                               HealDelay);
    }
}

// Updates health on Heal Modifier delta and stops timer then necessary 
void UCphHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);
    // Stop healing then already healed
    if (FMath::IsNearlyEqual(Health, MaxHealth, 0.05f)
        && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}
