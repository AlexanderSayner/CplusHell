// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "CphAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSHELL_API UCphAIPerceptionComponent final : public UAIPerceptionComponent
{
    GENERATED_BODY()

public:
    AActor* GetClosestEnemy() const;
};
