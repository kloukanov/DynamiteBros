#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "LevelManager.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMITEBROS_API ULevelManager : public UObject
{
	GENERATED_BODY()

private:
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game Instance", meta = (AllowPrivateAccess = "true"))
	class UDBGameInstance* GameInstance;

	class UUserWidget* LoadingLevel;

public:
	ULevelManager();

	void Initialize(UGameInstance* GameInstance);

	void LoadLevelAsync(TSoftObjectPtr<UWorld> Level);

	void OnLevelLoaded(FString LevelName);

	void SetSmallDelayForLoading(float DelayDuration, FString LevelName);
	
};
