// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/CphWeaponComponent.h"
#include "CphWeaponAIComponent.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSHELL_API UCphWeaponAIComponent final : public UCphWeaponComponent
{
    GENERATED_BODY()

public:
    // Changes weapon when ammo is empty on current
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
