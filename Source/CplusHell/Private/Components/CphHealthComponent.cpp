// C plus Hell Learning Game, All Right Reserved.


#include "Components/CphHealthComponent.h"

#include "CphGameModeBase.h"

// Sets default values for this component's properties
UCphHealthComponent::UCphHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

// Returns value between zero and one
float UCphHealthComponent::GetHealthRatio() const
{
    return Health / MaxHealth;
}

// Add some health
bool UCphHealthComponent::TryToAddHealth(const int32 HealthAmount)
{
    if (!IsAlive())
        return false;

    if (FMath::IsNearlyEqual(Health, MaxHealth, 0.1f))
        return false;

    SetHealth(Health + HealthAmount);
    return true;
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
    const float OldHealth = Health;
    // Health could not be less than 0 and more than available, if damage or heal is too big
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    // Print health changing
    OnHealthChanged.Broadcast(Health, Health - OldHealth);
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
        Killed(InstigatedBy);
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

    PlayCameraShake();
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

// Damage player camera shake effect
void UCphHealthComponent::PlayCameraShake() const
{
    if (!IsAlive()) return;

    APawn* Player = Cast<APawn>(GetOwner());
    if (!Player) return;

    APlayerController* Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager) return;

    Controller->PlayerCameraManager->StartCameraShake(CameraShake);
}

//
void UCphHealthComponent::Killed(AController* SlayerController) const
{
    ACphGameModeBase* GameMode = Cast<ACphGameModeBase>(
        GetWorld()->GetAuthGameMode());
    if (!GameMode) return;

    APawn* Player = Cast<APawn>(GetOwner());
    AController* VictimController = Player ? Player->Controller : nullptr;

    GameMode->Killed(SlayerController, VictimController);
}
