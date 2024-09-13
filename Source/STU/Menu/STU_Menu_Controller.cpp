#include "STU_Menu_Controller.h"

//------------------------------------------------------------------------------------------------------------
void ASTU_Menu_Controller::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeUIOnly());
	bShowMouseCursor = true;
}
//------------------------------------------------------------------------------------------------------------
