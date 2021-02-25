// C plus Hell Learning Game, All Right Reserved.


#include "Weapon/CphBaseWeapon.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Player/CphBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseWeapon, All, All)

// Sets default values
ACphBaseWeapon::ACphBaseWeapon()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

//
void ACphBaseWeapon::Fire()
{
    MakeShot();
}

// Called when the game starts or when spawned
void ACphBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh)
}

// Shot where look
void ACphBaseWeapon::MakeShot() const
{
    if (!GetWorld()) return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    // If got
    if (HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(),
                      GetMuzzleWorldLocation(),
                      HitResult.ImpactPoint,
                      FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24,
                        FColor::Red, false, 5.0f);
        MakeDamage(HitResult);
    }
    else
    {
        DrawDebugLine(GetWorld(),
                      GetMuzzleWorldLocation(), TraceEnd,
                      FColor::Green, false, 3.0f, 0, 3.0f);
    }
}

// Returns nullptr if fails
APlayerController* ACphBaseWeapon::GetPlayerController() const
{
    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return nullptr;

    return Player->GetController<APlayerController>();
}

// Returns false on fail
bool ACphBaseWeapon::GetPlayerViewPoint(FVector& ViewLocation,
                                        FRotator& ViewRotation) const
{
    const APlayerController* Controller = GetPlayerController();
    if (!Controller) return false;

    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

// 3d Vector of the muzzle
FVector ACphBaseWeapon::GetMuzzleWorldLocation() const
{
    return WeaponMesh->GetSocketLocation(MuzzleSocketName);
}

// Shot trace
bool ACphBaseWeapon::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation)) return false;

    // Draw direction line
    TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;
    return true;
}

// Find interception of shot
void ACphBaseWeapon::MakeHit(FHitResult& HitResult, const FVector& TraceStart,
                             const FVector& TraceEnd) const
{
    if (!GetWorld()) return;

    // Ignore player itself
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    // Draw interception sphere
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd,
                                         ECC_Visibility, CollisionParams);
}

// Deal damage to hit actor
void ACphBaseWeapon::MakeDamage(const FHitResult& HitResult) const
{
    AActor* DamagedActor = HitResult.GetActor();
    if (!DamagedActor) return;
    DamagedActor->TakeDamage(DamageAmount, FDamageEvent(), GetPlayerController(),
                             GetPlayerController()->GetCharacter());
}
