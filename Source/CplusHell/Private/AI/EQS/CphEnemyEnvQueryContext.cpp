// C plus Hell Learning Game, All Right Reserved.


#include "AI/EQS/CphEnemyEnvQueryContext.h"


#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"

void UCphEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance,
                                              FEnvQueryContextData& ContextData)
const
{
    AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

    UBlackboardComponent* Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(
        QueryOwner);
    if (!Blackboard) return;

    UObject* ContextActor = Blackboard->GetValueAsObject(EnemyActorKeyName);
    
    UEnvQueryItemType_Actor::SetContextHelper(ContextData,
                                              Cast<AActor>(ContextActor));
}
