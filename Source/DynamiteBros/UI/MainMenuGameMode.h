#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainMenuGameMode.generated.h"


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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Scenes, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<class ALevelSequenceActor> BackToMainMenuLevelSequenceActor;

	class ULevelSequencePlayer* LevelSequencePlayer;

	void PlayCutScene(TSoftObjectPtr<class ALevelSequenceActor> SceneActor);

	// TODO: probably move these in a level manager class

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Level", meta = (AllowPrivateAccess = "true"))
    TSoftObjectPtr<UWorld> GameMapLevel;

	class UUserWidget* LoadingLevel;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> LoadingLevelScreen;

	void LoadLevelAsync(TSoftObjectPtr<UWorld> Level);

	void OnLevelLoaded(FString LevelName);

	void SetSmallDelayForLoading(float DelayDuration, FString LevelName);

	// --------------------------------------------------

public:

	UFUNCTION(Blueprintcallable)
	void GoToCharacterSelectScreen();

	UFUNCTION(Blueprintcallable)
	void GoToMainMenu();

	void GoToPlayGame();

	USkeletalMesh* GetCharacterMeshAt(int Index) const;

	int GetCharacterArraySize() const;
	
};
