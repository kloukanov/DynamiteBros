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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Scenes, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<class ALevelSequenceActor> MainMenuLevelSequenceActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Scenes, meta = (AllowPrivateAccess = "true"))
	TSoftObjectPtr<class ALevelSequenceActor> BackToMainMenuLevelSequenceActor;

	class ULevelSequencePlayer* LevelSequencePlayer;

	void PlayCutScene(TSoftObjectPtr<class ALevelSequenceActor> SceneActor);

public:

	UFUNCTION(Blueprintcallable)
	void GoToCharacterSelectScreen();

	UFUNCTION(Blueprintcallable)
	void GoToMainMenu();

	void GoToPlayGame();
	
};
