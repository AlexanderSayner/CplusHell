// C plus Hell Learning Game, All Right Reserved.


#include "Player/CphPlayerController.h"
#include "Components/CphRespawnComponent.h"

ACphPlayerController::ACphPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<UCphRespawnComponent>(
        "RespawnComponent");
}

void ACphPlayerController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    OnNewPawn.Broadcast(InPawn);
}
