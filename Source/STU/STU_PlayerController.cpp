#include "STU_PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Components/STU_Respawn_Components.h"
#include "STUGameMode.h"

//------------------------------------------------------------------------------------------------------------
ASTU_PlayerController::ASTU_PlayerController()
{
	Respawn_Component = CreateDefaultSubobject<USTU_Respawn_Components>("Respawn_Component");
}
//------------------------------------------------------------------------------------------------------------
void ASTU_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(GetWorld())
	{
		const auto GameMode = Cast<ASTUGameMode>(GetWorld()->GetAuthGameMode());
		if(GameMode)
		{
			GameMode->OnMatchStateChangedSignature.AddUObject(this, &ASTU_PlayerController::OnMatchChanged);
		}
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTU_PlayerController::OnMatchChanged(ESTUMatchState State)
{
	if(State == ESTUMatchState::Inprrogress)
	{
		SetInputMode(FInputModeGameOnly());
		bShowMouseCursor = false;
	}
	else
	{
		SetInputMode(FInputModeUIOnly());
		bShowMouseCursor = true;
	}
}
//------------------------------------------------------------------------------------------------------------
void ASTU_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
}
//------------------------------------------------------------------------------------------------------------
void ASTU_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!InputComponent) return;

	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Failed GetlocalPlayer"));

	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent))
	{
		EnhancedInputComponent->BindAction(Pause_Game, ETriggerEvent::Triggered, this, &ASTU_PlayerController::OnPauseGame);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("Bad Cast GetlocalPlayer"));
}
//------------------------------------------------------------------------------------------------------------
void ASTU_PlayerController::OnPauseGame()
{
	if (!GetWorld() || !GetWorld()->GetAuthGameMode()) return;

	UE_LOG(LogTemp, Error, TEXT("Set Pause"));

	GetWorld()->GetAuthGameMode()->SetPause(this);
}
//------------------------------------------------------------------------------------------------------------
