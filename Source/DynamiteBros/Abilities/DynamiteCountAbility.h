// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"
#include "DynamiteCountAbility.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMITEBROS_API ADynamiteCountAbility : public AAbilityBase
{
	GENERATED_BODY()

public:
	ADynamiteCountAbility();

protected:	
	virtual void AddAbilityToPlayer(class APlayableCharacter &Player) override;
};
