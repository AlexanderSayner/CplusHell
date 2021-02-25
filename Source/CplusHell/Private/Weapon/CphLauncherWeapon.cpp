// C plus Hell Learning Game, All Right Reserved.


#include "Weapon/CphLauncherWeapon.h"

#include "Kismet/GameplayStatics.h"

void ACphLauncherWeapon::Fire()
{
    MakeShot();
}

void ACphLauncherWeapon::MakeShot()
{
    if (!GetWorld()) return;

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

    if (!Projectile) return;
    Projectile->SetShotDirection(Direction);
    Projectile->SetOwner(GetOwner());
    Projectile->FinishSpawning(SpawnTransform);
}
