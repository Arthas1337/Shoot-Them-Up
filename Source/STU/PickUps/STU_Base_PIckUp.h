#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "STU_Base_PIckUp.generated.h"

class USphereComponent;

UCLASS()
class STU_API ASTU_Base_PIckUp : public AActor
{
	GENERATED_BODY()
	
public:	

	ASTU_Base_PIckUp();

	bool CouldBeTaken() const;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collsion")
	USphereComponent* Sphere_Collision;
};
