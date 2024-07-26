#include "HUDUserWidget.h"
#include "../DynamiteBrosGameMode.h"
#include "../PlayableCharacter.h"
#include "Components/Image.h"

void UHUDUserWidget::NativeConstruct() {
    Super::NativeConstruct();

    ADynamiteBrosGameMode* GameMode = Cast<ADynamiteBrosGameMode>(GetWorld()->GetAuthGameMode());

    if(GameMode){
        GameMode->OnActorDeath.AddDynamic(this, &UHUDUserWidget::MarkImageAsDead);
    }
}

void UHUDUserWidget::ShowAllPlayerIcons() {
    for(int i = 0; i < ActorArray.Num(); i++){
        APlayableCharacter* Player = Cast<APlayableCharacter>(ActorArray[i]);
        if(Player){
            ImageArray[i]->SetBrushFromTexture(Player->GetPlayerIcon());
        }
    }
}

void UHUDUserWidget::MarkImageAsDead(class APlayableCharacter* DeadPlayer) {

    for(int i = 0; i < ActorArray.Num(); i++){

        APlayableCharacter* Player = Cast<APlayableCharacter>(ActorArray[i]);

        if(Player && Player->GetIsDead()){
            FSlateBrush Brush = ImageArray[i]->GetBrush();
            Brush.TintColor = FLinearColor(1,1,1,0.3f);
            ImageArray[i]->SetBrush(Brush);
        }
    }
}