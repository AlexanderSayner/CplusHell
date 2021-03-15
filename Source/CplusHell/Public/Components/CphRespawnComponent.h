// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CphRespawnComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class CPLUSHELL_API UCphRespawnComponent final : public UActorComponent
{
    GENERATED_BODY()

public:
    // Sets default values for this component's properties
    UCphRespawnComponent();

    //
    void Respawn(const int32 RespawnTime);
    //
    bool IsRespawnInProgress() const;

    /**
     * Getter
     */
    int32 GetRespawnCountdown() const
    {
        return RespawnCountdown;
    }

protected:
    // Called when the game starts
    virtual void BeginPlay() override;

private:
    FTimerHandle RespawnTimerHandle;
    int32 RespawnCountdown = 0;

    //
    void RespawnTimerUpdate();
};
