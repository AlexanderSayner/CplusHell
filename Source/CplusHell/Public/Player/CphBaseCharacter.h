// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "CphBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

/*
 * My main awesome character
 */
UCLASS()
class CPLUSHELL_API ACphBaseCharacter final : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    ACphBaseCharacter();

protected:
    // Smart camera controller
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;
    // Getting ful control on camera
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* CameraComponent;
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent) override;

private:
    // Calls then character moves by MoveForward action mapping 
    void MoveForward(float Amount);
    // Calls then character moves by MoveRight action mapping
    void MoveRight(float Amount);
};
