// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayableCharacter.generated.h"

UCLASS()
class DYNAMITEBROS_API APlayableCharacter : public ACharacter
{
	GENERATED_BODY()

	// input mapping context
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* InputMappingContext;

	// move input action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveInputAction;

	// drop dynamite input action
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* DropInputAction;

	// dynamite spawn point
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USceneComponent* DynamiteSpawnPoint;

	// ref to BP Dynamite class
	UPROPERTY(EditDefaultsOnly, Category = Dynamite)
	TSubclassOf<class ADynamite> DynamiteClass;

public:
	// Sets default values for this character's properties
	APlayableCharacter();

	void SetSpeed(float Speed);

	float GetSpeed() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// movement input
	void Move(const struct FInputActionValue& Value);

	// drop dynamite input
	void Drop();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
