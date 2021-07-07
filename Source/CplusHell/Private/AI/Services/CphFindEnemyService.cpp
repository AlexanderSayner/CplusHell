// C plus Hell Learning Game, All Right Reserved.


#include "AI/Services/CphFindEnemyService.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CphAIPerceptionComponent.h"

UCphFindEnemyService::UCphFindEnemyService()
{
    NodeName = "Find Enemy";
}

void UCphFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp,
                                    uint8* NodeMemory, float DeltaSeconds)
{
    UBlackboardComponent* BlackBoard = OwnerComp.GetBlackboardComponent();
    if (BlackBoard)
    {
        AAIController* Controller = OwnerComp.GetAIOwner();
        UActorComponent* PerceptionComponentCandidate = Controller->
            FindComponentByClass(UCphAIPerceptionComponent::StaticClass());
        UCphAIPerceptionComponent* PerceptionComponent =
            Cast<UCphAIPerceptionComponent>(PerceptionComponentCandidate);

        if (PerceptionComponent)
        {
            BlackBoard->SetValueAsObject(EnemyActorKey.SelectedKeyName,
                                         PerceptionComponent->
                                         GetClosestEnemy());
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
