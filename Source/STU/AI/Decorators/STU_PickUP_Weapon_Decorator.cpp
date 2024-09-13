#include "STU_PickUP_Weapon_Decorator.h"
#include "AIController.h"
#include "STU_AI_Character.h"
#include "../Weapon.h"

//------------------------------------------------------------------------------------------------------------
USTU_PickUP_Weapon_Decorator::USTU_PickUP_Weapon_Decorator()
{
	NodeName = "Pick Up Weapon";
}
//------------------------------------------------------------------------------------------------------------
bool USTU_PickUP_Weapon_Decorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto Character = Cast<ASTU_AI_Character>(Controller->GetPawn());
	if (!Character) return false;

	const auto Weapon = Character->Current_Weapon;

	return Weapon == nullptr;
}
//------------------------------------------------------------------------------------------------------------
