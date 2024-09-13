#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../STUCoreTypes.h"
#include "STU_GameOver_Widget.generated.h"

class UVerticalBox;
class UButton;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API USTU_GameOver_Widget : public UUserWidget
{
	GENERATED_BODY()
	
protected:

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* Player_Stat_Box;

	UPROPERTY(meta = (BindWidget))
	UButton* Reset_Level_Button;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> Player_Stat_Row_Widget_Class;


private:
	void OnMatchStateChange(ESTUMatchState state);
	void UpdatePlayerStat();

	UFUNCTION()
	void OnResetLevel();
};
//------------------------------------------------------------------------------------------------------------
