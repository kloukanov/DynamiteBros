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

public:

	USkeletalMesh* GetSelectedCharacterMesh() const;

	void SetSelectedCharacterMesh(USkeletalMesh* SelectedMesh);

	FLinearColor GetExplosionColor() const;

	void SetExplosionColor(FLinearColor);
	
};
