// Copyright Epic Games, Inc. All Rights Reserved.

#include "DynamiteBrosGameMode.h"
#include "DynamiteBrosCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "AI/EnemyAIController.h"
#include "EngineUtils.h"

ADynamiteBrosGameMode::ADynamiteBrosGameMode()
{
	// set default pawn class to our Blueprinted character
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	// if (PlayerPawnBPClass.Class != NULL)
	// {
	// 	DefaultPawnClass = PlayerPawnBPClass.Class;
	// }
}

// temp implementing this function here instead of creating separate gamemode
void ADynamiteBrosGameMode::PawnKilled(APawn* PawnKilled) {

	UE_LOG(LogTemp, Warning, TEXT("THIS PAWN DIED: %s"), *PawnKilled->GetActorNameOrLabel());

}

void ADynamiteBrosGameMode::EndGame(bool bIsPlayerWinner) {

}