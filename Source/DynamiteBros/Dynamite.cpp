#include "Dynamite.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"

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

void ADynamite::Explode() {

	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + FVector(500, 0, 0);

	FVector BoxSize(80, 80, 30);
	FHitResult Hit;

	TArray<AActor *, FDefaultAllocator> IgnoreActors;

	// will probably use BoxTraceMulti later to get all hit objects
	bool bHitSomething = UKismetSystemLibrary::BoxTraceSingle
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
		Hit, 
		true
	);

	if(bHitSomething){
		AActor* HitActor = Hit.GetActor();
		
		if(HitActor){
			UE_LOG(LogTemp, Warning, TEXT("we hit an actor with name %s"), *HitActor->GetActorNameOrLabel());
		}
	}

}
