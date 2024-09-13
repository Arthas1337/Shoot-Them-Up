#include "STU_PlayerState.h"
//------------------------------------------------------------------------------------------------------------
void ASTU_PlayerState::Log_Info()
{
	UE_LOG(LogTemp, Display, TEXT("TeamID: %i / Kills: %i / Deaths: %i"), Team_ID, Kills_Num, Deaths_Num);
}
//------------------------------------------------------------------------------------------------------------
