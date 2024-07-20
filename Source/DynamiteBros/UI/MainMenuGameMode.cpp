#include "MainMenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "LevelSequenceActor.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlayer.h"
#include "../DBGameInstance.h"
#include "../LevelManager.h"

void AMainMenuGameMode::BeginPlay() {

    Super::BeginPlay();

    MainMenu = CreateWidget(GetWorld(), MainMenuScreen);

    if(MainMenu){
        MainMenu->AddToViewport();
    }

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if(PlayerController){
        PlayerController->SetInputMode(FInputModeUIOnly());
        PlayerController->SetShowMouseCursor(true);
    }
}

void AMainMenuGameMode::GoToCharacterSelectScreen() {

    PlayCutScene(MainMenuLevelSequenceActor);

    CharacterSelect = CreateWidget(GetWorld(), CharacterSelectScreen);

    if(CharacterSelect){
        MainMenu->RemoveFromParent();
        MainMenu = nullptr;
        CharacterSelect->AddToViewport();
    }
}

void AMainMenuGameMode::GoToMainMenu() {
    
    PlayCutScene(BackToMainMenuLevelSequenceActor);

    if(CharacterSelect){
        CharacterSelect->RemoveFromParent();
        CharacterSelect = nullptr;

        MainMenu = CreateWidget(GetWorld(), MainMenuScreen);

        if(MainMenu){
            MainMenu->AddToViewport();
        }
    }
}

void AMainMenuGameMode::GoToPlayGame() {
    if(CharacterSelect) {
        CharacterSelect->RemoveFromParent();
        CharacterSelect = nullptr;
    }

    UDBGameInstance* GameInstance = Cast<UDBGameInstance>(GetWorld()->GetGameInstance());
    GameInstance->GetLevelManager()->LoadLevelAsync(GameInstance->GetGameMapLevel());

}

void AMainMenuGameMode::PlayCutScene(TSoftObjectPtr<ALevelSequenceActor> SceneActor) {

    if(SceneActor.IsValid()){

        ALevelSequenceActor* SceneActorReference = SceneActor.Get();

        if(!LevelSequencePlayer){
            FMovieSceneSequencePlaybackSettings PlaybackSettings;
            ULevelSequence* LevelSequence = SceneActorReference->GetSequence();
            LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
                GetWorld(),
                LevelSequence,
                PlaybackSettings,
                SceneActorReference
            );
        }
        else {
            // LevelSequencePlayer is already created
            ULevelSequence* LevelSequence = SceneActorReference->GetSequence();
            LevelSequencePlayer->Initialize(LevelSequence, GetWorld()->GetCurrentLevel(), FLevelSequenceCameraSettings());
        }

        if (LevelSequencePlayer) {
            LevelSequencePlayer->Play();
        };
    }
}