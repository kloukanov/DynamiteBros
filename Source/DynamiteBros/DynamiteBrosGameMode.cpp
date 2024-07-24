// Copyright Epic Games, Inc. All Rights Reserved.

#include "DynamiteBrosGameMode.h"
// #include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "PlayableCharacter.h"
#include "Blueprint/UserWidget.h"
#include "AI/EnemyAIController.h"
#include "DBGameInstance.h"
#include "LevelManager.h"

ADynamiteBrosGameMode::ADynamiteBrosGameMode()
{
	// set default pawn class to our Blueprinted character
	// static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	// if (PlayerPawnBPClass.Class != NULL)
	// {
	// 	DefaultPawnClass = PlayerPawnBPClass.Class;
	// }
}

void ADynamiteBrosGameMode::BeginPlay()
{
    Super::BeginPlay();

	HUD = CreateWidget(GetWorld(), HUDScreen);

    if(HUD){
        HUD->AddToViewport();
    }

	UDBGameInstance* GameInstance = Cast<UDBGameInstance>(GetWorld()->GetGameInstance());

    if(GameInstance){

		TArray<USkeletalMesh*> TempMeshArr = GameInstance->GetSpecifiedNumberOfCharacterMeshes(5);
		TArray<FLinearColor> TempColorArr =	GameInstance->GetAllColorsExceptSelected();

		for(int i = 0; i < 5; i++){
			APlayableCharacter* Enemy = GetWorld()->SpawnActor<APlayableCharacter>(EnemyPlayerClass, SpawnPoints[i], FRotator::ZeroRotator);
			Enemy->ChangeCharacterMesh(TempMeshArr[i]);
			FString PlayerName = FString("Player Number ");
			PlayerName.AppendInt(i + 1);
			Enemy->SetUpCharacter(PlayerName, TempColorArr[i]);
		}

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if(PlayerController){
			PlayerController->SetInputMode(FInputModeGameOnly());

			APlayableCharacter* PlayableCharacter = Cast<APlayableCharacter>(PlayerController->GetPawn());
			if(PlayableCharacter) {
				PlayableCharacter->ChangeCharacterMesh(GameInstance->GetSelectedCharacterMesh());
				PlayableCharacter->SetUpCharacter("Player", GameInstance->GetExplosionColor());
			}
		}

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayableCharacter::StaticClass(), AllPlayers);
    }
}


// temp implementing this function here instead of creating separate gamemode
void ADynamiteBrosGameMode::PawnKilled(APawn* PawnKilled) {

	UE_LOG(LogTemp, Warning, TEXT("THIS PAWN DIED: %s"), *PawnKilled->GetActorNameOrLabel());

	AllPlayers.Remove(PawnKilled);

	if(AllPlayers.Num() == 1) {
		EndGame(AllPlayers[0]);
	}
}

void ADynamiteBrosGameMode::EndGame(AActor* Winner) {

	TheWinner = Cast<APlayableCharacter>(Winner);

	if(TheWinner){
		UE_LOG(LogTemp, Warning, TEXT("THE WINNER IS: %s"), *TheWinner->GetPlayerName());

		GameOverScreen = CreateWidget(GetWorld(), EndGameScreen);

		if(GameOverScreen){
			GameOverScreen->AddToViewport();
			PauseGame(true);
		}

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if(PlayerController){
			PlayerController->SetInputMode(FInputModeUIOnly());
		}
	}
}

APlayableCharacter* ADynamiteBrosGameMode::GetTheWinner() const {
	return TheWinner;
}

void ADynamiteBrosGameMode::PauseGame(bool bShouldPause) {
	UGameplayStatics::SetGamePaused(GetWorld(), bShouldPause);
}

void ADynamiteBrosGameMode::GoToMainMenu() {
	if(GameOverScreen){
		GameOverScreen->RemoveFromParent();
        GameOverScreen = nullptr;
	}

	PauseGame(false);

	UDBGameInstance* GameInstance = Cast<UDBGameInstance>(GetWorld()->GetGameInstance());

	GameInstance->GetLevelManager()->LoadLevelAsync(GameInstance->GetMainMenuLevel());
}

void ADynamiteBrosGameMode::TogglePauseGame() {

	bool bGamePaused = UGameplayStatics::IsGamePaused(this);

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

	if(!bGamePaused){
		PauseGameWidget = CreateWidget(GetWorld(), PauseGameScreen);

		if(PauseGameWidget){
			PauseGameWidget->AddToViewport();
		}

		if(PlayerController){
			PlayerController->SetShowMouseCursor(true);
			PlayerController->SetInputMode(FInputModeGameAndUI());
		}

		PauseGame(true);

	}else {

		PauseGame(false);

		if(PauseGameWidget){
			PauseGameWidget->RemoveFromParent();
			PauseGameWidget = nullptr;
		}

		if(PlayerController){
			PlayerController->SetShowMouseCursor(false);
		}

		if(PlayerController){
			PlayerController->SetInputMode(FInputModeGameOnly());
		}
	}
}