#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "STU_GameInstance.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API USTU_GameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	FName Get_Startup_Level_Name() { return Startup_Level_Name; }
	FName Get_Menu_Level_Name() { return Menu_Level_Name; }

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName Startup_Level_Name = NAME_None;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FName Menu_Level_Name = NAME_None;
};
//------------------------------------------------------------------------------------------------------------
