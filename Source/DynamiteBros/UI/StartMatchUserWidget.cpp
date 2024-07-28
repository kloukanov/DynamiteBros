#include "StartMatchUserWidget.h"
#include "Math/UnrealMathUtility.h"
#include "Components/TextBlock.h"
#include "../DynamiteBrosGameMode.h"


void UStartMatchUserWidget::NativeConstruct() {
    Super::NativeConstruct();

    Countdown = StartDelay;

}

void UStartMatchUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime) {
    Super::NativeTick(MyGeometry, InDeltaTime);

    if(Countdown <= 0){
        ADynamiteBrosGameMode* GameMode = Cast<ADynamiteBrosGameMode>(GetWorld()->GetAuthGameMode());
        GameMode->EnableInputForPlayers(true);
        this->RemoveFromParent();
    }

    Countdown = Countdown - InDeltaTime;
    int CountdownTextNumber = FMath::CeilToInt(Countdown);

    UE_LOG(LogTemp, Warning, TEXT("timer: %d"), CountdownTextNumber);
    CountdownText->SetText(FText::AsNumber(CountdownTextNumber));
}