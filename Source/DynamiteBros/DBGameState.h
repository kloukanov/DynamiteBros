#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "DBGameState.generated.h"

UCLASS()
class DYNAMITEBROS_API ADBGameState : public AGameStateBase
{
	GENERATED_BODY()

private:

	USkeletalMesh* SelectedCharacterMesh;

public:

	USkeletalMesh* GetSelectedCharacterMesh() const;

	void SetSelectedCharacterMesh(USkeletalMesh* SelectedMesh);

};
