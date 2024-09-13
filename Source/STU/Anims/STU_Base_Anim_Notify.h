#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "STU_Base_Anim_Notify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*);

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API USTU_Base_Anim_Notify : public UAnimNotify
{
	GENERATED_BODY()
public:

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	FOnNotifiedSignature OnNotifiedSignature;
	
};
//------------------------------------------------------------------------------------------------------------
