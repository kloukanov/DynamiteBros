#include "DBGameState.h"

USkeletalMesh* ADBGameState::GetSelectedCharacterMesh() const {
    return SelectedCharacterMesh;
}

void ADBGameState::SetSelectedCharacterMesh(USkeletalMesh* SelectedMesh){
    SelectedCharacterMesh = SelectedMesh;
}