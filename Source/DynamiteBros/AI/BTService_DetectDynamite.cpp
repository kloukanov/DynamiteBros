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
    FVector Start = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();

    // early return if dynamite is already set
    if(Dynamite) { 
        SetRunAwayDirection(OwnerComp, Start, Dynamite);
        return;
    }

    FCollisionShape VisibilitySphere = FCollisionShape::MakeSphere(600.f);

    FHitResult OutHitResult;
    if(GetWorld()->SweepSingleByChannel(OutHitResult, Start, Start, FQuat::Identity, ECC_GameTraceChannel2, VisibilitySphere)){
        Dynamite = Cast<ADynamite>(OutHitResult.GetActor());
        if(Dynamite){
            UE_LOG(LogTemp, Warning, TEXT("we see a dynamite"));
            OwnerComp.GetBlackboardComponent()->SetValueAsObject(GetSelectedBlackboardKey(), Dynamite);
            SetRunAwayDirection(OwnerComp, Start, Dynamite);
        }else {
            OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
        }
    }else {
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }
}

void UBTService_DetectDynamite::SetRunAwayDirection(UBehaviorTreeComponent &OwnerComp, FVector Location, ADynamite* Dynamite) {
    FVector LocationOfDynamte = Dynamite->GetActorLocation();
    float DirectionX = FMath::RandRange(MIN_RUN_AWAY_RANGE, MAX_RUN_AWAY_RANGE);
    float DirectionY = FMath::RandRange(MIN_RUN_AWAY_RANGE, MAX_RUN_AWAY_RANGE);
    FVector RunAwayLocation = (Location - LocationOfDynamte) * FVector(DirectionX, DirectionY, 0.f);

    // DrawDebugSphere(GetWorld(), (Location + RunAwayLocation), 50.f, 8, FColor::Red, true, 5.f);
    OwnerComp.GetBlackboardComponent()->SetValueAsVector(TEXT("TargetLocation"), (Location + RunAwayLocation));
}