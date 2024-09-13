#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "STU_AI_Controller.generated.h"

class USTU_AI_Perception_Component;
class USTU_Respawn_Components;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API ASTU_AI_Controller : public AAIController
{
	GENERATED_BODY()
	
	ASTU_AI_Controller();

protected:

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName Focus_On_Key_Name = "EnemyActor";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTU_AI_Perception_Component* STU_Perception_Component;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTU_Respawn_Components* Respawn_Component;

private:

	AActor* Get_Focus_On_Actor() const;
};
//------------------------------------------------------------------------------------------------------------
