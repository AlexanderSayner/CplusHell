// C plus Hell Learning Game, All Right Reserved.


#include "Animations/CphAnimNotify.h"

// Notifies about the end of equip animation
void UCphAnimNotify::Notify(USkeletalMeshComponent* MeshComp,
                            UAnimSequenceBase* Animation)
{
    OnNotified.Broadcast(MeshComp);

    Super::Notify(MeshComp, Animation);
}
