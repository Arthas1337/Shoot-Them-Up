#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "STU_Sound_FunctionLibrary.generated.h"

class USoundClass;

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API USTU_Sound_FunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable)
	static void SetSoundClassVolume(USoundClass* SoundClass, float Volume);

	UFUNCTION(BlueprintCallable)
	static void ToggleSoundClassVolume(USoundClass* SoundClass);
};
//------------------------------------------------------------------------------------------------------------
