// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Player/CphBaseCharacter.h"
#include "CphCharacterAI.generated.h"

class UBehaviorTree;

/**
 * Simple AI character
 */
UCLASS()
class CPLUSHELL_API ACphCharacterAI final : public ACphBaseCharacter
{
    GENERATED_BODY()

public:
    explicit ACphCharacterAI(const FObjectInitializer& ObjectInitializer);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="AI")
    UBehaviorTree* BehaviorTreeAsset;
};
