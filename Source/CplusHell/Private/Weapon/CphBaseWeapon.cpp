// C plus Hell Learning Game, All Right Reserved.


#include "Weapon/CphBaseWeapon.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Player/CphBaseCharacter.h"

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
}

//
void ACphBaseWeapon::StopFire()
{
}

//
void ACphBaseWeapon::MakeShot()
{
}

// Called when the game starts or when spawned
void ACphBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh)
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
