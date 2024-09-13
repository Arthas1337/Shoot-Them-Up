#include "STU_Base_Anim_Notify.h"

//------------------------------------------------------------------------------------------------------------
void USTU_Base_Anim_Notify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	OnNotifiedSignature.Broadcast(MeshComp);
	Super::Notify(MeshComp, Animation);
}
//------------------------------------------------------------------------------------------------------------