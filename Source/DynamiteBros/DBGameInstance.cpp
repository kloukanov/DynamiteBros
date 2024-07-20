#include "DBGameInstance.h"
#include "LevelManager.h"

void UDBGameInstance::Init() {
    Super::Init();

    LevelManager = NewObject<ULevelManager>(this);
    LevelManager->Initialize(this);
}

ULevelManager* UDBGameInstance::GetLevelManager() const {
    return LevelManager;
}

TSubclassOf<class UUserWidget> UDBGameInstance::GetLoadingLevelScreen() const {
    return LoadingLevelScreen;
}

TSoftObjectPtr<UWorld> UDBGameInstance::GetMainMenuLevel() const{
    return MainMenuLevel;
}

TSoftObjectPtr<UWorld> UDBGameInstance::GetGameMapLevel() const{
    return GameMapLevel;
}

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

USkeletalMesh* UDBGameInstance::GetCharacterMeshAt(int Index) const {
    return CharacterMeshes[Index];
}

int UDBGameInstance::GetCharacterArraySize() const {
    return CharacterMeshes.Num();
}

// TODO: exclude selected mesh
TArray<USkeletalMesh*> UDBGameInstance::GetSpecifiedNumberOfCharacterMeshes(int Number) const {
    int Index = FMath::RandRange(0, CharacterMeshes.Num()-1);

    TArray<USkeletalMesh*> TempArr;

    for(int i = Index; i < (Index + Number); ++i){
        TempArr.Add(CharacterMeshes[i % CharacterMeshes.Num()]);
    }
    return TempArr;
}

TArray<FLinearColor> UDBGameInstance::GetAllColorsExceptSelected() const {
    TArray<FLinearColor> TempArr = PossibleColors;
    TempArr.Remove(ExplosionColor);
    return TempArr;
}