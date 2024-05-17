// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Obstacle.generated.h"

UCLASS()
class DYNAMITEBROS_API AObstacle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObstacle();

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(VisibleAnywhere, Category = Components)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* ObstacleMesh;

	UPROPERTY(EditAnywhere, Category = Destructible)
	bool IsDestructible;

	// ability spawn point
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Components, meta = (AllowPrivateAccess = "true"))
	USceneComponent* AbilitySpawnPoint;

	UPROPERTY(EditAnywhere, Category = Ability, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class UAbilityFactory> AbilityFactoryClass;

	UPROPERTY(EditAnywhere, Category = Ability, meta = (AllowPrivateAccess = "true"))
	int SpawnProbability = 3;

	void SpawnAbility();
};
