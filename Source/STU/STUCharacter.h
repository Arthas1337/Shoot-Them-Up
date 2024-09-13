#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "STUCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class AWeapon;
class USphereComponent;
class AProjectile;
struct FTimerHandle;
class UInputAction;
class UHealthComponent;
class UAnimMontage;
struct FInputActionValue;
class AGranede;
class ASTUGameMode;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnWeaponAttach, bool, Has_Rifle, bool, Has_Pistol);

//------------------------------------------------------------------------------------------------------------
UCLASS(config=Game)
class ASTUCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASTUCharacter();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable)
	FName Get_State_Name() const { return Controller->GetStateName(); }

	UFUNCTION()
	void AutoReload();

	bool CanEquip() const;
	bool CanFire() const;
	bool CanReload() const;
	virtual void Pick_Up_Weapon(AWeapon* weapon);
	void OnWeapon_Change();

	void Set_Player_Color(const FLinearColor& color);

	FTimerHandle Anim_Timer;

	TArray<AWeapon*> Weapons_Arr;

	UPROPERTY(BlueprintReadWrite)
	AWeapon* Current_Weapon = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Force_Throw = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)	
	float ThrowAngle = 45.0f;

	UPROPERTY(BlueprintReadWrite)
	bool HasPistol = false;

	UPROPERTY(BlueprintReadWrite)
	bool HasRifle = false;

	UPROPERTY(BlueprintReadWrite)
	bool Crouching = false;

	bool HasWeapon = false;
	bool Turning = false;
	bool IsReloading = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Weapon_Attached = false;

	UPROPERTY(BlueprintReadWrite, BlueprintAssignable)
	FOnWeaponAttach OnWeaponAttach;

protected:

	UFUNCTION()
	void Reloading();



	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Start_Attack(const FInputActionValue& Value);
	void Stop_Attack(const FInputActionValue& Value);
	void OnReload(const FInputActionValue& Value);
	void Attach_Weapon(AWeapon* weapon, FName socket_name);
	virtual void OnDeath();

	void OnThrowGranede();
	FVector CalculateThrowDirection(const FVector& ForwardVector, float Angle);

	UPROPERTY(EditDefaultsOnly, Category = "Weapons")
	TSubclassOf<AGranede> Granede_Class;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UHealthComponent* Health_Component = nullptr;

	UPROPERTY(BlueprintReadWrite)
	FVector2D LookAxisVector;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category= "Material")
	FName Material_Color_Name = "TeamColor";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Animation)
	UAnimMontage* Reload_Animation_Rifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Animation)
	UAnimMontage* Reload_Animation_Pistol;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Animation)
	UAnimMontage* Rifle_Equip_Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Animation)
	UAnimMontage* Pistol_Equip_Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Animation)
	UAnimMontage* Throw_Grenade_Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Animation)
	UAnimMontage* Take_Hit_Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Sounds)
	USoundBase* Change_Weapon_Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Sounds)
	USoundBase* PickUp_Weapon_Sound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category= Sounds)
	USoundBase* Death_Sound;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Grenade)
	float Throw_Delay = 0.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	float Life_Span = 5.0f;
	
private:

	UFUNCTION()
	void On_Take_Hit(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, 
		class AController* InstigatedBy, AActor* DamageCauser);

	ASTUGameMode* GetGameMode();

	void Start_Throw();
	void Finish_Throw();

	template<typename Class_Notify>
	void InitAnimations(UAnimMontage* Anim_Montage);

	void OnEquipFinished(USkeletalMeshComponent* MeshComp);
	void OnActionFinished(USkeletalMeshComponent* MeshComp);

	UFUNCTION()
	void OnCamerCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OnCamerCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void CheckCameraOverlap();

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* AttackAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Weapon_Change;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Throw_Granede;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Reload;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USphereComponent* CameraCollisionComponent;

	FTimerHandle Reload_Timer;
	FTimerHandle Throw_Grenade_Timer;

	bool EquipAnimInProgress = false;
	bool ReloadAnimInProgress = false;
	bool Is_Dead = false;
};
//------------------------------------------------------------------------------------------------------------
