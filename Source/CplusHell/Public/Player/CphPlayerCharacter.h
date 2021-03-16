// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Player/CphBaseCharacter.h"
#include "CphPlayerCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

/**
 * Logic than defines player only but AI
 */
UCLASS()
class CPLUSHELL_API ACphPlayerCharacter final : public ACphBaseCharacter
{
    GENERATED_BODY()

public:
    explicit ACphPlayerCharacter(const FObjectInitializer& ObjectInitializer);

    virtual bool IsSprinting() const override;

    virtual void SetupPlayerInputComponent(
        UInputComponent* PlayerInputComponent) override;

protected:
    // Smart camera controller
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;

    // Getting ful control on camera
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* FollowCamera;

    virtual void OnDeath() override;

private:
    // Variables
    // Indicates character wish to run
    bool IsMovingForward = false;
    bool IsReadyToSprint = false;

    // Functions
    // Calls then character moves by MoveForward action mapping 
    void MoveForward(float Amount);
    // Calls then character moves by MoveRight action mapping
    void MoveRight(float Amount);
    // Pressed acceleration key
    void OnStartSprinting();
    // Released acceleration key
    void OnStopSprinting();
};
