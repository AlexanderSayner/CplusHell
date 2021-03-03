#pragma once

class FAnimUtils
{
public:
    // Finding first meet notify in anim montage
    template <typename T>
    static T* FindFirstNotifyByClass(UAnimSequenceBase* Animation);
};

/**
* Cycle for all notifiers in amin montage
*/
template <typename T>
T* FAnimUtils::FindFirstNotifyByClass(UAnimSequenceBase* Animation)
{
    if (!Animation) return nullptr;

    const TArray<struct FAnimNotifyEvent> Notifies = Animation->
        Notifies;

    for (const FAnimNotifyEvent NotifyEvent : Notifies)
    {
        T* AnimNotify = Cast<T>(NotifyEvent.Notify);
        if (AnimNotify)
        {
            return AnimNotify;
        }
    }
    return nullptr;
}
