// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"

#include "CphGameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "Player/CphPlayerState.h"
#include "CphGameDataWidget.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSHELL_API UCphGameDataWidget final : public UUserWidget
{
    GENERATED_BODY()

public:

    // returns player kills, returns -1 if failed
    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetKillsNum() const;
    // returns current round number, returns -1 if failed
    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetCurrentRoundNum() const;
    // returns round number, returns -1 if failed
    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetTotalRoundsNum() const;
    // returns round countdown, returns -1 if failed
    UFUNCTION(BlueprintCallable, Category="UI")
    int32 GetRoundsSecondsRemaining() const;

private:
    ACphGameModeBase* GetCphGameMode() const;
    ACphPlayerState* GetCphPlayerState() const;
};
