#pragma once

#include "CoreMinimal.h"
#include "../Weapon.h"
#include "STU_Pistol.generated.h"

UCLASS()
class STU_API ASTU_Pistol : public AWeapon
{
	GENERATED_BODY()
public:
	ASTU_Pistol();

	virtual void Start_Fire() override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Sound")
	USoundBase* Pistol_Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Anim")
	UAnimMontage* Pistol_Equip;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Anim")
	UAnimMontage* Pistol_Fire_Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= "Anim")
	UAnimMontage* Pistol_Reload_Animation;

	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult & SweepResult) override;

	virtual void Reload() override;

};
