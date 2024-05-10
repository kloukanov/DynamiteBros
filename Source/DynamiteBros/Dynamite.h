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

	UPROPERTY(EditAnywhere, Category = Traces)
	bool ShowTraceLines = false;

private:

	UPROPERTY(VisibleAnywhere, Category = Components)
	class UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, Category = Mesh)
	class UStaticMeshComponent* DynamiteMesh;

	UPROPERTY(VisibleAnywhere, Category = Components)
	class UProjectileMovementComponent* ProjectileMovementComponent;

	void Explode();

	void DoExplosion(FVector StartLocation, FVector EndLocation, FVector Offset, TArray<FHitResult> &OutHitActors);

	void HandleExplosionCollision(TArray<FHitResult> OutHitActors);

	void SpawnExplosionEffect(FRotator Rotation);

	UPROPERTY(EditDefaultsOnly, Category = Explosion)
	FVector ExplosionLineTraceOffsetY = FVector(0, 20.f, 0);

	UPROPERTY(EditDefaultsOnly, Category = Explosion)
	FVector ExplosionLineTraceOffsetX = FVector(20.f, 0, 0);

	UPROPERTY(EditDefaultsOnly, Category = Explosion)
	int ExplosionPower = 600;

	UPROPERTY(EditDefaultsOnly, Category = Explosion)
	float ExplosionTimer = 3.f;

	UPROPERTY(EditAnywhere, Category = Explosion, meta = (AllowPrivateAccess = "true"))
	class UNiagaraSystem* ExplosionEffect;

	UPROPERTY(EditAnywhere, Category = Explosion, meta = (AllowPrivateAccess = "true"))
	FLinearColor ExplosionColor;

	FTimerHandle ExplosionTimerHandle;

};
