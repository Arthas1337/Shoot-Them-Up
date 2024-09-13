#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "STU_Weapon_FX_Component.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

//------------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STU_API USTU_Weapon_FX_Component : public UActorComponent
{
	GENERATED_BODY()

public:	
	USTU_Weapon_FX_Component();

	void PlayImpactFX(const FHitResult& HitResult);
	void PlayMuzzleFireFX(const FTransform& Muzzle_Transorm);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VFX)
	UNiagaraSystem* Default_Effect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VFX)
	UNiagaraSystem* Muzzle_Fire_Effect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = VFX)
	TMap<UPhysicalMaterial*, UNiagaraSystem*> Effects_Map;
		
};
//------------------------------------------------------------------------------------------------------------
