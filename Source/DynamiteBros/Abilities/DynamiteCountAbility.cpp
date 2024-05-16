// Fill out your copyright notice in the Description page of Project Settings.


#include "DynamiteCountAbility.h"
#include "../PlayableCharacter.h"

ADynamiteCountAbility::ADynamiteCountAbility() {
    AbilityName = "Dynamite Count Ability";
}

void ADynamiteCountAbility::AddAbilityToPlayer(APlayableCharacter &Player) {
    UE_LOG(LogTemp, Warning, TEXT("collected ability %s "), *AbilityName);
    Player.AddDynamite();
    HandleDestruction();
}

