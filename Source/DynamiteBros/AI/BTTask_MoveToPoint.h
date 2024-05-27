// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_MoveTo.h"
#include "BTTask_MoveToPoint.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMITEBROS_API UBTTask_MoveToPoint : public UBTTask_MoveTo
{
	GENERATED_BODY()

public:
	UBTTask_MoveToPoint();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) override;
};
