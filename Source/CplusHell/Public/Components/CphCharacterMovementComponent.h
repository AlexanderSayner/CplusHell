// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CphCharacterMovementComponent.generated.h"

/**
 * Changing speed of run for character
 */
UCLASS()
class CPLUSHELL_API
    UCphCharacterMovementComponent final : public UCharacterMovementComponent
{
    GENERATED_BODY()

public:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
        meta = (ClampMin = "1.5", ClampMax = "5.0"))
    float SprintModifier = 2.0f;

    // Setting max speed then character walk or run
    virtual float GetMaxSpeed() const override;
};
