#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STU_Base_PIckUp.h"
#include "STU_Health_PickUp.generated.h"

class UStaticMeshComponent;
class UNiagaraComponent;
class USphereComponent;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API ASTU_Health_PickUp : public ASTU_Base_PIckUp
{
	GENERATED_BODY()
	
public:	

	ASTU_Health_PickUp();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Health_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Pedestal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	UNiagaraComponent* N_Timer_Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	UNiagaraComponent* NS_HealthPud_Default;

	virtual void BeginPlay() override;

};
//------------------------------------------------------------------------------------------------------------
