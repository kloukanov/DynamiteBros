#include "CharacterSelectUserWidget.h"
#include "../PlayableCharacter.h"
#include "MainMenuGameMode.h"


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
            PlayableCharacter->ChangeCharacterMesh(CharMesh);
        }
    }
}

void UCharacterSelectUserWidget::ChangeCharacterColor(FLinearColor Color) {

    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

    if(PlayerController){
        APlayableCharacter* PlayableCharacter = Cast<APlayableCharacter>(PlayerController->GetPawn());
        if(PlayableCharacter) {
            PlayableCharacter->SetUpCharacter("Player", Color);
        }
    }
}