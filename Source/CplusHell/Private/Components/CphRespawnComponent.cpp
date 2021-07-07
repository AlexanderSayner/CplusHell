// C plus Hell Learning Game, All Right Reserved.


#include "Components/CphRespawnComponent.h"

#include "CphGameModeBase.h"

// Sets default values for this component's properties
UCphRespawnComponent::UCphRespawnComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

// Starts timer 
void UCphRespawnComponent::Respawn(const int32 RespawnTime)
{
    RespawnCountdown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this,
                                           &UCphRespawnComponent::RespawnTimerUpdate,
                                           1.0f, true);
}

//
bool UCphRespawnComponent::IsRespawnInProgress() const
{
    return GetWorld() &&
           GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}


// Called when the game starts
void UCphRespawnComponent::BeginPlay()
{
    Super::BeginPlay();

    check(GetWorld())
}

// Decrements timer and then calls respawn request to Game Mode 
void UCphRespawnComponent::RespawnTimerUpdate()
{
    if (--RespawnCountdown == 0)
    {
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

        ACphGameModeBase* GameMode = Cast<ACphGameModeBase>(
            GetWorld()->GetAuthGameMode());
        if (!GameMode) return;

        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}
