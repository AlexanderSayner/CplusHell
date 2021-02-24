// C plus Hell Learning Game, All Right Reserved.


#include "Weapon/CphBaseWeapon.h"

#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"

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

    const auto Player = Cast<ACharacter>(GetOwner());
    if (!Player) return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller) return;

    FVector ViewLocation;
    FRotator ViewRotation;
    Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);

    // Draw direction line
    const FTransform SocketTransform = WeaponMesh->GetSocketTransform(
        MuzzleSocketName);
    const FVector TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    // Ignore player itself
    FCollisionQueryParams CollisionParams;
    CollisionParams.AddIgnoredActor(GetOwner());

    // Draw interception sphere
    FHitResult HitResult;
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd,
                                         ECC_Visibility, CollisionParams);

    // If got
    if (HitResult.bBlockingHit)
    {
        DrawDebugLine(GetWorld(),
                      SocketTransform.GetLocation(),
                      HitResult.ImpactPoint,
                      FColor::Red, false, 3.0f, 0, 3.0f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.0f, 24,
                        FColor::Red, false, 5.0f);

        UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"),
               *HitResult.BoneName.ToString())
    }
    else
    {
        DrawDebugLine(GetWorld(),
                      SocketTransform.GetLocation(), TraceEnd,
                      FColor::Green, false, 3.0f, 0, 3.0f);
    }
}
