#include "STU_GameOver_Widget.h"
#include "../../STUGameMode.h"
#include "STU_PlayerState.h"
#include "STU_Player_Stat_Row_Widget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

//------------------------------------------------------------------------------------------------------------
void USTU_GameOver_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(GetWorld())
	{
		const auto GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChangedSignature.AddUObject(this, &USTU_GameOver_Widget::OnMatchStateChange);
		}
	}

	if(Reset_Level_Button)
	{
		Reset_Level_Button->OnClicked.AddDynamic(this, &USTU_GameOver_Widget::OnResetLevel);
	}
}
//------------------------------------------------------------------------------------------------------------
void USTU_GameOver_Widget::OnMatchStateChange(ESTUMatchState state)
{
	if(state == ESTUMatchState::GameOver)
	{
		UpdatePlayerStat();
	}
}
//------------------------------------------------------------------------------------------------------------
void USTU_GameOver_Widget::UpdatePlayerStat()
{
	if (!GetWorld() || !Player_Stat_Box) return;

	Player_Stat_Box->ClearChildren();
	
	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto Player_State = Cast<ASTU_PlayerState>(Controller->PlayerState);
		if (!Player_State) continue;

		const auto PlayerStateRowWidget = CreateWidget<USTU_Player_Stat_Row_Widget>(GetWorld(), Player_Stat_Row_Widget_Class);
		if (!PlayerStateRowWidget) continue;

		PlayerStateRowWidget->SetPlayerName(FText::FromString(Player_State->GetPlayerName() ) );
		PlayerStateRowWidget->SetKills(FText::FromString(FString::FromInt(Player_State->Get_Kills_Num() ) ) );
		PlayerStateRowWidget->SetDeaths(FText::FromString(FString::FromInt(Player_State->Get_Deaths_Num() ) ) );
		PlayerStateRowWidget->SetTeamID(FText::FromString(FString::FromInt(Player_State->Get_Team_ID() ) ) );
		PlayerStateRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());

		Player_Stat_Box->AddChild(PlayerStateRowWidget);
	}
}
//------------------------------------------------------------------------------------------------------------
void USTU_GameOver_Widget::OnResetLevel()
{
	const FString Current_Level_Name = UGameplayStatics::GetCurrentLevelName(this);
	UGameplayStatics::OpenLevel(this, FName(Current_Level_Name) );
}
//------------------------------------------------------------------------------------------------------------
