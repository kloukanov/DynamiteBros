// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilityBase.h"
#include "ExplosionMultiplierAbility.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMITEBROS_API AExplosionMultiplierAbility : public AAbilityBase
{
	GENERATED_BODY()

public: 
	AExplosionMultiplierAbility();

protected:	
	virtual void AddAbilityToPlayer(class APlayableCharacter *Player) override;
	
private:

	UPROPERTY(EditAnywhere, Category = Ability, meta = (AllowPrivateAccess = "true"))
	float Max = 800.f;

	UPROPERTY(EditAnywhere, Category = Ability, meta = (AllowPrivateAccess = "true"))
	float ExplosionIncrease = 200.f;

};
