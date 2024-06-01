#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_DropDynamite.generated.h"

UCLASS()
class DYNAMITEBROS_API UBTTask_DropDynamite : public UBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTask_DropDynamite();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;

};
