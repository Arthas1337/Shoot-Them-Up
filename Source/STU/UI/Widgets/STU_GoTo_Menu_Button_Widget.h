#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_GoTo_Menu_Button_Widget.generated.h"

class UButton;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API USTU_GoTo_Menu_Button_Widget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
	UButton* GoTo_Menu_Button;

private:

	UFUNCTION()
	void GoTo_MainMenu();
};
//------------------------------------------------------------------------------------------------------------
