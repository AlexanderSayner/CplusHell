// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CphControllerAI.generated.h"

/**
 * AI behaviour 
 */
UCLASS()
class CPLUSHELL_API ACphControllerAI final : public AAIController
{
    GENERATED_BODY()

protected:
    virtual void OnPossess(APawn* InPawn) override;
};
