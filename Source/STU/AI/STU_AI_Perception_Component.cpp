#include "STU_AI_Perception_Component.h"
#include "AIController.h"
#include "../HealthComponent.h"
#include "Perception/AISense_Sight.h"
#include "../STUUtils.h"

AActor* USTU_AI_Perception_Component::GetSTUCloseEnemy() const 
{
	TArray<AActor*> Perceive_Actors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), Perceive_Actors);
	if (Perceive_Actors.Num() == 0) return nullptr;

	const auto Controller = Cast<AAIController>(GetOwner());
	if (!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return nullptr;

	float Best_Distance = MAX_FLT;
	AActor* Best_Pawn = nullptr;

	for(const auto Perceive_Actor : Perceive_Actors)
	{
		const auto HealthComponent = Perceive_Actor->FindComponentByClass<UHealthComponent>();

		const auto Perceive_Pawn = Cast<APawn>(Perceive_Actor);
		const auto Are_Enemies = Perceive_Pawn && STUUtils::AreEnemies(Controller, Perceive_Pawn->Controller);	

		if (HealthComponent && !HealthComponent->Is_Dead() && Are_Enemies)
		{
			const auto Current_Distance = (Perceive_Actor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (Current_Distance < Best_Distance)
			{
				Best_Distance = Current_Distance;
				Best_Pawn = Perceive_Actor;
			}
		}
	}

	return Best_Pawn;
}