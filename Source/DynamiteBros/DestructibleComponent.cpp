#include "DestructibleComponent.h"


UDestructibleComponent::UDestructibleComponent()
{

	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UDestructibleComponent::BeginPlay()
{
	Super::BeginPlay();


}


// Called every frame
void UDestructibleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

