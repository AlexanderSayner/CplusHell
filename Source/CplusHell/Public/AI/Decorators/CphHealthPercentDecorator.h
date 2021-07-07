// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "CphHealthPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSHELL_API UCphHealthPercentDecorator final : public UBTDecorator
{
    GENERATED_BODY()

public:
    UCphHealthPercentDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float HealthPercent = 0.6f;

    virtual bool CalculateRawConditionValue(
        UBehaviorTreeComponent& OwnerComp,
        uint8* NodeMemory) const override;
};
