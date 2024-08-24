#include "DBGameInstance.h"
#include "LevelManager.h"
#include "PlayableCharacterAssets.h"
#include "Blueprint/UserWidget.h"

void UDBGameInstance::Init() {
    Super::Init();

    LevelManager = NewObject<ULevelManager>(this);
    LevelManager->Initialize(this);

    if(CharacterAssetsDataTable){
        TArray<FPlayableCharacterAssets*> Rows;
        CharacterAssetsDataTable->GetAllRows(TEXT("Meshes"), Rows);

        for(FPlayableCharacterAssets* Row : Rows){
            CharacterAssets.Add(*Row);
        }
    }
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
    return CharacterAssets[Index].CharacterMesh;
}

UTexture2D* UDBGameInstance::GetCharacterIconAt(int Index) const {
    return CharacterAssets[Index].Picture;
}

UTexture2D* UDBGameInstance::GetSelectedCharacterIcon() const {
    return SelectedCharacterIcon;
}

void UDBGameInstance::SetSelectedCharacterIcon(UTexture2D* SelectedIcon){
    SelectedCharacterIcon = SelectedIcon;
}

int UDBGameInstance::GetCharacterArraySize() const {
    return CharacterAssets.Num();
}

// TODO: exclude selected mesh
TArray<FPlayableCharacterAssets> UDBGameInstance::GetSpecifiedNumberOfCharacterMeshes(int Number) const {
    int Index = FMath::RandRange(0, CharacterAssets.Num()-1);

    TArray<FPlayableCharacterAssets> TempArr;

    for(int i = Index; i < (Index + Number); ++i){
        TempArr.Add(CharacterAssets[i % CharacterAssets.Num()]);
    }
    return TempArr;
}

TArray<FLinearColor> UDBGameInstance::GetAllColorsExceptSelected() const {
    TArray<FLinearColor> TempArr = PossibleColors;
    TempArr.Remove(ExplosionColor);
    return TempArr;
}

void UDBGameInstance::GoToOptionsMenuScreen() {
    OptionsMenu = CreateWidget(GetWorld(), OptionsScreen);
    OptionsMenu->AddToViewport();
}