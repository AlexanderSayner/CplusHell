// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"

#include "CphCoreTypes.h"
#include "GameFramework/Actor.h"
#include "CphBaseWeapon.generated.h"

class USkeletalMeshComponent;

/**
 * Utility logic for all weapons in the game
 */
UCLASS()
class CPLUSHELL_API ACphBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACphBaseWeapon();

    // Weapon Component subscribing on event for this weapon 
    FOnClipEmptySignature OnClipEmpty;

    // for a child class implementation
    virtual void StartFire();
    // for a child class implementation
    virtual void StopFire();
    // Called on end of animation. Set defaults bullets, but reduce current ammo clip by 1
    void ChangeClip();
    // Asks, before animation started to play
    bool CanReload() const;

    // Getters
    FWeaponDataUI GetUIData() const { return UIData; }
    FAmmoData GetCurrentAmmoData() const { return CurrentAmmo; }

    // Taking ammo bonus or not taking
    bool TryToAddAmmo(const int32 BulletsAmount);

protected:
    // Weapon mesh
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;
    //
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FName MuzzleSocketName = "MuzzleFlashSocket";
    //
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 3000.0f;
    /**
     * Bullets In Clip - amount in clip that max possible.
     * Bullets In Total - max possible amount in the stock plus in the clip
     */
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{20, 150, false};
    //
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    FWeaponDataUI UIData;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Do specific logic for each weapon
    virtual void MakeShot();

    // Shot trace
    virtual bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

    // Returns nullptr if fails
    APlayerController* GetPlayerController() const;
    // Returns false on fail
    bool GetPlayerViewPoint(FVector& ViewLocation,
                            FRotator& ViewRotation) const;
    // 3d Vector of the muzzle
    FVector GetMuzzleWorldLocation() const;
    // Find interception of shot
    void MakeHit(FHitResult& HitResult,
                 const FVector& TraceStart, const FVector& TraceEnd) const;
    // Changing current ammo count 
    void DecreaseAmmo();
    // Is bullets ended in clip and also in stock
    bool IsAmmoEmpty() const;
    // Set defaults bullets, bul reduce current ammo clip by 1
    bool IsClipEmpty() const;
    // Compare default ammo with current
    bool IsAmmoFull() const;

private:
    // Initialised in Begin Play
    FAmmoData CurrentAmmo;
};
