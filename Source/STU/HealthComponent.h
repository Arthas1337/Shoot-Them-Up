#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, float);

//------------------------------------------------------------------------------------------------------------
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class STU_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UHealthComponent();

	UFUNCTION(BlueprintCallable)
	float Get_Health() const { return Health; }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float Get_Health_Percent() const { return Health / Max_Health; } 

	UFUNCTION(BlueprintCallable, Category = "Health")
	void Set_Health(float New_Health) { Health = FMath::Clamp(Health + New_Health, 0.0f, Max_Health); } 

	FOnHealthChanged On_Health_Changed;
	FOnDeath OnDeath;
	FTimerHandle Heal;

	UFUNCTION(BlueprintCallable)
	bool Is_Dead() const { return Health <= 0.0f; }

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	bool AutoHeal = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float Max_Health = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float Heal_Update_Time = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float Delay_Heal = 3.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Health")
	float Heal_Modifier = 2.0f;

	bool Cant_Damage = false;

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void On_Take_Damage(AActor* DamagedActor, float Damage,
		const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
	void Auto_Heal();
	void Killed(AController* Killer);

	float Health = 0.0f;

};
//------------------------------------------------------------------------------------------------------------
