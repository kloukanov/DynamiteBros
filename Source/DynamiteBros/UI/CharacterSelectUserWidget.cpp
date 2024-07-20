#include "CharacterSelectUserWidget.h"
#include "../PlayableCharacter.h"
#include "MainMenuGameMode.h"
#include "../DBGameInstance.h"


void UCharacterSelectUserWidget::NativeConstruct() {
    Super::NativeConstruct();
    GameInstance = Cast<UDBGameInstance>(GetWorld()->GetGameInstance());
    GameMode = GetWorld()->GetAuthGameMode<AMainMenuGameMode>();
    ArraySize = GameInstance->GetCharacterArraySize();
    ChangeCharacterMesh(CurrentMeshIndex);
}

void UCharacterSelectUserWidget::GoNext() {

    CurrentMeshIndex++;

    if(CurrentMeshIndex > ArraySize - 1) {
        CurrentMeshIndex = 0;
    }
    ChangeCharacterMesh(CurrentMeshIndex);
}

void UCharacterSelectUserWidget::GoPrev() {

    CurrentMeshIndex--;

    if(CurrentMeshIndex < 0){
        CurrentMeshIndex = ArraySize - 1;
    }
    ChangeCharacterMesh(CurrentMeshIndex);
}

void UCharacterSelectUserWidget::GoBack() {
    GameMode->GoToMainMenu();
}

void UCharacterSelectUserWidget::ChangeCharacterMesh(int MeshIndex) {
	
    USkeletalMesh* CharMesh = GameInstance->GetCharacterMeshAt(MeshIndex);

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if(PlayerController){
        APlayableCharacter* PlayableCharacter = Cast<APlayableCharacter>(PlayerController->GetPawn());
        if(PlayableCharacter) {
            SelectedColor = PlayableCharacter->GetExplosionColor();
            PlayableCharacter->ChangeCharacterMesh(CharMesh);
        }
    }
}

void UCharacterSelectUserWidget::ChangeCharacterColor(FLinearColor Color) {

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if(PlayerController){
        APlayableCharacter* PlayableCharacter = Cast<APlayableCharacter>(PlayerController->GetPawn());
        if(PlayableCharacter) {
            SelectedColor = Color;
            PlayableCharacter->SetUpCharacter("Player", Color);
        }
    }
}

void UCharacterSelectUserWidget::GoPlayGame() {

    if(GameInstance){
        GameInstance->SetSelectedCharacterMesh(GameInstance->GetCharacterMeshAt(CurrentMeshIndex));
        GameInstance->SetExplosionColor(SelectedColor);
    }

    GameMode->GoToPlayGame();
}