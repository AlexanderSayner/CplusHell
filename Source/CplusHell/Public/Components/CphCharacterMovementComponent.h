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
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement",
        meta = (ClampMin = "1.0", ClampMax = "10.0"))
    float RunModifier = 1.5f;

    // Setting max speed then character walk or run
    virtual float GetMaxSpeed() const override;
};
