// C plus Hell Learning Game, All Right Reserved.


#include "Player/CphPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/CphWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"

ACphPlayerCharacter::ACphPlayerCharacter(
    const FObjectInitializer& ObjectInitializer)
    : ACphBaseCharacter(ObjectInitializer)
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

    // Sets character invisible, if camera inside him
    CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>(
        "CameraCollisionComponent");
    CameraCollisionComponent->SetupAttachment(FollowCamera);
    CameraCollisionComponent->SetSphereRadius(10.0f);
    CameraCollisionComponent->SetCollisionResponseToAllChannels(ECR_Overlap);
}

//
void ACphPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(CameraCollisionComponent)

    CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(
        this, &ACphPlayerCharacter::OnCameraCollisionBeginOverlap);
    CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(
        this, &ACphPlayerCharacter::OnCameraCollisionEndOverlap);
}

//
bool ACphPlayerCharacter::IsSprinting() const
{
    return IsReadyToSprint && IsMovingForward && !GetVelocity().IsZero();
}

//
void ACphPlayerCharacter::SetupPlayerInputComponent(
    UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    check(PlayerInputComponent)
    check(WeaponComponent)

    // MoveForward and MoveRight is mapped in unreal editor project preferences
    PlayerInputComponent->BindAxis("MoveForward", this,
                                   &ACphPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this,
                                   &ACphPlayerCharacter::MoveRight);

    // Set up mouse control
    // Set Input Pitch Scale to positive number to avoid inverse camera movement
    PlayerInputComponent->BindAxis("LookUp", this,
                                   &ACphPlayerCharacter::AddControllerPitchInput);
    // Turning character itself
    PlayerInputComponent->BindAxis("LookAround", this,
                                   &ACphPlayerCharacter::AddControllerYawInput);

    // Jump!
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this,
                                     &ACphPlayerCharacter::Jump);

    // Sprint
    PlayerInputComponent->BindAction("Sprint", IE_Pressed, this,
                                     &ACphPlayerCharacter::OnStartSprinting);
    PlayerInputComponent->BindAction("Sprint", IE_Released, this,
                                     &ACphPlayerCharacter::OnStopSprinting);

    // Fire
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent,
                                     &UCphWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent,
                                     &UCphWeaponComponent::StopFire);

    // Weapon choosing circle
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent,
                                     &UCphWeaponComponent::NextWeapon);

    // Reload animation
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent,
                                     &UCphWeaponComponent::Reload);
}

//
void ACphPlayerCharacter::MoveForward(float Amount)
{
    // If i am not falling, i can run
    IsMovingForward = Amount > 0.0f;
    // AddMovementInput is a part of Pawn and allows it to move.
    AddMovementInput(
        GetActorForwardVector(), // Go wherever character looks
        Amount);
}

//
void ACphPlayerCharacter::MoveRight(float Amount)
{
    AddMovementInput(
        GetActorRightVector(),
        Amount);
}

//
void ACphPlayerCharacter::OnStartSprinting()
{
    IsReadyToSprint = true;
}

//
void ACphPlayerCharacter::OnStopSprinting()
{
    IsReadyToSprint = false;
}

//
void ACphPlayerCharacter::OnCameraCollisionBeginOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
    const FHitResult& SweepResult) 
{
    CheckCameraOverlap();
}

//
void ACphPlayerCharacter::OnCameraCollisionEndOverlap(
    UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) 
{
    CheckCameraOverlap();
}

// Can't be const because of using like delegate subscriber 
void ACphPlayerCharacter::CheckCameraOverlap() 
{
    const bool HideMesh = CameraCollisionComponent->IsOverlappingComponent(
        GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);

    TArray<USceneComponent*> MeshChildren;
    GetMesh()->GetChildrenComponents(true, MeshChildren);
    
    for (USceneComponent* MeshChild : MeshChildren)
    {
        UPrimitiveComponent* MeshChildGeometry = Cast<UPrimitiveComponent>(
            MeshChild);
        if (MeshChildGeometry)
        {
            MeshChildGeometry->SetOwnerNoSee(HideMesh);
        }
    }
}

//
void ACphPlayerCharacter::OnDeath()
{
    Super::OnDeath();

    // Turn on spectator
    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}
