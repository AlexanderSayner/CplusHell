// C plus Hell Learning Game, All Right Reserved.


#include "Player/CphBaseCharacter.h"

#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACphBaseCharacter::ACphBaseCharacter()
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    // Attach SpringArm to root Actor's component using GetRootComponent function
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(
        "SpringArmComponent");
    // Set parent root component
    SpringArmComponent->SetupAttachment(GetRootComponent());
    /* For looking up and down set Use Pawn Control Rotation true in camera component
    * also it can be set up in details window in Base Character blueprint if you wish */
    SpringArmComponent->bUsePawnControlRotation = true;

    // Creating player eyes
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(
        "CameraComponent");
    // Attach camera to SpringArm
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void ACphBaseCharacter::BeginPlay()
{
    Super::BeginPlay();
}

// Called every frame
void ACphBaseCharacter::Tick(float const DeltaTime)
{
    Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACphBaseCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    // MoveForward and MoveRight is mapped in unreal editor project preferences
    PlayerInputComponent->BindAxis(
        "MoveForward", this, &ACphBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis(
        "MoveRight", this, &ACphBaseCharacter::MoveRight);

    // Set up mouse control
    // Set Input Pitch Scale to positive number to avoid inverse camera movement
    PlayerInputComponent->BindAxis("LookUp", this,
                                   &ACphBaseCharacter::AddControllerPitchInput);
    // Turning character itself
    PlayerInputComponent->BindAxis("LookAround", this,
                                   &ACphBaseCharacter::AddControllerYawInput);

    // Jump!
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this,
                                     &ACphBaseCharacter::Jump);

    // Running control
    PlayerInputComponent->BindAction("Run", IE_Pressed, this,
                                     &ACphBaseCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this,
                                     &ACphBaseCharacter::OnStopRunning);
}

// Tell for blueprint, if character is running
bool ACphBaseCharacter::IsRunning() const
{
    // Pressed LShift and W and speed is not a zero
    return IsReadyToRun && IsMovingForward && !GetVelocity().IsZero();
}

// Calls then character moves by MoveForward action mapping 
void ACphBaseCharacter::MoveForward(float const Amount)
{
    // If i am moving forward, i can run
    IsMovingForward = Amount > 0.0f;
    // AddMovementInput is a part of Pawn and allows it to move.
    AddMovementInput(
        GetActorForwardVector(), // Go wherever character looks
        Amount);
}

// Calls then character moves by MoveRight action mapping
void ACphBaseCharacter::MoveRight(float const Amount)
{
    AddMovementInput(GetActorRightVector(), Amount);
}

void ACphBaseCharacter::OnStartRunning()
{
    IsReadyToRun = true;
}

void ACphBaseCharacter::OnStopRunning()
{
    IsReadyToRun = false;
}
