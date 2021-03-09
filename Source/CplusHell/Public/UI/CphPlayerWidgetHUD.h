// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"

#include "CphCoreTypes.h"
#include "Blueprint/UserWidget.h"
#include "Components/CphHealthComponent.h"
#include "Components/CphWeaponComponent.h"
#include "CphPlayerWidgetHUD.generated.h"

/**
 * In game user interface
 */
UCLASS()
class CPLUSHELL_API UCphPlayerWidgetHUD final : public UUserWidget

{
    GENERATED_BODY()

public:
    // Progress bar value in UI
    UFUNCTION(BlueprintCallable, Category="UI")
    float GetHealthRatio() const;
    // Cross Hair and weapon interface icons for current weapon
    UFUNCTION(BlueprintCallable, Category="UI")
    bool GetCurrentWeaponDataUI(FWeaponDataUI& UIData) const;
    // Returns false if not valid
    UFUNCTION(BlueprintCallable, Category="UI")
    bool GetCurrentBulletsDataUI(FAmmoData& AmmoData) const;
    // 
    UFUNCTION(BlueprintCallable, Category="Spectating")
    bool IsPlayerAlive() const;
    //
    UFUNCTION(BlueprintCallable, Category="Spectating")
    bool IsPlayerSpectating() const;

private:
    // Returns nullptr if fails
    UCphWeaponComponent* GetWeaponComponent() const;
    UCphHealthComponent* GetHealthComponent() const;
};
