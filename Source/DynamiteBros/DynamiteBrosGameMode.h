// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DynamiteBrosGameMode.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnActorDeath, APlayableCharacter*, DeadPlayer);

UCLASS(minimalapi)
class ADynamiteBrosGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ADynamiteBrosGameMode();

	virtual void PawnKilled(APawn* PawnKilled);

	UFUNCTION(BlueprintPure)
	APlayableCharacter* GetTheWinner() const;

	UFUNCTION(Blueprintcallable)
	void GoToMainMenu();

	UFUNCTION(Blueprintcallable)
	void TogglePauseGame();

	UFUNCTION(Blueprintcallable)
	TArray<AActor*> GetAllPlayers() const;

	UPROPERTY(BlueprintAssignable, Category = "Events")
	FOnActorDeath OnActorDeath;

	void NotifyActorDeath(APlayableCharacter* DeadPlayer);

private:

	FVector SpawnPoints[5] = { 
		FVector(-695.f, -973.f, 88.f), 
		FVector(-695.f, 970.f, 88.f), 
		FVector(1170.f, 970.f, 88.f), 
		FVector(790.f, 16.f, 88.f), 
		FVector(-372.f, 16.f, 88.f), 	
	};

	class UUserWidget* GameOverScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> EndGameScreen;

	class UUserWidget* HUD;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDScreen;

	class UUserWidget* PauseGameWidget;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> PauseGameScreen;

	virtual void BeginPlay() override;

	TArray<AActor*> AllPlayers;

	void EndGame(AActor* Winner);

	APlayableCharacter* TheWinner;

	void PauseGame(bool bShouldPause);

	UPROPERTY(EditDefaultsOnly, Category = EnemyPlayer)
	TSubclassOf<class APlayableCharacter> EnemyPlayerClass;
};