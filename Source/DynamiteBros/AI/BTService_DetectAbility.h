#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_DetectAbility.generated.h"

UCLASS()
class DYNAMITEBROS_API UBTService_DetectAbility : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:
	UBTService_DetectAbility();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
	
};
