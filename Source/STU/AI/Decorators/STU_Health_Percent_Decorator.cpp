#include "STU_Health_Percent_Decorator.h"
#include "AIController.h"
#include "../HealthComponent.h"

//------------------------------------------------------------------------------------------------------------
USTU_Health_Percent_Decorator::USTU_Health_Percent_Decorator()
{
	NodeName = "HealthPercent";
}
//------------------------------------------------------------------------------------------------------------
bool USTU_Health_Percent_Decorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller)
		return false;

	const auto Health_Component = Controller->GetPawn()->FindComponentByClass<UHealthComponent>();
	if (!Health_Component || Health_Component->Is_Dead())
		return false;

	return Health_Component->Get_Health_Percent() <= Health_Percent;
}
//------------------------------------------------------------------------------------------------------------
