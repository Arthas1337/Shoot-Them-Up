#include "STU_Player_Stat_Row_Widget.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

//------------------------------------------------------------------------------------------------------------
void USTU_Player_Stat_Row_Widget::SetPlayerName(const FText& text)
{
	if (!Player_Name_TextBlock) return;

	Player_Name_TextBlock->SetText(text);
}
//------------------------------------------------------------------------------------------------------------
void USTU_Player_Stat_Row_Widget::SetKills(const FText& text)
{
	if (!Kills_TextBlock) return;

	Kills_TextBlock->SetText(text);
}
//------------------------------------------------------------------------------------------------------------
void USTU_Player_Stat_Row_Widget::SetDeaths(const FText& text)
{
	if (!Deaths_TextBlock) return;

	Deaths_TextBlock->SetText(text);
}
//------------------------------------------------------------------------------------------------------------
void USTU_Player_Stat_Row_Widget::SetTeamID(const FText& text)
{
	if (!TeamID_TextBlock) return;

	TeamID_TextBlock->SetText(text);
}
//------------------------------------------------------------------------------------------------------------
void USTU_Player_Stat_Row_Widget::SetPlayerIndicatorVisibility(bool visible)
{
	if (!Player_Indicator_Image) return;

	Player_Indicator_Image->SetVisibility(visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
//------------------------------------------------------------------------------------------------------------
