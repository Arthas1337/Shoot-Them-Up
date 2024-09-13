#include "STU_AI_Character.h"
#include "STU_AI_Controller.h"
#include "../Weapon.h"
#include "../Weapons/STU_Rifle.h"
#include "../Weapons/STU_Pistol.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BrainComponent.h"

//------------------------------------------------------------------------------------------------------------
ASTU_AI_Character::ASTU_AI_Character()
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	AIControllerClass = ASTU_AI_Controller::StaticClass();

	bUseControllerRotationYaw = false;
	if(GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTU_AI_Character::Pick_Up_Weapon(AWeapon* weapon)
{
	if (!weapon) return;

	for (AWeapon* ExistingWeapon : Weapons_Arr)
	{
		if (ExistingWeapon->GetClass() == weapon->GetClass())
			return;
	}

	ASTU_Rifle* Rifle = Cast<ASTU_Rifle>(weapon);
	ASTU_Pistol* Pistolet = Cast<ASTU_Pistol>(weapon);

	if (IsReloading && (Rifle && Weapons_Arr.ContainsByPredicate([](AWeapon* W) { return Cast<ASTU_Rifle>(W) != nullptr; })) ||
		(Pistolet && Weapons_Arr.ContainsByPredicate([](AWeapon* W) { return Cast<ASTU_Pistol>(W) != nullptr; })))
	{
		return;
	}

	if (Current_Weapon != nullptr)
	{
		Current_Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Current_Weapon->SetActorHiddenInGame(true);
		Current_Weapon->SetActorEnableCollision(false);
	}

	if(weapon == Rifle && Rifle_Equip_Animation != nullptr)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance != nullptr)
			AnimInstance->Montage_Play(Rifle_Equip_Animation, 1.0);
	} 
	else if(weapon == Pistolet && Pistol_Equip_Animation)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance != nullptr)
			AnimInstance->Montage_Play(Pistol_Equip_Animation, 1.0);
	}

	Weapon_Attached = true;
	Attach_Weapon(weapon, FName(TEXT("weapon_hand_r")));
	HasWeapon = true;
	HasPistol = weapon->Has_Pistol;
	HasRifle = weapon->Has_Rifle;
	Current_Weapon = weapon;

	Current_Weapon->SetOwner(this);

	if(PickUp_Weapon_Sound  != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickUp_Weapon_Sound, GetActorLocation());
	}

	Weapons_Arr.Add(weapon);
	OnWeaponAttach.Broadcast(HasRifle, HasPistol);
}
//------------------------------------------------------------------------------------------------------------
void ASTU_AI_Character::OnDeath()
{
	Super::OnDeath();

	const auto STU_Controller = Cast<ASTU_AI_Controller>(Controller);
	const auto Rifle = Cast<ASTU_Rifle>(Current_Weapon);
	if (Rifle)
		Rifle->Stop_Fire();
	if(STU_Controller && STU_Controller->BrainComponent)
	{
		STU_Controller->BrainComponent->Cleanup();
		UE_LOG(LogTemp, Warning, TEXT("AI Dead"));
	}
}
//------------------------------------------------------------------------------------------------------------
