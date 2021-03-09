// C plus Hell Learning Game, All Right Reserved.


#include "Pickups/CphBasePickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All)

// Sets default values
ACphBasePickup::ACphBasePickup()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>(
        "SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void ACphBasePickup::BeginPlay()
{
    Super::BeginPlay();

    check(GetRootComponent())
    check(CollisionComponent)
}

// For child classed implementing
bool ACphBasePickup::AddSomeBuffsTo(APawn* Pawn)
{ 
    return false;
}

// Called then player overlaps
void ACphBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    APawn* Pawn = Cast<APawn>(OtherActor);
    if (AddSomeBuffsTo(Pawn))
    {
        PickupWasTaken();
    }
    else
    {
        UE_LOG(LogBasePickup, Display, TEXT("You can not touch this"))
    }
}

// Called every frame
void ACphBasePickup::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Make bonus invisible
void ACphBasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);
    UE_LOG(LogBasePickup, Display, TEXT("Setted visibility to false"))

    FTimerHandle RespawnTimerHandle;
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this,
                                    &ACphBasePickup::Respawn, RespawnTime);
}

// Make visible
void ACphBasePickup::Respawn() const
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
    GetRootComponent()->SetVisibility(true, true);
    UE_LOG(LogBasePickup, Display, TEXT("Setted visibility to true"))
}
