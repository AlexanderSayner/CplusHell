// C plus Hell Learning Game, All Right Reserved.


#include "Components/CphWeaponComponent.h"

#include "GameFramework/Character.h"
#include "Weapon/CphBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogCphWeaponComponent, All, All)

// Sets default values for this component's properties
UCphWeaponComponent::UCphWeaponComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

// Destroy player weapons
void UCphWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon=nullptr;
    for (ACphBaseWeapon* Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
}

// Fire on action. Can not be const, because of using in BindAction
void UCphWeaponComponent::Fire()
{
    if (CurrentWeapon)
    {
        CurrentWeapon->Fire();
    }
}

// On mouse button release. Can not be const, because of using in BindAction
void UCphWeaponComponent::StopFire()
{
    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
    }
}

// Circle choosing weapon
void UCphWeaponComponent::NextWeapon()
{
    // The remainder of the division by the length of the array
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}


// Called when the game starts
void UCphWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    SpawnWeapons();
    check(CurrentWeaponIndex==0)
    EquipWeapon(CurrentWeaponIndex);
}

//
void UCphWeaponComponent::AttachWeaponToSocket(ACphBaseWeapon* Weapon,
                                               ACharacter* Character,
                                               const FName& Name)
{
    if (!Weapon || !Character) return;

    // Connect spawned weapon to mesh
    const FAttachmentTransformRules Rules(
        EAttachmentRule::SnapToTarget,
        false);
    // GetMesh() returns character's skeleton mesh component
    Weapon->AttachToComponent(Character->GetMesh(), Rules,
                              Name);
    // Set owner for access his camera for shooting direction
    Weapon->SetOwner(Character);
}

// Set Current weapon, attach to character's hand
void UCphWeaponComponent::EquipWeapon(const int32 WeaponIndex)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    // Take off weapon first if has one
    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character, WeaponArmorySocketName);
    }

    // Take weapon in hands
    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToSocket(CurrentWeapon, Character, WeaponEquipSocketName);
}

//
void UCphWeaponComponent::SpawnWeapons()
{
    // Actor spawn on world
    if (!GetWorld()) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    for (TSubclassOf<ACphBaseWeapon> WeaponClass : WeaponClasses)
    {
        ACphBaseWeapon* Weapon =
            GetWorld()->SpawnActor<ACphBaseWeapon>(WeaponClass);

        if (Weapon)
        {
            Weapon->SetOwner(Character);
            Weapons.Add(Weapon);

            AttachWeaponToSocket(Weapon, Character,
                                 WeaponArmorySocketName);
        }
        else
        {
            LogWarning(FString::Printf(TEXT("Could not spawn weapon")));
        }
    }
}

// Logger
void UCphWeaponComponent::LogWarning(const FString Reason)
{
    UE_LOG(LogCphWeaponComponent, Warning, TEXT("%s"), *Reason)
}
