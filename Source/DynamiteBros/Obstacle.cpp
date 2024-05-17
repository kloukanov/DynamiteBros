#include "Obstacle.h"
#include "Components/BoxComponent.h"
#include "Abilities/AbilityFactory.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComponent;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obstacle Mesh"));
	ObstacleMesh->SetupAttachment(BoxComponent);

	AbilitySpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	AbilitySpawnPoint->SetupAttachment(RootComponent);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObstacle::HandleDestruction() {
	if(IsDestructible){
		SpawnAbility();
		Destroy();
	}
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AObstacle::SpawnAbility() {

	int Probability = FMath::RandRange(1, SpawnProbability);

	if(Probability == 1) {
		FVector SpawnLocation = AbilitySpawnPoint->GetComponentLocation();
		UAbilityFactory* Factory = NewObject<UAbilityFactory>(GetWorld(), AbilityFactoryClass);
		Factory->CreateRandomAbility(GetWorld(), SpawnLocation, FRotator::ZeroRotator);
	}
}