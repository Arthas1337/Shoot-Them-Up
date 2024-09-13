#include "STU_AI_Controller.h"
#include "STU_AI_Character.h"
#include "STU_AI_Perception_Component.h"
#include "../Components/STU_Respawn_Components.h"
#include "BehaviorTree/BlackboardComponent.h"

//------------------------------------------------------------------------------------------------------------
ASTU_AI_Controller::ASTU_AI_Controller()
{
	STU_Perception_Component = CreateDefaultSubobject<USTU_AI_Perception_Component>("Perception_Component");
	SetPerceptionComponent(*STU_Perception_Component);

	Respawn_Component = CreateDefaultSubobject<USTU_Respawn_Components>("Respawn_Component");

	bWantsPlayerState = true;
}
//------------------------------------------------------------------------------------------------------------
void ASTU_AI_Controller::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto STUCharacter = Cast<ASTU_AI_Character>(InPawn);
	if (STUCharacter)
	{
		RunBehaviorTree(STUCharacter->BehaviorTreeAsset);
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTU_AI_Controller::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const auto AimActor = Get_Focus_On_Actor();
	SetFocus(AimActor);
}
//------------------------------------------------------------------------------------------------------------
AActor* ASTU_AI_Controller::Get_Focus_On_Actor() const
{
	if (!GetBlackboardComponent()) return nullptr;

	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(Focus_On_Key_Name));
}
//------------------------------------------------------------------------------------------------------------
