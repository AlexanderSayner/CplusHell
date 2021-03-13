// C plus Hell Learning Game, All Right Reserved.


#include "AI/Decorators/CphHealthPercentDecorator.h"

#include "AIController.h"
#include "Components/CphHealthComponent.h"

UCphHealthPercentDecorator::UCphHealthPercentDecorator()
{
    NodeName = "Health Percent";
}

bool UCphHealthPercentDecorator::CalculateRawConditionValue(
    UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    if (!AIController) return false;

    UActorComponent* HealthComponentCandidate = AIController->GetPawn()->
        FindComponentByClass(UCphHealthComponent::StaticClass());
    UCphHealthComponent* HealthComponent = Cast<UCphHealthComponent>(
        HealthComponentCandidate);
    if (!HealthComponent || !HealthComponent->IsAlive()) return false;

    return HealthComponent->GetHealthRatio() < HealthPercent;
}
