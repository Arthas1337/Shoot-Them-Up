#include "STU_Fire_Service.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../AI/STU_AI_Character.h"
#include "../STUUtils.h"
#include "../HealthComponent.h"
#include "../Weapon.h"

//------------------------------------------------------------------------------------------------------------
USTU_Fire_Service::USTU_Fire_Service()
{
	NodeName = "Fire";
}
//------------------------------------------------------------------------------------------------------------
void USTU_Fire_Service::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	ASTU_AI_Character* Character = nullptr;
	if(Controller)
		Character = Cast<ASTU_AI_Character>(Controller->GetPawn());

	UHealthComponent* HealthComponent = STUUtils::GetSTUPlayerComponent<UHealthComponent>(Character);
	if (!HealthComponent) return;

	const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

	if (Character->Current_Weapon == nullptr) return;

	if (Character->Current_Weapon->Get_Bullets() > 0 && !HealthComponent->Is_Dead() && Character->HasWeapon)
	{
		HasAim ? Character->Current_Weapon->Start_Fire() : Character->Current_Weapon->Stop_Fire();
		if(Character->Current_Weapon->Get_Bullets() <= 0 && Character->Current_Weapon->Clips > 0)
		{
			Character->Current_Weapon->Reload();
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
//------------------------------------------------------------------------------------------------------------
