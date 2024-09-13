#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "STU_FindEnemy_BTService.generated.h"

/**
 * 
 */
UCLASS()
class STU_API USTU_FindEnemy_BTService : public UBTService
{
	GENERATED_BODY()

public:

	USTU_FindEnemy_BTService();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
