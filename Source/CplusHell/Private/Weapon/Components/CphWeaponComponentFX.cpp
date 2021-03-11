// C plus Hell Learning Game, All Right Reserved.


#include "Weapon/Components/CphWeaponComponentFX.h"
#include "NiagaraFunctionLibrary.h"

// Sets default values for this component's properties
UCphWeaponComponentFX::UCphWeaponComponentFX()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Spawn effect
void UCphWeaponComponentFX::PlayImpactFX(const FHitResult& Hit)
{
    UNiagaraSystem* Effect = DefaultEffect;

    // Playing effect depends on physical material where bullet goes
    if (Hit.PhysMaterial.IsValid())
    {
        const UPhysicalMaterial* PhysMat = Hit.PhysMaterial.Get();
        if (EffectsMap.Contains(PhysMat))
        {
            Effect = EffectsMap[PhysMat];
        }
    }

    // World context, Niagara System, Location in world, Orientation in world
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(), Effect, Hit.ImpactPoint,
        Hit.ImpactNormal.Rotation());
}


// Called when the game starts
void UCphWeaponComponentFX::BeginPlay()
{
    Super::BeginPlay();
}


// Called every frame
void UCphWeaponComponentFX::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction*
                                          ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}
