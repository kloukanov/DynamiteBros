#include "EnemyAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"

void AEnemyAIController::BeginPlay() {
    Super::BeginPlay();

    APawn* AIPawn = GetPawn();
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if(AIBehavior){
        RunBehaviorTree(AIBehavior);

        if(AIPawn && PlayerPawn){
            GetBlackboardComponent()->SetValueAsObject(TEXT("Player"), PlayerPawn);
        }
    
    }

}