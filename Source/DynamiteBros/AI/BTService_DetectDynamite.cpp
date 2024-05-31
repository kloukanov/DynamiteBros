#include "BTService_DetectDynamite.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../Dynamite.h"

UBTService_DetectDynamite::UBTService_DetectDynamite() {
    NodeName = TEXT("Detect Dynamite");
}

void UBTService_DetectDynamite::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) {
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if(OwnerComp.GetAIOwner() == nullptr){
        return;
    }

    ADynamite* Dynamite = Cast<ADynamite>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

    // early return if dynamite is already set
    if(Dynamite) { 
        return;
    }

    FCollisionShape VisibilitySphere = FCollisionShape::MakeSphere(500.f);
    FVector Start = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();

    // DrawDebugSphere(GetWorld(), Start, 500.f, 10, FColor::Blue);

    FHitResult OutHitResult;
    if(GetWorld()->SweepSingleByChannel(OutHitResult, Start, Start, FQuat::Identity, ECC_GameTraceChannel2, VisibilitySphere)){
        Dynamite = Cast<ADynamite>(OutHitResult.GetActor());
        if(Dynamite){
            UE_LOG(LogTemp, Warning, TEXT("we see a dynamite"));
            OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), Dynamite);
        }
    }
}