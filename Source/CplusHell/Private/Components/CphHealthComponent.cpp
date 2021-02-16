// C plus Hell Learning Game, All Right Reserved.


#include "Components/CphHealthComponent.h"

#include "Dev/CphFireDamageType.h"
#include "Dev/CphIceDamageType.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

// Sets default values for this component's properties
UCphHealthComponent::UCphHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}


// Called when the game starts
void UCphHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    Health = MaxHealth;

    AActor* ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(
            this, &UCphHealthComponent::OnTakeAnyDamage);
    }
}

void UCphHealthComponent::OnTakeAnyDamage(AActor* DamagedActor,
                                          const float Damage,
                                          const UDamageType* DamageType,
                                          AController* InstigatedBy,
                                          AActor* DamageCauser)
{
    Health -= Damage;
    UE_LOG(LogHealthComponent, Display, TEXT("Damage: %f"), Damage)

    if (DamageType)
    {
        if (DamageType->IsA<UCphFireDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("I am in fire!"))
        }
        else if (DamageType->IsA<UCphIceDamageType>())
        {
            UE_LOG(LogHealthComponent, Display, TEXT("It's so cold here"))
        }
    }
}
