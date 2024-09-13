#include "STU_Damage_Actor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
//------------------------------------------------------------------------------------------------------------
ASTU_Damage_Actor::ASTU_Damage_Actor()
{
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	RootComponent = SceneComponent;
}
//------------------------------------------------------------------------------------------------------------
void ASTU_Damage_Actor::BeginPlay()
{
	Super::BeginPlay();
	
}
//------------------------------------------------------------------------------------------------------------
void ASTU_Damage_Actor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), Radius, 24, SphereColor);

	UGameplayStatics::ApplyRadialDamage(GetWorld(), Damage, GetActorLocation(), Radius, nullptr,
		{}, this, nullptr, Do_Full_Damage);
}
//------------------------------------------------------------------------------------------------------------
