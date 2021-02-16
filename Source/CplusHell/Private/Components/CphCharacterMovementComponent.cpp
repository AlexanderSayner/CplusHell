// C plus Hell Learning Game, All Right Reserved.


#include "Components/CphCharacterMovementComponent.h"

#include "Player/CphBaseCharacter.h"

// Setting max speed then character walk or run
float UCphCharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    // CphBaseCharacter is owner of this class
    const ACphBaseCharacter* Player = Cast<ACphBaseCharacter>(GetPawnOwner());
    // Check: run or sprint otherwise just MaxSpeed
    return Player && Player->IsSprinting()
               ? MaxSpeed * SprintModifier
               : MaxSpeed;
}
