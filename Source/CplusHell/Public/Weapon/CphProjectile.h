// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "CphProjectile.generated.h"

class UCphWeaponComponentFX;
class USphereComponent;
class UProjectileMovementComponent;

/**
 * Launcher's bullet
 */
UCLASS()
class CPLUSHELL_API ACphProjectile final : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACphProjectile();

    // Launcher sets Direction, then spawn
    void SetShotDirection(const FVector& Direction);

protected:
    UPROPERTY(VisibleAnywhere, Category="Weapon")
    USphereComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere, Category="Weapon")
    UProjectileMovementComponent* MovementComponent;

    UPROPERTY(VisibleAnywhere, Category="VFX")
    UCphWeaponComponentFX* WeaponComponentFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    float LifeSeconds = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Damage")
    float DamageRadius = 200.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Damage")
    float DamageAmount = 19.0f;

    // Is depends on radius from center
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Damage")
    bool DoFullDamage = false;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

private:
    FVector ShotDirection;

    // For delegate signature
    UFUNCTION()
    void OnProjectileHit(UPrimitiveComponent* HitComponent,
                         AActor* OtherActor,
                         UPrimitiveComponent* OtherComp,
                         FVector NormalImpulse,
                         const FHitResult& Hit);

    // Returns nullptr, if fails
    AController* GetController() const;
};
