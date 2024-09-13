#include "STU_GoTo_Menu_Button_Widget.h"
#include "../../STU_GameInstance.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

//------------------------------------------------------------------------------------------------------------
void USTU_GoTo_Menu_Button_Widget::NativeOnInitialized()
{

	Super::NativeOnInitialized();

	if(GoTo_Menu_Button)
	{
		GoTo_Menu_Button->OnClicked.AddDynamic(this, &USTU_GoTo_Menu_Button_Widget::GoTo_MainMenu);
	}
}
//------------------------------------------------------------------------------------------------------------
void USTU_GoTo_Menu_Button_Widget::GoTo_MainMenu()
{
	if (!GetWorld()) return;

	const auto GameInstance = Cast<USTU_GameInstance>(GetWorld()->GetGameInstance() );
	if (!GameInstance) return;

	if(GameInstance->Get_Menu_Level_Name().IsNone())
	{
		UE_LOG(LogTemp, Error, TEXT("Menu level is  NONE"));
		return;
	}

	UGameplayStatics::OpenLevel(this, GameInstance->Get_Menu_Level_Name());
}
//------------------------------------------------------------------------------------------------------------
