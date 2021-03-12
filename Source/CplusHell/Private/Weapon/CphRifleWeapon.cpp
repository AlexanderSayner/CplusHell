// C plus Hell Learning Game, All Right Reserved.


#include "Weapon/CphRifleWeapon.h"

#include "DrawDebugHelpers.h"
#include "Weapon/Components/CphWeaponComponentFX.h"
#include "NiagaraComponent.h"

// Construct VFX
ACphRifleWeapon::ACphRifleWeapon()
{
    WeaponComponentFX = CreateDefaultSubobject<UCphWeaponComponentFX>(
        "WeaponComponentFX");
}

//
void ACphRifleWeapon::StartFire()
{
    InitMuzzleFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this,
                                    &ACphRifleWeapon::MakeShot, ShotRate, true);
    MakeShot();
}

//
void ACphRifleWeapon::StopFire()
{
    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetMuzzleFXVisibility(false);
}

//
void ACphRifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponComponentFX)
}

//
void ACphRifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    }

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd))
    {
        StopFire();
        return;
    }

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    // If got
    if (HitResult.bBlockingHit)
    {
        /*
        DrawDebugLine(GetWorld(),
                      GetMuzzleWorldLocation(),
                      HitResult.ImpactPoint,
                      FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24,
                        FColor::Red, false, 5.0f); */
        MakeDamage(HitResult);
        WeaponComponentFX->PlayImpactFX(HitResult);
    }
    else
    {
        DrawDebugLine(GetWorld(),
                      GetMuzzleWorldLocation(), TraceEnd,
                      FColor::Green, false, 3.0f, 0, 3.0f);
    }

    DecreaseAmmo();
}

// Returns false when fails
bool ACphRifleWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    // Draw direction line
    TraceStart = ViewLocation;
    const float HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(
        ViewRotation.Vector(), HalfRad);
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

// Deal damage to hit actor
void ACphRifleWeapon::MakeDamage(const FHitResult& HitResult) const
{
    AActor* DamagedActor = HitResult.GetActor();
    if (!DamagedActor) return;
    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(),
                             GetPlayerController(),
                             GetOwner());
}

//
void ACphRifleWeapon::InitMuzzleFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    SetMuzzleFXVisibility(true);
}

//
void ACphRifleWeapon::SetMuzzleFXVisibility(const bool Visibility) const
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!Visibility);
        MuzzleFXComponent->SetVisibility(Visibility, true);
    }
}
