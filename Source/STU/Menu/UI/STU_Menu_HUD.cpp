#include "STU_Menu_HUD.h"
#include "Blueprint/UserWidget.h"

//------------------------------------------------------------------------------------------------------------
void ASTU_Menu_HUD::BeginPlay()
{
	Super::BeginPlay();
	if(Menu_Widget_Class)
	{
		const auto Menu_Widget = CreateWidget<UUserWidget>(GetWorld(), Menu_Widget_Class);
		if(Menu_Widget)
		{
			Menu_Widget->AddToViewport();
		}
	}
}
//------------------------------------------------------------------------------------------------------------
