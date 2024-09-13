#include "STU_Menu_Widget.h"
#include "Components/Button.h"
#include "Kismet/GamePlayStatics.h" 
#include "STU/STU_GameInstance.h"
#include "Kismet/KismetSystemLibrary.h"

//------------------------------------------------------------------------------------------------------------
void USTU_Menu_Widget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(Start_Game_Button)
	{
		Start_Game_Button->OnClicked.AddDynamic(this, &USTU_Menu_Widget::OnStartGame);
	}

	if(Quit_Game_Button)
	{	
		Quit_Game_Button->OnClicked.AddDynamic(this, &USTU_Menu_Widget::OnQuitGame);
	}
}
//------------------------------------------------------------------------------------------------------------
void USTU_Menu_Widget::OnStartGame()
{
	PlayAnimation(HideAnimation);
}
//------------------------------------------------------------------------------------------------------------
void USTU_Menu_Widget::OnAnimationFinished_Implementation(const UWidgetAnimation* Animation)
{
	if (Animation != HideAnimation) return;

	if (!GetWorld()) return;
	const auto STUGameInstance = GetWorld()->GetGameInstance<USTU_GameInstance>();

	if (!STUGameInstance) return;

	if (STUGameInstance->Get_Startup_Level_Name().IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("Error, Startup Level Name is NONE!"));
		return;
	}

	UGameplayStatics::OpenLevel(this, STUGameInstance->Get_Startup_Level_Name());
}
//------------------------------------------------------------------------------------------------------------
void USTU_Menu_Widget::OnQuitGame()
{
	UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
//------------------------------------------------------------------------------------------------------------
