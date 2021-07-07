// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CphFindEnemyService.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSHELL_API UCphFindEnemyService final : public UBTService
{
    GENERATED_BODY()

public:
    UCphFindEnemyService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
        float DeltaSeconds) override;
};
