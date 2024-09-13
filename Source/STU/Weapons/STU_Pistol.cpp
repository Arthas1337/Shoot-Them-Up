#include "STU_Pistol.h"
#include "../STUCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/Character.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"

//------------------------------------------------------------------------------------------------------------
ASTU_Pistol::ASTU_Pistol()
{
	UE_LOG(LogWeapon, Warning, TEXT("Pistol Constructor"));
}
//------------------------------------------------------------------------------------------------------------
void ASTU_Pistol::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult & SweepResult)
{
	ASTUCharacter* character = Cast<ASTUCharacter>(OtherActor);

	if(character)
	{
		Sphere_Collision->Deactivate();
		Has_Rifle = false;
		Has_Pistol = true;
		character->Pick_Up_Weapon(this);
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTU_Pistol::Start_Fire()
{
	if(Pistol_Sound != nullptr)
		UGameplayStatics::PlaySoundAtLocation(this, Pistol_Sound, GetActorLocation());

	if(Pistol_Fire_Animation!= nullptr)
	{
		UAnimInstance* AnimInstance = Weapon_Mesh->GetAnimInstance();

		if (AnimInstance != nullptr)
			AnimInstance->Montage_Play(Pistol_Fire_Animation, 1.0);
	}
	MakeShot();
}
//------------------------------------------------------------------------------------------------------------
void ASTU_Pistol::Reload()
{
	if (Clips > 0 && Get_Bullets() != Max_Bullets)
	{
		Clips -= 1;
		Set_Bullets(Max_Bullets);

		if(Pistol_Reload_Animation!= nullptr)
		{
			UAnimInstance* AnimInstance = Weapon_Mesh->GetAnimInstance();

			if (AnimInstance != nullptr)
				AnimInstance->Montage_Play(Pistol_Reload_Animation, 1.0);
		}
	}
}
//------------------------------------------------------------------------------------------------------------
