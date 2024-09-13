#include "STU_Enemy_EnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTypes.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

//------------------------------------------------------------------------------------------------------------
void USTU_Enemy_EnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, 
	FEnvQueryContextData& ContextData) const
{
	AActor* QueryOwner = Cast<AActor>(QueryInstance.Owner.Get());

	const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(QueryOwner);
	if (!Blackboard) return;
	const auto Context_Actor = Blackboard->GetValueAsObject(Enemy_Actor_Key_Name);
	UEnvQueryItemType_Actor::SetContextHelper(ContextData, Cast<AActor>(Context_Actor));
}
//------------------------------------------------------------------------------------------------------------
