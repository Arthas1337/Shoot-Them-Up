#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STU_PickUp_Ammo_Decorator.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API USTU_PickUp_Ammo_Decorator : public UBTDecorator
{
	GENERATED_BODY()

public:

	USTU_PickUp_Ammo_Decorator();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	int Clips_Remaining = 0;

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
	
};
//------------------------------------------------------------------------------------------------------------
