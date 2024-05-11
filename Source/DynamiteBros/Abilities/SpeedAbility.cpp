// Fill out your copyright notice in the Description page of Project Settings.


#include "SpeedAbility.h"
#include "../PlayableCharacter.h"

ASpeedAbility::ASpeedAbility() {
    AbilityName = "Speed Increase";
}

void ASpeedAbility::AddAbilityToPlayer(APlayableCharacter *Player){
    UE_LOG(LogTemp, Warning, TEXT("collected ability %s and the player speed is: %f"), *AbilityName, Player->GetSpeed());
    if(Player->GetSpeed() < MaxSpeed){
        Player->SetSpeed(Player->GetSpeed() + SpeedIncrease);
    }

    HandleDestruction();
}