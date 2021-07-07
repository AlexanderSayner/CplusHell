#pragma once

#include "Player/CphPlayerState.h"

class FCphUtils
{
public:
    bool static AreEnemies(AController* PlayerOne,
                           AController* PlayerTwo)
    {
        if (!PlayerOne || !PlayerTwo || PlayerOne == PlayerTwo)
            return false;

        ACphPlayerState* PlayerStateOne = Cast<ACphPlayerState>(
            PlayerOne->PlayerState);
        ACphPlayerState* PlayerStateTwo = Cast<ACphPlayerState>(
            PlayerTwo->PlayerState);

        return PlayerStateOne && PlayerStateTwo
               && PlayerStateOne->GetTeamID() != PlayerStateTwo->GetTeamID();
    }
};
