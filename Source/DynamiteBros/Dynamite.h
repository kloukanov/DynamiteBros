// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dynamite.generated.h"

UCLASS()
class DYNAMITEBROS_API ADynamite : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamite();

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
	class UStaticMeshComponent* DynamiteMesh;

	UPROPERTY(VisibleAnywhere, Category = Components)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	void Explode();

};
