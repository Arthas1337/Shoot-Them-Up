#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "Granede.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API AGranede : public AActor
{
	GENERATED_BODY()
	
public:	
	AGranede();
	void BeginPlay() override;

	void Set_Launch_Direction(FVector new_direction) { LaunchDirection = new_direction; }

	void Throw_Grenade(FVector& Direction, float Force);

	UPROPERTY(EditAnywhere)
	USphereComponent* Sphere_Collision;

	UPROPERTY(EditAnywhere)
	UProjectileMovementComponent* Projectile_Movement;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* Grenade_Mesh;


protected:

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float DamageAmount = 10.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Granade_Explosion_Radius = 15.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float Time_To_Explode = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector LaunchDirection = FVector(1.0f, 0.0f, 0.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float LaunchForce = 1000.0f; 

	TArray<AActor*> IgnoredActors;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UNiagaraSystem* ExplosionEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* Explosion_Sound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* Bounce_Sound;

	FTimerHandle Granede_Timer;

private:

	UFUNCTION()
	void Explode();

	UFUNCTION()
	void Make_Sound_Bounce(UPrimitiveComponent* HitComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);
};
//------------------------------------------------------------------------------------------------------------
