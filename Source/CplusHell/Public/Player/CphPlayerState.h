// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "CphPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class CPLUSHELL_API ACphPlayerState final : public APlayerState
{
    GENERATED_BODY()

public:

    void AddKill() { ++KillsNum; }
    void AddDeath() { ++DeathsNum; }

    void LogInfo();

    /**
     * Getters & Setters
     */

    // Team ID
    int32 GetTeamID() const
    {
        return TeamID;
    }

    void SetTeamID(const int32 TeamIDValue)
    {
        this->TeamID = TeamIDValue;
    }

    // Team Color
    FLinearColor GetTeamColor() const
    {
        return TeamColor;
    }

    void SetTeamColor(const FLinearColor& TeamColorValue)
    {
        this->TeamColor = TeamColorValue;
    }

    // Kills
    int32 GetKillsNum() const
    {
        return KillsNum;
    }

    // Deaths
    int32 GetDeathsNum() const
    {
        return DeathsNum;
    }

private:
    int32 TeamID;
    FLinearColor TeamColor;

    int32 KillsNum = 0;
    int32 DeathsNum = 0;
};
