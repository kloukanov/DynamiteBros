#include "Dynamite.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DestructibleComponent.h"
#include "Obstacle.h"
#include "DrawDebugHelpers.h"

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
	
	// will move to tick later and have a countdown and anim
	Explode();
}

void ADynamite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool ADynamite::HasExplosionHitAnyActors(FVector StartLocation, FVector EndLocation, FVector Offset, TArray<FHitResult> &OutHitActors) {
	
	TArray<FHitResult> AllActors;

	FVector TempOffset = Offset;

	for(int i = 0; i < 3; i++) {
		GetWorld()->LineTraceMultiByChannel(OutHitActors, StartLocation + TempOffset, EndLocation + TempOffset, ECollisionChannel::ECC_GameTraceChannel1);
		DrawDebugLine(GetWorld(), StartLocation + TempOffset, EndLocation + TempOffset, FColor::Red, true, 5);
		TempOffset = TempOffset - Offset;
		AllActors.Append(OutHitActors);
	}

	OutHitActors = AllActors;

	return AllActors.Num() > 0;
}

void ADynamite::Explode() {

	FVector StartLocation = GetActorLocation();

	int power = 600;

	FVector EndLocationNorth = StartLocation + FVector(power, 0, 0);
	FVector EndLocationSouth = StartLocation - FVector(power, 0, 0);
	FVector EndLocationEast = StartLocation + FVector(0, power, 0);
	FVector EndLocationWest = StartLocation - FVector(0, power, 0);
	FVector OffsetY(0, 20.f, 0);
	FVector OffsetX(20.f, 0, 0);

	TArray<FHitResult> TotalHitActors;

	TArray<FHitResult> HitActorsNorth;
	TArray<FHitResult> HitActorsSouth;
	TArray<FHitResult> HitActorsEast;
	TArray<FHitResult> HitActorsWest;


	bool bHitSomethingNorth = HasExplosionHitAnyActors(StartLocation, EndLocationNorth, OffsetY, HitActorsNorth);
	bool bHitSomethingSouth = HasExplosionHitAnyActors(StartLocation, EndLocationSouth, -(OffsetY), HitActorsSouth);

	bool bHitSomethingEast = HasExplosionHitAnyActors(StartLocation, EndLocationEast, OffsetX, HitActorsEast);
	bool bHitSomethingWest = HasExplosionHitAnyActors(StartLocation, EndLocationWest, -(OffsetX), HitActorsWest);

	TotalHitActors.Append(HitActorsNorth);
	TotalHitActors.Append(HitActorsSouth);
	TotalHitActors.Append(HitActorsEast);
	TotalHitActors.Append(HitActorsWest);

	if(TotalHitActors.Num() > 0){
		HandleExplosionCollision(TotalHitActors);
	}

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

			// TODO: come back to this to include the destructible component logic 

			// UActorComponent * ActorComponent  =  HitActor->GetComponentByClass(UDestructibleComponent::StaticClass());
			// if(ActorComponent){
			// 	UE_LOG(LogTemp, Warning, TEXT("we in here with the actor component breh %s"), *HitActor->GetActorNameOrLabel());
			// }
		}
	}
}
