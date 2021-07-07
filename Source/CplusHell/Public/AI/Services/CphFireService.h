// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CphFireService.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSHELL_API UCphFireService final : public UBTService
{
    GENERATED_BODY()

public:
    UCphFireService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FBlackboardKeySelector EnemyKeyActor;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp,
                          uint8* NodeMemory, float DeltaSeconds) override;
};
