// C plus Hell Learning Game, All Right Reserved.


#include "Weapon/Components/CphWeaponComponentFX.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values for this component's properties
UCphWeaponComponentFX::UCphWeaponComponentFX()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

// Spawn niagara effect first, then decal
void UCphWeaponComponentFX::PlayImpactFX(const FHitResult& Hit)
{
    FImpactData ImpactData = DefaultImpactData;

    // Playing effect depends on physical material where bullet goes
    if (Hit.PhysMaterial.IsValid())
    {
        const UPhysicalMaterial* PhysMat = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }

    // World context, Niagara System, Location in world, Orientation in world
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(
        GetWorld(), ImpactData.NiagaraSystem, Hit.ImpactPoint,
        Hit.ImpactNormal.Rotation());

    // Decal
    UDecalComponent* DecalComponent = UGameplayStatics::SpawnDecalAtLocation(
        GetWorld(),
        ImpactData.DecalData.
                   MaterialInterface,
        ImpactData.DecalData.Size,
        Hit.ImpactPoint,
        Hit.ImpactNormal.Rotation());

    if (DecalComponent)
    {
        DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime,
                                   ImpactData.DecalData.FadeOutTime);
    }
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
