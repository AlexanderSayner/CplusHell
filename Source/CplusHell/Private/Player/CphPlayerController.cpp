// C plus Hell Learning Game, All Right Reserved.


#include "Player/CphPlayerController.h"
#include "Components/CphRespawnComponent.h"

ACphPlayerController::ACphPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<UCphRespawnComponent>(
        "RespawnComponent");
}
