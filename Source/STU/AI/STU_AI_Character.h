#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../STUCharacter.h"
#include "STU_AI_Character.generated.h"

class UBehaviorTree;
class AWeapon;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API ASTU_AI_Character : public ASTUCharacter
{
	GENERATED_BODY()

public:

	ASTU_AI_Character();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
protected:

	virtual void Pick_Up_Weapon(AWeapon* weapon) override;
	virtual void OnDeath() override;
};
//------------------------------------------------------------------------------------------------------------
