// C plus Hell Learning Game, All Right Reserved.


#include "Components/CphWeaponComponent.h"

#include "Animations/AnimUtils.h"
#include "Animations/CphEquipFinishedAnimNotify.h"
#include "Animations/CphReloadFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapon/CphBaseWeapon.h"

DEFINE_LOG_CATEGORY_STATIC(LogCphWeaponComponent, All, All)

// The only count of character's weapons, supported by my game
constexpr static int32 WeaponNum = 2;

// Sets default values for this component's properties
UCphWeaponComponent::UCphWeaponComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

// Destroy player weapons
void UCphWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (ACphBaseWeapon* Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
}

// Fire on player action. Can not be const, because of using in BindAction
void UCphWeaponComponent::StartFire()
{
    if (CanFire())
    {
        CurrentWeapon->StartFire();
    }
}

// On mouse button release. Can not be const, because of using in BindAction
void UCphWeaponComponent::StopFire()
{
    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
    }
}

// Circle choosing weapon
void UCphWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;
    // The remainder of the division by the length of the array
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

// Reload action mapping
void UCphWeaponComponent::Reload()
{
    ChangeClip();
}

// Returns true if weapon valid and ui set successfully
bool UCphWeaponComponent::GetWeaponDataUI(FWeaponDataUI& UIData) const
{
    if (CurrentWeapon)
    {
        UIData = CurrentWeapon->GetUIData();
        return true;
    }
    return false;
}

// Returns true if weapon valid and ui set successfully
bool UCphWeaponComponent::GetWeaponAmmoUI(FAmmoData& AmmoData) const
{
    if (CurrentWeapon)
    {
        AmmoData = CurrentWeapon->GetCurrentAmmoData();
        return true;
    }
    return false;
}

// Add some ammo bonus
bool UCphWeaponComponent::TryToAddAmmo(
    const TSubclassOf<ACphBaseWeapon> WeaponType,
    const int32 BulletsAmount)
{
    for (ACphBaseWeapon* Weapon : Weapons)
    {
        if (Weapon && Weapon->IsA(WeaponType))
        {
            return Weapon->TryToAddAmmo(BulletsAmount);
        }
    }
    return false;
}


// Called when the game starts
void UCphWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    checkf(WeaponData.Num() == WeaponNum,
           TEXT("My character can hold only %i weapons"), WeaponNum)

    SpawnWeapons();
    check(CurrentWeaponIndex==0)
    EquipWeapon(CurrentWeaponIndex);
    InitAnimations();
}

// Logger
void UCphWeaponComponent::LogWarning(const FString Reason)
{
    UE_LOG(LogCphWeaponComponent, Warning, TEXT("%s"), *Reason)
}

//
void UCphWeaponComponent::AttachWeaponToSocket(ACphBaseWeapon* Weapon,
                                               ACharacter* Character,
                                               const FName& Name)
{
    if (!Weapon || !Character) return;

    // Connect spawned weapon to mesh
    const FAttachmentTransformRules Rules(
        EAttachmentRule::SnapToTarget,
        false);
    // GetMesh() returns character's skeleton mesh component
    Weapon->AttachToComponent(Character->GetMesh(), Rules,
                              Name);
    // Set owner for access his camera for shooting direction
    Weapon->SetOwner(Character);
}

// Set Current weapon, attach to character's hand
void UCphWeaponComponent::EquipWeapon(const int32 WeaponIndex)
{
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
        LogWarning(FString::Printf(TEXT("Invalid weapon index")));
        return;
    }

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    // Take off weapon first if has one
    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character, WeaponArmorySocketName);
    }

    // Take weapon in hands
    CurrentWeapon = Weapons[WeaponIndex];
    // CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
    const FWeaponData* CurrentWeaponData = WeaponData.FindByPredicate(
        [&](const FWeaponData& Data)
        {
            return Data.WeaponClass == CurrentWeapon->GetClass();
        });
    CurrentReloadAnimMontage = CurrentWeaponData
                                   ? CurrentWeaponData->ReloadAnimMontage
                                   : nullptr;

    AttachWeaponToSocket(CurrentWeapon, Character, WeaponEquipSocketName);
    EquipAnimInProgress = true;
    // Play animation
    PlayAnimMontage(EquipAnimMontage);
}

