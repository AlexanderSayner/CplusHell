// C plus Hell Learning Game, All Right Reserved.


#include "Player/CphBaseCharacter.h"


#include "Components/CphCharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
ACphBaseCharacter::ACphBaseCharacter(const FObjectInitializer& ObjInit)
    : Super(
        ObjInit.SetDefaultSubobjectClass<UCphCharacterMovementComponent>(
            ACharacter::CharacterMovementComponentName))
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
    PlayerInputComponent->BindAxis("MoveForward", this,
                                   &ACphBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this,
                                   &ACphBaseCharacter::MoveRight);

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

    // Sprint
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this,
                                     &ACphBaseCharacter::OnStartSprinting);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this,
                                     &ACphBaseCharacter::OnStopSprinting);
}

// Tell for blueprint, if character is sprinting
bool ACphBaseCharacter::IsSprinting() const
{
    return IsReadyToSprint && IsMovingForward && !GetVelocity().IsZero();
}

// Tell for blueprint, there player looks
float ACphBaseCharacter::GetMovementDirection() const
{
    // No need to calculate if player doesn't move
    if (GetVelocity().IsZero()) return 0.0f;
    // Normal for vector of speed
    const FVector Normal = GetVelocity().GetSafeNormal();
    // Arc cosine from scalar product (dot product) between vector where camera looks and velocity normal 
    const float AngleBetween = FMath::Acos(
        FVector::DotProduct(GetActorForwardVector(), Normal));
    // Orthogonal vector
    const FVector CrossProduct = FVector::CrossProduct(
        GetActorForwardVector(), Normal);
    // Acos returns radians
    const float AngleBetweenDegrees = FMath::RadiansToDegrees(AngleBetween);
    // If Z < 0, then multiply -1, otherwise 1
    return CrossProduct.IsZero()
               ? AngleBetweenDegrees
               : AngleBetweenDegrees * FMath::Sign(CrossProduct.Z);
}

// Calls then character moves by MoveForward action mapping 
void ACphBaseCharacter::MoveForward(float const Amount)
{
    // If i am not falling, i can run
    IsMovingForward = Amount > 0.0f;
    // AddMovementInput is a part of Pawn and allows it to move.
    AddMovementInput(
        GetActorForwardVector(), // Go wherever character looks
        Amount);
}

// Calls then character moves by MoveRight action mapping
void ACphBaseCharacter::MoveRight(float const Amount)
{
    AddMovementInput(
        GetActorRightVector(),
        Amount);
}

// Pressed sprint key
void ACphBaseCharacter::OnStartSprinting()
{
    IsReadyToSprint = true;
}

// Released sprint key
void ACphBaseCharacter::OnStopSprinting()
{
    IsReadyToSprint = false;
}
