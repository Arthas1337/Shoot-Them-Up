#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "STU_AI_Perception_Component.generated.h"

UCLASS()
class STU_API USTU_AI_Perception_Component : public UAIPerceptionComponent
{
	GENERATED_BODY()
	
public:

	AActor* GetSTUCloseEnemy() const;

};
