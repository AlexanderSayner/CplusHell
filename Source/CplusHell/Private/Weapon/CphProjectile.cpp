// C plus Hell Learning Game, All Right Reserved.


#include "Weapon/CphProjectile.h"


#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/CphWeaponComponentFX.h"

// Sets default values
ACphProjectile::ACphProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(
        "SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Block);
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(
        "ProjectileMovementComponent");
    MovementComponent->InitialSpeed = 5000.0f;

    WeaponComponentFX = CreateDefaultSubobject<UCphWeaponComponentFX>(
        "WeaponComponentFX");
}

// Launcher sets Direction, then spawn
void ACphProjectile::SetShotDirection(const FVector& Direction)
{
    ShotDirection = Direction;
}

// Called when the game starts or when spawned
void ACphProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(CollisionComponent)
    check(MovementComponent)
    check(WeaponComponentFX)

    CollisionComponent->OnComponentHit.AddDynamic(
        this, &ACphProjectile::OnProjectileHit);

    MovementComponent->Velocity =
        ShotDirection * MovementComponent->InitialSpeed;

    SetLifeSpan(LifeSeconds);
}

// For delegate signature
void ACphProjectile::OnProjectileHit(UPrimitiveComponent* HitComponent,
                                     AActor* OtherActor,
                                     UPrimitiveComponent* OtherComp,
                                     FVector NormalImpulse,
                                     const FHitResult& Hit)
{
    if (!GetWorld()) return;

    MovementComponent->StopMovementImmediately();

    // Deal damage
    UGameplayStatics::ApplyRadialDamage(GetWorld(),
                                        DamageAmount,
                                        GetActorLocation(),
                                        DamageRadius,
                                        UDamageType::StaticClass(),
                                        {},
                                        this,
                                        GetController(),
                                        DoFullDamage);

    // Visualisation of damage sphere
    DrawDebugSphere(GetWorld(),
                    GetActorLocation(),
                    DamageRadius,
                    32,
                    FColor::Red,
                    false,
                    5.0f);

    // Visual effect
    WeaponComponentFX->PlayImpactFX(Hit);

    // Destroy then hits or after life span time
    Destroy();
}

// Returns nullptr, if fails
AController* ACphProjectile::GetController() const
{
    const APawn* Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController() : nullptr;
}
