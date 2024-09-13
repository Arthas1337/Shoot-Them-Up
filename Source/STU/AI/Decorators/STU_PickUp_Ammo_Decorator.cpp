#include "STU_PickUp_Ammo_Decorator.h"
#include "AIController.h"
#include "STU_AI_Character.h"
#include "../Weapon.h"

//------------------------------------------------------------------------------------------------------------
USTU_PickUp_Ammo_Decorator::USTU_PickUp_Ammo_Decorator()
{
	NodeName = "Pick Up Ammo";
}
//------------------------------------------------------------------------------------------------------------
bool USTU_PickUp_Ammo_Decorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return false;

	const auto Character = Cast<ASTU_AI_Character>(Controller->GetPawn());
	if (!Character) return false;

	const auto Weapon = Character->Current_Weapon;
	if (!Weapon) return false;

	return Weapon->Clips <= Clips_Remaining;
}
//------------------------------------------------------------------------------------------------------------
