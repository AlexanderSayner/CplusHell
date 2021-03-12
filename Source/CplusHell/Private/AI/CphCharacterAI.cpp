// C plus Hell Learning Game, All Right Reserved.


#include "AI/CphCharacterAI.h"
#include "AI/CphControllerAI.h"
#include "GameFramework/CharacterMovementComponent.h"

ACphCharacterAI::ACphCharacterAI(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = ACphControllerAI::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}
