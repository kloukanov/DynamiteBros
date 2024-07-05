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
    ChangeCharacterMesh((++CurrentMeshIndex) % ArraySize);
}

void UCharacterSelectUserWidget::GoPrev() {
    if(CurrentMeshIndex == 0){
        CurrentMeshIndex = ArraySize;
    }
    ChangeCharacterMesh((--CurrentMeshIndex) % ArraySize);
}

void UCharacterSelectUserWidget::GoBack() {
    // TODO: implement
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