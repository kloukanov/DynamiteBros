// Copyright Epic Games, Inc. All Rights Reserved.

#include "DynamiteBrosGameMode.h"
// #include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "PlayableCharacter.h"
#include "Blueprint/UserWidget.h"
#include "AI/EnemyAIController.h"
#include "DBGameInstance.h"
#include "LevelManager.h"
#include "PlayableCharacterAssets.h"
#include "EngineUtils.h"

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

	UDBGameInstance* GameInstance = Cast<UDBGameInstance>(GetWorld()->GetGameInstance());

    if(GameInstance){

		TArray<FPlayableCharacterAssets> TempMeshArr = GameInstance->GetSpecifiedNumberOfCharacterMeshes(5);
		TArray<FLinearColor> TempColorArr =	GameInstance->GetAllColorsExceptSelected();

		for(int i = 0; i < 5; i++){
			APlayableCharacter* Enemy = GetWorld()->SpawnActor<APlayableCharacter>(EnemyPlayerClass, SpawnPoints[i], FRotator::ZeroRotator);
			Enemy->ChangeCharacterMesh(TempMeshArr[i].CharacterMesh);
			Enemy->SetPlayerIcon(TempMeshArr[i].Picture);
			FString PlayerName = FString("Player Number ");
			PlayerName.AppendInt(i + 1);
			Enemy->SetUpCharacter(PlayerName, TempColorArr[i]);
			// AEnemyAIController* EnemyController = Cast<AEnemyAIController>(Enemy->GetController());
			// if(EnemyController){
			// 	EnemyController->DisableAI();
			// }
		}

		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();

		if(PlayerController){
			PlayerController->SetInputMode(FInputModeGameOnly());

			APlayableCharacter* PlayableCharacter = Cast<APlayableCharacter>(PlayerController->GetPawn());
			if(PlayableCharacter) {
				PlayableCharacter->ChangeCharacterMesh(GameInstance->GetSelectedCharacterMesh());
				PlayableCharacter->SetPlayerIcon(GameInstance->GetSelectedCharacterIcon());
				PlayableCharacter->SetUpCharacter("Player", GameInstance->GetExplosionColor());
				PlayableCharacter->DisableInput(PlayerController);
			}
		}

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayableCharacter::StaticClass(), AllPlayers);
    }

	if(HUD){
        HUD->AddToViewport();
    }

	StartMatch = CreateWidget(GetWorld(), StartMatchScreen);

	if(StartMatch){
		StartMatch->AddToViewport();
	}
}


// temp implementing this function here instead of creating separate gamemode
void ADynamiteBrosGameMode::PawnKilled(APawn* PawnKilled) {

	UE_LOG(LogTemp, Warning, TEXT("THIS PAWN DIED: %s"), *PawnKilled->GetActorNameOrLabel());

	APlayableCharacter* DeadPlayer = Cast<APlayableCharacter>(PawnKilled);
	if(DeadPlayer){
		NotifyActorDeath(DeadPlayer);
	}

	AllPlayers.Remove(PawnKilled);

	if(AllPlayers.Num() == 1) {
		EndGame(AllPlayers[0]);
	}
}

void ADynamiteBrosGameMode::NotifyActorDeath(APlayableCharacter* DeadPlayer) {
	OnActorDeath.Broadcast(DeadPlayer);
}

void ADynamiteBrosGameMode::EnableInputForPlayers(bool bEnable) {

	for (TActorIterator<AEnemyAIController> It(GetWorld()); It; ++It) {
        AEnemyAIController* EnemyController = *It;
        if (EnemyController) {
            bEnable == true ? EnemyController->EnableAI() : EnemyController->DisableAI();
        }
    }

	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	APlayableCharacter* PlayableCharacter = Cast<APlayableCharacter>(PlayerController->GetPawn());

	bEnable == true ? PlayableCharacter->EnableInput(PlayerController) : PlayableCharacter->DisableInput(PlayerController);
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

TArray<AActor*> ADynamiteBrosGameMode::GetAllPlayers() const {
	return AllPlayers;
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