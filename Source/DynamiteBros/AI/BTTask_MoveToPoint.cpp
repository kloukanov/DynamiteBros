#include "BTTask_MoveToPoint.h"
#include "BehaviorTree/BlackboardComponent.h"


UBTTask_MoveToPoint::UBTTask_MoveToPoint() {
    NodeName = TEXT("Move To Point");
}

EBTNodeResult::Type UBTTask_MoveToPoint::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) {

    EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

    if(Result == EBTNodeResult::Failed || Result == EBTNodeResult::Aborted){
        UE_LOG(LogTemp, Warning, TEXT("task result is:Failed or Aborted"));
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(TEXT("IsAIStuck"), true);
    }

    return Result;

}