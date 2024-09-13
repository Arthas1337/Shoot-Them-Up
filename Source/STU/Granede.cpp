#include "Granede.h"
#include "STUCharacter.h"
#include "TimerManager.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
//------------------------------------------------------------------------------------------------------------
AGranede::AGranede()
{
	Grenade_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Grenade_Mesh"));
	SetRootComponent(Grenade_Mesh);
	Grenade_Mesh->SetSimulatePhysics(true);
	Grenade_Mesh->IgnoreActorWhenMoving(GetOwner(), true);

	Sphere_Collision = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere_Collision"));
	Sphere_Collision->SetSphereRadius(5.0f);
	Sphere_Collision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Sphere_Collision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);


	Projectile_Movement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	Projectile_Movement->SetUpdatedComponent(Grenade_Mesh);
	Projectile_Movement->bRotationFollowsVelocity = true;
	Projectile_Movement->InitialSpeed = 1000.0f;
	Projectile_Movement->MaxSpeed = 1000.0f;
	Projectile_Movement->bShouldBounce = true;
	Projectile_Movement->ProjectileGravityScale = 1.0f;
	Projectile_Movement->Bounciness = 0.6f;
	Projectile_Movement->Friction = 0.2f;
	Projectile_Movement->BounceVelocityStopSimulatingThreshold = 10.0f;
}
//------------------------------------------------------------------------------------------------------------
void AGranede::BeginPlay()
{
	check(Sphere_Collision)
	check(Projectile_Movement)
	Grenade_Mesh->OnComponentHit.AddDynamic(this, &ThisClass::Make_Sound_Bounce);

	if(GetWorld())
		GetWorld()->GetTimerManager().SetTimer(Granede_Timer, this, &AGranede::Explode, Time_To_Explode, false);

	SetLifeSpan(Time_To_Explode);
}
//------------------------------------------------------------------------------------------------------------
void AGranede::Throw_Grenade(FVector& Direction, float Force)
{
	LaunchDirection = Direction.GetSafeNormal();
	LaunchForce = Force;
	Projectile_Movement->Velocity = LaunchDirection * LaunchForce;
}
//------------------------------------------------------------------------------------------------------------
void AGranede::Explode()
{
	IgnoredActors.Add(this);
	if (GetWorld())
	{
		DrawDebugSphere(GetWorld(), GetActorLocation(), Granade_Explosion_Radius, 24, FColor::Red);

		UGameplayStatics::ApplyRadialDamage(GetWorld(), DamageAmount, GetActorLocation(), Granade_Explosion_Radius,
			UDamageType::StaticClass(),IgnoredActors,this,GetInstigatorController(),
			false);

		UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ExplosionEffect, GetActorLocation());
		UGameplayStatics::PlaySoundAtLocation(this, Explosion_Sound, GetActorLocation());

		Destroy();
	}
}
//------------------------------------------------------------------------------------------------------------
void AGranede::Make_Sound_Bounce(UPrimitiveComponent* HitComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	UGameplayStatics::PlaySoundAtLocation(this, Bounce_Sound, GetActorLocation());
}
//------------------------------------------------------------------------------------------------------------