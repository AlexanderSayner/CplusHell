// C plus Hell Learning Game, All Right Reserved.


#include "Player/CphBaseCharacter.h"


#include "Components/CapsuleComponent.h"
#include "Components/CphCharacterMovementComponent.h"
#include "Components/CphHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/CphWeaponComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBaseCharacter, All, All);

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
        "CameraBoom");
    // Set parent root component
    SpringArmComponent->SetupAttachment(GetRootComponent());
    /* For looking up and down set Use Pawn Control Rotation true in camera component
    * also it can be set up in details window in Base Character blueprint if you wish */
    SpringArmComponent->bUsePawnControlRotation = true;
    // Camera angle
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 70.0f);

    // Creating player eyes
    FollowCamera = CreateDefaultSubobject<UCameraComponent>(
        "FollowCamera");
    // Attach camera to SpringArm
    FollowCamera->SetupAttachment(SpringArmComponent);

    // For logical components no need to SetupAttachment
    HealthComponent = CreateDefaultSubobject<UCphHealthComponent>(
        "HealthComponent");

    // Set up health number
    HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>(
        "HealthTextComponent");
    HealthTextComponent->SetupAttachment(GetRootComponent());
    // See only other players health 
    HealthTextComponent->SetOwnerNoSee(true);

    // Weapon is just logical component
    WeaponComponent = CreateDefaultSubobject<UCphWeaponComponent>(
        "WeaponComponent");
}

// Called when the game starts or when spawned
void ACphBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    // Checking for null only in debug and development mode
    check(HealthComponent)
    check(HealthTextComponent)
    check(GetCharacterMovement())

    // Init health before delegate declaration
    OnHealthChanged(HealthComponent->GetHealth());
    HealthComponent->OnDeath
                   .AddUObject(this, &ACphBaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged
                   .AddUObject(this, &ACphBaseCharacter::OnHealthChanged);
    // Subscribe for landing
    LandedDelegate.AddDynamic(this, &ACphBaseCharacter::OnGroundLanded);
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
    check(PlayerInputComponent)
    check(WeaponComponent)

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

    // Fire
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent,
                                     &UCphWeaponComponent::Fire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent,
                                     &UCphWeaponComponent::StopFire);

    // Weapon choosing circle
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent,
                                     &UCphWeaponComponent::NextWeapon);

    // Reload animation
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent,
                                     &UCphWeaponComponent::Reload);
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
    return AngleBetweenDegrees * FMath::Sign(CrossProduct.Z);
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

// Event for playing death animation
void ACphBaseCharacter::OnDeath()
{
    UE_LOG(LogBaseCharacter, Display, TEXT("Oh no, player %s is dead"),
           *GetName())
    // Play animation montage
    PlayAnimMontage(DeathAminMontage);
    // Player can not move after death
    GetCharacterMovement()->DisableMovement();
    // Span after some seconds
    SetLifeSpan(LifeSpanOnDeath);
    // Turn on spectator
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
    // Turn off collision
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
    // Stop firing
    WeaponComponent->StopFire();
}

// Health changed event
void ACphBaseCharacter::OnHealthChanged(const float Health) const
{
    // Display health number
    HealthTextComponent->SetText(
        FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

// Subscription for landing delegate
void ACphBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    // Always negative when fall
    const float FallVelocityZ = -GetVelocity().Z;
    UE_LOG(LogBaseCharacter, Display, TEXT("On landed: %f"), FallVelocityZ)

    // If fall speed is not too big then no damage
    if (FallVelocityZ < LandedDamageVelocity.X) return;
    // Proportional damage calculation
    const float FinalDamage = FMath::GetMappedRangeValueClamped(
        LandedDamageVelocity, LandedDamage, FallVelocityZ);
    UE_LOG(LogBaseCharacter, Display, TEXT("Damage dealed: %f"), FinalDamage)
    // Character deal damage itself
    TakeDamage(FinalDamage, FDamageEvent{}, GetController(), this);
}
