#include "Dynamite.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Obstacle.h"
#include "DrawDebugHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

ADynamite::ADynamite()
{
 	
	PrimaryActorTick.bCanEverTick = false; // turn off for now

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComponent;

	DynamiteMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Dynamite Mesh"));
	DynamiteMesh->SetupAttachment(BoxComponent);

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->MaxSpeed = 200.f;
	ProjectileMovementComponent->InitialSpeed = 1.f;

}

void ADynamite::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(ExplosionTimerHandle, this, &ADynamite::Explode, ExplosionTimer, false);
}

void ADynamite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADynamite::Explode() {

	FVector StartLocation = GetActorLocation();

	TArray<FHitResult> TotalHitActors;

	DoExplosion(StartLocation, StartLocation + FVector(ExplosionPower, 0, 0), ExplosionLineTraceOffsetY, TotalHitActors); // north
	DoExplosion(StartLocation, StartLocation - FVector(ExplosionPower, 0, 0), -(ExplosionLineTraceOffsetY), TotalHitActors); // south
	DoExplosion(StartLocation, StartLocation + FVector(0, ExplosionPower, 0), ExplosionLineTraceOffsetX, TotalHitActors); // east
	DoExplosion(StartLocation, StartLocation - FVector(0, ExplosionPower, 0), -(ExplosionLineTraceOffsetX), TotalHitActors); // west

	if(TotalHitActors.Num() > 0){
		HandleExplosionCollision(TotalHitActors);
	}

	Destroy();
}

void ADynamite::DoExplosion(FVector StartLocation, FVector EndLocation, FVector Offset, TArray<FHitResult> &OutHitActors) {
	
	TArray<FHitResult> AllActors;

	FVector TempOffset = Offset;

	FVector ExplosionDirection = ((StartLocation + TempOffset) - (EndLocation + TempOffset)).GetSafeNormal();
	
	SpawnExplosionEffect(ExplosionDirection.Rotation());

	for(int i = 0; i < 3; i++) {
		TArray<FHitResult> TempHitActors;

		GetWorld()->LineTraceMultiByChannel(TempHitActors, StartLocation + TempOffset, EndLocation + TempOffset, ECollisionChannel::ECC_GameTraceChannel1);
		DrawDebugLine(GetWorld(), StartLocation + TempOffset, EndLocation + TempOffset, FColor::Red, true, 5);

		AllActors.Append(TempHitActors);
		TempHitActors.Empty();
		TempOffset -= Offset;
	}

	OutHitActors.Append(AllActors);
}

void ADynamite::HandleExplosionCollision(TArray<FHitResult> OutHitActors) {
	for(int i = 0; i < OutHitActors.Num(); i++) {
		AActor* HitActor = OutHitActors[i].GetActor();
		
		if(HitActor){
			UE_LOG(LogTemp, Warning, TEXT("we hit an actor with name %s"), *HitActor->GetActorNameOrLabel());

			AObstacle *HitObstacle = Cast<AObstacle>(HitActor);

			if(HitObstacle){
				HitObstacle->HandleDestruction();
			} 
		}
	}
}

void ADynamite::SpawnExplosionEffect(FRotator Rotation) {
	if(ExplosionEffect) {
			UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation(), Rotation);
	}
}