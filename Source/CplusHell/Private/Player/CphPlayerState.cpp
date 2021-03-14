// C plus Hell Learning Game, All Right Reserved.


#include "Player/CphPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogCphPlayerState, All, All)

void ACphPlayerState::LogInfo()
{
    UE_LOG(LogCphPlayerState, Display,
           TEXT("TeamID: %i, Kills: %i, Deaths: %i"),
           TeamID, KillsNum, DeathsNum);
}
