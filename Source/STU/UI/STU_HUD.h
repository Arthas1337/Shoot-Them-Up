#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Blueprint/UserWidget.h"
#include "../STUCoreTypes.h"
#include "STU_HUD.generated.h"

class UHealthComponent;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API ASTU_HUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void DrawHUD() override;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PauseWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	virtual void BeginPlay() override;

private:

	UPROPERTY()
	TMap<ESTUMatchState, UUserWidget*> GameWidgets;

	UPROPERTY()
	UUserWidget* Current_Widget = nullptr;


	void OnMatchChanged(ESTUMatchState State);
};
//------------------------------------------------------------------------------------------------------------
