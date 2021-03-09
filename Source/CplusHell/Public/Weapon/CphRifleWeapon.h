// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/CphBaseWeapon.h"
#include "CphRifleWeapon.generated.h"

/**
 * Rifle unique logic
 */
UCLASS()
class CPLUSHELL_API ACphRifleWeapon final : public ACphBaseWeapon
{
    GENERATED_BODY()

public:
    virtual void StartFire() override;
    virtual void StopFire() override;

protected:
    // Damage amount of weapon mesh
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon",
        meta = (ClampMin = "0.01", ClampMax = "10.0"))
    float ShotRate = 1.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float BulletSpread = 1.5f;

    virtual void MakeShot() override;
    // Returns false when fails
    virtual bool GetTraceData(FVector& TraceStart,
                              FVector& TraceEnd) const override;

private:
    // Rifle shot rate control
    FTimerHandle ShotTimerHandle;

    // Deal damage to hit actor
    void MakeDamage(const FHitResult& HitResult) const;
};
