// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CphChangeWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSHELL_API UCphChangeWeaponService final : public UBTService
{
    GENERATED_BODY()

public:
    UCphChangeWeaponService();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI",
        meta=(ClampMin="0.0", ClampMax="1.0"))
    float Probability = 0.5f;

    virtual void TickNode(UBehaviorTreeComponent& OwnerComp,
                          uint8* NodeMemory, float DeltaSeconds) override;
};
