#include "BTTask_DropDynamite.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "../PlayableCharacter.h"

UBTTask_DropDynamite::UBTTask_DropDynamite() {
    NodeName = TEXT("Drop Dynamite");
}

EBTNodeResult::Type UBTTask_DropDynamite::ExecuteTask(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) {
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if(OwnerComp.GetAIOwner() == nullptr){
        return EBTNodeResult::Failed;
    }
    
    APlayableCharacter *PlayableCharacter = Cast<APlayableCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if(PlayableCharacter == nullptr){
        return EBTNodeResult::Failed;
    }

    PlayableCharacter->Drop();
    OwnerComp.GetBlackboardComponent()->ClearValue(TEXT("DropDynamite"));

    return EBTNodeResult::Succeeded;
}