// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/CphBasePickup.h"
#include "CphHealthPickup.generated.h"

class UCphHealthComponent;

/**
 * Health buff
 */
UCLASS()
class CPLUSHELL_API ACphHealthPickup final : public ACphBasePickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Health",
            meta=(ClampMin="1.0", ClampMax="10000.0"))
    int32 HealthAmount = 10;
    
    virtual bool AddSomeBuffsTo(APawn* Pawn) override;

private:
    UCphHealthComponent* GetCphPlayerHealthComponent(AActor* SomeActor) const;
};
