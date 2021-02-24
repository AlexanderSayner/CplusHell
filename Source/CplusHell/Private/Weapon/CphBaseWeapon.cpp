// C plus Hell Learning Game, All Right Reserved.


#include "Weapon/CphBaseWeapon.h"

// Sets default values
ACphBaseWeapon::ACphBaseWeapon()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

// Called when the game starts or when spawned
void ACphBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}
