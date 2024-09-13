#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "STUCoreTypes.h"
#include "STUGameMode.generated.h"

USTRUCT(BlueprintType)
struct FGameData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "game",
		meta = (ClampMin = "1", ClampMax = "100"))
	int32 Players_Num = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "game",
		meta = (ClampMin = "1", ClampMax = "10"))
	int32 RoundsNum = 2;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "game",
		meta = (ClampMin = "3", ClampMax = "600"))
	int32 RoundsTime = 10; // seconds

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "game",
		meta = (ClampMin = "3", ClampMax = "15"))
	int32 Respawn_Time = 5;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	FLinearColor Default_Team_Color = FLinearColor::Red;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	TArray<FLinearColor> Team_Colors;
};

class AAIController;
class AWeapon;

//------------------------------------------------------------------------------------------------------------
UCLASS(minimalapi)
class ASTUGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASTUGameMode();

	FOnMatchStateChangedSignature OnMatchStateChangedSignature;

	void Respawn_Request(AController* controller);

	virtual void StartPlay() override;
	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	void Killed(AController* killer_controller, AController* victim_controller);

	UFUNCTION(BlueprintCallable)
	int32 Get_Current_Round() const {return Current_Round; }

	UFUNCTION(BlueprintCallable)
	int32 Get_Round_Count_Down() const {return Round_Count_Down; }

	UFUNCTION(BlueprintCallable)
	int32 Get_Round_Nums() const {return GameData.RoundsNum; }

	virtual bool SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate = FCanUnpause());

	virtual bool ClearPause() override;

private:

	ESTUMatchState MatchState = ESTUMatchState::WaitingToStart;

	void Get_All_Weapons();
	void Spawn_Bots();
	void Start_Round();
	void Game_Timer_Update();

	void Reset_Players();
	void Reset_One_Player(AController* Controller);

	void Create_Teams_Info();
	FLinearColor Determine_Color_By_TeamID(int32 team_id) const;
	void Set_Player_Color(AController* Controller);

	void Log_Player_Info();
	void Start_Respawn(AController* controller);
	void GameOver();

	void SetMatchState(ESTUMatchState State);

	TArray<AActor*> Weapons;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIController_Class;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<APawn> AI_Pawn_Class;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

	int32 Current_Round = 1;
	int32 Round_Count_Down = 0;

	FTimerHandle Weapon_Respawn_Timer_Handle;
	FTimerHandle Game_Round_Timer_Handle;
};
//------------------------------------------------------------------------------------------------------------
