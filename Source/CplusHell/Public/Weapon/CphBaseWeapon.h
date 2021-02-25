// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
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
    //
    virtual void Fire();
    //
    virtual void StopFire();

protected:
    // Weapon mesh
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;
    //
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleFlashSocket";
    //
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TraceMaxDistance = 3000.0f;

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
};
