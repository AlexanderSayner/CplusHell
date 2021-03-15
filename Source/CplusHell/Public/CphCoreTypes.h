#pragma once

#include "CphCoreTypes.generated.h"

class UNiagaraSystem;
class ACphBaseWeapon;

/* Health Component delegates */
// Telling player about his death
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature)
// Call on heath change then player can print health UI on event but every tick
DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedSignature, float, float)

/**
 * Using in Weapon Component
 * Bullets ended delegate
 */
DECLARE_MULTICAST_DELEGATE(FOnClipEmptySignature)

/**
 * Using two structures for each weapon - default and current.
 * Default is weapon settings like clip capacity and bullets count in total,
 * but current is how many bullets remaining for player 
 */
USTRUCT(BlueprintType)
struct FAmmoData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullets")
    int32 BulletsInClip; // Bullets remaining

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Bullets",
        meta = (EditCondition = "!Infinite"))
    int32 BulletsInTotal; // Ammo stock in players inventory

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool Infinite; // true - bullets are infinite, otherwise - false
};

/**
 * Weapon reload animation settings
 */
USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<ACphBaseWeapon> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    UAnimMontage* ReloadAnimMontage;
};

/**
 * Stores interface images for the current weapon, which can be changed if desired.
 * Depending on which weapon is selected, this image will be displayed in the interface.
 */
USTRUCT(BlueprintType)
struct FWeaponDataUI
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* WeaponIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* CrossHairIcon;
};

/**
 * Decal settings
 */
USTRUCT(BlueprintType)
struct FDecalData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    UMaterialInterface* MaterialInterface;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    FVector Size = FVector(10.0f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    float LifeTime = 5.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="VFX")
    float FadeOutTime = 0.7f;
};

/**
 * Niagara and decal union
 */
USTRUCT(BlueprintType)
struct FImpactData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    // ReSharper disable once UnrealHeaderToolParserError
    UNiagaraSystem* NiagaraSystem;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FDecalData DecalData;
};

/**
 * Global game settings, time variables in seconds
 */
USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game",
        meta=(ClampMin="1", ClamMax="100"))
    int32 PlayerNum = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game",
        meta=(ClampMin="1", ClampMax="10"))
    int32 RoundsNum = 3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game",
        meta=(ClampMin="1", ClampMax="300"))
    int32 RoundDuration = 10;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FLinearColor DefaultTeamColor = FLinearColor::Red;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    TArray<FLinearColor> TeamColors;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Game",
        meta=(ClampMin="1", ClampMax="20"))
    int32 RespawnTime = 5;
};
