// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "CphAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature,
                                    USkeletalMeshComponent*)

/**
 * 
 */
UCLASS()
class CPLUSHELL_API UCphAnimNotify : public UAnimNotify
{
    GENERATED_BODY()


public:
    // Notifies about the end of equip animation
    virtual void Notify(USkeletalMeshComponent* MeshComp,
                        UAnimSequenceBase* Animation) override;

    // Delegate
    FOnNotifiedSignature OnNotified;
};
