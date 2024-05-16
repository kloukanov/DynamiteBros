// Fill out your copyright notice in the Description page of Project Settings.


#include "ExplosionMultiplierAbility.h"
#include "../PlayableCharacter.h"

AExplosionMultiplierAbility::AExplosionMultiplierAbility(){
     AbilityName = "Explosion Multiplier Ability";
}

void AExplosionMultiplierAbility::AddAbilityToPlayer(APlayableCharacter *Player){
    UE_LOG(LogTemp, Warning, TEXT("collected ability %s "), *AbilityName);
    if(Player->GetExplosionPower() < Max){
        Player->SetExplosionPower(Player->GetExplosionPower() + ExplosionIncrease);
    }

    HandleDestruction();
}