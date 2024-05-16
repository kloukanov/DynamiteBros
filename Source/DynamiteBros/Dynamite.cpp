#include "Dynamite.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Obstacle.h"
#include "DrawDebugHelpers.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"
#include "PlayableCharacter.h"

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

	APlayableCharacter* PlayerCharacter = Cast<APlayableCharacter>(GetOwner());

	if(PlayerCharacter){
		DoExplosion(StartLocation, StartLocation + FVector(PlayerCharacter->GetExplosionPower(), 0, 0), ExplosionLineTraceOffsetY, TotalHitActors); // north
		DoExplosion(StartLocation, StartLocation - FVector(PlayerCharacter->GetExplosionPower(), 0, 0), -(ExplosionLineTraceOffsetY), TotalHitActors); // south
		DoExplosion(StartLocation, StartLocation + FVector(0, PlayerCharacter->GetExplosionPower(), 0), ExplosionLineTraceOffsetX, TotalHitActors); // east
		DoExplosion(StartLocation, StartLocation - FVector(0, PlayerCharacter->GetExplosionPower(), 0), -(ExplosionLineTraceOffsetX), TotalHitActors); // west
	}

	if(TotalHitActors.Num() > 0){
		HandleExplosionCollision(TotalHitActors);
	}

	// before we destroy, add a dynamite back to the DynamiteCount of player
	if(PlayerCharacter){
		PlayerCharacter->AddDynamite();
	}

	Destroy();
}

// this function does 3 ray casts in provided direction
// another way to do this would probably be to create a FCollisionShape and then use SweepMultipleByChannel() with the shape? 
void ADynamite::DoExplosion(FVector StartLocation, FVector EndLocation, FVector Offset, TArray<FHitResult> &OutHitActors) {
	
	TArray<FHitResult> AllActors;

	FVector TempOffset = Offset;

	FVector ExplosionDirection = ((StartLocation + TempOffset) - (EndLocation + TempOffset)).GetSafeNormal();
	
	SpawnExplosionEffect(ExplosionDirection.Rotation());

	for(int i = 0; i < 3; i++) {
		TArray<FHitResult> TempHitActors;

		GetWorld()->LineTraceMultiByChannel(TempHitActors, StartLocation + TempOffset, EndLocation + TempOffset, ECollisionChannel::ECC_GameTraceChannel1);
		if(ShowTraceLines){
			DrawDebugLine(GetWorld(), StartLocation + TempOffset, EndLocation + TempOffset, FColor::Red, true, 5);
		}

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
	APlayableCharacter* PlayerCharacter = Cast<APlayableCharacter>(GetOwner());

	if(ExplosionEffect && PlayerCharacter) {
		UNiagaraComponent* NiagaraComp = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ExplosionEffect, GetActorLocation(), Rotation);
		NiagaraComp->SetVariableLinearColor(FName("Color"), PlayerCharacter->GetExplosionColor());
		NiagaraComp->SetVariableFloat(FName("Velocity_Speed"), PlayerCharacter->GetExplosionPower() * 4);
	}
}