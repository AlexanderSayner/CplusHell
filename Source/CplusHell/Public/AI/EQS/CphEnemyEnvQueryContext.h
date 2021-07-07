// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "CphEnemyEnvQueryContext.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSHELL_API UCphEnemyEnvQueryContext final : public UEnvQueryContext
{
    GENERATED_BODY()

public:
    virtual void ProvideContext(
        FEnvQueryInstance& QueryInstance,
        FEnvQueryContextData& ContextData) const override;

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FName EnemyActorKeyName = "EnemyActor";
};
