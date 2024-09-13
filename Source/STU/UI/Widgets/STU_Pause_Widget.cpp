#include "STU_Pause_Widget.h"
#include "GameFramework/GameModeBase.h"
#include "Kismet/GameplayStatics.h"
#include "Components/Button.h"

//------------------------------------------------------------------------------------------------------------
bool USTU_Pause_Widget::Initialize()
{
	const auto InitStatus = Super::Initialize();

	if(Clear_Pause_Button)
	{
		Clear_Pause_Button->OnClicked.AddDynamic(this, &USTU_Pause_Widget::OnClearPause);
	}

	return InitStatus;
}
//------------------------------------------------------------------------------------------------------------
void USTU_Pause_Widget::OnClearPause()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	GetWorld()->GetAuthGameMode()->ClearPause();
}
//------------------------------------------------------------------------------------------------------------
