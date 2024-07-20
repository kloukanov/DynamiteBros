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

public:

	USkeletalMesh* GetSelectedCharacterMesh() const;

	void SetSelectedCharacterMesh(USkeletalMesh* SelectedMesh);

	FLinearColor GetExplosionColor() const;

	void SetExplosionColor(FLinearColor);

	USkeletalMesh* GetCharacterMeshAt(int Index) const;

	int GetCharacterArraySize() const;

	TArray<USkeletalMesh*> GetSpecifiedNumberOfCharacterMeshes(int Number) const;

	TArray<FLinearColor> GetAllColorsExceptSelected() const;
	
};
