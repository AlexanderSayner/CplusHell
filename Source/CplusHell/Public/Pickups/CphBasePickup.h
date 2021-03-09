// C plus Hell Learning Game, All Right Reserved.

#pragma once

#include "CoreMinimal.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "CphBasePickup.generated.h"

UCLASS()
class CPLUSHELL_API ACphBasePickup : public AActor
{
    GENERATED_BODY()

public:
    // Sets default values for this actor's properties
    ACphBasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category="Pickup")
    USphereComponent* CollisionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Spawn")
    float RespawnTime = 5.0f;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    // Add some buff (debuff) for any player
    virtual bool AddSomeBuffsTo(APawn* Pawn);

public:
    // Called then player overlaps
    virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
    // Called every frame
    virtual void Tick(float DeltaTime) override;

private:
    // Make bonus invisible
    void PickupWasTaken();
    // Make visible
    void Respawn() const;
};
