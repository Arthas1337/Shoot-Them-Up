#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STU_Base_PIckUp.h"
#include "STU_Ammo_PickUp.generated.h"

class UStaticMeshComponent;
class UNiagaraComponent;
class USphereComponent;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API ASTU_Ammo_PickUp : public ASTU_Base_PIckUp
{
	GENERATED_BODY()
	
public:	

	ASTU_Ammo_PickUp();

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Armory_Mesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh")
	UStaticMeshComponent* Pedestal;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Niagara")
	UNiagaraComponent* NS_Loading;

	virtual void BeginPlay() override;


};
//------------------------------------------------------------------------------------------------------------
