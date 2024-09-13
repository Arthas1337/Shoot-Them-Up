#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STU_PickUP_Weapon_Decorator.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API USTU_PickUP_Weapon_Decorator : public UBTDecorator
{
	GENERATED_BODY()

public:

	USTU_PickUP_Weapon_Decorator();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
//------------------------------------------------------------------------------------------------------------
