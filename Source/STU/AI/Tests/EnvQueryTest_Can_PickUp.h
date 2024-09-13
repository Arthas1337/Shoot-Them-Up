#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_Can_PickUp.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API UEnvQueryTest_Can_PickUp : public UEnvQueryTest
{
	GENERATED_BODY()

public:

	UEnvQueryTest_Can_PickUp(const FObjectInitializer& ObjectIntializer);

protected:

	virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;
	
};
//------------------------------------------------------------------------------------------------------------
