#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "STU_Enemy_EnvQueryContext.generated.h"

//------------------------------------------------------------------------------------------------------------
UCLASS()
class STU_API USTU_Enemy_EnvQueryContext : public UEnvQueryContext
{
	GENERATED_BODY()
	
public:

	virtual void ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FName Enemy_Actor_Key_Name = "EnemyActor";
};
//------------------------------------------------------------------------------------------------------------
