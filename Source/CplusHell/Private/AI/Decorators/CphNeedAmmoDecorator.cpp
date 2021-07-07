// C plus Hell Learning Game, All Right Reserved.


#include "AI/Decorators/CphNeedAmmoDecorator.h"

#include "AIController.h"
#include "Components/CphWeaponComponent.h"

UCphNeedAmmoDecorator::UCphNeedAmmoDecorator()
{
    NodeName = "Need Ammo";
}

bool UCphNeedAmmoDecorator::CalculateRawConditionValue(
    UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return false;

    UActorComponent* WeaponComponentCandidate = AIController->GetPawn()->
        FindComponentByClass(UCphWeaponComponent::StaticClass());
    UCphWeaponComponent* WeaponComponent = Cast<UCphWeaponComponent>(
        WeaponComponentCandidate);
    if (!WeaponComponent) return false;

    return WeaponComponent->NeedAmmo(WeaponType);
}
