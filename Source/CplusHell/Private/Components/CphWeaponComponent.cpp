// C plus Hell Learning Game, All Right Reserved.


#include "Components/CphWeaponComponent.h"

#include "GameFramework/Character.h"
#include "Weapon/CphBaseWeapon.h"

// Sets default values for this component's properties
UCphWeaponComponent::UCphWeaponComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

// Fire on action. Can not be const, because of using in BindAction
void UCphWeaponComponent::Fire()
{
    if(CurrentWeapon)
    {
        CurrentWeapon->Fire();
    }
}


// Called when the game starts
void UCphWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    SpawnWeapon();
}

void UCphWeaponComponent::SpawnWeapon()
{
    // Actor spawn on world
    if (GetWorld())
    {
        ACharacter* Character = Cast<ACharacter>(GetOwner());
        if (Character)
        {
            CurrentWeapon =
                GetWorld()->SpawnActor<ACphBaseWeapon>(WeaponClass);
            // Connect spawned weapon to mesh
            if (CurrentWeapon)
            {
                const FAttachmentTransformRules Rules(
                    EAttachmentRule::SnapToTarget,
                    false);
                // GetMesh() returns character's skeleton mesh component
                CurrentWeapon->AttachToComponent(Character->GetMesh(), Rules,
                                                 WeaponAttachPointName);
            }
        }
    }
}
