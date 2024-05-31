#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "../Dynamite.h"

void AEnemyAIController::BeginPlay() {
    Super::BeginPlay();

    APawn* AIPawn = GetPawn();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(AIBehavior){
        RunBehaviorTree(AIBehavior);

        if(AIPawn && PlayerPawn){
            GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
            TargetLocation = GetPawn()->GetActorLocation();
            GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), TargetLocation);
            GetBlackboardComponent()->SetValueAsBool(TEXT("IsAIStuck"), IsAIStuck);
        }
    }
}

// probably need to put this into its own BTService later
void AEnemyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    ADynamite* Dynamite = Cast<ADynamite>(GetBlackboardComponent()->GetValueAsObject(TEXT("Dynamite")));

    // early return if dynamite is already set
    if(Dynamite) { 
        return;
    }

    FCollisionShape VisibilitySphere = FCollisionShape::MakeSphere(500.f);
    FVector Start = GetPawn()->GetActorLocation();

    DrawDebugSphere(GetWorld(), Start, 500.f, 10, FColor::Blue);

    FHitResult OutHitResult;
    if(GetWorld()->SweepSingleByChannel(OutHitResult, Start, Start, FQuat::Identity, ECC_GameTraceChannel2, VisibilitySphere)){
        Dynamite = Cast<ADynamite>(OutHitResult.GetActor());
        if(Dynamite){
            UE_LOG(LogTemp, Warning, TEXT("we see a dynamite"));
            GetBlackboardComponent()->SetValueAsObject(TEXT("Dynamite"), Dynamite);
        }
    }
}