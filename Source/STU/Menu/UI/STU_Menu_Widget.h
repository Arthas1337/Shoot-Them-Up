#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_Menu_Widget.generated.h"

class UButton;
//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API USTU_Menu_Widget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	virtual void NativeOnInitialized() override;
	virtual void OnAnimationFinished_Implementation(const UWidgetAnimation* Animation) override;

	UPROPERTY(meta = (BindWidget))
	UButton* Start_Game_Button;

	UPROPERTY(meta = (BindWidget))
	UButton* Quit_Game_Button;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* HideAnimation;

private:

	UFUNCTION()
	void OnStartGame();

	UFUNCTION()
	void OnQuitGame();

};
//------------------------------------------------------------------------------------------------------------
