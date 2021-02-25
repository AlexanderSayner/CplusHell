// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CphWeaponComponent.generated.h"

class ACphBaseWeapon;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPLUSHELL_API UCphWeaponComponent final : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UCphWeaponComponent();
    // Fire on action. Can not be const, because of using in BindAction
    void Fire();
    // On mouse button release. Can not be const, because of using in BindAction
    void StopFire();

protected:
    // Custom weapon class
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<ACphBaseWeapon> WeaponClass;
    //
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponAttachPointName = "WeaponPoint";

    // Called when the game starts
    virtual void BeginPlay() override;

private:
    UPROPERTY()
    ACphBaseWeapon* CurrentWeapon = nullptr;
    //
    void SpawnWeapon();
};
