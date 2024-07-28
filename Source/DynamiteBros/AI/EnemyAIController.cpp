#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "BrainComponent.h"

void AEnemyAIController::BeginPlay() {
    Super::BeginPlay();

    APawn* AIPawn = GetPawn();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(AIBehavior){
        if(AIPawn && PlayerPawn){
            GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
            TargetLocation = GetPawn()->GetActorLocation();
            GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), TargetLocation);
            GetBlackboardComponent()->SetValueAsBool(TEXT("IsAIStuck"), IsAIStuck);
        }
    }
}

void AEnemyAIController::EnableAI(){
    RunBehaviorTree(AIBehavior);
}

void AEnemyAIController::DisableAI(){
    GetBrainComponent()->StopLogic(TEXT("Disabled during countdown"));;
}