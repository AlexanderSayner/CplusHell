// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"

#include "CphCoreTypes.h"
#include "Components/ActorComponent.h"
#include "CphWeaponComponent.generated.h"

/**
 * Ability for weapon changing
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CPLUSHELL_API UCphWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UCphWeaponComponent();
    // Called when the game starts
    virtual void BeginPlay() override;
    // Destroy player weapons
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
    // Fire on player action. Can not be const, because of using in BindAction
    virtual void StartFire();
    // On mouse button release. Can not be const, because of using in BindAction
    void StopFire();
    // Circle choosing weapon
    virtual void NextWeapon();
    // Reload action mapping
    void Reload();
    // Returns true if weapon valid and ui set successfully.
    bool GetWeaponDataUI(FWeaponDataUI& UIData) const;
    bool GetWeaponAmmoUI(FAmmoData& AmmoData) const;

    // Add some ammo bonus
    bool TryToAddAmmo(const TSubclassOf<ACphBaseWeapon> WeaponType,
                      const int32 BulletsAmount);

    // AI using for getting ready to reload
    bool NeedAmmo(const TSubclassOf<ACphBaseWeapon> WeaponType);

protected:
    // Custom weapon class
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")

    // TArray<TSubclassOf<ACphBaseWeapon>> WeaponClasses;
    TArray<FWeaponData> WeaponData;

    // Right hand socket
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponPoint";

    // Addition weapon socket
    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    // Weapon component field in BP_PlayerCharacter
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* EquipAnimMontage;

    // Set a weapon than player hold in his hands
    UPROPERTY()
    ACphBaseWeapon* CurrentWeapon = nullptr;

    // Init in Begin Play by Spawning Weapon classes
    UPROPERTY()
    TArray<ACphBaseWeapon*> Weapons;

    // Default weapon in game begin 
    int32 CurrentWeaponIndex = 0;

    // Solution for non stop weapon changing
    bool CanFire() const;
    bool CanEquip() const;

    // Set Current weapon, attach to character's hand
    void EquipWeapon(int32 WeaponIndex);

private:
    // Different weapons - different animation
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    // Console logger
    static void LogWarning(FString Reason);
    // Taking in hands or taking off
    static void AttachWeaponToSocket(ACphBaseWeapon* Weapon,
                                     ACharacter* Character,
                                     const FName& Name);
    // Initialisation
    void SpawnWeapons();

    //
    void PlayAnimMontage(UAnimMontage* Animation) const;
    // Subscribe for Anim Notify
    void InitAnimations();
    // Could not be static because of using in delegate callback
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    // Changing clip here, only when reload animation is finished
    void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

    // Checking reload and equip animation progress
    bool CanReload() const;

    // Call by delegate FOnClipEmptySignature in Base Weapon 
    void OnEmptyClip();

    // Utility logic
    void ChangeClip();
};
