#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "STU_PlayerState.generated.h"

USTRUCT(BlueprintType)
struct FTeamData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor Default_Team_Color = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FLinearColor> Teadm_Colors;
};

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API ASTU_PlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	int32 Get_Team_ID() const { return Team_ID; }
		
	void Set_Team_ID(int32 new_id) { Team_ID = new_id; }

	FLinearColor Get_Team_Color() const { return Team_Color; }
	void Set_Team_Color(const FLinearColor& New_Color) { Team_Color = New_Color; }

	void Add_Kill() { ++Kills_Num; }
	void Add_Death() { ++Deaths_Num; }

	UFUNCTION(BlueprintCallable)
	int32 Get_Kills_Num() const { return Kills_Num; }
	UFUNCTION(BlueprintCallable)
	int32 Get_Deaths_Num() const { return Deaths_Num; }

	void Log_Info();

private:

	int32 Team_ID;
	FLinearColor Team_Color = FLinearColor::Red;

	int32 Kills_Num = 0;
	int32 Deaths_Num = 0;

};
//------------------------------------------------------------------------------------------------------------
