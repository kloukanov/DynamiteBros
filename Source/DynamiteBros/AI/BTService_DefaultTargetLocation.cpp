#include "BTService_DefaultTargetLocation.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"

UBTService_DefaultTargetLocation::UBTService_DefaultTargetLocation() {
    NodeName = TEXT("Set Default Target Location");
}

void UBTService_DefaultTargetLocation::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) {

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    if(OwnerComp.GetAIOwner() == nullptr){
        return;
    }

    if(
        OwnerComp.GetBlackboardComponent()->GetValueAsBool(TEXT("IsAIStuck")) 
        || 
        OwnerComp.GetAIOwner()->GetPawn()->GetVelocity() == FVector::ZeroVector
        ||
        IsTargetLocationReached(
            OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation(), 
            OwnerComp.GetBlackboardComponent()->GetValueAsVector(GetSelectedBlackboardKey()), 50.f)
        ){
        
        float RandomX = FMath::RandRange(MIN_X, MAX_X);
        float RandomY = FMath::RandRange(MIN_Y, MAX_Y);

        FVector TargetLocation(RandomX, RandomY, 50.f);
        DrawDebugSphere(GetWorld(), TargetLocation, 50.f, 8, FColor::Green, true, 5.f);

        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsAIStuck"), false);

        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), TargetLocation);
    }
}

bool UBTService_DefaultTargetLocation::IsTargetLocationReached(FVector OwnerLocation, FVector TargetLocation, float MarginOfError) const {

    return(
        ((TargetLocation.X - OwnerLocation.X) >= -MarginOfError && (TargetLocation.X - OwnerLocation.X) <= MarginOfError)
        &&
        ((TargetLocation.Y - OwnerLocation.Y) >= -MarginOfError && (TargetLocation.Y - OwnerLocation.Y) <= MarginOfError)
    );
}