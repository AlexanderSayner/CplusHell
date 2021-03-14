// C plus Hell Learning Game, All Right Reserved.


#include "Components/CphAIPerceptionComponent.h"


#include "AIController.h"
#include "CphUtils.h"
#include "Components/CphHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* UCphAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> PerceiveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PerceiveActors);
    if (PerceiveActors.Num() == 0) return nullptr;

    AAIController* Controller = Cast<AAIController>(GetOwner());
    if (!Controller) return nullptr;

    APawn* Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;

    float BestDistance = MAX_FLT;
    AActor* BestPawn = nullptr;

    for (AActor* PerceiveActor : PerceiveActors)
    {
        UActorComponent* CandidateComponent = PerceiveActor->
            FindComponentByClass(UCphHealthComponent::StaticClass());
        const UCphHealthComponent* HealthComponent = Cast<UCphHealthComponent>(
            CandidateComponent);

        APawn* PerceivePawn = Cast<APawn>(PerceiveActor);
        const bool AreEnemies = PerceivePawn && FCphUtils::AreEnemies(
                                    Controller, PerceivePawn->Controller);

        // TODO: check for allies
        if (HealthComponent && HealthComponent->IsAlive() && AreEnemies)
        {
            const float CurrentDistance = (
                    PerceiveActor->GetActorLocation() - Pawn->GetActorLocation()
                ).
                Size();

            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PerceiveActor;
            }
        }
    }

    return BestPawn;
}