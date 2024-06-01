#include "BTService_UpdateDropDynamite.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_UpdateDropDynamite::UBTService_UpdateDropDynamite(){
    NodeName = TEXT("Update Drop Dynamite");

    NextDrop = FMath::RandRange(MIN_DROP_TIME, MAX_DROP_TIME);
}

void UBTService_UpdateDropDynamite::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) {

    UE_LOG(LogTemp, Warning, TEXT("next drop is %f, count is %f"), NextDrop, CurrentCount);

    if(CurrentCount >= NextDrop){
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), true);
        CurrentCount = 1.f;
        NextDrop = FMath::RandRange(MIN_DROP_TIME, MAX_DROP_TIME);
    }else{
        CurrentCount = CurrentCount + (CurrentCount * DeltaSeconds);
    }
}
