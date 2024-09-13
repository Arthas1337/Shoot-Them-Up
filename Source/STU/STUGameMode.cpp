#include "STUGameMode.h"
#include "AIController.h"
#include "STUCharacter.h"
#include "AI/STU_AI_Character.h"
#include "Weapon.h"
#include "Player/STU_PlayerState.h"
#include "UI/STU_HUD.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/STU_Respawn_Components.h"
#include "STU_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "EngineUtils.h"
#include "BrainComponent.h"

DEFINE_LOG_CATEGORY_STATIC(Log_Game_Mode, All, All);

const static int32 MinRoundTimeForRespawn = 10;

//------------------------------------------------------------------------------------------------------------
ASTUGameMode::ASTUGameMode()
{

	DefaultPawnClass = ASTUCharacter::StaticClass();
	HUDClass = ASTU_HUD::StaticClass();
	PlayerStateClass = ASTU_PlayerState::StaticClass();
	PlayerControllerClass = ASTU_PlayerController::StaticClass();
}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::StartPlay()
{
	Super::StartPlay();

	Spawn_Bots();
	Create_Teams_Info();
	Current_Round = 1;
	Start_Round();
	Get_All_Weapons();	
	SetMatchState(ESTUMatchState::Inprrogress);
}
//------------------------------------------------------------------------------------------------------------
UClass* ASTUGameMode::GetDefaultPawnClassForController_Implementation(AController* InController)
{
	if(InController && InController->IsA<AAIController>())
	{
		return AI_Pawn_Class;
	}
	return Super::GetDefaultPawnClassForController_Implementation(InController);
}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::Get_All_Weapons()
{
	if (!GetWorld()) return;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AWeapon::StaticClass(), Weapons);
}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::Spawn_Bots()
{

	if (!GetWorld()) return;

	for(int32 i = 0; i < GameData.Players_Num - 1; ++i)
	{
		FActorSpawnParameters Spawn_Info;
		Spawn_Info.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		const auto STU_AIController = GetWorld()->SpawnActor<AAIController>(AIController_Class, Spawn_Info);
		RestartPlayer(STU_AIController);
	}

}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::Start_Round()
{
	Round_Count_Down = GameData.RoundsTime;
	GetWorld()->GetTimerManager().SetTimer(Game_Round_Timer_Handle, this, &ASTUGameMode::Game_Timer_Update, 1.0f, true);
}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::Game_Timer_Update()
{
	if(--Round_Count_Down == 0)
	{
		GetWorldTimerManager().ClearTimer(Game_Round_Timer_Handle);

		if(Current_Round + 1 <= GameData.RoundsNum)
		{
			++Current_Round;
			Reset_Players();
			Start_Round();
		}
		else
		{
			GameOver();
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::Reset_Players()
{
	if (!GetWorld()) return;

	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto Character = Cast<ASTUCharacter>(Controller->GetPawn());
		if (Character && Character->Current_Weapon)
			Character->Current_Weapon->Destroy();
			

		Reset_One_Player(Controller);
	}

}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::Reset_One_Player(AController* Controller)
{
	if (Controller && Controller->GetPawn())
		Controller->GetPawn()->Reset();

	RestartPlayer(Controller);
	Set_Player_Color(Controller);
}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::Create_Teams_Info()
{
	if (!GetWorld()) return;

	int32 Team_ID = 1;
	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto Player_State = Cast<ASTU_PlayerState>(Controller->PlayerState);
		if (!Player_State) continue;

		Player_State->Set_Team_ID(Team_ID);
		Player_State->Set_Team_Color(Determine_Color_By_TeamID(Team_ID));
		Player_State->SetPlayerName(Controller->IsPlayerController() ? "Arthas" : "Bot");
		Set_Player_Color(Controller);
		Team_ID = Team_ID == 1 ? 2 : 1;
	}
}
//------------------------------------------------------------------------------------------------------------
FLinearColor ASTUGameMode::Determine_Color_By_TeamID(int32 team_id) const
{
	if(team_id - 1 < GameData.Team_Colors.Num())
	{
		return GameData.Team_Colors[team_id - 1];
	}
	UE_LOG(Log_Game_Mode, Warning, TEXT("No Color for team  id: %i, set to default: %s"), team_id, 
		*GameData.Default_Team_Color.ToString());

	return GameData.Default_Team_Color;
}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::Set_Player_Color(AController* Controller)
{
	if (!Controller) return;

	const auto Character = Cast<ASTUCharacter>(Controller->GetPawn());
	if (!Character) return;

	const auto Player_State = Cast<ASTU_PlayerState>(Controller->PlayerState);
	if (!Player_State) return;

	Character->Set_Player_Color(Player_State->Get_Team_Color());

}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::Killed(AController* killer_controller, AController* victim_controller)
{
	const auto Killer_State = killer_controller ? Cast<ASTU_PlayerState>(killer_controller->PlayerState) : nullptr;
	const auto Victim_State = victim_controller ? Cast<ASTU_PlayerState>(victim_controller->PlayerState) : nullptr;

	if(Killer_State)
	{
		Killer_State->Add_Kill();
	}
	
	if(Victim_State)
	{
		Victim_State->Add_Death();
	}

	Start_Respawn(victim_controller);
}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::Log_Player_Info()
{
	for(auto It = GetWorld()->GetControllerIterator(); It; ++It)
	{
		const auto Controller = It->Get();
		if (!Controller) continue;

		const auto Player_State = Cast<ASTU_PlayerState>(Controller->PlayerState);
		if (!Player_State) continue;

		Player_State->Log_Info();
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::Start_Respawn(AController* controller)
{
	const auto RespawnAvalible = Round_Count_Down > MinRoundTimeForRespawn + GameData.Respawn_Time;
	if (!RespawnAvalible) return;

	const auto Respawn_Component = controller->FindComponentByClass<USTU_Respawn_Components>();
	if (!Respawn_Component) return;

	Respawn_Component->Respawn(GameData.Respawn_Time);

}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::Respawn_Request(AController* controller)
{
	Reset_One_Player(controller);
}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::GameOver()
{
	UE_LOG(Log_Game_Mode, Display, TEXT("=========== Game Over ==========="));	
	Log_Player_Info();

	for(auto Pawn :  TActorRange<APawn>(GetWorld()))
	{
		if(Pawn)
		{
			Pawn->TurnOff();
			Pawn->DisableInput(nullptr);

			AAIController* AIController = Cast<AAIController>(Pawn->GetController());
			if (AIController)
			{
				AIController->StopMovement();
				if (AIController->BrainComponent)
				{
					AIController->BrainComponent->StopLogic(TEXT("GameOver")); // Останавливаем выполнение поведения AI
				}
			}
		}
		
	}
	SetMatchState(ESTUMatchState::GameOver);
}
//------------------------------------------------------------------------------------------------------------
void ASTUGameMode::SetMatchState(ESTUMatchState State)
{
	if (MatchState == State) return;

	MatchState = State;
	OnMatchStateChangedSignature.Broadcast(MatchState);
}
//------------------------------------------------------------------------------------------------------------
bool ASTUGameMode::SetPause(APlayerController* PC, FCanUnpause CanUnpauseDelegate)
{
	const auto PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
	if(PauseSet)
		SetMatchState(ESTUMatchState::Pause);

	return Super::SetPause(PC, CanUnpauseDelegate);
}
//------------------------------------------------------------------------------------------------------------
bool ASTUGameMode::ClearPause()
{
	const auto Pause_Cleared = Super::ClearPause();
	if(Pause_Cleared)
	{
		SetMatchState(ESTUMatchState::Inprrogress);
	}
	return Pause_Cleared;
}
//------------------------------------------------------------------------------------------------------------