// C plus Hell Learning Game, All Right Reserved.


#include "AI/CphControllerAI.h"

#include "AI/CphCharacterAI.h"

void ACphControllerAI::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    const ACphCharacterAI* CphCharacter = Cast<ACphCharacterAI>(InPawn);
    if (CphCharacter)
    {
        RunBehaviorTree(CphCharacter->BehaviorTreeAsset);
    }
}