//
void UCphWeaponComponent::SpawnWeapons()
{
    // Actor spawn on world
    if (!GetWorld()) return;

    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    for (FWeaponData OneWeaponData : WeaponData)
    {
        ACphBaseWeapon* Weapon =
            GetWorld()->SpawnActor<ACphBaseWeapon>(OneWeaponData.WeaponClass);

        if (Weapon)
        {
            Weapon->OnClipEmpty.AddUObject(
                this, &UCphWeaponComponent::OnEmptyClip);
            Weapon->SetOwner(Character);
            Weapons.Add(Weapon);

            AttachWeaponToSocket(Weapon, Character,
                                 WeaponArmorySocketName);
        }
        else
        {
            LogWarning(FString::Printf(TEXT("Could not spawn weapon")));
        }
    }
}

//
void UCphWeaponComponent::PlayAnimMontage(UAnimMontage* Animation) const
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character) return;

    Character->PlayAnimMontage(Animation);
}

// Subscribe for Anim Notify
void UCphWeaponComponent::InitAnimations()
{
    UCphEquipFinishedAnimNotify* EquipFinishedAnimNotify =
        FAnimUtils::FindFirstNotifyByClass<UCphEquipFinishedAnimNotify>(
            EquipAnimMontage);
    if (EquipFinishedAnimNotify)
    {
        EquipFinishedAnimNotify->OnNotified.AddUObject(
            this, &UCphWeaponComponent::OnEquipFinished);
    }
    else
    {
        UE_LOG(LogCphWeaponComponent, Error,
               TEXT(
                   "Equip and anim notify in amin montage is forgotten to set"))
        checkNoEntry()
    }

    for (FWeaponData Data : WeaponData)
    {
        UCphReloadFinishedAnimNotify* ReloadFinishedAnimNotify =
            FAnimUtils::FindFirstNotifyByClass<UCphReloadFinishedAnimNotify>(
                Data.ReloadAnimMontage);
        if (ReloadFinishedAnimNotify)
        {
            ReloadFinishedAnimNotify->OnNotified.AddUObject(
                this, &UCphWeaponComponent::OnReloadFinished);
        }
        else
        {
            UE_LOG(LogCphWeaponComponent, Error,
                   TEXT(
                       "ReloadFinishedAnimNotify must be set in weapon Anim Montage"
                   ))
            checkNoEntry()
        }
    }
}

// Could not be static because of using in delegate callback
void UCphWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent) return;

    EquipAnimInProgress = false;
}

// Changing clip here, only when reload animation is finished
void UCphWeaponComponent::OnReloadFinished(
    USkeletalMeshComponent* MeshComponent)
{
    ACharacter* Character = Cast<ACharacter>(GetOwner());
    if (!Character || MeshComponent != Character->GetMesh()) return;

    // OnReloadFinished function calls two times for some reason.
    // That is why ReloadAnimInProgress check is needed
    if (CurrentWeapon && ReloadAnimInProgress)
    {
        CurrentWeapon->ChangeClip();
    }

    ReloadAnimInProgress = false;
}

//
bool UCphWeaponComponent::CanFire() const
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

//
bool UCphWeaponComponent::CanEquip() const
{
    return !EquipAnimInProgress && !ReloadAnimInProgress;
}

//
bool UCphWeaponComponent::CanReload() const
{
    return CurrentWeapon
           && !EquipAnimInProgress
           && !ReloadAnimInProgress
           && CurrentWeapon->CanReload();
}

// Call by delegate FOnClipEmptySignature in Base Weapon
void UCphWeaponComponent::OnEmptyClip()
{
    ChangeClip();
}

// Utility logic
void UCphWeaponComponent::ChangeClip()
{
    if (!CanReload()) return;
    StopFire();
    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}
