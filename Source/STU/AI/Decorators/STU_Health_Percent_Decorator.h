#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "STU_Health_Percent_Decorator.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API USTU_Health_Percent_Decorator : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	USTU_Health_Percent_Decorator();

protected:

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float Health_Percent = 0.6f;
};
//------------------------------------------------------------------------------------------------------------
