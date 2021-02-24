// C plus Hell Learning Game, All Right Reserved.


#include "Weapon/CphBaseWeapon.h"

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
    UE_LOG(LogBaseWeapon, Display, TEXT("Fires"))
}

// Called when the game starts or when spawned
void ACphBaseWeapon::BeginPlay()
{
    Super::BeginPlay();
}
