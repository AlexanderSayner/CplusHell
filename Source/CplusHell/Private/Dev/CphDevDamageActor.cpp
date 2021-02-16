// C plus Hell Learning Game, All Right Reserved.


#include "Dev/CphDevDamageActor.h"

#include "DrawDebugHelpers.h"

// Sets default values
ACphDevDamageActor::ACphDevDamageActor()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
}

// Called when the game starts or when spawned
void ACphDevDamageActor::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ACphDevDamageActor::Tick(const float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Debug damage sphere
    DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 16, SphereColor);
}
