// C plus Hell Learning Game, All Right Reserved.


#include "AI/Services/CphChangeWeaponService.h"

#include "AIController.h"
#include "Components/CphWeaponComponent.h"

UCphChangeWeaponService::UCphChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void UCphChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp,
                                       uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (AIController)
    {
        UActorComponent* WeaponComponentCandidate = AIController->GetPawn()->
            FindComponentByClass(
                UCphWeaponComponent::StaticClass());
        UCphWeaponComponent* WeaponComponent = Cast<UCphWeaponComponent>(
            WeaponComponentCandidate);
        if (WeaponComponent && FMath::FRand() < Probability)
        {
            WeaponComponent->NextWeapon();
        }
    }
}
