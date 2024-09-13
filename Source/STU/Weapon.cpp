#include "Weapon.h"
#include "Kismet/GameplayStatics.h"
#include "Animation/AnimInstance.h"
#include "Anims/STU_Equip_Anim_Notify.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "STUCharacter.h"
#include "AI/STU_AI_Character.h"
#include "Weapons/Components/STU_Weapon_FX_Component.h"
#include "Kismet/KismetMathLibrary.h"

DEFINE_LOG_CATEGORY(LogWeapon);
//------------------------------------------------------------------------------------------------------------
AWeapon::AWeapon()
{
	Weapon_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon_Mesh"));
	SetRootComponent(Weapon_Mesh);

	Sphere_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere_Collsion"));
	Sphere_Collision->SetupAttachment(RootComponent);
	Sphere_Collision->SetSphereRadius(20.0);
	Sphere_Collision->OnComponentBeginOverlap.AddDynamic(this, &AWeapon::BeginOverlap);

	WeaponFXComponent = CreateDefaultSubobject<USTU_Weapon_FX_Component>("WeaponFXComponent");
}
//------------------------------------------------------------------------------------------------------------
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	check(Sphere_Collision)
	check(Weapon_Mesh);
	check(WeaponFXComponent);
	Bullets = Max_Bullets;
}
//------------------------------------------------------------------------------------------------------------
void AWeapon::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
	bool bFromSweep, const FHitResult & SweepResult)
{
	ASTUCharacter* character = Cast<ASTUCharacter>(OtherActor);
	if(character != nullptr)
	{
		Sphere_Collision->Deactivate();
		character->Pick_Up_Weapon(this);
	}
	
}
//------------------------------------------------------------------------------------------------------------
void AWeapon::Reload()
{
	if (Clips > 0 && Bullets != Max_Bullets)
	{
		Clips -= 1;
		Bullets = Max_Bullets;
	}
}
//------------------------------------------------------------------------------------------------------------
void AWeapon::MakeShot()
{
	if (!GetWorld()) return;

	const auto* Player = Cast<ACharacter>(GetOwner());
	if (!Player) return;

	ASTU_AI_Character* STU_AI_Player = Cast<ASTU_AI_Character>(GetOwner());
	ASTUCharacter* STU_Player = Cast<ASTUCharacter>(GetOwner());

	if (STU_AI_Player)
		if (!STU_AI_Player->CanFire()) return;
	if (STU_Player)
		if (!STU_Player->CanFire()) return;

	if (Bullets <= 0)
		OnBulletEmpty.Broadcast();

	if (Bullets <= 0 || Bullets <= 0 && Clips <= 0)
	{
		if (STU_AI_Player)
			STU_AI_Player->AutoReload();

		if (STU_Player)
			STU_Player->AutoReload();

		return;
	}

	FVector ViewLocation;
	FRotator View_Rotation;
	if(Player->IsPlayerControlled())
	{
		const auto Controller = Player->GetController<APlayerController>();
		if (!Controller) return;

		Controller->GetPlayerViewPoint(ViewLocation, View_Rotation);
	}
	else
	{
		ViewLocation = Weapon_Mesh->GetSocketLocation(Muzzle_Socket_Name);
		View_Rotation = Weapon_Mesh->GetSocketRotation(Muzzle_Socket_Name);
	}

	if (Fire_Character_Animation != nullptr)
	{
		UAnimInstance* AnimInstance = Player->GetMesh()->GetAnimInstance();
		if (AnimInstance != nullptr)
			AnimInstance->Montage_Play(Fire_Character_Animation, 1.0f);
	}

	if (Rifle_Fire_Animation != nullptr)
	{
		UAnimInstance* AnimInstance = Weapon_Mesh->GetAnimInstance();
		if (AnimInstance != nullptr)
			AnimInstance->Montage_Play(Rifle_Fire_Animation, 1.0f);
	}

	FCollisionQueryParams CollisoinParams;
	CollisoinParams.AddIgnoredActor(GetOwner());
	CollisoinParams.bReturnPhysicalMaterial = true;

	const auto HalfRad = FMath::DegreesToRadians(BulletSpeed);
	const FTransform Socket_Transform = Weapon_Mesh->GetSocketTransform(Muzzle_Socket_Name);
	const FVector Trace_Start = ViewLocation;
	const FVector Shoot_Direction = FMath::VRandCone(View_Rotation.Vector(), HalfRad);
	const FVector Trace_End = Trace_Start + Shoot_Direction * Trace_Max_Distance;

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, Trace_Start, Trace_End, ECollisionChannel::ECC_Visibility, CollisoinParams);
	Bullets -= 1;

	if(FireSound != nullptr)
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());

	Muzzle_Transform = Weapon_Mesh->GetSocketTransform(Muzzle_Socket_Name);
	WeaponFXComponent->PlayMuzzleFireFX(Muzzle_Transform);

	if (HitResult.bBlockingHit)
	{
		Take_Damage(HitResult);
		if(Hit_Sound != nullptr)
			UGameplayStatics::PlaySoundAtLocation(this, Hit_Sound, HitResult.ImpactPoint);

		WeaponFXComponent->PlayImpactFX(HitResult);
	}
}
//------------------------------------------------------------------------------------------------------------
void AWeapon::Take_Damage(FHitResult HitResult)
{
	if (HitResult.GetActor() != nullptr)
	{
		UGameplayStatics::ApplyPointDamage(HitResult.GetActor(), Weapon_Damage_Amount, GetActorForwardVector(), HitResult,
			Get_Controller(), this, UDamageType::StaticClass() );
	}
}
//------------------------------------------------------------------------------------------------------------
void AWeapon::Start_Fire()
{
	MakeShot();
	GetWorldTimerManager().SetTimer(ShotTimerHadle, this, &AWeapon::MakeShot, TimeBetweenShot, true);
}
//------------------------------------------------------------------------------------------------------------
void AWeapon::Stop_Fire()
{
	GetWorldTimerManager().ClearTimer(ShotTimerHadle);
}
//------------------------------------------------------------------------------------------------------------
void AWeapon::Detach()
{
	DetachFromActor(FDetachmentTransformRules::KeepRelativeTransform);
}
//------------------------------------------------------------------------------------------------------------
AController* AWeapon::Get_Controller()
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}
//------------------------------------------------------------------------------------------------------------
