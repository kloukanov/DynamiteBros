#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_UpdateDropDynamite.generated.h"

UCLASS()
class DYNAMITEBROS_API UBTService_UpdateDropDynamite : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public: 
	UBTService_UpdateDropDynamite();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

private:

	float CurrentCount = 1;
	float NextDrop = 1;

	const float MIN_DROP_TIME = 1;
	const float MAX_DROP_TIME = 10;
};
