// C plus Hell Learning Game, All Right Reserved.


#include "Weapon/CphBaseWeapon.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Player/CphBaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogCphBaseWeapon, All, All)

// Sets default values
ACphBaseWeapon::ACphBaseWeapon()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

// for a child class implementation
void ACphBaseWeapon::StartFire()
{
}

void ACphBaseWeapon::StopFire()
{
}

void ACphBaseWeapon::MakeShot()
{
}

// Called when the game starts or when spawned
void ACphBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh)
    checkf(DefaultAmmo.Bullets>0,
           TEXT("Bullets count couldn't be less or equals zero"))
    checkf(DefaultAmmo.Clips>0,
           TEXT("Clips count couldn't be less or equals zero"))
    CurrentAmmo = DefaultAmmo;
}

// Returns nullptr if fails
APlayerController* ACphBaseWeapon::GetPlayerController() const
{
    ACharacter* const Player = Cast<ACharacter>(GetOwner());
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

//
void ACphBaseWeapon::DecreaseAmmo()
{
    if (CurrentAmmo.Bullets == 0)
    {
        UE_LOG(LogCphBaseWeapon, Display, TEXT("Clip is empty"))
        return;
    }

    CurrentAmmo.Bullets--;
    LogAmmo();

    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        // Delegate will do animation and change weapon clip
        StopFire();
        OnClipEmpty.Broadcast();
    }
}

//
bool ACphBaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.Clips == 0 && IsClipEmpty();
}

//
bool ACphBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

//
void ACphBaseWeapon::ChangeClip()
{
    if (!CurrentAmmo.Infinite)
    {
        if (CurrentAmmo.Clips == 0)
        {
            UE_LOG(LogCphBaseWeapon, Display, TEXT("No more clips in hell"))
            return;
        }
        CurrentAmmo.Clips--;
    }
    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    UE_LOG(LogCphBaseWeapon, Display, TEXT("Changed clip"))
}

// If for some reason weapon can not reload at all
bool ACphBaseWeapon::CanReload() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

//
void ACphBaseWeapon::LogAmmo()
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
    AmmoInfo += CurrentAmmo.Infinite
                    ? "Infinite"
                    : FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(LogCphBaseWeapon, Display, TEXT("%s"), *AmmoInfo);
}
