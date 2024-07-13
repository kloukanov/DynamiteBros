#include "MainMenuGameMode.h"
#include "Blueprint/UserWidget.h"
#include "LevelSequenceActor.h"
#include "LevelSequence.h"
#include "LevelSequencePlayer.h"
#include "MovieSceneSequencePlayer.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

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
    LoadLevelAsync(GameMapLevel);
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

void AMainMenuGameMode::LoadLevelAsync(TSoftObjectPtr<UWorld> Level) {

    FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

    if(CharacterSelect) {
        CharacterSelect->RemoveFromParent();
        CharacterSelect = nullptr;
    }

    LoadingLevel = CreateWidget(GetWorld(), LoadingLevelScreen);
    LoadingLevel->AddToViewport();

    float DelayDuration = 1.0f;

    Streamable.RequestAsyncLoad(Level.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &AMainMenuGameMode::SetSmallDelayForLoading, DelayDuration, Level.GetAssetName()));
}

// very small delay so that if the scene loads really fast the player doesn't just get a screen flash
void AMainMenuGameMode::SetSmallDelayForLoading(float DelayDuration, FString LevelName) {

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, LevelName](){
        OnLevelLoaded(LevelName);
    }, DelayDuration, false);
}

void AMainMenuGameMode::OnLevelLoaded(FString LevelName) {

    if(LoadingLevel) {
        LoadingLevel->RemoveFromParent();
        LoadingLevel = nullptr;
    }
    
    UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName));
}

USkeletalMesh* AMainMenuGameMode::GetCharacterMeshAt(int Index) const {
    return CharacterMeshes[Index];
}

int AMainMenuGameMode::GetCharacterArraySize() const {
    return CharacterMeshes.Num();
}