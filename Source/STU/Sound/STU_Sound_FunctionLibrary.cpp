#include "STU_Sound_FunctionLibrary.h"
#include "Sound/SoundClass.h"

//------------------------------------------------------------------------------------------------------------
void USTU_Sound_FunctionLibrary::SetSoundClassVolume(USoundClass* SoundClass, float Volume)
{
	if (!SoundClass) return;

	SoundClass->Properties.Volume = FMath::Clamp(0.0f, 1.0f, Volume);
}
//------------------------------------------------------------------------------------------------------------
void USTU_Sound_FunctionLibrary::ToggleSoundClassVolume(USoundClass* SoundClass)
{
	if (!SoundClass) return;
	const auto NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;
	SetSoundClassVolume(SoundClass, NextVolume);
}
//------------------------------------------------------------------------------------------------------------
