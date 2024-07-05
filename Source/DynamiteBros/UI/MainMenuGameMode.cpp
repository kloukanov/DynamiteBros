#include "MainMenuGameMode.h"
#include "Blueprint/UserWidget.h"

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

    CharacterSelect = CreateWidget(GetWorld(), CharacterSelectScreen);

    if(CharacterSelect){
        MainMenu->RemoveFromParent();
        CharacterSelect->AddToViewport();
    }
}

USkeletalMesh* AMainMenuGameMode::GetCharacterMeshAt(int Index) const {
    return CharacterMeshes[Index];
}

int AMainMenuGameMode::GetCharacterArraySize() const {
    return CharacterMeshes.Num();
}