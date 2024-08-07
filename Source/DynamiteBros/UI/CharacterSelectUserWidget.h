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

	class UDBGameInstance* GameInstance;

	int CurrentMeshIndex = 0;

	int ArraySize = 0;

	FLinearColor SelectedColor;

	void ChangeCharacterMesh(int MeshIndex);

public:

	UFUNCTION(Blueprintcallable)
	void GoNext();

	UFUNCTION(Blueprintcallable)
	void GoPrev();

	UFUNCTION(Blueprintcallable)
	void GoBack();

	UFUNCTION(Blueprintcallable)
	void GoPlayGame();

	UFUNCTION(Blueprintcallable)
	void ChangeCharacterColor(FLinearColor Color);

	virtual void NativeConstruct() override;
	
};
