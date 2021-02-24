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
    UPROPERTY(VisibleAnywhere,BlueprintReadWrite,Category="Components")
    USkeletalMeshComponent* WeaponMesh;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
};
