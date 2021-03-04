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

    FOnClipEmptySignature OnClipEmpty;

    //
    virtual void StartFire();
    //
    virtual void StopFire();
    // Calls by Weapon Component 
    void ChangeClip();
    // If for some reason weapon can not reload at all
    bool CanReload() const;

    // Getters
    FWeaponDataUI GetUIData() const { return UIData; }
    FAmmoData GetCurrentAmmoData() const { return CurrentAmmo; }
    FAmmoData GetDefaultAmmoData() const { return DefaultAmmo; }

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
    //
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    FAmmoData DefaultAmmo{15, 10, false};
    //
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="UI")
    FWeaponDataUI UIData;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Shot in direction player looks
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
    //
    void DecreaseAmmo();
    bool IsAmmoEmpty() const;
    bool IsClipEmpty() const;

private:
    // Initialised in Begin Play
    FAmmoData CurrentAmmo;
};
