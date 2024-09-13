#pragma once

#include "CoreMinimal.h"
#include "../Weapon.h"
#include "STU_Rifle.generated.h"

class USTU_Weapon_FX_Component;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API ASTU_Rifle : public AWeapon
{
	GENERATED_BODY()

public:

	virtual void Start_Fire() override;
	virtual void Stop_Fire() override;

protected:

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult & SweepResult) override;

	virtual void Reload() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Animation")
	UAnimMontage* Rifle_Attack_Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Animation")
	UAnimMontage* Rifle_Reload_Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Animation")
	UAnimMontage* Rifle_Equip_Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Transform")
	FTransform Rifle_Transform;

	FTimerHandle RifleShotTimerHadle;
	FTimerHandle Respawn_Rifle_Timer_Handle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Is_Rifle_Attached = false;
};
//------------------------------------------------------------------------------------------------------------
