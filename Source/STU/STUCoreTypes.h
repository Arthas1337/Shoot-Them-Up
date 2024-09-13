#pragma once

#include "CoreMinimal.h"

UENUM(BlueprintType)
enum class ESTUMatchState : uint8
{
	WaitingToStart = 0,
	Inprrogress,
	Pause,
	GameOver
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnMatchStateChangedSignature, ESTUMatchState);