// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CphWeaponComponent.generated.h"

class ACphBaseWeapon;

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    TSubclassOf<ACphBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Weapon")
    UAnimMontage* ReloadAnimMontage;
};

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
    // Reload action mapping
    void Reload();

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

    // Called when the game starts
    virtual void BeginPlay() override;

private:
    // Set a first one in Begin Play
    UPROPERTY()
    ACphBaseWeapon* CurrentWeapon = nullptr;

    // Init in Begin Play by Spawning Weapon classes
    UPROPERTY()
    TArray<ACphBaseWeapon*> Weapons;

    // Different weapons - different animation
    UPROPERTY()
    UAnimMontage* CurrentReloadAnimMontage = nullptr;

    // Default weapon in game begin 
    int32 CurrentWeaponIndex = 0;
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    // Console logger
    static void LogWarning(FString Reason);
    // Taking in hands or taking off
    static void AttachWeaponToSocket(ACphBaseWeapon* Weapon,
                                     ACharacter* Character,
                                     const FName& Name);
    // Set Current weapon, attach to character's hand
    void EquipWeapon(int32 WeaponIndex);
    // Initialisation
    void SpawnWeapons();

    //
    void PlayAnimMontage(UAnimMontage* Animation) const;
    // Subscribe for Anim Notify
    void InitAnimations();
    // Could not be static because of using in delegate callback
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    void OnReloadFinished(USkeletalMeshComponent* MeshComponent);

    // Solution for non stop weapon changing
    bool CanFire() const;
    bool CanEquip() const;
    bool CanReload() const;

    //
    template <typename T>
    T* FindFirstNotifyByClass(UAnimSequenceBase* Animation);
};

/**
 * Cycle for all notifiers in amin montage
 */
template <typename T>
T* UCphWeaponComponent::FindFirstNotifyByClass(UAnimSequenceBase* Animation)
{
    if (!Animation) return nullptr;

    const TArray<struct FAnimNotifyEvent> Notifies = Animation->
        Notifies;

    for (const FAnimNotifyEvent NotifyEvent : Notifies)
    {
        T* AnimNotify = Cast<T>(NotifyEvent.Notify);
        if (AnimNotify)
        {
            return AnimNotify;
        }
    }
    return nullptr;
}
