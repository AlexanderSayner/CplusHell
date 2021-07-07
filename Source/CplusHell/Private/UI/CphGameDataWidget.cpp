// C plus Hell Learning Game, All Right Reserved.


#include "UI/CphGameDataWidget.h"

int32 UCphGameDataWidget::GetKillsNum() const
{
    ACphPlayerState* PlayerState = GetCphPlayerState();
    return PlayerState ? PlayerState->GetKillsNum() : -1;
}

int32 UCphGameDataWidget::GetCurrentRoundNum() const
{
    ACphGameModeBase* GameMode = GetCphGameMode();
    return GameMode ? GameMode->GetCurrentRoundNum() : -1;
}

int32 UCphGameDataWidget::GetTotalRoundsNum() const
{
    ACphGameModeBase* GameMode = GetCphGameMode();
    return GameMode ? GameMode->GetGameData().RoundsNum : -1;
}

int32 UCphGameDataWidget::GetRoundsSecondsRemaining() const
{
    ACphGameModeBase* GameMode = GetCphGameMode();
    return GameMode ? GameMode->GetRoundCountDown() : -1;
}

ACphGameModeBase* UCphGameDataWidget::GetCphGameMode() const
{
    return GetWorld()
               ? Cast<ACphGameModeBase>(GetWorld()->GetAuthGameMode())
               : nullptr;
}

ACphPlayerState* UCphGameDataWidget::GetCphPlayerState() const
{
    return GetOwningPlayer()
               ? Cast<ACphPlayerState>(GetOwningPlayer()->PlayerState)
               : nullptr;
}
