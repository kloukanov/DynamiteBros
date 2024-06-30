// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_DefaultTargetLocation.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMITEBROS_API UBTService_DefaultTargetLocation : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
public:
	UBTService_DefaultTargetLocation();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

private:

	const float MIN_X = -737.f;
	const float MAX_X = 1201.f;
	const float MIN_Y = -1294.f;
	const float MAX_Y = 1268.f;

	bool IsTargetLocationReached(FVector OwnerLocation, FVector TargetLocation, float MarginOfError = 3.f) const;
};
