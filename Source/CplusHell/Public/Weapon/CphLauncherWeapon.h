// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"


#include "CphProjectile.h"
#include "Weapon/CphBaseWeapon.h"
#include "CphLauncherWeapon.generated.h"

/**
 * Launcher unique logic
 */
UCLASS()
class CPLUSHELL_API ACphLauncherWeapon final : public ACphBaseWeapon
{
    GENERATED_BODY()

public:
    virtual void Fire() override;

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ACphProjectile> ProjectileClass;

    virtual void MakeShot() override;
};
