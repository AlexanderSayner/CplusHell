// C plus Hell Learning Game, All Right Reserved.


#include "AI/Tasks/ChpNextLocationTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackboardComponent.h"

// Default constructor
UChpNextLocationTask::UChpNextLocationTask()
{
    NodeName = "Next Location";
}

//
EBTNodeResult::Type UChpNextLocationTask::ExecuteTask(
    UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const AAIController* Controller = OwnerComp.GetAIOwner();
    UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
    if (!Controller || !Blackboard) return EBTNodeResult::Failed;

    APawn* Pawn = Controller->GetPawn();
    if (!Pawn) return EBTNodeResult::Failed;

    const UNavigationSystemV1* NavSys = UNavigationSystemV1::GetCurrent(Pawn);
    if (!NavSys) return EBTNodeResult::Failed;

    FNavLocation NavLocation;
    FVector Location = Pawn->GetActorLocation();
    if (!SelfCenter)
    {
        AActor* CenterActor = Cast<AActor>(
            Blackboard->GetValueAsObject(CenterActorKey.SelectedKeyName));
        if (!CenterActor) return EBTNodeResult::Failed;
        Location = CenterActor->GetActorLocation();
    }

    const bool Found = NavSys->GetRandomReachablePointInRadius(
        Location, Radius, NavLocation);
    if (!Found) return EBTNodeResult::Failed;

    Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName,
                                 NavLocation.Location);
    return EBTNodeResult::Succeeded;
}
