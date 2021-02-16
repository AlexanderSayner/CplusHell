// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CphHealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPLUSHELL_API UCphHealthComponent final : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UCphHealthComponent();

    // Getter
    float GetHealth() const { return Health; }

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
