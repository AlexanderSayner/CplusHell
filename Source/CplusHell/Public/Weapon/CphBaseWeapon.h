// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CphBaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class CPLUSHELL_API ACphBaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACphBaseWeapon();
    //
    virtual void Fire();

protected:
    // Weapon mesh
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent* WeaponMesh;
    //
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleFlashSocket";
    //
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
    float TraceMaxDistance = 3000.0f;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Shot where look
    void MakeShot() const;
};
