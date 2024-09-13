#include "STU_Health_PickUp.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

//------------------------------------------------------------------------------------------------------------
ASTU_Health_PickUp::ASTU_Health_PickUp()
{
   Health_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Health_Mesh");
   Health_Mesh->SetupAttachment(Sphere_Collision);

   Pedestal = CreateDefaultSubobject<UStaticMeshComponent>("Pedestal");
   Pedestal->SetupAttachment(Sphere_Collision);

   N_Timer_Health = CreateDefaultSubobject<UNiagaraComponent>("N_Timer_Health");
   N_Timer_Health->SetupAttachment(Sphere_Collision);

   NS_HealthPud_Default = CreateDefaultSubobject<UNiagaraComponent>("NS_HealthPud_Default");
   NS_HealthPud_Default->SetupAttachment(Sphere_Collision);
}

//------------------------------------------------------------------------------------------------------------
void ASTU_Health_PickUp::BeginPlay()
{
	Super::BeginPlay();
	check(Health_Mesh);
	check(Pedestal);
	check(N_Timer_Health);
	check(NS_HealthPud_Default);
	
}
//------------------------------------------------------------------------------------------------------------

