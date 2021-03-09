﻿#pragma once

#include "CphCoreTypes.generated.h"

class ACphBaseWeapon;

/* Health Component delegates */
// Telling player about his death
DECLARE_MULTICAST_DELEGATE(FOnDeathSignature)
// Call on heath change then player can print health on event but every tick
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChangedSignature, float)

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
