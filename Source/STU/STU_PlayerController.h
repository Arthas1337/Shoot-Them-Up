#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STUCoreTypes.h"
#include "STU_PlayerController.generated.h"

class USTU_Respawn_Components;
class UInputAction;
class UInputMappingContext;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API ASTU_PlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	ASTU_PlayerController();

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USTU_Respawn_Components* Respawn_Component;

	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* Pause_Game;

	void OnPauseGame();
	void OnMatchChanged(ESTUMatchState State);
};
//------------------------------------------------------------------------------------------------------------
