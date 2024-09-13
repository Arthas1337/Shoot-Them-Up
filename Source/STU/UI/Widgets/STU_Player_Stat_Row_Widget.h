#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "STU_Player_Stat_Row_Widget.generated.h"

class UImage;
class UTextBlock;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API USTU_Player_Stat_Row_Widget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetPlayerName(const FText& text);
	void SetKills(const FText& text);
	void SetDeaths(const FText& text);
	void SetTeamID(const FText& text);
	void SetPlayerIndicatorVisibility(bool visible);

protected:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Player_Name_TextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Kills_TextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Deaths_TextBlock;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TeamID_TextBlock;

	UPROPERTY(meta = (BindWidget))
	UImage* Player_Indicator_Image;
};
//------------------------------------------------------------------------------------------------------------
