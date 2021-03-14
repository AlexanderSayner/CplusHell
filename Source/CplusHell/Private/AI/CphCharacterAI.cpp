// C plus Hell Learning Game, All Right Reserved.


#include "AI/CphCharacterAI.h"

#include "BrainComponent.h"
#include "AI/CphControllerAI.h"
#include "Components/CphWeaponAIComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ACphCharacterAI::ACphCharacterAI(const FObjectInitializer& ObjectInitializer)
    : Super(
        ObjectInitializer.SetDefaultSubobjectClass<UCphWeaponAIComponent>(
            "WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = ACphControllerAI::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }
}

void ACphCharacterAI::OnDeath()
{
    Super::OnDeath();

    AAIController* CphController = Cast<AAIController>(Controller);
    if (CphController && CphController->BrainComponent)
    {   
        CphController->BrainComponent->Cleanup();
    }
}
