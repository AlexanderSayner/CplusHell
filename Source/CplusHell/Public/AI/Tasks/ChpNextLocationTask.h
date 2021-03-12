// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "ChpNextLocationTask.generated.h"

/**
 * AI patrolling point destination generator
 */
UCLASS()
class CPLUSHELL_API UChpNextLocationTask final : public UBTTaskNode
{
    GENERATED_BODY()

public:
    // Sets visual node name
    UChpNextLocationTask();
    
    virtual EBTNodeResult::Type ExecuteTask(
        UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
    
protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    float Radius = 1000.0f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FBlackboardKeySelector AimLocationKey;
};
