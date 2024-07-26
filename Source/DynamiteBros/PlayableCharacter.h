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

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* PauseGameInputAction;

	// dynamite spawn point
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USceneComponent* DynamiteSpawnPoint;

	// ref to BP Dynamite class
	UPROPERTY(EditDefaultsOnly, Category = Dynamite)
	TSubclassOf<class ADynamite> DynamiteClass;

	UPROPERTY(EditDefaultsOnly, Category = Explosion, meta = (AllowPrivateAccess = "true"))
	int ExplosionPower = 200;

	UPROPERTY(EditAnywhere, Category = Explosion, meta = (AllowPrivateAccess = "true"))
	FLinearColor ExplosionColor;

	UPROPERTY(EditAnywhere, Category = Explosion, meta = (AllowPrivateAccess = "true"))
	int DynamiteCount = 1;

	UPROPERTY(EditAnywhere, Category = Player, meta = (AllowPrivateAccess = "true"))
	FString PlayerName;

	UPROPERTY(EditAnywhere, Category = Light, meta = (AllowPrivateAccess = "true"))
	class UPointLightComponent* PointLightComponent;

	UTexture2D* PlayerIcon;

	bool bIsDead;

public:
	// Sets default values for this character's properties
	APlayableCharacter();

	void SetSpeed(float Speed);

	float GetSpeed() const;

	int GetExplosionPower() const;

	void SetExplosionPower(int ExplosionPower);

	UFUNCTION(BlueprintPure)
	FLinearColor GetExplosionColor() const;

	void SetExplosionColor(FLinearColor Color);

	int GetDynamiteCount() const;

	UFUNCTION(BlueprintPure)
	FString GetPlayerName() const;

	void SetPlayerName(FString PlayerName);

	UFUNCTION(BlueprintPure)
	UTexture2D* GetPlayerIcon() const;

	void SetPlayerIcon(UTexture2D* Icon);

	void AddDynamite();

	void RemoveDynamite();

	UFUNCTION(BlueprintCallable)
	bool GetIsDead() const;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// movement input
	void Move(const struct FInputActionValue& Value);

	void PauseGame();

public:	

	// drop dynamite input
	void Drop();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void DamageCharacter();

	void SetUpCharacter(FString Name, FLinearColor Color);

	void ChangeCharacterMesh(USkeletalMesh* CharMesh);

};
