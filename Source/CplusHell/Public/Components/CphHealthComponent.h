// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CphHealthComponent.generated.h"

// Delegate for telling player about his death
DECLARE_MULTICAST_DELEGATE(FOnDeath)
// Call on heath change then player can print health on event but every tick
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float)

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPLUSHELL_API UCphHealthComponent final : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UCphHealthComponent();

    // Getter
    float GetHealth() const { return Health; }

    // Set health uses clamp, so health will never be much less than zero 
    UFUNCTION(BlueprintCallable)
    bool IsAlive() const { return !FMath::IsNearlyZero(Health); }

    // Delegates declaration
    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

protected:
    // Setting for max health
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health",
        meta = (ClampMin = "1.0", ClampMax = "10000.0"))
    float MaxHealth = 20.0f;

    // Enable heal after taking a damage
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal")
    bool AutoHeal = true;

    // Time interval of healing in seconds
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal",
        meta = (ClampMin = "0.1", ClampMax = "60.0",
            EditCondition = "AutoHeal"))
    float HealUpdateTime = 1.0f;

    // Time delay in second after which heal starts
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal",
        meta = (ClampMin = "0.1", ClampMax = "60.0",
            EditCondition = "AutoHeal"))
    float HealDelay = 3.0f;

    // Heal delta 
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Heal",
        meta = (ClampMin = "0.01", ClampMax = "1000.0",
            EditCondition = "AutoHeal"))
    float HealModifier = 5.0f;

    // Called when the game starts
    virtual void BeginPlay() override;

private:
    // Player health
    float Health = 0.0f;

    // Auto heal timer
    FTimerHandle HealTimerHandle;

    // Set and translate to delegate
    void SetHealth(const float NewHealth);

    // Deals damage and starts healing 
    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamagedActor,
                         float Damage,
                         const class UDamageType* DamageType,
                         class AController* InstigatedBy,
                         AActor* DamageCauser);
    // Updates health on Heal Modifier delta and stops timer then necessary 
    void HealUpdate();
};
