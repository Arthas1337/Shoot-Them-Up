#include "STU_Rifle.h"
#include "../STUCharacter.h"
#include "Components/STU_Weapon_FX_Component.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

void ASTU_Rifle::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult & SweepResult)
{
	ASTUCharacter* character = Cast<ASTUCharacter>(OtherActor);

	if(character != nullptr)
	{
		Sphere_Collision->Deactivate();
		Has_Pistol = false;
		Has_Rifle = true;
		Is_Rifle_Attached = true;
		character->Pick_Up_Weapon(this);
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTU_Rifle::Start_Fire()
{
	MakeShot();
	GetWorldTimerManager().SetTimer(RifleShotTimerHadle, this, &AWeapon::MakeShot, TimeBetweenShot, true);
}
//------------------------------------------------------------------------------------------------------------
void ASTU_Rifle::Stop_Fire()
{
	GetWorldTimerManager().ClearTimer(RifleShotTimerHadle);
}
//------------------------------------------------------------------------------------------------------------
void ASTU_Rifle::Reload()
{
	if (Clips > 0 && Get_Bullets() != Max_Bullets)
	{
		Clips -= 1;
		Set_Bullets(Max_Bullets);

		if(Rifle_Reload_Animation!= nullptr)
		{
			UAnimInstance* AnimInstance = Weapon_Mesh->GetAnimInstance();

			if (AnimInstance != nullptr)
				AnimInstance->Montage_Play(Rifle_Reload_Animation, 1.0);
		}
	}
}
//------------------------------------------------------------------------------------------------------------