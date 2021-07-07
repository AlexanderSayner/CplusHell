// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "Weapon/CphBaseWeapon.h"
#include "CphNeedAmmoDecorator.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSHELL_API UCphNeedAmmoDecorator final : public UBTDecorator
{
    GENERATED_BODY()

public:
    UCphNeedAmmoDecorator();

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    TSubclassOf<ACphBaseWeapon> WeaponType;

    virtual bool CalculateRawConditionValue(
        UBehaviorTreeComponent& OwnerComp,
        uint8* NodeMemory) const override;
};
