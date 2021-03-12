// C plus Hell Learning Game, All Right Reserved.


#include "Weapon/CphLauncherWeapon.h"

#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogCphLauncherWeapon, All, All)

void ACphLauncherWeapon::StartFire()
{
    MakeShot();
}

void ACphLauncherWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty()) return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit
                                 ? HitResult.ImpactPoint
                                 : TraceEnd;
    const FVector Direction = (EndPoint - GetMuzzleWorldLocation())
        .GetSafeNormal();

    const FTransform SpawnTransform(FRotator::ZeroRotator,
                                    GetMuzzleWorldLocation());

    ACphProjectile* Projectile = GetWorld()
        ->SpawnActorDeferred<ACphProjectile>(ProjectileClass, SpawnTransform);

    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTransform);
    }

    DecreaseAmmo();
    if (!SpawnMuzzleFX())
    {
        UE_LOG(LogCphLauncherWeapon, Warning,
               TEXT("Could not spawn launcher muzzle effect"))
    }
}
