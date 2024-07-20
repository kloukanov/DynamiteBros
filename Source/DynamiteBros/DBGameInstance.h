#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "DBGameInstance.generated.h"

UCLASS()
class DYNAMITEBROS_API UDBGameInstance : public UGameInstance
{
	GENERATED_BODY()

private:

	USkeletalMesh* SelectedCharacterMesh;
	FLinearColor ExplosionColor;

	UPROPERTY(EditAnywhere, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	TArray<USkeletalMesh*> CharacterMeshes;

	UPROPERTY(EditAnywhere, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	TArray<FLinearColor> PossibleColors;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels", meta = (AllowPrivateAccess = "true"))
    TSoftObjectPtr<UWorld> GameMapLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels", meta = (AllowPrivateAccess = "true"))
    TSoftObjectPtr<UWorld> MainMenuLevel;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Levels", meta = (AllowPrivateAccess = "true"))
	class ULevelManager* LevelManager;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Screens", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UUserWidget> LoadingLevelScreen;

public:

	virtual void Init() override;

	class ULevelManager* GetLevelManager() const;

	TSubclassOf<class UUserWidget> GetLoadingLevelScreen() const; 

	TSoftObjectPtr<UWorld> GetMainMenuLevel() const;

	TSoftObjectPtr<UWorld> GetGameMapLevel() const;

	USkeletalMesh* GetSelectedCharacterMesh() const;

	void SetSelectedCharacterMesh(USkeletalMesh* SelectedMesh);

	FLinearColor GetExplosionColor() const;

	void SetExplosionColor(FLinearColor);

	USkeletalMesh* GetCharacterMeshAt(int Index) const;

	int GetCharacterArraySize() const;

	TArray<USkeletalMesh*> GetSpecifiedNumberOfCharacterMeshes(int Number) const;

	TArray<FLinearColor> GetAllColorsExceptSelected() const;
	
};
