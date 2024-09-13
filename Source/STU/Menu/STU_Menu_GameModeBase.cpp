#include "STU_Menu_GameModeBase.h"
#include "STU_Menu_Controller.h"
#include "UI/STU_Menu_HUD.h"
//------------------------------------------------------------------------------------------------------------
ASTU_Menu_GameModeBase::ASTU_Menu_GameModeBase()
{
	PlayerControllerClass = ASTU_Menu_Controller::StaticClass();
	HUDClass = ASTU_Menu_HUD::StaticClass();
}
//------------------------------------------------------------------------------------------------------------
