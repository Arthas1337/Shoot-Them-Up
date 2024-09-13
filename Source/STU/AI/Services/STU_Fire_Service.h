#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STU_Fire_Service.generated.h"

UCLASS()
class STU_API USTU_Fire_Service : public UBTService
{
	GENERATED_BODY()
	
public:

	USTU_Fire_Service();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
