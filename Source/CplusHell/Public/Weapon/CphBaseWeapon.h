// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CphBaseWeapon.generated.h"

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets; // Bullets count in weapon

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon",
        meta = (EditCondition = "!Infinite"))
    int32 Clips; // Bullets total

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool Infinite; // true - bullets are infinite, otherwise - false
};

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
    //
    virtual void Fire();
    //
    virtual void StopFire();

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
    UPROPERTY(EditDefaultsOnly,BlueprintReadWrite,Category="Weapon")
    FAmmoData DefaultAmmo{15, 10, false};

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Shot where look
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
    void ChangeClip();
    void LogAmmo();

private:
    // Initialised in Begin Play
    FAmmoData CurrentAmmo;
};
