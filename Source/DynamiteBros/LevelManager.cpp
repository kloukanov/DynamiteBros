#include "LevelManager.h"
#include "DBGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Engine/StreamableManager.h"
#include "Engine/AssetManager.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ULevelManager::ULevelManager() {}


void ULevelManager::Initialize(UGameInstance* DBGameInstance) {
    GameInstance = Cast<UDBGameInstance>(DBGameInstance);
}


void ULevelManager::LoadLevelAsync(TSoftObjectPtr<UWorld> Level) {

    FStreamableManager& Streamable = UAssetManager::GetStreamableManager();

    LoadingLevel = CreateWidget(GetWorld(), GameInstance->GetLoadingLevelScreen());
    LoadingLevel->AddToViewport();

    float DelayDuration = 1.0f;

    Streamable.RequestAsyncLoad(Level.ToSoftObjectPath(), FStreamableDelegate::CreateUObject(this, &ULevelManager::SetSmallDelayForLoading, DelayDuration, Level.GetAssetName()));
}

// very small delay so that if the scene loads really fast the player doesn't just get a screen flash
void ULevelManager::SetSmallDelayForLoading(float DelayDuration, FString LevelName) {

    FTimerHandle TimerHandle;
    GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, LevelName](){
        OnLevelLoaded(LevelName);
    }, DelayDuration, false);
}

void ULevelManager::OnLevelLoaded(FString LevelName) {

    if(LoadingLevel) {
        LoadingLevel->RemoveFromParent();
        LoadingLevel = nullptr;
    }
    
    UGameplayStatics::OpenLevel(GetWorld(), FName(LevelName));
}