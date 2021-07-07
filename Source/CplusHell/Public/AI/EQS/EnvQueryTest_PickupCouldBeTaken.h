// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_PickupCouldBeTaken.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSHELL_API UEnvQueryTest_PickupCouldBeTaken final : public UEnvQueryTest
{
    GENERATED_BODY()

public:
    explicit UEnvQueryTest_PickupCouldBeTaken(
        const FObjectInitializer& ObjectInitializer);

    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
};
