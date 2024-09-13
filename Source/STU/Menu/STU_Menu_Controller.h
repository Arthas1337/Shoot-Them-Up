// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "STU_Menu_Controller.generated.h"

/**
 * 
 */
UCLASS()
class STU_API ASTU_Menu_Controller : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;
};
