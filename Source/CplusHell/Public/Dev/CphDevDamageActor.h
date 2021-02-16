// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CphDevDamageActor.generated.h"

UCLASS()
class CPLUSHELL_API ACphDevDamageActor final : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACphDevDamageActor();

    // Needs for ability to move component on scene
    UPROPERTY(VisibleAnywhere,BlueprintReadWrite)
    USceneComponent* SceneComponent;
    // Damage debug sphere radius
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    float Radius = 100.0f;
    // Color of damage sphere
    UPROPERTY(EditAnywhere, BlueprintReadWrite)
    FColor SphereColor = FColor::Purple;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
};
