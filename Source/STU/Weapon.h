#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Engine/EngineTypes.h"
#include "Weapon.generated.h"

class ASTUCharacter;
class USoundBase;
class UAnimMontage;
class USkeletaMeshComponent;
class AProjectile;
class USTU_Weapon_FX_Component;

DECLARE_LOG_CATEGORY_EXTERN(LogWeapon, Log, All);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnBulletEmpty);

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	AWeapon();
	
	virtual void Start_Fire();
	virtual void Stop_Fire();

	UFUNCTION(BlueprintCallable)
	int Get_Bullets() const { return Bullets; }

	UFUNCTION(BlueprintCallable)
	void Set_Bullets(int const& New_Bullets) { Bullets = New_Bullets; }

	UFUNCTION()
	virtual void Reload();

	void MakeShot();

	FOnBulletEmpty OnBulletEmpty;

	UPROPERTY(EditAnywhere, Category = "Weapon")
	USphereComponent* Sphere_Collision;

	UPROPERTY(BlueprintReadWrite,VisibleAnyWhere, Category = "Components")
	USkeletalMeshComponent* Weapon_Mesh;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category = "Shoot")
	float TimeBetweenShot = 0.1f;

	UPROPERTY(BlueprintReadWrite,EditDefaultsOnly, Category = "Shoot")
	float BulletSpeed = 1.5f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armory")
	int Max_Bullets = 25;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Armory")
	int Clips = 3;

	bool Has_Pistol = false;
	bool Has_Rifle = false;

protected:

	UFUNCTION()
	virtual void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
		bool bFromSweep, const FHitResult & SweepResult);

	virtual void BeginPlay() override;
	void Take_Damage(FHitResult HitResult);
	void Detach();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Gameplay)
	USoundBase* FireSound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* Fire_Character_Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* Rifle_Fire_Animation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	UAnimMontage* Base_Reload_Animation;

	UPROPERTY(EditAnywhere, Category = "Sounds")
	USoundBase* Hit_Sound;

	UPROPERTY(VisibleAnywhere, Category= "VFX")
	USTU_Weapon_FX_Component* WeaponFXComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	FName Muzzle_Socket_Name = "Muzzle";

	UPROPERTY(EditDefaultsOnly, Category = "Trace")
	float Trace_Max_Distance = 15000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Weapon_Damage_Amount = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Damage")
	float Respawn_Delay = 5.0f;
	FTransform Muzzle_Transform;
private:

	AController* Get_Controller();

	UPROPERTY()
	UAnimMontage* Current_Reload_Anim;
	FTimerHandle ShotTimerHadle;
	int Bullets = Max_Bullets;
	
};
//------------------------------------------------------------------------------------------------------------
