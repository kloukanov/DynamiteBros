#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "AbilityFactory.generated.h"

UCLASS(Blueprintable)
class DYNAMITEBROS_API UAbilityFactory : public UObject
{

	GENERATED_BODY()

	// ref to BP Ability classes
	UPROPERTY(EditDefaultsOnly, Category = Abilities)
	TArray<TSubclassOf<class AAbilityBase>> AbilityClasses;

public:

	UAbilityFactory(const FObjectInitializer& ObjectInitializer);

	class AAbilityBase* CreateRandomAbility(UWorld* World, FVector Location, FRotator Rotation);

};
