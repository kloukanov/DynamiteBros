#include "AbilityFactory.h"
#include "Engine/World.h"
#include "AbilityBase.h"
#include "DynamiteCountAbility.h"
#include "ExplosionMultiplierAbility.h"
#include "SpeedAbility.h"


UAbilityFactory::UAbilityFactory(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer){

}

AAbilityBase* UAbilityFactory::CreateRandomAbility(UWorld* World, FVector Location, FRotator Rotation) {

    if(AbilityClasses.Num() > 0) {
        int Index = FMath::RandRange(0, AbilityClasses.Num() - 1);
        return World->SpawnActor<AAbilityBase>(AbilityClasses[Index], Location, Rotation);
    }

    UE_LOG(LogTemp, Warning, TEXT("AbilityClasses length is 0"));
    return nullptr;
}