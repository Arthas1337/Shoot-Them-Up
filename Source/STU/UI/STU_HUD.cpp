#include "STU_HUD.h"
#include "Widgets/STU_Player_UserWidget.h"
#include "../STUGameMode.h"
#include "../HealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHUD, All, All);

void ASTU_HUD::DrawHUD()
{
	Super::DrawHUD();
}

void ASTU_HUD::BeginPlay()
{
	Super::BeginPlay();

	GameWidgets.Add(ESTUMatchState::Inprrogress, CreateWidget<UUserWidget>(GetWorld(), PlayerWidgetClass));
	GameWidgets.Add(ESTUMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseWidgetClass));
	GameWidgets.Add(ESTUMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidgetClass));

	for(auto GameWidgetPair: GameWidgets)
	{
		const auto Game_Widget = GameWidgetPair.Value;
		if (!Game_Widget)  continue;

		Game_Widget->AddToViewport();
		Game_Widget->SetVisibility(ESlateVisibility::Hidden);
	}

	if(GetWorld())
	{
		const auto GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChangedSignature.AddUObject(this, &ASTU_HUD::OnMatchChanged);
		}
	}
}

void ASTU_HUD::OnMatchChanged(ESTUMatchState State)
{
	if(Current_Widget)
	{
		Current_Widget->SetVisibility(ESlateVisibility::Hidden);
	}

	if(GameWidgets.Contains(State))
	{
		Current_Widget = GameWidgets[State];
	}

	if(Current_Widget)
	{
		Current_Widget->SetVisibility(ESlateVisibility::Visible);
	}

	UE_LOG(LogHUD, Display, TEXT("Match state changed: %s"), *UEnum::GetValueAsString(State));
}
