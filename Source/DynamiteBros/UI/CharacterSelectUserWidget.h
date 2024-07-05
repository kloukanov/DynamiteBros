// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacterSelectUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class DYNAMITEBROS_API UCharacterSelectUserWidget : public UUserWidget
{
	GENERATED_BODY()

private:

	class AMainMenuGameMode* GameMode;

	int CurrentMeshIndex = 0;

	int ArraySize = 0;

	void ChangeCharacterMesh(int MeshIndex);

public:

	UFUNCTION(Blueprintcallable)
	void GoNext();

	UFUNCTION(Blueprintcallable)
	void GoPrev();

	UFUNCTION(Blueprintcallable)
	void GoBack();

	virtual void NativeConstruct() override;
	
};
