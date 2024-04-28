#include "Dynamite.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"

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
	
}

void ADynamite::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

