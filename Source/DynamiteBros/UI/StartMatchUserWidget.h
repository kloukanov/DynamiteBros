#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StartMatchUserWidget.generated.h"

UCLASS()
class DYNAMITEBROS_API UStartMatchUserWidget : public UUserWidget
{
	GENERATED_BODY()
	

private:

	UPROPERTY(EditAnywhere, Category = Time, meta = (AllowPrivateAccess = "true"))
	float StartDelay = 3.f;

	float Countdown;

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget))
	class UTextBlock* CountdownText;

	virtual void NativeConstruct() override;

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
};
