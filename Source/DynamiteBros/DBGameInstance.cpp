#include "DBGameInstance.h"

USkeletalMesh* UDBGameInstance::GetSelectedCharacterMesh() const {
    return SelectedCharacterMesh;
}

void UDBGameInstance::SetSelectedCharacterMesh(USkeletalMesh* SelectedMesh){
    SelectedCharacterMesh = SelectedMesh;
}

FLinearColor UDBGameInstance::GetExplosionColor() const {
    return ExplosionColor;
}

void UDBGameInstance::SetExplosionColor(FLinearColor Color) {
    ExplosionColor = Color;
}