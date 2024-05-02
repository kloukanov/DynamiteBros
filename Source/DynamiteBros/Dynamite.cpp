#include "Dynamite.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "DestructibleComponent.h"

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

bool ADynamite::HasExplosionHitAnyActors(FVector StartLocation, FVector EndLocation, FVector BoxSize, TArray<FHitResult, FDefaultAllocator> &OutHitActors) {

	TArray<AActor* , FDefaultAllocator> IgnoreActors;

	bool result =
	UKismetSystemLibrary::BoxTraceMulti
	(
		this, 
		StartLocation, 
		EndLocation, 
		BoxSize, 
		FRotator::ZeroRotator, 
		ETraceTypeQuery::TraceTypeQuery1, // take a look at the collision settings later
		false, 
		IgnoreActors, 
		EDrawDebugTrace::Persistent, 
		OutHitActors, 
		true
	);

	return result;
}

void ADynamite::Explode() {

	FVector StartLocation = GetActorLocation();

	int power = 600;

	FVector EndLocationNorth = StartLocation + FVector(power, 0, 0);
	FVector EndLocationSouth = StartLocation - FVector(power, 0, 0);
	FVector EndLocationEast = StartLocation + FVector(0, power, 0);
	FVector EndLocationWest = StartLocation - FVector(0, power, 0);
	FVector ExplosionSize(50, 50, 30);

	TArray<FHitResult , FDefaultAllocator> TotalHitActors;

	TArray<FHitResult, FDefaultAllocator> HitActorsNorth;
	TArray<FHitResult, FDefaultAllocator> HitActorsSouth;
	TArray<FHitResult, FDefaultAllocator> HitActorsEast;
	TArray<FHitResult, FDefaultAllocator> HitActorsWest;


	bool bHitSomethingNorth = HasExplosionHitAnyActors(StartLocation, EndLocationNorth, ExplosionSize, HitActorsNorth);
	bool bHitSomethingSouth = HasExplosionHitAnyActors(StartLocation, EndLocationSouth, ExplosionSize, HitActorsSouth);

	bool bHitSomethingEast = HasExplosionHitAnyActors(StartLocation, EndLocationEast, ExplosionSize, HitActorsEast);
	bool bHitSomethingWest = HasExplosionHitAnyActors(StartLocation, EndLocationWest, ExplosionSize, HitActorsWest);

	TotalHitActors.Append(HitActorsNorth);
	TotalHitActors.Append(HitActorsSouth);
	TotalHitActors.Append(HitActorsEast);
	TotalHitActors.Append(HitActorsWest);

	if(TotalHitActors.Num() > 0){
		HandleExplotionCollision(TotalHitActors);
	}

}

void ADynamite::HandleExplotionCollision(TArray<FHitResult, FDefaultAllocator> OutHitActors) {
	for(int i = 0; i < OutHitActors.Num(); i++) {
		AActor* HitActor = OutHitActors[i].GetActor();
		
		if(HitActor){
			UE_LOG(LogTemp, Warning, TEXT("we hit an actor with name %s"), *HitActor->GetActorNameOrLabel());
			UActorComponent * ActorComponent  =  HitActor->GetComponentByClass(UDestructibleComponent::StaticClass());
			if(ActorComponent){
				UE_LOG(LogTemp, Warning, TEXT("we in here with the actor component breh %s"), *HitActor->GetActorNameOrLabel());
			}
		}
	}
}
