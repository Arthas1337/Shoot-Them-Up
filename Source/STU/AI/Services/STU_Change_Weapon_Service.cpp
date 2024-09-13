#include "STU_Change_Weapon_Service.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../Weapon.h"
#include "../AI/STU_AI_Character.h"

//------------------------------------------------------------------------------------------------------------
USTU_Change_Weapon_Service::USTU_Change_Weapon_Service()
{
	NodeName = "Change Weapon";
}
//------------------------------------------------------------------------------------------------------------
void USTU_Change_Weapon_Service::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	if (!Controller) return;

	ASTU_AI_Character* Character = Cast<ASTU_AI_Character>(Controller->GetPawn());
	if (!Character) return;
	
	if (FMath::FRand() >= Probability && Character->Weapons_Arr.Num() > 1) 
	{
		Character->OnWeapon_Change();
	}

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
//------------------------------------------------------------------------------------------------------------
