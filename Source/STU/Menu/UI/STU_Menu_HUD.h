// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "STU_Menu_HUD.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API ASTU_Menu_HUD : public AHUD
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> Menu_Widget_Class;

	virtual void BeginPlay() override;
};
//------------------------------------------------------------------------------------------------------------
