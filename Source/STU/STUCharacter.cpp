#include "STUCharacter.h"
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Animation/AnimMontage.h"
#include "Anims/STU_Equip_Anim_Notify.h"
#include "Anims/STU_Reload_Anim_Notify.h"
#include "Weapon.h"
#include "Weapons/STU_Pistol.h"
#include "Weapons/STU_Rifle.h"
#include "Granede.h"
#include "HealthComponent.h"
#include "Engine/DamageEvents.h"
#include "STUGameMode.h"
#include "InputActionValue.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);
//------------------------------------------------------------------------------------------------------------
ASTUCharacter::ASTUCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);
		
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->bAllowPhysicsRotationDuringAnimRootMotion = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 720.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 1400.0f;
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->BrakingFrictionFactor = 1.0f;
	GetCharacterMovement()->BrakingFriction = 6.0f;
	GetCharacterMovement()->GroundFriction = 8.0f;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 400.0f;
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	Health_Component = CreateDefaultSubobject<UHealthComponent>(TEXT("HealthComponent"));

	CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("Camera_Collision"));
	CameraCollisionComponent->SetupAttachment(FollowCamera);
	CameraCollisionComponent->SetSphereRadius(10.0f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(Health_Component);
	check(GetCharacterMovement());
	check(GetMesh());
	check(CameraCollisionComponent);

	CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &ASTUCharacter::OnCamerCollisionBeginOverlap);
	CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &ASTUCharacter::OnCamerCollisionEndOverlap);

	Health_Component->OnDeath.AddUObject(this, &ThisClass::OnDeath);
	OnTakeAnyDamage.AddDynamic(this, &ThisClass::On_Take_Hit);
	InitAnimations<USTU_Equip_Anim_Notify>(Pistol_Equip_Animation);
	InitAnimations<USTU_Equip_Anim_Notify>(Rifle_Equip_Animation);
	InitAnimations<USTU_Reload_Anim_Notify>(Reload_Animation_Pistol);
	InitAnimations<USTU_Reload_Anim_Notify>(Reload_Animation_Rifle);
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
	
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ASTUCharacter::Move);
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ASTUCharacter::Look);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Started, this, &ASTUCharacter::Start_Attack);
		EnhancedInputComponent->BindAction(AttackAction, ETriggerEvent::Completed, this, &ASTUCharacter::Stop_Attack);
		EnhancedInputComponent->BindAction(Weapon_Change, ETriggerEvent::Triggered, this, &ASTUCharacter::OnWeapon_Change);
		EnhancedInputComponent->BindAction(Throw_Granede, ETriggerEvent::Triggered, this, &ASTUCharacter::OnThrowGranede);
		EnhancedInputComponent->BindAction(Reload, ETriggerEvent::Triggered, this, &ASTUCharacter::OnReload);
		EnhancedInputComponent->BindAction(Reload, ETriggerEvent::Triggered, this, &ASTUCharacter::OnReload);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error, TEXT("'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."), *GetNameSafe(this));
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D MovementVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// find out which way is forward
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0, Rotation.Yaw, 0);

		// get forward vector
		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	
		// get right vector 
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		// add movement 
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}
//------------------------------------------------------------------------------------------------------------s
void ASTUCharacter::Start_Attack(const FInputActionValue& Value)
{
	if (!HasWeapon) return;
	if (Current_Weapon->Get_Bullets() <= 0) return;	

	if(CanFire())
	{
		Current_Weapon->SetOwner(this);
		Current_Weapon->Start_Fire();
	}	
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::Stop_Attack(const FInputActionValue& Value)
{
	if (!HasWeapon) return;
	if (Current_Weapon == nullptr) return;
	Current_Weapon->Stop_Fire();
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::Pick_Up_Weapon(AWeapon* weapon)
{

	if (!weapon) return;
	if (!GetWorld()) return;

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
	

	if(PickUp_Weapon_Sound  != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, PickUp_Weapon_Sound, GetActorLocation());
	}

	Weapons_Arr.Add(weapon);
	OnWeaponAttach.Broadcast(HasRifle, HasPistol);
	//Current_Weapon->OnBulletEmpty.AddDynamic(this, &ThisClass::AutoReload);
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::Attach_Weapon(AWeapon* weapon, FName socket_name)
{
	EquipAnimInProgress = true;
	FAttachmentTransformRules Attach_Rules(EAttachmentRule::SnapToTarget, true);
	weapon->AttachToComponent(GetMesh(), Attach_Rules, socket_name);

	USphereComponent* SphereCollision = weapon->FindComponentByClass<USphereComponent>();
	if(SphereCollision != nullptr)
	{
		SphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		SphereCollision->SetVisibility(false);
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::OnWeapon_Change()
{
	if (Weapons_Arr.IsEmpty()) return;
	if (!CanEquip()) return; 

	if (Current_Weapon != nullptr)
	{
		Current_Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		Current_Weapon->SetActorHiddenInGame(true);
		Current_Weapon->SetActorEnableCollision(false);
	}

	int32 CurrentWeaponIndex = Weapons_Arr.IndexOfByKey(Current_Weapon);
	int32 NextWeaponIndex = (CurrentWeaponIndex + 1) % Weapons_Arr.Num();
	Current_Weapon = Weapons_Arr[NextWeaponIndex];

	if(Weapons_Arr.Num() > 1)
	{
		ASTU_Rifle* Rifle = Cast<ASTU_Rifle>(Current_Weapon);
		ASTU_Pistol* Pistolet = Cast<ASTU_Pistol>(Current_Weapon);

		if(Current_Weapon == Rifle && Rifle_Equip_Animation != nullptr)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

			if (AnimInstance != nullptr)
				AnimInstance->Montage_Play(Rifle_Equip_Animation, 1.0);
		} 
		else if(Current_Weapon == Pistolet && Pistol_Equip_Animation)
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

			if (AnimInstance != nullptr)
				AnimInstance->Montage_Play(Pistol_Equip_Animation, 1.0);
		}

		if(Change_Weapon_Sound != nullptr)
			UGameplayStatics::PlaySoundAtLocation(this, Change_Weapon_Sound, GetActorLocation());
	}

	Attach_Weapon(Current_Weapon, FName(TEXT("weapon_hand_r")));
	if(Current_Weapon)
	{
		Current_Weapon->SetActorHiddenInGame(false);
		Current_Weapon->SetActorEnableCollision(true);
	}

	HasPistol = Current_Weapon->Has_Pistol;
	HasRifle = Current_Weapon->Has_Rifle;

	OnWeaponAttach.Broadcast(HasRifle, HasPistol);
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::Set_Player_Color(const FLinearColor& color)
{
	const auto Material_Instance_0 = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
	const auto Material_Instance_1 = GetMesh()->CreateAndSetMaterialInstanceDynamic(1);
	if (!Material_Instance_0 && !Material_Instance_1) return;

	Material_Instance_0->SetVectorParameterValue(Material_Color_Name, color);	
	Material_Instance_1->SetVectorParameterValue(Material_Color_Name, color);	
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::OnDeath()
{
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(Life_Span);
	if(Current_Weapon != nullptr)
	{
		Current_Weapon->SetActorHiddenInGame(true);
		Current_Weapon->SetActorEnableCollision(true);
		Current_Weapon->Destroy();
	}
	Health_Component->Cant_Damage = true;
	if (Controller)
		Controller->ChangeState(NAME_Spectating);

	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetMesh()->SetSimulatePhysics(true);

	if(Death_Sound  != nullptr)
	{
		UGameplayStatics::PlaySoundAtLocation(this, Death_Sound, GetActorLocation());
	}

	Is_Dead = true;
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::OnThrowGranede()
{
	if(Throw_Grenade_Animation!= nullptr)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance != nullptr)
			AnimInstance->Montage_Play(Throw_Grenade_Animation, 1.0);
	}

	GetWorldTimerManager().SetTimer(Throw_Grenade_Timer, this, &ASTUCharacter::Start_Throw, Throw_Delay);
}
//------------------------------------------------------------------------------------------------------------
ASTUGameMode* ASTUCharacter::GetGameMode()
{
	if(!GetWorld())
		return nullptr;

	const auto GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());

	if (!GameMode)
		return nullptr;

	return GameMode;
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::Start_Throw()
{
	if(GetWorld() && Granede_Class != nullptr)
	{
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.Owner = this;

		FVector Spawn_Location = GetMesh()->GetSocketLocation(TEXT("Grenade_Socket"));
		FRotator Spawn_Rotation = GetMesh()->GetSocketRotation(TEXT("Grenade_Socket"));

		AGranede* Granede = GetWorld()->SpawnActor<AGranede>(Granede_Class, Spawn_Location, Spawn_Rotation, SpawnParameters);

		if (Granede != nullptr)
		{
			FVector Forward_Direction = Spawn_Rotation.Vector();
			FVector Throw_Direction = CalculateThrowDirection(Forward_Direction, ThrowAngle);
			Granede->Throw_Grenade(Throw_Direction, Force_Throw);
		}
	}
	Finish_Throw();
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::Finish_Throw()
{
	GetWorldTimerManager().ClearTimer(Throw_Grenade_Timer);
}
//------------------------------------------------------------------------------------------------------------
FVector ASTUCharacter::CalculateThrowDirection(const FVector& ForwardVector, float Angle)
{
	float RadAngle = FMath::DegreesToRadians(Angle);

	float VerticalComponent = FMath::Sin(RadAngle);
	float HorizontalComponent = FMath::Cos(RadAngle);

	FVector ThrowDirection = ForwardVector * HorizontalComponent + FVector(0, 0, VerticalComponent);
	return ThrowDirection.GetSafeNormal();
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::OnReload(const FInputActionValue& Value)
{
	AutoReload();
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::AutoReload()
{
	if (CanReload())
	{
		ReloadAnimInProgress = true;
		Reloading();
		UE_LOG(LogTemp, Display, TEXT("Start Reload"));
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::Reloading()
{
	if(HasRifle && Reload_Animation_Rifle != nullptr)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance != nullptr)
		{
			Current_Weapon->Reload();
			AnimInstance->Montage_Play(Reload_Animation_Rifle, 1.0);
		}
	}
	else if(HasPistol && Reload_Animation_Pistol != nullptr)
	{
		UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();

		if (AnimInstance != nullptr)
		{
			Current_Weapon->Reload();
			AnimInstance->Montage_Play(Reload_Animation_Pistol, 1.0);
		}

	}
}
//------------------------------------------------------------------------------------------------------------
template<typename Class_Notify>
void ASTUCharacter::InitAnimations(UAnimMontage* Anim_Montage)
{
	if(Anim_Montage != nullptr)
	{
		const auto NotifyRifleEvents = Anim_Montage->Notifies;

		for(auto NotifyRifleEvent : NotifyRifleEvents)
		{
			auto EquipFinisNotify = Cast<Class_Notify>(NotifyRifleEvent.Notify);
			if (EquipFinisNotify != nullptr)
			{
				EquipFinisNotify->OnNotifiedSignature.AddUObject(this, &ASTUCharacter::OnActionFinished);
				break;
			}
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
	if(GetMesh() == MeshComp)
		EquipAnimInProgress = false;
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::OnActionFinished(USkeletalMeshComponent* MeshComp)
{
	if (GetMesh() == MeshComp)
	{
		ReloadAnimInProgress = false;
		EquipAnimInProgress = false;

		UE_LOG(LogTemp, Display, TEXT("ReloadAnimInProgress = %d\nEquipAnimInProgress = %d"), ReloadAnimInProgress, EquipAnimInProgress);
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::OnCamerCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	CheckCameraOverlap();
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::OnCamerCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	CheckCameraOverlap();
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::CheckCameraOverlap()
{
	const auto HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
	GetMesh()->SetOwnerNoSee(HideMesh);
	if(Current_Weapon)
		Current_Weapon->Weapon_Mesh->SetOwnerNoSee(HideMesh);
}
//------------------------------------------------------------------------------------------------------------
bool ASTUCharacter::CanEquip() const
{
	return !EquipAnimInProgress && !ReloadAnimInProgress;
}
//------------------------------------------------------------------------------------------------------------
bool ASTUCharacter::CanFire() const
{
	return Current_Weapon && !EquipAnimInProgress && !ReloadAnimInProgress && !Health_Component->Is_Dead();
}
//------------------------------------------------------------------------------------------------------------
bool ASTUCharacter::CanReload() const
{
	return !EquipAnimInProgress && Current_Weapon && Current_Weapon->Get_Bullets() != Current_Weapon->Max_Bullets && 
		Current_Weapon->Clips > 0 && HasWeapon;
}
//------------------------------------------------------------------------------------------------------------
void ASTUCharacter::On_Take_Hit(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, 
	class AController* InstigatedBy, AActor* DamageCauser)
{
	if (Is_Dead) return;

	UAnimInstance* Instance = GetMesh()->GetAnimInstance();
	if (Instance != nullptr)
		Instance->Montage_Play(Take_Hit_Animation);
}
//------------------------------------------------------------------------------------------------------------
