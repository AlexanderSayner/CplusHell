// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/CphBasePickup.h"
#include "Weapon/CphBaseWeapon.h"
#include "CphAmmoPickup.generated.h"

class UCphHealthComponent;
class UCphWeaponComponent;
/**
 * Ammo buff
 */
UCLASS()
class CPLUSHELL_API ACphAmmoPickup final : public ACphBasePickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammos",
        meta=(ClampMin="1.0", ClampMax="300.0"))
    int32 BulletsAmount = 10;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Ammos")
    TSubclassOf<ACphBaseWeapon> WeaponType;

    virtual bool AddSomeBuffsTo(APawn* Pawn) override;

private:
    UCphWeaponComponent* GetCphPlayerComponent(AActor* SomeActor) const;
    UCphHealthComponent* GetCphPlayerHealthComponent(AActor* SomeActor) const;
};
