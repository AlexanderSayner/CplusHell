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

    // For logical components no need to SetupAttachment
    HealthComponent = CreateDefaultSubobject<UCphHealthComponent>(
        "HealthComponent");

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
    check(GetCharacterMovement())
    check(GetMesh())

    // Init health before delegate declaration
    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);

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

// Tell for blueprint, if character is sprinting
bool ACphBaseCharacter::IsSprinting() const
{
    return false;
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

// Called by Game Mode Base, sets color for player mesh material
void ACphBaseCharacter::SetPlayerColor(const FLinearColor& Color) const
{
    UMaterialInstanceDynamic* MaterialInstance = GetMesh()->
        CreateAndSetMaterialInstanceDynamic(0);
    if (!MaterialInstance) return;

    MaterialInstance->SetVectorParameterValue(MaterialColorName, Color);
}

// Event for playing death animation
void ACphBaseCharacter::OnDeath()
{
    UE_LOG(LogBaseCharacter, Display, TEXT("Oh no, player %s is dead"),
           *GetName())

    // Player can not move after death
    GetCharacterMovement()->DisableMovement();
    // Span after some seconds
    SetLifeSpan(LifeSpanOnDeath);
    // Turn off collision
    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
    // Stop firing
    WeaponComponent->StopFire();

    // Rag doll physics
    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);
}

// Health changed event
void ACphBaseCharacter::OnHealthChanged(const float Health,
                                        const float Delta) const
{
    // Display health number
    // HealthTextComponent->SetText(
        // FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

// Subscription for landing delegate
void ACphBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    // Always negative when fall
    const float FallVelocityZ = -GetVelocity().Z;
    // UE_LOG(LogBaseCharacter, Display, TEXT("On landed: %f"), FallVelocityZ)

    // If fall speed is not too big then no damage
    if (FallVelocityZ < LandedDamageVelocity.X) return;
    // Proportional damage calculation
    const float FinalDamage = FMath::GetMappedRangeValueClamped(
        LandedDamageVelocity, LandedDamage, FallVelocityZ);
    // UE_LOG(LogBaseCharacter, Display, TEXT("Damage dealt: %f"), FinalDamage)
    // Character deal damage itself
    TakeDamage(FinalDamage, FDamageEvent{}, GetController(), this);
}
