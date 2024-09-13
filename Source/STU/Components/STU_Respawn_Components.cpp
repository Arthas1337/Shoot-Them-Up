#include "STU_Respawn_Components.h"
#include "../STUGameMode.h"

//------------------------------------------------------------------------------------------------------------
USTU_Respawn_Components::USTU_Respawn_Components()
{

	PrimaryComponentTick.bCanEverTick = false;

}
//------------------------------------------------------------------------------------------------------------
void USTU_Respawn_Components::Respawn(int32 respawn_time)
{
	if (!GetWorld()) return;

	Respawn_Count_Down = respawn_time;

	GetWorld()->GetTimerManager().SetTimer(Respawn_Timer_Handle, this, &USTU_Respawn_Components::Respawn_Timer_Update, 1.0f, true);
}
//------------------------------------------------------------------------------------------------------------
void USTU_Respawn_Components::Respawn_Timer_Update()
{
	if(--Respawn_Count_Down == 0)
	{
		if (!GetWorld()) return;
		GetWorld()->GetTimerManager().ClearTimer(Respawn_Timer_Handle);

		const auto Game_Mode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
		if (!Game_Mode) return;

		Game_Mode->Respawn_Request(Cast<AController>(GetOwner() ) );
	}
}
//------------------------------------------------------------------------------------------------------------

