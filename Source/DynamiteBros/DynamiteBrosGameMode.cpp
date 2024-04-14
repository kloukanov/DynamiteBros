// Copyright Epic Games, Inc. All Rights Reserved.

#include "DynamiteBrosGameMode.h"
#include "DynamiteBrosCharacter.h"
#include "UObject/ConstructorHelpers.h"

ADynamiteBrosGameMode::ADynamiteBrosGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
