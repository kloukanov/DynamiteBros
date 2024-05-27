// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyAIController.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMITEBROS_API AEnemyAIController : public AAIController
{
	GENERATED_BODY()

protected: 

	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* AIBehavior;

	UPROPERTY(EditAnywhere, Category = AI)
	FVector TargetLocation = FVector::ZeroVector;

	UPROPERTY(EditAnywhere, Category = AI)
	bool IsAIStuck = false;
	
};
