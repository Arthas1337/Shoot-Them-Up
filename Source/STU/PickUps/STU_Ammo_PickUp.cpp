#include "STU_Ammo_PickUp.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

//------------------------------------------------------------------------------------------------------------
ASTU_Ammo_PickUp::ASTU_Ammo_PickUp()
{
   Armory_Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Armory_Mesh");
   Armory_Mesh->SetupAttachment(Sphere_Collision);

   Pedestal = CreateDefaultSubobject<UStaticMeshComponent>("Pedestal");
   Pedestal->SetupAttachment(Sphere_Collision);

   NS_Loading = CreateDefaultSubobject<UNiagaraComponent>("NS_Loading");
   NS_Loading->SetupAttachment(Sphere_Collision);
}
//------------------------------------------------------------------------------------------------------------
void ASTU_Ammo_PickUp::BeginPlay()
{
	Super::BeginPlay();
   check(Armory_Mesh);
   check(Pedestal);
   check(NS_Loading);
}
//------------------------------------------------------------------------------------------------------------
