// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMITEBROS_API AMainMenuGameMode : public AGameModeBase
{
	GENERATED_BODY()

private:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> MainMenuScreen;

	class UUserWidget* MainMenu;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> CharacterSelectScreen;

	class UUserWidget* CharacterSelect;

	UPROPERTY(EditAnywhere, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	TArray<USkeletalMesh*> CharacterMeshes;


	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Scenes, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<class ALevelSequenceActor> MainMenuLevelSequenceActor;

	void PlayMainMenuLevelCutScene();

public:

	UFUNCTION(Blueprintcallable)
	void GoToCharacterSelectScreen();

	USkeletalMesh* GetCharacterMeshAt(int Index) const;

	int GetCharacterArraySize() const;
	
};
