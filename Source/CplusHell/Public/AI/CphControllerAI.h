// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "CphControllerAI.generated.h"

class UCphAIPerceptionComponent;

/**
 * AI behaviour 
 */
UCLASS()
class CPLUSHELL_API ACphControllerAI final : public AAIController
{
    GENERATED_BODY()

public:
    ACphControllerAI();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UCphAIPerceptionComponent* AIPerceptionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="AI")
    FName FocusOnKeyName = "EnemyActor";

    virtual void OnPossess(APawn* InPawn) override;

public:
    // Detect closest enemy and turn controller on him
    virtual void Tick(float DeltaTime) override;

private:
    // Return actor that has to be in focus
    AActor* GetFocusOnActor();
};
