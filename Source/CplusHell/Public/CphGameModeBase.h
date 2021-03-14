// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"

#include "AIController.h"
#include "CphCoreTypes.h"
#include "GameFramework/GameModeBase.h"
#include "CphGameModeBase.generated.h"

/**
 * CPH is abbreviation of C plus Hell
 */
UCLASS()
class CPLUSHELL_API ACphGameModeBase final : public AGameModeBase
{
    GENERATED_BODY()

public:
    ACphGameModeBase();

    virtual void StartPlay() override;

    virtual UClass* GetDefaultPawnClassForController_Implementation(
        AController* InController) override;

    void Killed(AController* SlayerController, AController* VictimController) const;

protected:
    UPROPERTY(EditDefaultsOnly, Category="Game")
    TSubclassOf<AAIController> AIControllerClass;

    UPROPERTY(EditDefaultsOnly, Category="Game")
    TSubclassOf<APawn> AIPawnClass;

    UPROPERTY(EditDefaultsOnly, Category="Game")
    FGameData GameData;

private:
    int32 CurrentRoundNum = 1;
    int32 RoundCountDown = 0;
    FTimerHandle GameRoundTimerHandle;

    void SpawnBots();
    void StartRound();
    void GameTimerUpdate();

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamID(const int32 TeamID);
    void SetPlayerColor(AController* PlayerController) const;

    void LogPlayerInfo() const;
};
