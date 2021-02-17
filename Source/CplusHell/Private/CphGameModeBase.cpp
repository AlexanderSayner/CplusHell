// C plus Hell Learning Game, All Right Reserved.


#include "CphGameModeBase.h"

#include "Player/CphBaseCharacter.h"
#include "Player/CphPlayerController.h"

ACphGameModeBase::ACphGameModeBase()
{
    // Set defaults
    DefaultPawnClass = ACphBaseCharacter::StaticClass();
    PlayerControllerClass = ACphPlayerController::StaticClass();
}
