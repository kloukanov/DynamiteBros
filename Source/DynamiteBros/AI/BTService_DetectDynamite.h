// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_DetectDynamite.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMITEBROS_API UBTService_DetectDynamite : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTService_DetectDynamite();

protected:
	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;

private:

	const float MIN_RUN_AWAY_RANGE = 2.f;
	const float MAX_RUN_AWAY_RANGE = 7.f;

	void SetRunAwayDirection(UBehaviorTreeComponent &OwnerComp, FVector Location, class ADynamite* Dynamite);

};
