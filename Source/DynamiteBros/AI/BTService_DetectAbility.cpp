#include "BTService_DetectAbility.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "../Abilities/AbilityBase.h"

UBTService_DetectAbility::UBTService_DetectAbility() {
    NodeName = TEXT("Detect Ability"); 
}

void UBTService_DetectAbility::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) {
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if(OwnerComp.GetAIOwner() == nullptr){
        return;
    }

    AAbilityBase* Ability = Cast<AAbilityBase>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(GetSelectedBlackboardKey()));

    if(Ability) { 
        return;
    }

    FCollisionShape VisibilitySphere = FCollisionShape::MakeSphere(500.f);
    FVector Start = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();

    FHitResult OutHitResult;
    if(GetWorld()->SweepSingleByChannel(OutHitResult, Start, Start, FQuat::Identity, ECC_GameTraceChannel2, VisibilitySphere)){
        UE_LOG(LogTemp, Warning, TEXT("we see %s"), *OutHitResult.GetActor()->GetActorNameOrLabel());
        Ability = Cast<AAbilityBase>(OutHitResult.GetActor());
        if(Ability){
            UE_LOG(LogTemp, Warning, TEXT("we see an ability"));
            OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), Ability);
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("AbilityLocation"), Ability->GetActorLocation());
        }
    }
}