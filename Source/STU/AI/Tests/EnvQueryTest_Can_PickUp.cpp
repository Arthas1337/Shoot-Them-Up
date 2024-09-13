#include "EnvQueryTest_Can_PickUp.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "../PickUps/STU_Base_PIckUp.h"

//------------------------------------------------------------------------------------------------------------
UEnvQueryTest_Can_PickUp::UEnvQueryTest_Can_PickUp(const FObjectInitializer& ObjectIntializer) //
	: Super(ObjectIntializer)
{
	Cost = EEnvTestCost::Low;
	ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
	SetWorkOnFloatValues(false);
}
//------------------------------------------------------------------------------------------------------------
void UEnvQueryTest_Can_PickUp::RunTest(FEnvQueryInstance& QueryInstance) const
{
	UObject* DataOwner = QueryInstance.Owner.Get();
	BoolValue.BindData(DataOwner, QueryInstance.QueryID);
	bool WantsBeTakable = BoolValue.GetValue();

	for(FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
	{
		AActor* ItemActor = GetItemActor(QueryInstance, It.GetIndex());

		const auto PickUp_Actor = Cast<ASTU_Base_PIckUp>(ItemActor);
		if (!PickUp_Actor) continue;

		const auto CouldBeTaken = PickUp_Actor->CouldBeTaken();
		It.SetScore(TestPurpose, FilterType, CouldBeTaken, WantsBeTakable);
	}
}
//------------------------------------------------------------------------------------------------------------
