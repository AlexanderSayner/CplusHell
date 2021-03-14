// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/Character.h"
#include "CphBaseCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UCphHealthComponent;
class UTextRenderComponent;
class UCphWeaponComponent;

/*
 * My main awesome character
 */
UCLASS()
class CPLUSHELL_API ACphBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Constructor
    // Sets default values for this character's properties
    explicit ACphBaseCharacter(const FObjectInitializer& ObjInit);


    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    // Called every frame
    virtual void Tick(float DeltaTime) override;

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(
        class UInputComponent* PlayerInputComponent) override;

    // Tell for blueprint, if character is sprinting
    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsSprinting() const;

    // Tell for blueprint, there player looks
    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

    // Called by Game Mode Base, sets color for player mesh material
    void SetPlayerColor(const FLinearColor& Color) const;

protected:
    // Smart camera controller
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USpringArmComponent* SpringArmComponent;
    // Getting ful control on camera
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCameraComponent* FollowCamera;
    // Allows to display health status above character
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCphHealthComponent* HealthComponent;
    // For display health number
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UTextRenderComponent* HealthTextComponent;
    // Weapon management
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UCphWeaponComponent* WeaponComponent;
    // Play death animation
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAminMontage;
    // Time before respawn
    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    float LifeSpanOnDeath = 6.0f;
    // Landed force interval when damage is dealt 
    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamageVelocity = FVector2D(550.0f, 1250.0f);
    // Landed damage interval
    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamage = FVector2D(1, 10000);
    // Variable name for mesh material color
    UPROPERTY(EditDefaultsOnly, Category="Material")
    FName MaterialColorName = "Paint Color";

    // Event for playing death animation
    virtual void OnDeath();

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
    // Health changed event
    void OnHealthChanged(const float Health, const float Delta) const;
    // Subscription for landing delegate
    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);
};
