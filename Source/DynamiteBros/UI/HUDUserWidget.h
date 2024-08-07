#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDUserWidget.generated.h"

UCLASS()
class DYNAMITEBROS_API UHUDUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    TArray<class UImage*> ImageArray;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
    TArray<class AActor*> ActorArray;

	virtual void NativeConstruct() override;

	UFUNCTION(Blueprintcallable)
	void MarkImageAsDead(class APlayableCharacter* DeadPlayer);

	UFUNCTION(Blueprintcallable)
	void ShowAllPlayerIcons();
	
};
