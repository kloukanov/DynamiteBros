#include "CharacterSelectUserWidget.h"
#include "../PlayableCharacter.h"
#include "MainMenuGameMode.h"
#include "../DBGameInstance.h"


void UCharacterSelectUserWidget::NativeConstruct() {
    Super::NativeConstruct();
    GameMode = GetWorld()->GetAuthGameMode<AMainMenuGameMode>();
    ArraySize = GameMode->GetCharacterArraySize();
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
	
    USkeletalMesh* CharMesh = GameMode->GetCharacterMeshAt(MeshIndex);

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

    UDBGameInstance* GameInstance = Cast<UDBGameInstance>(GetWorld()->GetGameInstance());

    if(GameInstance){
        GameInstance->SetSelectedCharacterMesh(GameMode->GetCharacterMeshAt(CurrentMeshIndex));
        GameInstance->SetExplosionColor(SelectedColor);
    }

    GameMode->GoToPlayGame();
}