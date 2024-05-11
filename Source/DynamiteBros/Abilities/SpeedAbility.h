// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"
#include "SpeedAbility.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMITEBROS_API ASpeedAbility : public AAbilityBase
{
	GENERATED_BODY()

public:
	ASpeedAbility();

protected:	
	virtual void AddAbilityToPlayer(class APlayableCharacter *Player) override;

private:

	UPROPERTY(EditAnywhere, Category = Ability, meta = (AllowPrivateAccess = "true"))
	float MaxSpeed = 800.f;

	UPROPERTY(EditAnywhere, Category = Ability, meta = (AllowPrivateAccess = "true"))
	float SpeedIncrease = 100.f;

};
