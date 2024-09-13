#include "STU_FindEnemy_BTService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../STU_AI_Perception_Component.h"

USTU_FindEnemy_BTService::USTU_FindEnemy_BTService()
{
	NodeName = "Find Enemy";
}

void USTU_FindEnemy_BTService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if(Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		const auto Perception_Component = Controller->FindComponentByClass<USTU_AI_Perception_Component>();
		if(Perception_Component)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, Perception_Component->GetSTUCloseEnemy());

		}
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
