#include "STU_Weapon_FX_Component.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
//------------------------------------------------------------------------------------------------------------
USTU_Weapon_FX_Component::USTU_Weapon_FX_Component()
{
	PrimaryComponentTick.bCanEverTick = false;
}
//------------------------------------------------------------------------------------------------------------
void USTU_Weapon_FX_Component::PlayImpactFX(const FHitResult& HitResult)
{
	auto Effect = Default_Effect;

	if(HitResult.PhysMaterial.IsValid())
	{
		const auto PhysMat = HitResult.PhysMaterial.Get();
		if(Effects_Map.Contains(PhysMat))
		{
			Effect = Effects_Map[PhysMat];
		}
	}

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, HitResult.ImpactPoint, HitResult.ImpactNormal.Rotation());
}
//------------------------------------------------------------------------------------------------------------
void USTU_Weapon_FX_Component::PlayMuzzleFireFX(const FTransform& Muzzle_Transorm)
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Muzzle_Fire_Effect, Muzzle_Transorm.GetLocation(),
		Muzzle_Transorm.GetRotation().Rotator());
}
//------------------------------------------------------------------------------------------------------------