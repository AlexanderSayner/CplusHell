// C plus Hell Learning Game, All Right Reserved.


#include "AI/Services/CphFireService.h"


#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CphWeaponComponent.h"

UCphFireService::UCphFireService()
{
    NodeName = "Fire";
}

void UCphFireService::TickNode(UBehaviorTreeComponent& OwnerComp,
                               uint8* NodeMemory, float DeltaSeconds)
{
    AAIController* AIController = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();

    const bool HasAim = Blackboard && Blackboard->GetValueAsObject(
                            EnemyKeyActor.SelectedKeyName);

    if (AIController)
    {
        UActorComponent* WeaponComponentCandidate = AIController->GetPawn()->
            FindComponentByClass(UCphWeaponComponent::StaticClass());
        UCphWeaponComponent* WeaponComponent = Cast<UCphWeaponComponent>(
            WeaponComponentCandidate);
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }
}
