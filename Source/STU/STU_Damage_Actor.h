#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STU_Damage_Actor.generated.h"
//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API ASTU_Damage_Actor : public AActor
{
	GENERATED_BODY()
	
public:	

	ASTU_Damage_Actor();
	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;


	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	bool Do_Full_Damage = false;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Radius = 100.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	float Damage = 10.0f;

	UPROPERTY(EditAnyWhere, BlueprintReadWrite)
	FColor SphereColor = FColor::Blue;

	USceneComponent* SceneComponent;

};
//------------------------------------------------------------------------------------------------------------
