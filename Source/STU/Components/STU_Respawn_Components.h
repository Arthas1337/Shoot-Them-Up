#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_Respawn_Components.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STU_API USTU_Respawn_Components : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USTU_Respawn_Components();

	void Respawn(int32 respawn_time);

private:

	FTimerHandle Respawn_Timer_Handle;
	int32 Respawn_Count_Down;

	void Respawn_Timer_Update();
};
