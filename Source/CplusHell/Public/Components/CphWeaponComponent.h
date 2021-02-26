// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CphWeaponComponent.generated.h"

class ACphBaseWeapon;

/**
 * Ability for weapon changing
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class CPLUSHELL_API UCphWeaponComponent final : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UCphWeaponComponent();
    // Destroy player weapons
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    // Fire on action. Can not be const, because of using in BindAction
    void Fire();
    // On mouse button release. Can not be const, because of using in BindAction
    void StopFire();
    // Circle choosing weapon
    void NextWeapon();

protected:
    // Custom weapon class
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<ACphBaseWeapon>> WeaponClasses;
    // Right hand socket
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponPoint";
    // Addition weapon socket
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    // Called when the game starts
    virtual void BeginPlay() override;

private:
    // Set a first one in Begin Play
    UPROPERTY()
    ACphBaseWeapon* CurrentWeapon = nullptr;

    // Init in Begin Play by Spawning Weapon classes
    UPROPERTY()
    TArray<ACphBaseWeapon*> Weapons;

    // Default weapon in game begin 
    int32 CurrentWeaponIndex = 0;


    // Logger
    static void LogWarning(FString Reason);
    // Taking in hands or taking off
    static void AttachWeaponToSocket(ACphBaseWeapon* Weapon,
                                     ACharacter* Character,
                                     const FName& Name);
    // Set Current weapon, attach to character's hand
    void EquipWeapon(int32 WeaponIndex);
    // Initialisation
    void SpawnWeapons();
};
