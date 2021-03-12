// C plus Hell Learning Game, All Right Reserved.


#include "Weapon/CphBaseWeapon.h"

#include "DrawDebugHelpers.h"
#include "NiagaraFunctionLibrary.h"
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

// for a child class implementation
void ACphBaseWeapon::StopFire()
{
}

// Do specific logic for each weapon
void ACphBaseWeapon::MakeShot()
{
}

// Called when the game starts or when spawned
void ACphBaseWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponMesh)
    checkf(DefaultAmmo.BulletsInClip>0,
           TEXT("Bullets count couldn't be less or equals zero"))
    checkf(DefaultAmmo.BulletsInTotal>0,
           TEXT("Clips count couldn't be less or equals zero"))

    CurrentAmmo = DefaultAmmo;
    // First clip is not free
    CurrentAmmo.BulletsInTotal -= DefaultAmmo.BulletsInClip;
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
    // Pass physical material for choosing right effect
    CollisionParams.bReturnPhysicalMaterial = true;

    // Draw interception sphere
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd,
                                         ECC_Visibility, CollisionParams);
}

// Changing current ammo count
void ACphBaseWeapon::DecreaseAmmo()
{
    // Can't decrease ammo, if it is zero already
    if (CurrentAmmo.BulletsInClip == 0)
    {
        UE_LOG(LogCphBaseWeapon, Display, TEXT("Clip is empty"))
        return;
    }

    CurrentAmmo.BulletsInClip--;

    // If my clip is empty, i should have some bullets in my pocket for reloading
    if (IsClipEmpty() && !IsAmmoEmpty())
    {
        // Delegate will do animation and change weapon clip
        StopFire();
        OnClipEmpty.Broadcast();
    }
}

// Is bullets ended in clip and also in stock
bool ACphBaseWeapon::IsAmmoEmpty() const
{
    return !CurrentAmmo.Infinite && CurrentAmmo.BulletsInTotal == 0 &&
           IsClipEmpty();
}

// Set defaults bullets, bul reduce current ammo clip by 1
bool ACphBaseWeapon::IsClipEmpty() const
{
    return CurrentAmmo.BulletsInClip == 0;
}

// Compare default ammo with current
bool ACphBaseWeapon::IsAmmoFull() const
{
    // Player starts with empty clip, then reload
    return CurrentAmmo.BulletsInTotal + CurrentAmmo.BulletsInClip ==
           DefaultAmmo.BulletsInTotal;
}

//
UNiagaraComponent* ACphBaseWeapon::SpawnMuzzleFX() const
{
    return UNiagaraFunctionLibrary::SpawnSystemAttached(
        MuzzleFX, WeaponMesh, MuzzleSocketName, FVector::ZeroVector,
        FRotator::ZeroRotator, EAttachLocation::SnapToTarget, true);
}

// Called on end of animation. Set defaults bullets, but reduce current ammo clip by 1
void ACphBaseWeapon::ChangeClip()
{
    if (!CurrentAmmo.Infinite)
    {
        if (CurrentAmmo.BulletsInTotal == 0)
        {
            UE_LOG(LogCphBaseWeapon, Warning, TEXT("No more bullets in hell"))
            return;
        }

        const int BulletsLack = DefaultAmmo.BulletsInClip
                                - CurrentAmmo.BulletsInClip;
        const int Supplement = FMath::Clamp(BulletsLack, 0,
                                            CurrentAmmo.BulletsInTotal);

        CurrentAmmo.BulletsInClip += Supplement;
        CurrentAmmo.BulletsInTotal -= Supplement;
    }
    else
    {
        CurrentAmmo.BulletsInClip = DefaultAmmo.BulletsInClip;
    }
    UE_LOG(LogCphBaseWeapon, Display, TEXT("Changed clip"))
}

// Asks, before animation started to play
bool ACphBaseWeapon::CanReload() const
{
    return CurrentAmmo.BulletsInClip < DefaultAmmo.BulletsInClip
           && CurrentAmmo.BulletsInTotal > 0;
}

// Taking ammo bonus or not taking
bool ACphBaseWeapon::TryToAddAmmo(const int32 BulletsAmount)
{
    if (CurrentAmmo.Infinite || IsAmmoFull() || BulletsAmount <= 0)
        return false;

    // how much can I put in
    const int FreeAmmoSpace = DefaultAmmo.BulletsInTotal -
                              (CurrentAmmo.BulletsInClip
                               + CurrentAmmo.BulletsInTotal);

    UE_LOG(LogCphBaseWeapon, Display, TEXT("Total bullets before %i"),
           CurrentAmmo.BulletsInTotal)

    const int32 Clamp = FMath::Clamp(BulletsAmount, 0,
                                     FreeAmmoSpace);

    UE_LOG(LogCphBaseWeapon, Display, TEXT("Clamp %i"), Clamp)

    // You can not take more, then you can carry
    CurrentAmmo.BulletsInTotal += Clamp;

    UE_LOG(LogCphBaseWeapon, Display, TEXT("Total bullets after %i"),
           CurrentAmmo.BulletsInTotal)
    //OnClipEmpty.Broadcast(); // Broadcast for reload
    return true;
}
