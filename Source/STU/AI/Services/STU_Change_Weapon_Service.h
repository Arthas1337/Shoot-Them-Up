#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STU_Change_Weapon_Service.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API USTU_Change_Weapon_Service : public UBTService
{
	GENERATED_BODY()

public:
	USTU_Change_Weapon_Service();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (CampMin = "0.0", ClampMax = "1.0"))
	float Probability = 0.5f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
//------------------------------------------------------------------------------------------------------------
