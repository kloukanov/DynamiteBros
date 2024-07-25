#pragma once

#include "CoreMinimal.h"
#include "PlayableCharacterAssets.generated.h"

USTRUCT(BlueprintType)
struct FPlayableCharacterAssets : public FTableRowBase {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	USkeletalMesh* CharacterMesh;

	UPROPERTY(EditAnywhere, Category = Meshes, meta = (AllowPrivateAccess = "true"))
	UTexture2D* Picture;
};