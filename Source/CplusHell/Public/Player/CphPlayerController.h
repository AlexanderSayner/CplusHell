// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "CphPlayerController.generated.h"

class UCphRespawnComponent;

/**
 * Changed input pitch scale to positive 2.5 to resolve mouse inverse 
 */
UCLASS()
class CPLUSHELL_API ACphPlayerController final : public APlayerController
{
    GENERATED_BODY()

public:
    ACphPlayerController();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Components")
    UCphRespawnComponent* RespawnComponent;

    virtual void OnPossess(APawn* InPawn) override;
};
