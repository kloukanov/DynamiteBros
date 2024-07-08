#include "MainMenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "LevelSequenceActor.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlayer.h"

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

    PlayMainMenuLevelCutScene();

    CharacterSelect = CreateWidget(GetWorld(), CharacterSelectScreen);

    if(CharacterSelect){
        MainMenu->RemoveFromParent();
        CharacterSelect->AddToViewport();
    }
}

void AMainMenuGameMode::PlayMainMenuLevelCutScene() {
    if(MainMenuLevelSequenceActor.IsValid()){

        ALevelSequenceActor* MainMenuLevelSequenceActorReference = MainMenuLevelSequenceActor.Get();

        FMovieSceneSequencePlaybackSettings PlaybackSettings;
        ULevelSequence* MainMenuSequence = MainMenuLevelSequenceActorReference->GetSequence();
        ULevelSequencePlayer* LevelSequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(
            GetWorld(),
            MainMenuSequence,
            PlaybackSettings,
            MainMenuLevelSequenceActorReference
        );
        LevelSequencePlayer->Play();
    }
}

USkeletalMesh* AMainMenuGameMode::GetCharacterMeshAt(int Index) const {
    return CharacterMeshes[Index];
}

int AMainMenuGameMode::GetCharacterArraySize() const {
    return CharacterMeshes.Num();
}