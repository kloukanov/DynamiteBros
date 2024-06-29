// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DynamiteBrosGameMode.generated.h"

UCLASS(minimalapi)
class ADynamiteBrosGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADynamiteBrosGameMode();

	virtual void PawnKilled(APawn* PawnKilled);

	UFUNCTION(BlueprintPure)
	APlayableCharacter* GetTheWinner() const;

private:

	virtual void BeginPlay() override;

	TArray<AActor*> AllPlayers;

	void EndGame(AActor* Winner);

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> EndGameScreen;

	APlayableCharacter* TheWinner;
};