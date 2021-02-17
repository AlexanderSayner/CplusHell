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

    UFUNCTION(BlueprintCallable)
    bool IsAlive() const { return Health > 0.0f; }

    // Delegates declaration
    FOnDeath OnDeath;
    FOnHealthChanged OnHealthChanged;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health",
        meta = (ClampMin = "0.0", ClampMax = "10000.0"))
    float MaxHealth = 20.0f;

    // Called when the game starts
    virtual void BeginPlay() override;

private:
    float Health = 0.0f;

    UFUNCTION()
    void OnTakeAnyDamage(AActor* DamagedActor,
                         float Damage,
                         const class UDamageType* DamageType,
                         class AController* InstigatedBy,
                         AActor* DamageCauser);
};
