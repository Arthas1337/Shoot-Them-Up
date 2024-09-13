#include "HealthComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "STUGameMode.h"
//------------------------------------------------------------------------------------------------------------
UHealthComponent::UHealthComponent()
{
	Health = Max_Health;
}
//------------------------------------------------------------------------------------------------------------
void UHealthComponent::BeginPlay()
{
	check(Max_Health > 0);
	Super::BeginPlay();

	AActor* ComponentOwner = GetOwner();
	if (ComponentOwner)
		ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &ThisClass::On_Take_Damage);

}
//------------------------------------------------------------------------------------------------------------
void UHealthComponent::On_Take_Damage(AActor* DamagedActor, float Damage, 
	const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (Damage <= 0.0f || Is_Dead() && GetWorld() && Cant_Damage) return;

	Health -= FMath::Min(Health, Damage);
	On_Health_Changed.Broadcast(Health);

	GetWorld()->GetTimerManager().ClearTimer(Heal);

	if (Is_Dead())
	{
		Killed(InstigatedBy);
		OnDeath.Broadcast();
	}
	if(AutoHeal)
		GetWorld()->GetTimerManager().SetTimer(Heal,this, &UHealthComponent::Auto_Heal, Heal_Update_Time, true, Delay_Heal);
}
//------------------------------------------------------------------------------------------------------------
void UHealthComponent::Auto_Heal()
{
	Health = FMath::Clamp(Health + Heal_Modifier, 0.0f, Max_Health);
	On_Health_Changed.Broadcast(Health);

	if(FMath::IsNearlyEqual(Health, Max_Health))
		GetWorld()->GetTimerManager().ClearTimer(Heal);
}
//------------------------------------------------------------------------------------------------------------
void UHealthComponent::Killed(AController* Killer)
{
	if (!GetWorld()) return;
	const auto Game_Mode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode() );
	if (!Game_Mode) return;

	const auto Player = Cast<APawn>(GetOwner());
	const auto Victim_Controller = Player ? Player->Controller : nullptr;

	Game_Mode->Killed(Killer, Victim_Controller);
}
//------------------------------------------------------------------------------------------------------------
