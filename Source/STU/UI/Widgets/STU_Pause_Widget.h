#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_Pause_Widget.generated.h"

class UButton;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API USTU_Pause_Widget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	virtual bool Initialize() override;

protected:

	UPROPERTY(meta = (BindWidget))
	UButton* Clear_Pause_Button;

private:

	UFUNCTION()
	void OnClearPause();
};
//------------------------------------------------------------------------------------------------------------
