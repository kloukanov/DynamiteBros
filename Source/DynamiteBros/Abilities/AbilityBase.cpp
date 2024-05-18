#include "AbilityBase.h"
#include "Components/BoxComponent.h"
#include "../PlayableCharacter.h"

AAbilityBase::AAbilityBase()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Component"));
	RootComponent = BoxComponent;

	AbilityMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Ability Mesh"));
	AbilityMesh->SetupAttachment(BoxComponent);
}

void AAbilityBase::BeginPlay() {
	Super::BeginPlay();

	if(BoxComponent)
	{
		BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &AAbilityBase::OnSphereBeginOverlap);
	}

}

void AAbilityBase::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if(AbilityMesh) {
		FRotator Rotation = AbilityMesh->GetComponentRotation() + FRotator(0, 90 * DeltaTime, 0);
		AbilityMesh->SetRelativeRotation(Rotation);
	}

}

void AAbilityBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("we collided with an actor with name %s"), *OtherActor->GetActorNameOrLabel());
	APlayableCharacter* Player = Cast<APlayableCharacter>(OtherActor);
	if(Player){
		AddAbilityToPlayer(*Player);
		BoxComponent->OnComponentBeginOverlap.RemoveAll(this);
	}
}

void AAbilityBase::HandleDestruction() {
	Destroy();
}

