#include "Obstacle.h"
#include "Components/BoxComponent.h"

AObstacle::AObstacle()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComponent;

	ObstacleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Obstacle Mesh"));
	ObstacleMesh->SetupAttachment(BoxComponent);

}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

void AObstacle::HandleDestruction() {
	if(IsDestructible){
		Destroy();
	}
}

void AObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

