// C plus Hell Learning Game, All Right Reserved.


#include "AI/CphControllerAI.h"

#include "Components/CphAIPerceptionComponent.h"
#include "AI/CphCharacterAI.h"
#include "BehaviorTree/BlackboardComponent.h"

ACphControllerAI::ACphControllerAI()
{
    AIPerceptionComponent = CreateDefaultSubobject<UCphAIPerceptionComponent>(
        "CphAIPerceptionComponent");
    SetPerceptionComponent(*AIPerceptionComponent);
}

void ACphControllerAI::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const ACphCharacterAI* CphCharacter = Cast<ACphCharacterAI>(InPawn);
    if (CphCharacter)
    {
        RunBehaviorTree(CphCharacter->BehaviorTreeAsset);
    }
}

// Detect closest enemy and turn controller on him
void ACphControllerAI::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AActor* AimActor = GetFocusOnActor();
    SetFocus(AimActor);
}

// Return actor that has to be in focus
AActor* ACphControllerAI::GetFocusOnActor()
{
    if (!GetBlackboardComponent()) return nullptr;
    return Cast<AActor>(
        GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
